#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Booking.h"
#include <vector>
#include "Service.h"

template <typename T> //just a forward declaration
class CarWashStation;

class User : public Account {
private:
    std::vector<Booking> bookingHistory;

public:
    User(const std::string& id, const std::string& name, const std::string& password);
    void registerUser();
    void displayInfo() const override;
    void viewServices(const CarWashStation<Service>& carWash) const;
    void bookService(CarWashStation<Service>& carWash);
    void viewBookingHistory() const;
    void addBooking(const Booking& booking);
};

#endif