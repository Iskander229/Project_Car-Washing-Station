#include <iostream>
#include <unordered_map>
#include "User.h"
#include "Admin.h"
#include "Service.h"
#include "Booking.h"
#include "CarWashStation.h"

//global vars
std::unordered_map<std::string, User*> users;
Admin admin("A001", "Admin User");
CarWashStation<Service> carWash;

void userMenu(User* user) {
    int choice;

    while (true) {
        std::cout << "\n1. View Services\n2. Book Service\n3. View Booking History\n4. Change Password\n5. Logout\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            user->viewServices(carWash);
            break;

        case 2: 
            user->bookService(carWash);
            break;

        case 3: 
            user->viewBookingHistory();
            break;

        case 4:
        {
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            user->changePassword(newPassword);
        }
        break;

        case 5:
            std::cout << "Logging out..." << std::endl;
            return;

        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}

void adminMenu() {
    int choice;

    while (true) {
        std::cout << "\n1. Add Service\n2. Remove Service\n3. View Sales Report\n4. Change Password\n5. Logout\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: 
            admin.addService(carWash);
            break;

        case 2: 
            admin.removeService(carWash);
            break;

        case 3: 
            admin.viewSalesReport(carWash);
            break;

        case 4: 
        {
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            admin.changePassword(newPassword);
        }
        break;

        case 5:
            std::cout << "Logging out..." << std::endl;
            return;

        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}

int main() {
    int choice;
    std::string userID, name, password;

    while (true) {
        std::cout << "\n1. Register\n2. Login\n3. Admin Login\n4. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: //register
            std::cout << "Enter user ID: ";
            std::cin >> userID;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter password: ";
            std::cin >> password;
            users[userID] = new User(userID, name, password);
            users[userID]->registerUser();
            break;

        case 2: //User login
            std::cout << "Enter user ID: ";
            std::cin >> userID;
            std::cout << "Enter password: ";
            std::cin >> password;
            if (users.find(userID) != users.end() && users[userID]->login(password)) {
                userMenu(users[userID]);
            }
            else {
                std::cout << "!Invalid login or password!" << std::endl;
            }
            break;

        case 3: //Admin login
            std::cout << "Enter admin password: ";
            std::cin >> password;
            if (admin.login(password)) {
                adminMenu();
            }
            break;

        case 4: //exit
            std::cout << "Exiting..." << std::endl;
            //memory freeing
            for (auto& pair : users) {
                delete pair.second;
            }
            return 0;

        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}