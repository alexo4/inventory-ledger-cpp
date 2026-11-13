//
// Created by Alexander O'Carroll on 11/03/2024.
//

#ifndef COMP2034CW_C___BLOCK_H
#define COMP2034CW_C___BLOCK_H


#include "Information.h"
#include <ctime>

class Block {

public:
    Block(int blockNumber, std::string currentBlockHash, std::string prevBlockHash, Information *blockInformation,
          Block *prevBlock, Block *nextBlock, time_t timestamp);
    Block(Information *blockInformation, time_t timestamp);
    void printBlock();
    std::string toString();
    void setBlockNumber(int);
    void setCurrentBlockHash(std::string);
    void setPrevBlockHash(std::string);
    void setPrevBlock(Block *);
    void setNextBlock(Block *);
    Block *getPrevBlock();
    Block *getNextBlock();
    std::string getCurrentBlockHash();
    std::string getPrevBlockHash();
    Information* getInformation();
    int getBlockNumber();
    time_t getTimestamp();

private:
    int blockNumber = 0;
    std::string currentBlockHash;
    std::string prevBlockHash;
    Information *blockInformation;
    Block *prevBlock = nullptr;
    Block *nextBlock = nullptr;
    time_t timestamp;

};


#endif //COMP2034CW_C___BLOCK_H
