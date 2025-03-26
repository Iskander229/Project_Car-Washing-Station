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
    Service(const std::string& id, const std::string& name, double price, int duration);

    // Overload comparison operators
    bool operator<(const Service& other) const;
    bool operator>(const Service& other) const;
    bool operator==(const Service& other) const;

    // Getter methods
    std::string getServiceDetails() const;
    std::string getServiceID() const;
    double getPrice() const; // Add this method
};

#endif