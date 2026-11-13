//
// Created by Alexander O'Carroll on 23/03/2024.
//

#ifndef COMP2034CW_C___RECEIVE_H
#define COMP2034CW_C___RECEIVE_H


#include "Order.h"

class Receive : public Order{

public:
    Receive(int quantity, std::string orderID, int transactionAmount,
            std::string paymentType);
    std::string toString() override;
    int getTransactionAmount();
    std::string getPaymentType();

private:
    int transactionAmount;
    std::string paymentType;


};


#endif //COMP2034CW_C___RECEIVE_H
