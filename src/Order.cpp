//
// Created by Alexander O'Carroll on 19/03/2024.
//

#include "../headers/Order.h"

std::string Order::toString() {
    return std::string();
}

Order::Order(int quantity, std::string orderID) : Information((quantity)) {
    this->orderID = orderID;
}

std::string Order::getOrderID() {
    return orderID;
}
