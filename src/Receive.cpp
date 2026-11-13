//
// Created by Alexander O'Carroll on 23/03/2024.
//

#include "../headers/Receive.h"

Receive::Receive(int quantity, std::string orderID,  int transactionAmount,
                 std::string paymentType) : Order(quantity, orderID) {

    this->transactionAmount = transactionAmount;
    this->paymentType = paymentType;

}

std::string Receive::toString() {
    return getOrderID() + "|" + std::to_string(getQuantity()) + "|" + std::to_string(transactionAmount)
    + "|" + paymentType + "|";
}

int Receive::getTransactionAmount() {
    return transactionAmount;
}

std::string Receive::getPaymentType() {
    return paymentType;
}
