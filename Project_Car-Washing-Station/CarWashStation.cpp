#include "Admin.h"
#include "User.h"
#include <fstream>
#include "CarWashStation.h"
#include <iostream>
#include <string>

void CarWashStation::loadAccounts()
{
    for (auto pair : accountsById) {
        delete pair.second;
    }
    accountsById.clear();
    accountsByName.clear();

    std::ifstream accountsFile("accountsDatabase.txt");

    if (accountsFile) {
        int errors = 0;
        while (true) {
            std::string line;
            if (!std::getline(accountsFile, line)) {
                break;
            }
            Account* account = Account::FromLine(line);
            if (account == nullptr) {
                errors += 1;
            }
            else {
                accountsById[account->GetAccountId()] = account;
                accountsByName[account->GetName()] = account;
            }
        }
        accountsFile.close();
        if (errors > 0) {
            std::cout << "Found and ignored " << errors << " errors in accounts data" << std::endl << std::endl;
        }
    }
}

void CarWashStation::saveAccounts()
{
    std::ofstream accountsFile("accountsDatabase.txt");

    if (!accountsFile) {
        std::cout << "Cannot write to accounts database" << std::endl;
        return;
    }

    for (auto pair : accountsById) {
        std::string line = Account::ToLine(pair.second);
        accountsFile << line << std::endl;
    }
    accountsFile.close();
}

void CarWashStation::SaveData()
{
    saveAccounts();
}

void CarWashStation::FindServiceOptions(std::string& query, std::vector<std::vector<std::string>>& results)
{
    serviceOptions.FindAll(query, results);
}

bool CarWashStation::AddRootService(std::string& name)
{
    return serviceOptions.AddOption(name);
}

bool CarWashStation::AddService(std::vector<std::string>& path, std::string& name)
{
    return serviceOptions.AddOption(path, name);
}

bool CarWashStation::RemoveService(std::vector<std::string>& path)
{
    return serviceOptions.RemoveService(path);
}

bool CarWashStation::BookService(Account* account, std::vector<std::string>& path)
{
    return false;
}

void CarWashStation::LoadData()
{
    loadAccounts();
}

Account* CarWashStation::FindAccountByName(std::string name)
{
    // a common way to get an object from a map without creating a new default value uses iterator
    auto it = accountsByName.find(name);
    if (it != accountsByName.end()) {
        // second stands for the Account* value
        return it->second;
    }
    else {
        return nullptr;
    }
}
Account* CarWashStation::FindAccountById(std::string id)
{
    auto it = accountsById.find(id);
    if (it != accountsById.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

bool CarWashStation::RegisterAccount(std::string& username, std::string& password, bool admin, std::string& errorMessage)
{
    if (FindAccountByName(username) != nullptr) {
        errorMessage = "Username already exists.";
        return false;
    }
    
    std::string id;
    int i = 0;
    do {
        id = username + std::to_string(i);
        i += 1;
    } while (FindAccountById(id) != nullptr);

    Account* newAccount = nullptr;
    if (admin) {
        newAccount = new Admin(id, username, password);
    }
    else {
        newAccount = new User(id, username, password);
    }

    accountsById[id] = newAccount;
    accountsByName[username] = newAccount;

    return true;
}
