#include <iostream>
#include <algorithm>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "../headers/Request.h"
#include "../headers/Transport.h"
#include "../headers/Receive.h"
#include "../headers/Block.h"
#include "../headers/Sale.h"
#include "../library/sha256.h"
#include "../headers/BlockChain.h"
#include <ctime>
#include <regex>

using namespace std;

int printMenuOptions();
void menuResponse(int);
void displayBlockChain();
void addToBlockChain();
void insertIntoBlockChain();
void displayOrders();
string getOrderID();
BlockChain::good getGoodName();
Information* selectTransactionType();
Request* createRequestBlock();
Transport *createTransportBlock();
Receive *createReceiveBlock();
Sale* createSaleBlock();
time_t askTime();
string generateRandomID(int);
int getQuantity(string);
void displayStockLevels();
void displaySales();
void moveBlock();


BlockChain *bc;



int main() {

    bc = new BlockChain();

    cout << "would you like to load blocks (yes): ";
    string choice;
    cin >> choice;
    //if (choice == "yes"){
        Request req1 = *new Request(100, "1234567890", "apple co", "apple farm", "apple");
        Request req2 = *new Request(200, "abcdefghij", "pear co", "pear farm", "pear");
        Request req3 = *new Request(250, "klmnopqrst", "orange co", "orange farm", "orange");
        Request req4 = *new Request(150, "0987654321", "durian co", "durian farm", "durian");
        Request req5 = *new Request(100, "1122334455", "durian co", "durian farm", "durian");
        Request req6 = *new Request(150, "0099887766", "apple co", "apple farm", "apple");
        Request req7 = *new Request(50, "6677554488", "orange co", "orange farm", "orange");
        Transport tran1 = *new Transport(100, "1234567890", "fedex", "van", "apple farm", "KL warehouse", 5);
        Transport tran2 = *new Transport(200, "abcdefghij", "fedex", "van", "pear farm", "KL warehouse", 7);
        Transport tran3 = *new Transport(250, "klmnopqrst", "DHL", "plane", "orange farm", "penang warehouse", 12);
        Receive rec1 = *new Receive(100, "1234567890", 2500, "cash");
        Receive rec2 = *new Receive(200, "abcdefghij", 6000, "card");
        Sale sale1 = *new Sale(30, "apple", 1200, "card");
        Sale sale2 = *new Sale(10, "apple", 500, "cash");
        Sale sale3 = *new Sale(80, "pear", 2500, "cash");
        Sale sale4 = *new Sale(20, "pear", 700, "cash");

        time_t blockTime =  time(0);

        Block *block1 = new Block(&req1, blockTime);
        auto *block2 = new Block(&req2, blockTime);
        auto *block3 = new Block(&req3, blockTime);
        auto *block4 = new Block(&req4, blockTime);
        auto *block5 = new Block(&tran1, blockTime);
        auto *block6 = new Block(&tran2, blockTime);
        auto *block7 = new Block(&tran3, blockTime);
        auto *block8 = new Block(&rec1, blockTime);
        auto *block9 = new Block(&rec2, blockTime);
        auto *block10 = new Block(&sale1, blockTime);
        auto *block11 = new Block(&sale2, blockTime);
        auto *block12 = new Block(&sale3, blockTime);
        auto *block13 = new Block(&sale4, blockTime);
        auto *block14 = new Block(&req5, blockTime);
        auto *block15 = new Block(&req6, blockTime);
        auto *block16 = new Block(&req7, blockTime);

        bc->addBlock(block1);
        bc->addBlock(block2);
        bc->addBlock(block3);
        bc->addBlock(block4);
        bc->addBlock(block5);
        bc->addBlock(block6);
        bc->addBlock(block7);
        bc->addBlock(block8);
        bc->addBlock(block9);
        bc->addBlock(block10);
        bc->addBlock(block11);
        bc->addBlock(block12);
        bc->addBlock(block13);
        bc->addBlock(block14);
        bc->addBlock(block15);
        bc->addBlock(block16);
   // }

    bool loop = true;
    do {

        int choice = printMenuOptions();
        menuResponse(choice);

        cout << "would you like to end (yes): ";
        string end;
        cin >> end;
        if (end == "yes"){
            loop = false;
        }

    }while(loop);

    return 0;
}


