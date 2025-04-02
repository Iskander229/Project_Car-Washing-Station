#include "Service.h"
#include <iostream>

Service::Service(const std::string& id, const std::string& name, double price, int duration)
    : serviceID(id), serviceName(name), price(price), duration(duration) {}


//Overload of < operator
bool Service::operator<(const Service& other) const {
    return serviceID < other.serviceID; //Compare based on serviceID
}
// > 
bool Service::operator>(const Service& other) const {
    return serviceID > other.serviceID; 
}
// == 
bool Service::operator==(const Service& other) const {
    return serviceID == other.serviceID; 
}

//getters
std::string Service::getServiceDetails() const {
    return "Service: " + serviceName + ", ID: " + serviceID + ", Price: $" + std::to_string(price) + ", Duration: " + std::to_string(duration) + " mins";
}
std::string Service::getServiceID() const {
    return serviceID;
}
double Service::getPrice() const {
    return price;
}