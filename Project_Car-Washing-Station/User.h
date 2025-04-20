#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Booking.h"
#include <vector>
#include <queue>
#include "Service.h"

class User : public Account {

private:

    // Queue of paths
    std::queue<std::vector<std::string>> bookedServices;

public:
    User(const std::string& id, const std::string& name, const std::string& password);




    virtual bool fromLine(std::string line) override;
    virtual bool toLine(std::string& line) override;
};

#endif