int printMenuOptions(){

    bool choiceMade = false;
    int choice;
    do{
        cout << "(1)   Display blockchain\n"
                "(2)   Display orders\n"
                "(3)   Display stock levels\n"
                "(4)   Display sales\n"
                "(5)   Add to blockchain\n"
                "(6)   Insert into blockchain\n"
                "(7)   Move block\n"
                "What would you like to do?: ";

        cin >> choice;
        if(0 < choice && choice < 8){
            choiceMade = true;
        }else{
            cout << "Please choose an option displayed\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }while(!choiceMade);

    return choice;

}

void menuResponse(int choice){

    switch(choice){
        case 1:
            displayBlockChain();
            break;
        case 2:
            displayOrders();
            break;
        case 3:
            displayStockLevels();
            break;
        case 4:
            displaySales();
            break;
        case 5:
            addToBlockChain();
            break;
        case 6:
            insertIntoBlockChain();
            break;
        case 7:
            moveBlock();
            break;
    }

}

void displayBlockChain(){

    bc->displayBlockChain();

}

void displayStockLevels(){
    bc->displayStockLevels();
}

void displayOrders(){
    bc->displayOrders();
}

void displaySales(){

    bc->displaySales();

}

void addToBlockChain(){

    Information *info = selectTransactionType();
    if(info == nullptr){
        return;
    }
    time_t timestamp = askTime();
    bc->addBlock(new Block(info, timestamp));

}

void moveBlock(){

    bc->displayBlockChain();
    if(bc->getSize() == 0){
        return;
    }
    bool choiceMade = false;
    int currentPos;
    int newPos;
    do{
        cout << "Choose a block and the one to move it after (x y): ";

        cin >> currentPos;
        cin >> newPos;
        if(0 < currentPos && 0 <= newPos && currentPos <= bc->getSize() && newPos <= bc->getSize()
        && currentPos != newPos +1 && currentPos != newPos){
            choiceMade = true;
        }else{
            cout << "Please choose valid blocks that change its position\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }while(!choiceMade);

    bc->moveBlock(currentPos, newPos);
}

void insertIntoBlockChain(){

    bc->displayBlockChain();
    if(bc->getSize() == 0){
        return;
    }
    bool choiceMade = false;
    int choice;
    do{
        cout << "What block would you like to insert after: ";

        cin >> choice;
        if(0 < choice && choice <= bc->getSize()){
            choiceMade = true;
        }else{
            cout << "Please choose a valid block\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }while(!choiceMade);

    Information *info = selectTransactionType();
    if(info == nullptr){
        return;
    }
    time_t timestamp = askTime();
    if(choice == bc->getSize()){
        bc->addBlock(new Block(info, timestamp));
    }else{
        bc->insertBlock(choice, new Block(info, timestamp));
    }

}

Information *selectTransactionType(){

    bool choiceMade = false;
    int choice;
    do{
        cout << "(1)   Request\n"
                "(2)   Transport\n"
                "(3)   Receive\n"
                "(4)   Sale\n"
                "What transaction type would you like to create a block for?: ";

        cin >> choice;
        if(0 < choice && choice < 5){
            choiceMade = true;
        }else{
            cout << "Please choose an option displayed\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }while(!choiceMade);

    switch(choice){
        case 1:
            return createRequestBlock();
        case 2:
            return createTransportBlock();
        case 3:
            return createReceiveBlock();
        case 4:
            return createSaleBlock();
    }
    return nullptr;
}

int getQuantity(string message){
    int quantity = -1;
    while(quantity <=0){
        cout << message;
        cin >> quantity;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    return quantity;
}

Request *createRequestBlock(){

    string supplierName;
    cout << "Supplier Name: ";
    cin >> supplierName;

    string location;
    cout << "Location: ";
    cin >> location;

    string goodName;
    cout << "Good Name: ";
    cin >> goodName;

    return new Request(getQuantity("Quantity: "), generateRandomID(10), supplierName, location, goodName);
}

Transport *createTransportBlock(){

    string orderID = getOrderID();
    if(orderID.empty()){
        return nullptr;
    }
    string transporterName;
    cout << "Transporter Name: ";
    cin >> transporterName;

    string transportType;
    cout << "Transport Type: ";
    cin >> transportType;

    string origin;
    cout << "Origin: ";
    cin >> origin;

    string destination;
    cout << "Destination: ";
    cin >> destination;

    int time = -1;
    while(time <=0){
        cout << "Estimated travel time (days): ";
        cin >> time;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return new Transport(getQuantity("Quantity: "), orderID, transporterName, transportType, origin, destination, time);
}

Receive *createReceiveBlock(){

    string orderID = getOrderID();
    if(orderID.empty()){
        return nullptr;
    }

    string paymentType;
    cout << "Payment type: ";
    cin >> paymentType;

    return new Receive(getQuantity("Quantity: "), orderID,
                       getQuantity("Transaction amount: RM"), paymentType);
}

Sale *createSaleBlock(){

    BlockChain::good good = getGoodName();

    int quantity = -1;
    while(quantity <=0 || quantity > (good.quantity[2] - good.quantity[3])){
        cout << "How many sold: ";
        cin >> quantity;
        if(quantity > (good.quantity[2] - good.quantity[3])){
            cout << "Quantity sold cannot be larger than stock\n";
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }


    string paymentType;
    cout << "Payment type: ";
    cin >> paymentType;

    return new Sale(quantity, good.goodName, getQuantity("Transaction amount: RM"), paymentType);

}

string generateRandomID(int length){

    char alphaNum[] = "0123456789"
                      "abcdefghijklmnopqrstuvxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVXYZ";
    bool unique = false;
    string ID;
    ID.reserve(length);
    vector<string> orderIDs = bc->getOrderIDs();

    while(!unique){
        srand((unsigned) time(nullptr));
        for(int i = 0; i < length; i++){
            ID += alphaNum[rand() % strlen(alphaNum)];
        }
        if(count(orderIDs.begin(), orderIDs.end(), ID) == 0){
            unique = true;
        }
    }
    return ID;
}

string getOrderID(){

    vector<string> orderIDs = bc->getUncompletedOrderIDs();
    if(orderIDs.empty()){
        cout << "Create a Request Block first\n";
        return {};
    }
    int i = 0;
    for(string &orderID : orderIDs){
        i++;
        cout << "(" << i << ")   " << orderID << "\n";
    }

    int choice = -1;
    while(choice <=0 || choice > i){
        cout << "Choose an order ID: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return orderIDs[choice-1];
}

BlockChain::good getGoodName(){

    vector<BlockChain::good> goods = bc->getStockLevels();
    if(goods.empty()){
        cout << "Get stock first\n";
        return {};
    }
    int i = 0;
    for(BlockChain::good good : goods){
        if(good.quantity[2] > good.quantity[3]){
            i++;
            cout << "(" << i << ")   " << good.goodName << " " << to_string(good.quantity[2] - good.quantity[3]) <<
            "\n";
        }
    }

    if(i == 0){
        cout << "Get stock first\n";
        return {};
    }

    int choice = -1;
    while(choice <=0 || choice > i){
        cout << "Choose a good: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    i = 0;
    for(BlockChain::good good : goods){
        if(good.quantity[2] > good.quantity[3]){
            i++;
            if(i==choice){
                return good;
            }

        }
    }
    return {};
}

time_t askTime(){

    bool choiceMade = false;
    string choice;
    do{
        cout << "would you like to input time(y/n) (default is current): ";

        cin >> choice;
        if(choice == "y" || choice == "n"){
            choiceMade = true;
        }else{
            cout << "Please choose an option displayed\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }while(!choiceMade);
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    string str;
    time_t timestamp;
    if(choice == "y"){
        bool correctFormat = false;

        do{
            cout << "(dd/mm/yyyy HH:MM): ";
            getline(cin, str);
            regex reg ( R"(([0-2][0-9]|[3][0-1])/([0][0-9]|[1][0-2])/[2][0][0-9][0-9]\s([0-1][0-9]|[2][0-3]):[0-5][0-9])");

            if (regex_match(str, reg)){
                correctFormat = true;
            }
            else {
                cout << "Please input a date and time in the format displayed";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }while(!correctFormat);

        struct tm timestc = {};
        const char *format = "%d/%m/%Y %H:%M";
        const char* timeStr = str.data();
        strptime(timeStr, format, &timestc);
        timestamp = mktime(&timestc);
    }else{
        timestamp = time(0);
    }

    return timestamp;

}

