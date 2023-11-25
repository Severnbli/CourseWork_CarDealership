#pragma once
#include "User.h"
#include "Client.h"
#include "Employee.h"
#include "Car.h"
#include <vector>
#include <memory>

#define CLIENTS_FILE "clients.txt"
#define EMPLOYEES_FILE "employees.txt"
#define CARS_FILE "cars.txt"

class Database
{
public:
	Database();
	Database(const Database&);
	~Database() = default;
	void loadInfoFromUsersFile();
	void makeFirstAdminAccount();
	std::vector<std::shared_ptr<User>> getUsersList() const;
	void makeNewUser(const std::string&, const std::string&, const std::string&);
	void loadInfoFromCarsFile();
	void makeRebuildFile(const std::string&);
	void cleanAllVectors();
	void fullUpLastUserInfo(const std::string&, const std::string&, const std::string&);
	bool isValidUsername(const std::string&) const;
	int showUsersInfo(const std::shared_ptr<User>& = nullptr) const;
	int showCarsInfo(const std::shared_ptr<Car> & = nullptr) const;
private:
	std::vector<std::shared_ptr<User>> users_;
	std::vector<std::shared_ptr<Car>> cars_;
};