//
// Created by Alexander O'Carroll on 11/03/2024.
//

#include <iostream>
#include <utility>
#include "../headers/Block.h"
#include "../headers/Information.h"
#include <ctime>


using namespace std;

Block::Block(int blockNumber, string currentBlockHash, string prevBlockHash, Information *blockInformation,
             Block *prevBlock, Block *nextBlock, time_t timestamp){
    this->blockNumber = blockNumber;
    this->currentBlockHash = std::move(currentBlockHash);
    this->prevBlockHash = std::move(prevBlockHash);
    this->nextBlock = nextBlock;
    this->prevBlock = prevBlock;
    this->blockInformation = blockInformation;
    this->timestamp = timestamp;
}

Block::Block(Information *blockInformation, time_t timestamp){
    this->blockInformation = blockInformation;
    this->timestamp = timestamp;
}

void Block::printBlock(){
    cout << this->toString();
}

string Block::toString() {
    return "|" + to_string(blockNumber) + "|" + currentBlockHash + "|" + prevBlockHash + "|" + ctime(&timestamp) + "|" +
               blockInformation->toString();
}

void Block::setBlockNumber(int blockNumber) {
    this->blockNumber = blockNumber;
}

void Block::setCurrentBlockHash(string currentBlockHash) {
    this->currentBlockHash = std::move(currentBlockHash);
}

void Block::setPrevBlockHash(string prevBlockHash) {
    this->prevBlockHash = std::move(prevBlockHash);
}

void Block::setPrevBlock(Block *prevBlock) {
    this->prevBlock = prevBlock;
}

void Block::setNextBlock(Block *nextBlock) {
    this->nextBlock = nextBlock;
}

Block *Block::getPrevBlock() {
    return prevBlock;
}

Block *Block::getNextBlock() {
    return nextBlock;
}

std::string Block::getCurrentBlockHash() {
    return currentBlockHash;
}

std::string Block::getPrevBlockHash() {
    return prevBlockHash;
}

Information * Block::getInformation() {
    return blockInformation;
}

int Block::getBlockNumber() {
    return blockNumber;
}

time_t Block::getTimestamp(){
    return timestamp;
}




