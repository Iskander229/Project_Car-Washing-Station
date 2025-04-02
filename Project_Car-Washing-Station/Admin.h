#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include "CarWashStation.h"
#include "Service.h"

class Admin : public Account {
private:
    static const std::string ADMIN_DEFAULT_PASSWORD; //const password for admin account

public:
    //constr
    Admin(const std::string& id, const std::string& name);
    
    //logins
    bool login(const std::string& inputPassword) const override;
    void displayInfo() const override;

    //services
    void addService(CarWashStation<Service>& carWash);
    void removeService(CarWashStation<Service>& carWash);
    void viewSalesReport(const CarWashStation<Service>& carWash) const;
};

#endif