#include "Admin.h"
#include "CarWashStation.h"
#include "Service.h"
#include <iostream>

const std::string Admin::ADMIN_DEFAULT_PASSWORD = "admin123";

//constr
Admin::Admin(const std::string& id, const std::string& name)
    : Account(id, name, ADMIN_DEFAULT_PASSWORD) {}

//logins
bool Admin::login(const std::string& inputPassword) const {
    if (Account::login(inputPassword)) {
        std::cout << "Admin " << name << " logged in." << std::endl;
        return true;
    }
    std::cout << "Invalid password!" << std::endl;
    return false;
}
void Admin::displayInfo() const {
    std::cout << "Admin ID: " << accountID << "\nName: " << name << std::endl;
}


//SERVICES
void Admin::addService(CarWashStation<Service>& carWash) {
    std::string serviceID, serviceName;
    double price;
    int duration;

    std::cout << "Enter service ID: ";
    std::cin >> serviceID;
    std::cout << "Enter service name: ";
    std::cin.ignore();
    std::getline(std::cin, serviceName);
    std::cout << "Enter service price: ";
    std::cin >> price;
    std::cout << "Enter service duration (in minutes): ";
    std::cin >> duration;

    Service newService(serviceID, serviceName, price, duration);
    carWash.addService(newService);
}

void Admin::removeService(CarWashStation<Service>& carWash) {
    carWash.displayAllServices();
    std::string serviceID;
    std::cout << "Enter the service ID you want to remove: ";
    std::cin >> serviceID;
    carWash.removeService(serviceID);
}

void Admin::viewSalesReport(const CarWashStation<Service>& carWash) const {
    std::cout << "Sales Report:\n";
    std::cout << "Total bookings: " << carWash.getTotalBookings() << "\n";
    std::cout << "Total revenue: $" << carWash.getTotalRevenue() << "\n";
}