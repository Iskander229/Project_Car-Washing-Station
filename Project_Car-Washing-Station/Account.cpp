#include "Account.h"
#include <iostream>

Account::Account(const std::string& id, const std::string& name, const std::string& password)
    : accountID(id), name(name), password(password) {}


//login
bool Account::login(const std::string& inputPassword) const {
    return inputPassword == password;
}
void Account::changePassword(const std::string& newPassword) {
    password = newPassword;
    std::cout << "Password changed successfully!" << std::endl;
}

//getters
std::string Account::getAccountID() const {
    return accountID;
}
std::string Account::getName() const {
    return name;
}
