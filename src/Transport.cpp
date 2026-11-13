//
// Created by Alexander O'Carroll on 21/03/2024.
//

#include "../headers/Transport.h"

Transport::Transport(int quantity, std::string orderID, std::string transporterName, std::string transportType,
                     std::string origin, std::string destination, int estimatedTravelTime) : Order(quantity, orderID) {

    this->transporterName = transporterName;
    this->transportType = transportType;
    this->origin = origin;
    this->destination = destination;
    this->estimatedTravelTime = estimatedTravelTime;
}

std::string Transport::toString() {
    return std::to_string(getQuantity()) + "|" + getOrderID() + "|" + transporterName + "|" + transportType + "|" + origin
    + "|" + destination + "|" + std::to_string(estimatedTravelTime) + "|";
}

std::string Transport::getTransporterName() {
    return transporterName;
}

std::string Transport::getTransportType() {
    return transportType;
}

std::string Transport::getOrigin() {
    return origin;
}

std::string Transport::getDestination() {
    return destination;
}

int Transport::getEstimatedTravelTime() {
    return estimatedTravelTime;
}
