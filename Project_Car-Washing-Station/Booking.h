#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    std::string bookingID;
    std::string userID;
    std::string serviceID;

public:
    Booking(const std::string& id, const std::string& userId, const std::string& serviceId);
    std::string getBookingID() const;
    std::string getServiceID() const;
};

#endif