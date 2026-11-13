//
// Created by Alexander O'Carroll on 13/03/2024.
//

#include "../headers/Information.h"
#include <iostream>

std::string Information::toString() { return ""; }

Information::Information(int quantity){
    this->quantity = quantity;
}

int Information::getQuantity() {
    return quantity;
}
