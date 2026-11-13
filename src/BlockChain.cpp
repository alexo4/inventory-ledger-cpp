//
// Created by Alexander O'Carroll on 14/03/2024.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "../headers/BlockChain.h"
#include "../library/sha256.h"
#include "../headers/Request.h"
#include "../headers/Receive.h"
#include "../headers/Transport.h"
#include <ctime>

using namespace std;

BlockChain:: BlockChain() {
    size = 0;
    headBlock = nullptr;
}
void BlockChain:: addBlock(Block *block){

    if(headBlock == nullptr){

        headBlock = block;
        block->setCurrentBlockHash(generateHash(block));
        block->setPrevBlockHash(block->getCurrentBlockHash());
        block->setBlockNumber(1);
        size = 1;
    }
    else{

        Block *currentBlock = headBlock;
        while(currentBlock->getNextBlock() != nullptr){
            currentBlock = currentBlock->getNextBlock();
        }

        block->setPrevBlockHash(currentBlock->getCurrentBlockHash());
        block->setPrevBlock(currentBlock);
        block->setCurrentBlockHash(generateHash(block));
        block->setBlockNumber(currentBlock->getBlockNumber()+1);
        currentBlock->setNextBlock(block);
        size++;
    }
}

void BlockChain::insertBlock(int pos, Block *block) {

    Block *currentBlock = headBlock;

    while(currentBlock->getNextBlock() != nullptr){
        if(currentBlock->getBlockNumber() == pos){
            break;
        }
        currentBlock = currentBlock->getNextBlock();
    }

    block->setPrevBlockHash(currentBlock->getCurrentBlockHash());
    block->setPrevBlock(currentBlock);
    block->setCurrentBlockHash(generateHash(block));
    block->setBlockNumber(currentBlock->getBlockNumber()+1);
    block->setNextBlock(currentBlock->getNextBlock());
    currentBlock->getNextBlock()->setPrevBlock(block);
    currentBlock->setNextBlock(block);

    size++;

    int check = checkBlockChain();
    if(check > 0){
        fixBlockChain(check);
    }
}

string BlockChain:: generateHash(Block *block){
    return block->getPrevBlock() != nullptr ? sha256(block->getInformation()->toString() + block->getPrevBlockHash()) :
    sha256(block->getInformation()->toString());
}

void BlockChain:: displayBlockChain() {

    if(size == 0){
        cout << "Blockchain empty\n";
        return;
    }
    Block *currentBlock = headBlock;
    cout << "\n";
    while(currentBlock->getNextBlock() != nullptr){
        currentBlock->printBlock();
        cout << "\n";
        currentBlock = currentBlock->getNextBlock();
    }
    currentBlock->printBlock();
    cout << "\n";
}

void BlockChain::fixBlockChain(int pos) {

    Block *currentBlock = headBlock;
    int i = 1;
    while(currentBlock->getNextBlock() != nullptr){

        if(i >= pos){
            string hash = generateHash(currentBlock);
            currentBlock->setCurrentBlockHash(hash);
            currentBlock->getNextBlock()->setPrevBlockHash(hash);
            currentBlock->setBlockNumber(i);
        }
        i++;
        currentBlock = currentBlock->getNextBlock();
    }
    currentBlock->setCurrentBlockHash(generateHash(currentBlock));
    currentBlock->setBlockNumber(i);
}

int BlockChain::checkBlockChain() {

    Block *currentBlock = headBlock;
    int i = 1;
    while(currentBlock->getNextBlock() != nullptr){

        if(generateHash(currentBlock) != currentBlock->getNextBlock()->getPrevBlockHash()){
            return i;
        }
        i++;
        currentBlock = currentBlock->getNextBlock();
    }
    return -1;
}

int BlockChain:: getSize(){
    return size;
}

vector<string> BlockChain::getOrderIDs() {

    if(size == 0){
        return {};
    }
    vector<string> orderIDs;

    Block *currentBlock = headBlock;
    while(currentBlock->getNextBlock() != nullptr){

        if(dynamic_cast<Request*>(currentBlock->getInformation()) != nullptr){
            orderIDs.push_back(dynamic_cast<Request*>(currentBlock->getInformation())->getOrderID());
        }

        currentBlock = currentBlock->getNextBlock();
    }

    if(size > 0 && dynamic_cast<Request*>(currentBlock->getInformation()) != nullptr){
        orderIDs.push_back(dynamic_cast<Request*>(currentBlock->getInformation())->getOrderID());
    }
    return orderIDs;
}

