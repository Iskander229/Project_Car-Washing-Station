#include "Account.h"
#include "Admin.h"
#include "User.h"
#include "Util.h"
#include <iostream>

Account::Account(const std::string& id, const std::string& name, const std::string& password)
    : accountId(id), name(name), password(password) {}


bool Account::MatchPassword(const std::string& inputPassword) const
{
    return inputPassword == password;
}

//getters
std::string Account::GetAccountId() const {
    return accountId;
}
std::string Account::GetName() const {
    return name;
}

bool Account::IsValidUsername(std::string& username, std::string& errorMessage)
{
    static const char* usernameAllowedSymbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._-";
    static const size_t usernameAllowedSymbolsNum = strlen(usernameAllowedSymbols);
    if (username.size() < 4) {
        errorMessage = "Username too short.";
        return false;
    }
    bool errorSymbolsFound = false;
    std::string errorSymbols = "Username symbols not allowed: ";
    for (int i = 0; i < username.size(); i++) {
        bool symbolFound = false;
        char symbol = username[i];
        for (int j = 0; i < usernameAllowedSymbolsNum; i++) {
            if (symbol == usernameAllowedSymbols[i]) {
                symbolFound = true;
                break;
            }
        }
        if (!symbolFound) {
            errorSymbols = errorSymbols + " '" + symbol + "'";
            errorSymbolsFound = true;
        }
    }
    if (errorSymbolsFound) {
        errorMessage = errorSymbols;
        return false;
    }
    return true;
}

bool Account::IsValidPassword(std::string& password, std::string& errorMessage)
{
    static const char* passwordAllowedSymbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._-";
    static const size_t passwordAllowedSymbolsNum = strlen(passwordAllowedSymbols);
    if (password.size() < 4) {
        errorMessage = "Password too short.";
        return false;
    }
    bool errorSymbolsFound = false;
    std::string errorSymbols = "Password symbols not allowed:";
    for (int i = 0; i < password.size(); i++) {
        bool symbolFound = false;
        char symbol = password[i];
        for (int j = 0; j < passwordAllowedSymbolsNum; j++) {
            if (symbol == passwordAllowedSymbols[j]) {
                symbolFound = true;
                break;
            }
        }
        if (!symbolFound) {
            errorSymbols = errorSymbols + " '" + symbol + "'";
            errorSymbolsFound = true;
        }
    }
    if (errorSymbolsFound) {
        errorMessage = errorSymbols;
        return false;
    }
    return true;
}

Account* Account::FromLine(std::string line)
{
    if (line.size() == 0) {
        return nullptr;
    }
    bool success = true;

    std::string accountId;
    std::string name;
    std::string password;
    success &= Util::readUntillComma(line, accountId);
    success &= Util::readUntillComma(line, name);
    success &= Util::readUntillComma(line, password);

    std::string type;
    success &= Util::readUntillComma(line, type);

    if (!success) {
        return nullptr;
    }

    Account* out = nullptr;
    if (type == "user") {
        out = new User(accountId, name, password);
    }
    else if (type == "admin") {
        out = new Admin(accountId, name, password);
    }
    else {
        return nullptr;
    }

    success &= out->fromLine(line);

    if (!success) {
        delete out;
    }
    else {
        return out;
    }

}

std::string Account::ToLine(Account* account)
{
    std::string line = "";
    Util::writeWithComma(line, account->accountId);
    Util::writeWithComma(line, account->name);
    Util::writeWithComma(line, account->password);

    std::string type = "";

    if (dynamic_cast<Admin*>(account)) {
        type = "admin";
    }
    else {
        type = "user";
    }

    Util::writeWithComma(line, type);

    account->toLine(line);
    return line;
}
