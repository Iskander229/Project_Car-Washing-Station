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

void CarWashStation::loadServices()
{
	serviceOptions = OptionTree();

	std::ifstream servicesFile("servicesDatabase.txt");

	if (!servicesFile) {
		std::cout << "Cannot load services database." << std::endl;
		return;
	}

	int errors = 0;
	while (true) {
		std::string line;
		if (!std::getline(servicesFile, line)) {
			break;
		}

		std::vector<std::string> path;
		float price;

		bool success = true;

		success &= Util::readManyUntilComma(line, path);
		success &= Util::readUntilComma(line, price);

		// Ignore root node. TODO: fix when have added root renaming
		if (path.size() == 1) {

		}
		else {
			std::string last = path[path.size() - 1];
			path.pop_back();
			success &= serviceOptions.AddOption(path, last);
			path.push_back(last);
			success &= serviceOptions.SetOptionPrice(path, price);
		}
		if (!success) {
			errors += 1;
		}
	}
	servicesFile.close();
	if (errors > 0) {
		std::cout << "Found and ignored " << errors << " errors in services data" << std::endl << std::endl;
	}

}


void CarWashStation::saveServices()
{
	std::ofstream servicesFile("servicesDatabase.txt");

	if (!servicesFile) {
		std::cout << "Cannot write to services database" << std::endl;
		return;
	}
	std::vector<std::vector<std::string>> paths;
	serviceOptions.FindAll("", paths);

	for (std::vector<std::string>& path : paths) {
		float price = serviceOptions.GetOptionPrice(path);
		std::string line = "";
		Util::writeManyWithComma(line, path);
		Util::writeWithComma(line, price);
		servicesFile << line << std::endl;
	}
	servicesFile.close();
}

void CarWashStation::loadRevenue()
{
	std::ifstream file("revenue.txt");

	if (!file) {
		std::cout << "Cannot load revenue." << std::endl;
		return;
	}
	try {
		file >> revenue;
	}
	catch (...) {
		std::cout << "Cannot load revenue." << std::endl;
	}
}

void CarWashStation::saveRevenue()
{
	std::ofstream file("revenue.txt");

	if (!file) {
		std::cout << "Cannot write to revenue database" << std::endl;
		return;
	}
	file << revenue;
}

void CarWashStation::SaveData()
{
	saveAccounts();
	saveServices();
	saveRevenue();
}

void CarWashStation::FindServiceOptions(std::string& query, std::vector<std::vector<std::string>>& results)
{
	serviceOptions.FindAll(query, results);
}

bool CarWashStation::AddService(std::vector<std::string>& path, std::string& name, float price)
{
	if (price < 0) {
		return false;
	}

	std::string name1 = "";
	for (unsigned char s : name) {
		if (s != ',') {
			name1 += s;
		}
	}

	bool success = serviceOptions.AddOption(path, name1);
	if (success) {
		path.push_back(name);
		success = SetServicePrice(path, price);
		path.pop_back();
	}
	return success;
}

bool CarWashStation::RemoveService(std::vector<std::string>& path)
{
	return serviceOptions.RemoveService(path);
}

bool CarWashStation::BookService(User* account, std::vector<std::string>& path)
{
	if (!serviceOptions.checkOption(path)) {
		return false;
	}
	account->AddServiceToQueue(path);
	return true;
}

float CarWashStation::GetServicePrice(std::vector<std::string>& path)
{
	return serviceOptions.GetOptionPrice(path);
}
bool CarWashStation::SetServicePrice(std::vector<std::string>& path, float price)
{
	if (price < 0) {
		return false;
	}
	return serviceOptions.SetOptionPrice(path, price);
}

void CarWashStation::GetUsersAsVector(std::vector<User*>& out)
{
	for (auto pair : accountsByName) {
		User* user = dynamic_cast<User*>(pair.second);
		if (user) {
			out.push_back(user);
		}
	}
}

bool CarWashStation::ValidateService(std::vector<std::string>& path)
{
	return serviceOptions.checkOption(path);
}

bool CarWashStation::ApproveOneService(User* user)
{
	std::vector<std::string> service = user->GetPendingService();
	bool success = ValidateService(service);
	if (success) {
		float price = GetServicePrice(service);
		user->PopPendingService();
		revenue += price;
		return true;
	}
	else {
		return false;
	}
}

float CarWashStation::GetRevenue()
{
	return revenue;
}

void CarWashStation::LoadData()
{
	loadAccounts();
	loadServices();
	loadRevenue();
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