vector<vector<Block *>> BlockChain::groupOrders() {

    if(size == 0){
        return {};
    }

    vector<vector<Block *>> orders;

    Block *currentBlock = headBlock;
    while(currentBlock != nullptr){

        string currentOrderID;
        if(dynamic_cast<Order*>(currentBlock->getInformation()) != nullptr){
            currentOrderID = dynamic_cast<Order*>(currentBlock->getInformation())->getOrderID();
        }else{
            currentBlock = currentBlock->getNextBlock();
            continue;
        }

        bool alreadyIn = false;
        for(vector<Block*> &order : orders){
            if(dynamic_cast<Order*>(order[0]->getInformation())->getOrderID() == currentOrderID){
                order.push_back(currentBlock);
                alreadyIn = true;
                break;
            }
        }

        if(!alreadyIn){
            vector<Block *> order;
            order.push_back(currentBlock);
            orders.push_back(order);
        }
        currentBlock = currentBlock->getNextBlock();
    }

    return orders;
}

vector<string> BlockChain::getUncompletedOrderIDs() {

    if(size == 0){
        return {};
    }
    vector<string> orderIDs = getOrderIDs();

    Block *currentBlock = headBlock;
    while(currentBlock != nullptr){

        if(dynamic_cast<Receive*>(currentBlock->getInformation()) != nullptr){
            orderIDs.erase(remove(orderIDs.begin(), orderIDs.end(),
                                  dynamic_cast<Receive*>(currentBlock->getInformation())->getOrderID()),
                           orderIDs.end());
        }

        currentBlock = currentBlock->getNextBlock();
    }

    return orderIDs;
}

vector<BlockChain::good> BlockChain::getStockLevels() {

    vector<good> goods;
    vector<vector<Block *>> orders = groupOrders();

    for(vector<Block*> &order : orders){
        int completion = 1;
        int quantity = 0;
        string goodName;

        for(Block* &block : order){

            if(dynamic_cast<Receive*>(block->getInformation()) != nullptr){
                completion = 3;
                quantity = block->getInformation()->getQuantity();
            }else if(dynamic_cast<Transport*>(block->getInformation()) != nullptr && completion < 2){
                completion = 2;
                quantity = block->getInformation()->getQuantity();
            }else if(dynamic_cast<Request*>(block->getInformation()) != nullptr){
                goodName = dynamic_cast<Request*>(block->getInformation())->getGoodName();
                if(completion == 1){
                    quantity = block->getInformation()->getQuantity();
                }
            }
        }

        int i = 0;
        for(good &good : goods){
            if(good.goodName == goodName){
                break;
            }
            i++;
        }

        if(i < goods.size()){
            goods[i].quantity[completion-1] += quantity;
        }else{
            good tempGood;
            tempGood.goodName = goodName;
            tempGood.quantity[completion-1] += quantity;
            goods.push_back(tempGood);
        }
    }

    vector<Block*> sales = getSales();
    for(Block* &sale : sales){
        for(good &good : goods){
            if(good.goodName == dynamic_cast<Sale*>(sale->getInformation())->getGoodName()){
                good.quantity[3] += dynamic_cast<Sale*>(sale->getInformation())->getQuantity();
            }
        }
    }
    return goods;
}

vector<Block*> BlockChain:: getSales(){

    vector<Block*> sales;
    Block *currentBlock = headBlock;
    while(currentBlock != nullptr){
        if(dynamic_cast<Sale*>(currentBlock->getInformation()) != nullptr){
            sales.push_back(currentBlock);
        }
        currentBlock = currentBlock->getNextBlock();
    }
    return sales;
}

void BlockChain:: displayStockLevels(){

    vector<BlockChain::good> goods = getStockLevels();

    cout << "|Good name   |In Stock    |In Transit  |Ordered     |\n";

    for(BlockChain::good good : goods){

        cout << "|" + good.goodName;
        if(good.goodName.length() < 12){
            for(int i = 0; i < 12 - good.goodName.length(); i++){
                cout << " ";
            }
        }
        cout << "|";
        printNumber(good.quantity[2] - good.quantity[3], 12);
        cout << "|";
        printNumber(good.quantity[1], 12);
        cout << "|";
        printNumber(good.quantity[0], 12);
        cout << "|\n";
    }
}

void BlockChain:: printNumber(int num, int size){

    int spaces = size - to_string(num).length();

    for(int i = 0; i < spaces/2; i++){
        cout << " ";
    }
    if(spaces%2 == 1){
        cout << " ";
    }
    cout << num;
    for(int i = 0; i < spaces/2; i++){
        cout << " ";
    }
}

