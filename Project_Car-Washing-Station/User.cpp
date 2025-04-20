#include "User.h"
#include "CarWashStation.h"
#include "Service.h"
#include "Util.h"
#include <iostream>


User::User(const std::string& id, const std::string& name, const std::string& password)
    : Account(id, name, password)
{

}


bool User::fromLine(std::string line)
{
    std::string sizeStr;
    if (!Util::readUntillComma(line, sizeStr)) {
        return false;
    }
    int size = std::stoi(sizeStr);
    bookedServices = std::queue<std::vector<std::string>>();

    for (int i = 0; i < size; i++) {
        std::vector<std::string> service;
        if (!Util::readManyUntilComma(line, service)) {
            return false;
        }
        bookedServices.push(service);
    }
    return true;
}

bool User::toLine(std::string& line)
{
    std::queue<std::vector<std::string>> bookedServicesCopy = bookedServices;
    size_t size = bookedServicesCopy.size();
    std::string sizeStr = std::to_string(size);
    Util::writeWithComma(line, sizeStr);
    for (int i = 0; i < size; i++) {
        Util::writeManyWithComma(line, bookedServicesCopy.front());
    }
    return true;
}
