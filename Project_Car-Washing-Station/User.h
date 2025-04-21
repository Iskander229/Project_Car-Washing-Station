#ifndef USER_H
#define USER_H

#include "Account.h"
#include "Booking.h"
#include <vector>
#include <queue>
#include "Service.h"

class User : public Account {

private:

    // Queue of paths
    std::queue<std::vector<std::string>> bookedServices;

public:
    User(const std::string& id, const std::string& name, const std::string& password);

    void AddServiceToQueue(std::vector<std::string>& path) {
        bookedServices.push(path);
    }

    bool HasPendingService() {
        return !bookedServices.empty();
    }

    std::vector<std::string> GetPendingService() {
        return bookedServices.front();
    }

    bool PopPendingService() {
        if (bookedServices.size() > 0) {
            bookedServices.pop();
            return true;
        }
        else {
            return false;
        }
    }

    virtual bool fromLine(std::string line) override;
    virtual bool toLine(std::string& line) override;
};

#endif