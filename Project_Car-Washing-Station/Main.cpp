#include <iostream>
#include <unordered_map>
#include "User.h"
#include "Admin.h"
#include "Service.h"
#include "Booking.h"
#include "CarWashStation.h"

// Global variables
std::unordered_map<std::string, User*> users; //Store registered users
Admin admin("A001", "Admin User"); //Single admin
CarWashStation<Service> carWash; //Car wash station (instantiated with Service type)

void userMenu(User* user);
void adminMenu();

int main() {
    int choice;
    std::string userID, name, password;

    while (true) {
        std::cout << "\n1. Register\n2. Login\n3. Admin Login\n4. Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: // Register
            std::cout << "Enter user ID: ";
            std::cin >> userID;
            std::cout << "Enter name: ";
            std::cin >> name;
            users[userID] = new User(userID, name);
            users[userID]->registerUser();
            break;

        case 2: // User Login
            std::cout << "Enter user ID: ";
            std::cin >> userID;
            if (users.find(userID) != users.end()) {
                users[userID]->login();
                userMenu(users[userID]);
            }
            else {
                std::cout << "User not found!" << std::endl;
            }
            break;

        case 3: // Admin Login
            std::cout << "Enter admin password: ";
            std::cin >> password;
            if (admin.login(password)) {
                adminMenu();
            }
            break;

        case 4: // Exit
            std::cout << "Exiting..." << std::endl;
            return 0;

        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}

void userMenu(User* user) {
    int choice;

    while (true) {
        std::cout << "\n1. View Services\n2. Book Service\n3. View Booking History\n4. Logout\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: //View Services
            user->viewServices(carWash);
            break;

        case 2: //Book Service
            user->bookService(carWash);
            break;

        case 3: //View Booking History
            user->viewBookingHistory();
            break;

        case 4: //Logout
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
        std::cout << "\n1. Add Service\n2. Remove Service\n3. View Sales Report\n4. Logout\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: //Add Service
            admin.addService(carWash);
            break;

        case 2: //Remove Service
            admin.removeService(carWash);
            break;

        case 3: //View Sales Report
            admin.viewSalesReport(carWash);
            break;

        case 4: //Logout
            std::cout << "Logging out..." << std::endl;
            return;

        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }
}