void BlockChain::displaySales() {

    vector<Block*> sales = getSales();
    if(sales.empty()){
        cout << "Make a sale first\n";
        return;
    }

    while(!sales.empty()){

        Block* saleBlock = sales[0];
        sales.erase(sales.begin());
        Sale* saleInfo = dynamic_cast<Sale*>(saleBlock->getInformation());
        cout << " " << saleInfo->getGoodName() <<"\n";
        printSale(saleBlock, saleInfo);
        int total = saleInfo->getRevenue();

        vector<int> positions;
        int i = 0;
        for(Block* &sale : sales){

            if(dynamic_cast<Sale*>(sale->getInformation())->getGoodName() == saleInfo->getGoodName()){
                positions.push_back(i);
                Sale* saleInfo = dynamic_cast<Sale*>(sale->getInformation());
                total += saleInfo->getRevenue();
                printSale(sale, saleInfo);
            }
            i++;
        }

        int count = 0;
        for(int &pos : positions){
            sales.erase(sales.begin()+pos-count);
            count++;
        }

        cout << "Total - RM" << total << "\n";
    }
}

void BlockChain::printSale(Block* saleBlock, Sale* saleInfo){

    time_t time = saleBlock->getTimestamp();
    cout << " - RM" << saleInfo->getRevenue() << "  Quantity: "<< saleInfo->getQuantity() << "  " << ctime(&time)<< "";

}

void BlockChain::displayOrders() {

    vector<vector<Block *>> orders = groupOrders();

    for(vector<Block*> &order : orders) {
        int completion = 1;
        time_t transitTime;
        int estTravel;
        cout << "Order: " << dynamic_cast<Order *>(order[0]->getInformation())->getOrderID() << "\n";

        for (Block *&block: order) {

            if (dynamic_cast<Receive *>(block->getInformation()) != nullptr) {
                auto* rec = dynamic_cast<Receive *>(block->getInformation());
                time_t blockTime = block->getTimestamp();
                cout << "-Complete:\n  Quantity: " << rec->getQuantity() << " RM" << rec->getTransactionAmount() <<
                " Type: " << rec->getPaymentType() << "  " << ctime(&blockTime);
                completion = 3;

            } else if (dynamic_cast<Transport *>(block->getInformation()) != nullptr && completion < 2) {
                auto* tran = dynamic_cast<Transport *>(block->getInformation());
                time_t blockTime = block->getTimestamp();
                transitTime = (time(0) - blockTime)/86400;
                estTravel = tran->getEstimatedTravelTime();
                cout << "-Transport:\n  Quantity: " << tran->getQuantity() << " Name: " << tran->getTransporterName() <<
                " Type: " << tran->getTransportType() << " Origin: " << tran->getOrigin() << " Destination: " <<
                tran->getDestination() << " Estimated transit time: " << tran->getEstimatedTravelTime() << "  " <<
                ctime(&blockTime);
                completion = 2;
            } else {
                auto* req = dynamic_cast<Request *>(block->getInformation());
                time_t blockTime = block->getTimestamp();
                cout << "-Request:\n  Quantity: " << req->getQuantity() << " Supplier name: " << req->getSupplierName()
                << " Location: " << req->getLocation() << "  Good name: " << req->getGoodName() << "  " << ctime(&blockTime);
            }
        }
        if(completion == 2){
            cout << "  Estimated days to arrival: " << to_string(estTravel - transitTime) << "\n";
        }
    }
}

void BlockChain::moveBlock(int currentPos, int newPos) {

    Block *currentBlock = headBlock;

    while(currentBlock->getNextBlock() != nullptr){
        if(currentBlock->getBlockNumber() == currentPos){
            break;
        }
        currentBlock = currentBlock->getNextBlock();
    }

    if(currentPos == 1){
        headBlock = currentBlock->getNextBlock();
        headBlock->setPrevBlock(nullptr);
    }else if(currentPos == size){
        currentBlock->getPrevBlock()->setNextBlock(nullptr);
    }else{
        currentBlock->getNextBlock()->setPrevBlock(currentBlock->getPrevBlock());
        currentBlock->getPrevBlock()->setNextBlock(currentBlock->getNextBlock());
    }


    Block *preBlock = headBlock;

    while(preBlock->getNextBlock() != nullptr){
        if(preBlock->getBlockNumber() == newPos){
            break;
        }
        preBlock = preBlock->getNextBlock();
    }

    if(newPos == 0){
        currentBlock->setNextBlock(headBlock);
        currentBlock->setPrevBlock(nullptr);
        headBlock->setPrevBlock(currentBlock);
        headBlock = currentBlock;
    }else if(newPos == size){
        currentBlock->setNextBlock(nullptr);
        currentBlock->setPrevBlock(preBlock);
        preBlock->setNextBlock(currentBlock);
    }else{
        preBlock->getNextBlock()->setPrevBlock(currentBlock);
        currentBlock->setNextBlock(preBlock->getNextBlock());
        currentBlock->setPrevBlock(preBlock);
        preBlock->setNextBlock(currentBlock);
    }

    int check = checkBlockChain();
    if(check > 0){
        fixBlockChain(check);
    }
}



