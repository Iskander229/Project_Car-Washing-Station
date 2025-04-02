#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class Service {
private:
    std::string serviceID;
    std::string serviceName;
    double price;
    int duration;
public:
    //constr
    Service(const std::string& id, const std::string& name, double price, int duration);

    //overload comparison opers
    bool operator<(const Service& other) const;
    bool operator>(const Service& other) const;
    bool operator==(const Service& other) const;

    //getters
    std::string getServiceDetails() const;
    std::string getServiceID() const;
    double getPrice() const;
};

#endif