#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Booking.h"
#include "Service.h"

template <typename T>
class CarWashStation;

class User {
private:
    std::string userID;
    std::string name;
    std::vector<Booking> bookingHistory;

public:
    User(const std::string& id, const std::string& name);
    void registerUser();
    void login() const;
    void viewServices(const CarWashStation<Service>& carWash) const;
    void bookService(CarWashStation<Service>& carWash);
    void viewBookingHistory() const;
    void addBooking(const Booking& booking);
    std::string getUserID() const;
};

#endif