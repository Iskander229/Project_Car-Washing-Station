#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

//base class (inheritance)
class Account {
protected:
    std::string accountId;
    std::string name;
    std::string password;

    virtual bool fromLine(std::string line) = 0;
    virtual bool toLine(std::string& line) = 0;

public:
    //constr
    Account(const std::string& id, const std::string& name, const std::string& password);
    virtual ~Account() {};

    //logins
    virtual bool MatchPassword(const std::string& inputPassword) const;
    void changePassword(const std::string& newPassword);
    virtual void displayInfo() const = 0; //pure virtual function (makes abstract)

    //getters
    std::string GetAccountId() const;
    std::string GetName() const;

    static bool IsValidUsername(std::string& username, std::string& errorMessage);
    static bool IsValidPassword(std::string& password, std::string& errorMessage);

    static Account* FromLine(std::string line);
    static std::string ToLine(Account* account);
};

#endif