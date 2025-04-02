#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    std::string userID;
    std::string bookingID;

public:
    //constr
    Booking(const std::string& userId, const std::string& serviceId);
    //getters    
    std::string getUserID() const;
    std::string getBookingID() const;
};


#endif