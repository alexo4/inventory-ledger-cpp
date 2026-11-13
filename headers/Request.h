//
// Created by Alexander O'Carroll on 20/03/2024.
//

#ifndef COMP2034CW_C___REQUEST_H
#define COMP2034CW_C___REQUEST_H


#include "Order.h"

class Request : public Order{

public:
    Request(int quantity, std::string orderID, std::string supplierName, std::string location, std::string goodName);
    std::string toString() override;
    std::string getSupplierName();
    std::string getLocation();
    std::string getGoodName();

private:
    std::string supplierName;
    std::string location;
    std::string goodName;

};


#endif //COMP2034CW_C___REQUEST_H
