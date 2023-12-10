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
#define NO_INFO_IN_FILE "NO INFO"

class Database
{
public:
	Database();

	Database(const Database&);
	
	~Database();
	
	std::vector<std::string> loadInfoFromFile(const std::string&);
	
	void loadUsersVector(const std::string&);

	void loadCarsVector(const std::string&);

	template <typename T>
	void unloadInfoToFile(const std::vector<std::shared_ptr<T>>&, const std::string&);

	void fullUpUsersVector(const Client&);

	void fullUpUsersVector(const Employee&);

	template <typename T>
	void fullUpCarsVector(const T&);

	std::vector<std::shared_ptr<User>> getUsersList() const;

	size_t getUsersVectorSize() const;

	std::shared_ptr<User> getUserByPositionInVector(size_t);

	void updateAccessRights(const std::shared_ptr<User>&);

	void sortUsersVector();

	std::vector<std::shared_ptr<User>> parseUsersVector(bool);

	size_t getCarsVectorSize() const;

	std::shared_ptr<Car> getCarByPositionInVector(size_t);

	void cleanAllVectors();

	void deleteUser(std::shared_ptr<User>&);
	
	bool isValidUsername(const std::string&) const;

	void functionalCheckUsername(std::shared_ptr<User>&);
	
	void showUsersInfo(const std::shared_ptr<User>& = nullptr) const;
	
	void showCarsInfo(const std::shared_ptr<Car> & = nullptr) const;

private:
	std::vector<std::shared_ptr<User>> users_;

	std::vector<std::shared_ptr<Car>> cars_;
};