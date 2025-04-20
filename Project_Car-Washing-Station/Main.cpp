#include <iostream>
#include <unordered_map>
#include "User.h"
#include "Admin.h"
#include "Service.h"
#include "Booking.h"
#include "CarWashStation.h"
#include "ChoiceForm.h"

void login(Account*& account, CarWashStation* carWash) {
	std::cout << "Log in" << std::endl;

	std::string username;
	std::cout << "    Username: ";
	std::getline(std::cin, username);

	std::string password;
	std::cout << "    Password: ";
	std::getline(std::cin, password);

	Account* foundAccount = carWash->FindAccountByName(username);
	if (foundAccount == nullptr || !foundAccount->MatchPassword(password)) {
		std::cout << "Incorrect username or password." << std::endl;
	}
	else {
		account = foundAccount;
	}

}


void registerDialogue(Account*& account, CarWashStation* carWash, bool setupMode) {
	std::cout << "Sign up" << std::endl;

	std::string username;
	std::cout << "    Username: ";
	std::getline(std::cin, username);

	std::string error;
	if (!Account::IsValidUsername(username, error)) {
		std::cout << "Invalid username. " << error << std::endl;
		return;
	}

	std::string password;
	std::cout << "    Password: ";
	std::getline(std::cin, password);

	if (!Account::IsValidPassword(password, error)) {
		std::cout << "Invalid password. " << error << std::endl;
		return;
	}

	bool isAdmin = false;
	if (setupMode) {
		isAdmin = true;
	}
	else {
		if (dynamic_cast<Admin*>(account) != nullptr) {
			std::string adminResponse;
			std::cout << "Grant Admin permission? (Y/N) : ";
			std::getline(std::cin, adminResponse);
			if (adminResponse == "Y") {
				isAdmin = true;
			}
		}
	}

	bool success = carWash->RegisterAccount(username, password, isAdmin, error);
	if (!success) {
		std::cout << "Cannot create account. " << error << std::endl;
	}
	else {
		std::cout << "Account created. " << std::endl;
	}
}

bool findService(Account*& account, CarWashStation* carWash, std::vector<std::string>& foundService, bool ignoreRoot) {
	std::cout << "Find service:" << std::endl;
	std::cout << "    Enter service name: ";
	std::string findName;
	std::getline(std::cin, findName);

	std::vector<std::vector<std::string>> services;
	carWash->FindServiceOptions(findName, services);

	if (services.size() == 0 || services.size() == 1 && ignoreRoot) {
		std::cout << "No services found." << std::endl;
		return false;
	}
	else {

		bool cancel = false;

		ChoiceForm choices = ChoiceForm("Found " + std::to_string(services.size()) + " services:");
		for (std::vector<std::string>& path : services) {
			if (path.size() == 1 && ignoreRoot) {
				continue;
			}
			std::string servicePathAsString = "";
			bool first = true;
			for (std::string& s : path) {
				if (!first) {
					servicePathAsString = servicePathAsString + " > " + s;
				}
				else {
					servicePathAsString = servicePathAsString + s;
					first = false;
				}
			}
			choices.AddChoice(servicePathAsString, [&foundService, path]() {foundService = path; });
		}
		choices.AddChoice("Cancel", [&cancel]() {cancel = true; });
		choices.AskUser();
		if (cancel) {
			std::cout << "Operation canceled." << std::endl;
			return false;
		}
		else {
			return true;
		}
	}

}

void listServices(CarWashStation* carWash) {
	std::vector<std::vector<std::string>> services;
	std::string query = "";
	carWash->FindServiceOptions(query, services);

	std::cout << std::endl << "Found " << services.size() << " services: " << std::endl;

	for (std::vector<std::string>& path : services) {
		std::string servicePathAsString = "";
		bool first = true;
		for (std::string& s : path) {
			if (!first) {
				servicePathAsString = servicePathAsString + " > " + s;
			}
			else {
				servicePathAsString = servicePathAsString + s;
				first = false;
			}
		}
		std::cout << "    " << servicePathAsString << std::endl;
	}
}

void removeServiceOption(Account*& account, CarWashStation* carWash) {
	std::cout << std::endl << "Remove service:" << std::endl;
	std::vector<std::string> result;
	findService(account, carWash, result, true);
	bool success = carWash->RemoveService(result);
	if (success) {
		std::cout << "Service removed." << std::endl;
	}
	else {
		std::cout << "Operation failed." << std::endl;
	}
}

void newServiceOption(Account*& account, CarWashStation* carWash) {
	bool cancel = false;

	while (true) {
		bool addToExisting = false;
		ChoiceForm choices("Add service: ");
		choices.AddChoice("Add option to existing service", [&addToExisting]() {addToExisting = true; });
		choices.AddChoice("Add new service", [&addToExisting]() {addToExisting = false; });
		choices.AddChoice("Cancel", [&cancel]() {cancel = true; });
		choices.AskUser();

		if (cancel) {
			std::cout << "Operation canceled." << std::endl;
			return;
		}

		bool success = false;

		if (addToExisting) {
			std::vector<std::string> foundServicePath;
			success = findService(account, carWash, foundServicePath, false);
			if (success) {
				std::string newServiceName;
				std::cout << "New service name: ";
				std::getline(std::cin, newServiceName);
				success = carWash->AddService(foundServicePath, newServiceName);
			}
		}
		else {
			std::string newServiceName;
			std::cout << "New service name: ";
			std::getline(std::cin, newServiceName);
			success = carWash->AddRootService(newServiceName);
		}

		if (success) {
			std::cout << "Service option added." << std::endl;
			return;
		}
	}
}

void bookService(Account*& account, CarWashStation* carWash) {
	std::cout << std::endl << "Book:" << std::endl;
	std::vector<std::string> result;
	findService(account, carWash, result, true);
	bool success = carWash->BookService(account, result);
	if (success) {
		std::cout << "Service booked." << std::endl;
	}
	else {
		std::cout << "Operation failed." << std::endl;
	}
}

int main() {
	CarWashStation carWash = CarWashStation();
	carWash.LoadData();
	Account* account = nullptr;

	if (carWash.GetAccountsNumber() == 0) {
		std::cout << "Setup mode: no accounts exist yet." << std::endl;
		std::cout << "Register admin user:" << std::endl;
		registerDialogue(account, &carWash, true);
		carWash.SaveData();
	}



	while (true) {
		ChoiceForm choices("Actions: ");
		if (account == nullptr) {
			choices.AddChoice("Login", [&account, &carWash]() {login(account, &carWash); });
			choices.AddChoice("Register", [&account, &carWash]() {registerDialogue(account, &carWash, false); });
		}
		else {
			choices.AddChoice("Log out", [&account]() {account = nullptr; });
			choices.AddChoice("List services", [&carWash]() {listServices(&carWash); });
			if (dynamic_cast<Admin*>(account)) {
				choices.AddChoice("Register account", [&account, &carWash]() {registerDialogue(account, &carWash, false); });
				choices.AddChoice("New service option", [&account, &carWash]() {newServiceOption(account, &carWash); });
				choices.AddChoice("Remove service option", [&account, &carWash]() {removeServiceOption(account, &carWash); });
			}
			else {
				choices.AddChoice("Book service", [&account, &carWash]() {bookService(account, &carWash); });

			}


		}
		choices.AskUser();
		carWash.SaveData();
	}


	return 0;

}