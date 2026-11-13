//
// Created by Alexander O'Carroll on 14/03/2024.
//

#ifndef COMP2034CW_C___BLOCKCHAIN_H
#define COMP2034CW_C___BLOCKCHAIN_H


#include <vector>
#include <string>
#include "Block.h"
#include "Sale.h"

class BlockChain {

private:
    Block *headBlock;
    static std::string generateHash(Block *);
    int size;

public:
    struct good{
        int quantity[4]{0};
        std::string goodName;
    };
    void addBlock(Block*);
    void displayBlockChain();
    void displayStockLevels();
    void displaySales();
    void displayOrders();
    void insertBlock(int, Block*);
    void moveBlock(int, int);
    void fixBlockChain(int);
    int checkBlockChain();
    int getSize();
    std::vector<std::string> getOrderIDs();
    std::vector<std::string> getUncompletedOrderIDs();
    std::vector<std::vector<Block*>> groupOrders();
    std::vector<good> getStockLevels();
    //std::vector<Sale*> getSales();
    std::vector<Block*> getSales();
    BlockChain();
    void printNumber(int, int);
    void printSale(Block*, Sale*);

};


#endif //COMP2034CW_C___BLOCKCHAIN_H
