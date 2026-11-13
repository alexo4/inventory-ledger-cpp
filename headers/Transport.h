//
// Created by Alexander O'Carroll on 21/03/2024.
//

#ifndef COMP2034CW_C___TRANSPORT_H
#define COMP2034CW_C___TRANSPORT_H


#include "Order.h"


class Transport : public Order{

public:
    Transport(int quantity, std::string orderID, std::string transporterName, std::string transportType, std::string origin,
              std::string destination, int estimatedTravelTime);
    std::string toString() override;
    std::string getTransporterName();
    std::string getTransportType();
    std::string getOrigin();
    std::string getDestination();
    int getEstimatedTravelTime();

private:
    std::string transporterName;
    std::string transportType;
    std::string origin;
    std::string destination;
    int estimatedTravelTime;
};


#endif //COMP2034CW_C___TRANSPORT_H
