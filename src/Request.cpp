//
// Created by Alexander O'Carroll on 20/03/2024.
//

#include "../headers/Request.h"

#include <utility>

Request::Request(int quantity, std::string orderID, std::string supplierName, std::string location, std::string goodName)
: Order(quantity, orderID) {

    this->supplierName = std::move(supplierName);
    this->location = location;
    this->goodName = goodName;
}

std::string Request::toString() {
     return supplierName + "|" + location + "|" + goodName + "|" + getOrderID() + "|" +
     std::to_string(getQuantity()) + "|";
}

std::string Request::getSupplierName() {
    return supplierName;
}

std::string Request::getLocation() {
    return location;
}

std::string Request::getGoodName() {
    return goodName;
}
