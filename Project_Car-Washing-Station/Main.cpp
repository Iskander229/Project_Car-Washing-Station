#include <iostream>
#include <unordered_map>
#include "User.h"
#include "Admin.h"
#include "Service.h"
#include "Booking.h"
#include "CarWashStation.h"
#include <iomanip>
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


void registerDialogue(Account* account, CarWashStation* carWash, bool setupMode) {
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

bool findService(Account* account, CarWashStation* carWash, std::vector<std::string>& foundService, bool ignoreRoot) {
	std::cout << "Find service:" << std::endl;
	std::cout << "    Enter service name: ";
	std::string findName;
	std::getline(std::cin, findName);

	std::vector<std::vector<std::string>> services;
	carWash->FindServiceOptions(findName, services);

	if (ignoreRoot) {
		for (int i = 0; i < services.size(); i++) {
			if (services[i].size() == 1) {
				services.erase(services.begin() + i);
				break;
			}
		}
	}

	bool cancel = false;

	ChoiceForm choices = ChoiceForm("Found " + std::to_string(services.size()) + " services:");
	for (std::vector<std::string>& path : services) {
		if (path.size() == 1 && ignoreRoot) {
			continue;
		}
		std::string servicePathAsString = Util::StackServicePath(path);

		float price = carWash->GetServicePrice(path);
		servicePathAsString = servicePathAsString + " (" + Util::FormatPrice(price) + "$)";

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

void listServices(CarWashStation* carWash, bool ignoreRoot) {
	std::vector<std::vector<std::string>> services;
	std::string query = "";
	carWash->FindServiceOptions(query, services);

	if (ignoreRoot) {
		for (int i = 0; i < services.size(); i++) {
			if (services[i].size() == 1) {
				services.erase(services.begin() + i);
				break;
			}
		}
	}

	std::cout << std::endl << "Found " << services.size() << " services: " << std::endl;



	int i = 0;
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

		float price = carWash->GetServicePrice(path);
		std::cout << "    " << ++i << ". " << servicePathAsString << " (" << Util::FormatPrice(price) << "$)" << std::endl;
	}
}

void removeServiceOption(Account* account, CarWashStation* carWash) {
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

void approveServiceDone(Account* account, CarWashStation* carWash) {
	std::cout << std::endl << "Active booked services:" << std::endl;

	ChoiceForm choice("Mark service as done:");

	std::vector<User*> allUsers;
	carWash->GetUsersAsVector(allUsers);
	User* chosenUser = nullptr;
	int pendingUsers = 0;
	for (User* user : allUsers) {
		if (user->HasPendingService()) {
			std::vector<std::string> service = user->GetPendingService();
			bool success = carWash->ValidateService(service);
			std::string lastBlock;
			if (success) {
				float price = carWash->GetServicePrice(service);
				lastBlock = "Price: " + Util::FormatPrice(price) + "$";
			}
			else {
				lastBlock = "Error: options does not exist anymore. Choose to skip.";
			}
			choice.AddChoice(
				"User '" + user->GetName() +
				"', " + Util::StackServicePath(service) +
				", " + lastBlock,
				[&chosenUser, user]() {chosenUser = user; });
			pendingUsers += 1;
		}
	}
	choice.AddChoice("Cancel", []() {});

	if (pendingUsers == 0) {
		std::cout << "There is no booked services pending." << std::endl;
		return;
	}

	choice.AskUser();

	if (chosenUser == nullptr) {
		std::cout << "Operation canceled." << std::endl;
	}
	else {
		std::vector<std::string> service = chosenUser->GetPendingService();
		bool success = carWash->ApproveOneService(chosenUser);
		if (success) {
			std::cout << "Service approved. Total revenue: " << carWash->GetRevenue() << "$" << std::endl;
		}
		else {
			// Should never happen since the existence of the sevice was checked before
			std::cout << "Operation failed." << std::endl;

		}
	}



}

void seeRevenue(Account* account, CarWashStation* carWash) {
	std::cout << "Carwash revenue:\n    " << carWash->GetRevenue() << "$" << std::endl;
}

float getFloatInput() {
	while (true) {
		std::string s;
		std::getline(std::cin, s);
		try {
			float result = std::stof(s);
			return result;
		}
		catch (std::invalid_argument) {
			std::cout << "Invalid input." << std::endl;
		}
	}

}

void newServiceOption(Account* account, CarWashStation* carWash) {
	bool cancel = false;

	while (true) {

		if (cancel) {
			std::cout << "Operation canceled." << std::endl;
			return;
		}

		bool success = false;

		std::vector<std::string> foundServicePath;
		success = findService(account, carWash, foundServicePath, false);
		if (success) {
			std::string newServiceName;
			std::cout << "New service name: ";
			std::getline(std::cin, newServiceName);
			std::cout << "Enter price: ";
			float price = getFloatInput();
			success = carWash->AddService(foundServicePath, newServiceName, price);
			if (success) {
				foundServicePath.push_back(newServiceName);
				carWash->SetServicePrice(foundServicePath, price);
			}
			else {
				std::cout << "Invalid name / price." << std::endl;
			}
		}

		if (success) {
			std::cout << "Service option added." << std::endl;
			return;
		}
	}
}

void bookService(User* user, CarWashStation* carWash) {
	if (user == nullptr) {
		std::cout << std::endl << "Operation failed." << std::endl;
		return;
	}
	std::cout << std::endl << "Book:" << std::endl;
	std::vector<std::string> result;
	findService(user, carWash, result, true);
	bool success = carWash->BookService(user, result);
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
			if (dynamic_cast<Admin*>(account)) {
				choices.AddChoice("New service option", [&account, &carWash]() {newServiceOption(account, &carWash); });
				choices.AddChoice("Remove service option", [&account, &carWash]() {removeServiceOption(account, &carWash); });
				choices.AddChoice("Approve service done", [&account, &carWash]() {approveServiceDone(account, &carWash); });
				choices.AddChoice("Show revenue", [&account, &carWash]() {seeRevenue(account, &carWash); });
				choices.AddChoice("Register account", [&account, &carWash]() {registerDialogue(account, &carWash, false); });
			}
			else {
				choices.AddChoice("Book service", [account, &carWash]() {bookService(dynamic_cast<User*>(account), &carWash); });

			}
			choices.AddChoice("List services", [&carWash, account]() {listServices(&carWash, dynamic_cast<Admin*>(account) == nullptr); });
			choices.AddChoice("Log out", [&account]() {account = nullptr; });
		}
		choices.AskUser();
		carWash.SaveData();
	}


	return 0;

}