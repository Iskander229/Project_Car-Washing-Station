#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Booking.h"
#include <vector>
#include "Service.h"

class User : public Account {

public:
    User(const std::string& id, const std::string& name, const std::string& password);


    void displayInfo() const override;

    virtual bool fromLine(std::string line) override;
    virtual bool toLine(std::string& line) override;
};

#endif