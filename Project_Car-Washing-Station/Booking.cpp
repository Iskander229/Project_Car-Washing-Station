#include "Booking.h"
#include <iostream>

Booking::Booking(const std::string& id, const std::string& userId, const std::string& serviceId)
    : bookingID(id), userID(userId), serviceID(serviceId) {}

std::string Booking::getBookingID() const {
    return bookingID;
}

std::string Booking::getServiceID() const {
    return serviceID;
}