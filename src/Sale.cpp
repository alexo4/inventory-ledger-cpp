//
// Created by Alexander O'Carroll on 23/03/2024.
//

#include "../headers/Sale.h"

Sale::Sale(int quantity, std::string goodName, int revenue, std::string paymentType) : Information(quantity){
    this->goodName = goodName;
    this->revenue = revenue;
    this->paymentType = paymentType;
}

std::string Sale::toString() {
    return goodName + "|" + std::to_string(getQuantity()) + "|" + std::to_string(revenue) + "|" +
    paymentType + "|";
}

std::string Sale::getGoodName() {
    return goodName;
}

int Sale::getRevenue() {
    return revenue;
}

