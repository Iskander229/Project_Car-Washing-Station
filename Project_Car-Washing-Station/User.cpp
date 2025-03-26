#include "User.h"
#include "CarWashStation.h"
#include "Service.h"
#include <iostream>

User::User(const std::string& id, const std::string& name)
    : userID(id), name(name) {}

void User::registerUser() {
    std::cout << "User " << name << " registered with ID: " << userID << std::endl;
}

void User::login() const {
    std::cout << "User " << name << " logged in." << std::endl;
}

void User::viewServices(const CarWashStation<Service>& carWash) const {
    carWash.displayAllServices();
}

void User::bookService(CarWashStation<Service>& carWash) {
    std::string serviceID;
    std::cout << "Enter the service ID you want to book: ";
    std::cin >> serviceID;

    Booking newBooking("B001", userID, serviceID);
    carWash.processBooking(newBooking);
    addBooking(newBooking);

    std::cout << "Service booked successfully!\n";
}

void User::viewBookingHistory() const {
    std::cout << "Booking History for User: " << name << "\n";
    for (const auto& booking : bookingHistory) {
        std::cout << "Booking ID: " << booking.getBookingID() << ", Service ID: " << booking.getServiceID() << "\n";
    }
}

void User::addBooking(const Booking& booking) {
    bookingHistory.push_back(booking);
}

std::string User::getUserID() const {
    return userID;
}