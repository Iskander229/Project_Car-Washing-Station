#ifndef CARWASHSTATION_H
#define CARWASHSTATION_H
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Queue.h"
#include "OptionTree.h"
#include "Booking.h"
#include "Service.h"


class Account;
class User;

class CarWashStation {
private:
    Queue<Booking> bookingQueue;
    std::vector<Booking> confirmedBookings;
    
    OptionTree serviceOptions;

    //fast-searching
    std::unordered_map<std::string, Account*> accountsById;
    std::unordered_map<std::string, Account*> accountsByName;

    void loadAccounts();
    void saveAccounts();

    void loadServices();
    void saveServices();

    float revenue;


public:
    CarWashStation() {}

    void SaveData();

    void FindServiceOptions(std::string& query, std::vector<std::vector<std::string>>& results);
    bool AddRootService(std::string& name);
    bool AddService(std::vector<std::string>& path, std::string& name);
    bool RemoveService(std::vector<std::string>& path);
    bool BookService(User* account, std::vector<std::string>& path);
    float GetServicePrice(std::vector<std::string>& path);
    bool SetServicePrice(std::vector<std::string>& path, float price);
    void GetUsersAsVector(std::vector<User*>& out);
    bool ValidateService(std::vector<std::string>& path);
    bool ApproveOneService(User* user);

    void LoadData();


    size_t getTotalBookings() const {
        return confirmedBookings.size();
    }

    Account* FindAccountByName(std::string name);
    Account* FindAccountById(std::string name);

    bool RegisterAccount(std::string& username, std::string& password, bool admin, std::string& errorMessage);

    size_t GetAccountsNumber() {
        return accountsById.size();
    }
};

#endif

