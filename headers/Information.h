//
// Created by Alexander O'Carroll on 13/03/2024.
//

#ifndef COMP2034CW_C___INFORMATION_H
#define COMP2034CW_C___INFORMATION_H


#include <string>


class Information {

public:
    virtual std::string toString() = 0;
    int getQuantity();
private:
    int quantity;

protected:
    Information(int quantity);
};

#endif //COMP2034CW_C___INFORMATION_H
