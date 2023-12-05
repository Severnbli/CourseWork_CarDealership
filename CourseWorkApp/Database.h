﻿#pragma once
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
	
	~Database();
	
	std::vector<std::string> loadInfoFromFile(const std::string&);
	
	template <typename T>
	void loadVector(std::vector<std::shared_ptr<T>>&, const std::string&);

	template <typename T>
	void unloadInfoToFile(const std::vector<std::shared_ptr<T>>&, const std::string&);

	template <typename T, typename Y>
	void fullUpVector(const std::vector<std::shared_ptr<T>>&, const Y&);

	template <typename T>
	void fullUpVector(std::vector<std::shared_ptr<T>>&, const T&);

	void fullUpUsersVector(const Client&);

	void fullUpUsersVector(const Employee&);

	void fullUpCarsVector(const Car&);

	std::vector<std::shared_ptr<User>> getUsersList() const;

	void cleanAllVectors();
	
	bool isValidUsername(const std::string&) const;
	
	int showUsersInfo(const std::shared_ptr<User>& = nullptr) const;
	
	int showCarsInfo(const std::shared_ptr<Car> & = nullptr) const;

private:
	std::vector<std::shared_ptr<User>> users_;

	std::vector<std::shared_ptr<Car>> cars_;
};