//
// Created by Alexander O'Carroll on 23/03/2024.
//

#ifndef COMP2034CW_C___SALE_H
#define COMP2034CW_C___SALE_H


#include "Information.h"

class Sale : public Information{

public:
    Sale(int quantity, std::string goodName, int revenue, std::string paymentType);
    std::string toString() override;
    std::string getGoodName();
    int getRevenue();

private:
    std::string goodName;
    int revenue;
    std::string paymentType;

};


#endif //COMP2034CW_C___SALE_H
