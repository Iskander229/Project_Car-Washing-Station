#include "Booking.h"
#include <iostream>

Booking::Booking(const std::string& userId, const std::string& serviceId)
    : userID(userId), bookingID(serviceId) {}

//getters
std::string Booking::getUserID() const {
    return userID;
}
std::string Booking::getBookingID() const {
    return bookingID;
}