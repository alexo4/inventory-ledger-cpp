//
// Created by Alexander O'Carroll on 19/03/2024.
//

#ifndef COMP2034CW_C___ORDER_H
#define COMP2034CW_C___ORDER_H


#include "Information.h"

class Order : public Information{

public:
    std::string toString() override;
    std::string getOrderID();
    void setOrderID();

private:
    std::string orderID;

protected:
    Order(int quantity, std::string orderID);
};


#endif //COMP2034CW_C___ORDER_H
