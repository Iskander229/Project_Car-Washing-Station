#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "CarWashStation.h" 
#include "Service.h"        

class Admin {
private:
    std::string adminID;
    std::string name;
    static const std::string ADMIN_PASSWORD; // Fixed password

public:
    Admin(const std::string& id, const std::string& name);
    bool login(const std::string& password) const;

    // Using CarWashStation<Service>
    void addService(CarWashStation<Service>& carWash);
    void removeService(CarWashStation<Service>& carWash);
    void viewSalesReport(const CarWashStation<Service>& carWash) const;
};

#endif