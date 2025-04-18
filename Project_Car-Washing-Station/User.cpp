#include "User.h"
#include "CarWashStation.h"
#include "Service.h"
#include <iostream>


User::User(const std::string& id, const std::string& name, const std::string& password)
    : Account(id, name, password)
{

}

void User::displayInfo() const {
    std::cout << "Admin ID: " << accountId << "\nName: " << name << std::endl;
}

bool User::fromLine(std::string line)
{
    // In this version of application user does not have any special data in comparison to Account, so do nothing
    return true;
}

bool User::toLine(std::string& line)
{
    // In this version of application user does not have any special data in comparison to Account, so do nothing
    return true;
}
