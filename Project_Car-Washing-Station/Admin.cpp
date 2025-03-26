#include "Admin.h"
#include "CarWashStation.h" 
#include "Service.h"        
#include <iostream>

const std::string Admin::ADMIN_PASSWORD = "admin123"; // Fixed password

Admin::Admin(const std::string& id, const std::string& name)
    : adminID(id), name(name) {}

bool Admin::login(const std::string& password) const {
    if (password == ADMIN_PASSWORD) {
        std::cout << "Admin " << name << " logged in." << std::endl;
        return true;
    }
    else {
        std::cout << "Invalid password!" << std::endl;
        return false;
    }
}

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
    carWash.displayAllServices(); // Display all services

    std::string serviceID;
    std::cout << "Enter the service ID you want to remove: ";
    std::cin >> serviceID;

    carWash.removeService(serviceID); // Pass the serviceID directly
}

void Admin::viewSalesReport(const CarWashStation<Service>& carWash) const {
    std::cout << "Sales Report:\n";
    std::cout << "Total bookings: " << carWash.getTotalBookings() << "\n";
    std::cout << "Total revenue: $" << carWash.getTotalRevenue() << "\n";
}