#include "Admin.h"
#include "CarWashStation.h"
#include "Service.h"
#include <iostream>

const std::string Admin::ADMIN_DEFAULT_PASSWORD = "admin123";

//constr
Admin::Admin(const std::string& id, const std::string& name, const std::string& password)
	: Account(id, name, password) {}


void Admin::displayInfo() const {
	std::cout << "Admin ID: " << accountId << "\nName: " << name << std::endl;
}

bool Admin::fromLine(std::string line)
{
	// In this version of application admin does not have any special data in comparison to Account, so do nothing
	return true;
}

bool Admin::toLine(std::string& line)
{
	// In this version of application user does not have any special data in comparison to Account, so do nothing
	return true;
}
