#include "User.h"
#include "CarWashStation.h"
#include "Service.h"
#include <iostream>

User::User(const std::string& id, const std::string& name, const std::string& password)
    : Account(id, name, password) {}

//logins
void User::registerUser() {
    std::cout << "User " << name << " registered with ID: " << accountID << std::endl;
}
void User::displayInfo() const {
    std::cout << "User ID: " << accountID << "\nName: " << name << std::endl;
}

//services
void User::viewServices(const CarWashStation<Service>& carWash) const {
    carWash.displayAllServices();
}

void User::bookService(CarWashStation<Service>& carWash) {
    std::string serviceID;

    std::cout << "Enter the service ID you want to book: ";
    std::cin >> serviceID;

    Booking newBooking(accountID, serviceID); 
    carWash.processBooking(newBooking);
    addBooking(newBooking);

    std::cout << "Service booked successfully!\n";
}

void User::viewBookingHistory() const {
    int i = 0;
    std::cout << "Booking History for User: " << name << "\n";
    for (const auto& booking : bookingHistory) {
        std::cout <<"Service ID #" <<  ++i <<": " << booking.getBookingID() << "\n";
    }
}

//pushes the booking
void User::addBooking(const Booking& booking) {
    bookingHistory.push_back(booking);
}