#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

//base class (inheritance)
class Account {
protected:
    std::string accountID;
    std::string name;
    std::string password;

public:
    //constr
    Account(const std::string& id, const std::string& name, const std::string& password);
    virtual ~Account() {};

    //logins
    virtual bool login(const std::string& inputPassword) const;
    void changePassword(const std::string& newPassword);
    virtual void displayInfo() const = 0; //pure virtual function (makes abstract)

    //getters
    std::string getAccountID() const;
    std::string getName() const;
};

#endif