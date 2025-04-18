#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

class Admin : public Account {
private:
    static const std::string ADMIN_DEFAULT_PASSWORD; //const password for admin account

public:
    //constr
    Admin(const std::string& id, const std::string& name, const std::string& password);
    
    void displayInfo() const override;

    virtual bool fromLine(std::string line) override;
    virtual bool toLine(std::string& line) override;
};

#endif