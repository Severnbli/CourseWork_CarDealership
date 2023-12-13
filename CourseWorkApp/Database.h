#pragma once
#include "User.h"
#include "Client.h"
#include "Employee.h"
#include "Car.h"
#include "Receipt.h"
#include <vector>
#include <memory>

#define CLIENTS_FILE "clients.txt"
#define EMPLOYEES_FILE "employees.txt"
#define CARS_FILE "cars.txt"
#define RECEIPTS_FILE "receipts.txt"

class Database
{
public:
	Database();

	Database(const Database&);
	
	~Database();
	
	std::vector<std::string> loadInfoFromFile(const std::string&);
	
	void loadUsersVector(const std::string&);

	void loadCarsVector(const std::string&);

	void loadReceiptsVector(const std::string&);

	template <typename T>
	void unloadInfoToFile(const std::vector<std::shared_ptr<T>>&, const std::string&);

	void fullUpUsersVector(const Client&);

	void fullUpUsersVector(const Employee&);

	template <typename T>
	void fullUpCarsVector(const T&);

	void fullUpReceiptsVector(const std::shared_ptr<User>&, const std::shared_ptr<Car>&);

	std::vector<std::shared_ptr<User>> getUsersList() const;

	size_t getUsersVectorSize() const;

	std::shared_ptr<User> getUserByPositionInVector(size_t);

	void updateAccessRights(const std::shared_ptr<User>&);

	std::vector<std::shared_ptr<User>> parseUsersVector(bool, bool = true);

	size_t getCarsVectorSize() const;

	std::shared_ptr<Car> getCarByPositionInVector(size_t);

	void sortUsersVector();

	void searchInUsersVector();

	void sortCarsVector();

	void searchInCarsVector(const std::shared_ptr<User>& = nullptr) const;

	void sortReceiptsVector();

	void searchInReceiptsVector() const;

	void clearDatabase(const std::string&);

	void deleteUser(const std::shared_ptr<User>&);

	void deleteCar(const std::shared_ptr<Car>&);
	
	bool isValidUsername(const std::string&) const;

	void functionalCheckUsername(std::shared_ptr<User>&) const;
	
	void customizeCar(const std::shared_ptr<Car>&);
	
	void showUsersInfo(const std::shared_ptr<User>& = nullptr, const std::vector<std::shared_ptr<User>>& = {}) const;

	void showCarsInfo(const std::shared_ptr<Car> & = nullptr, const std::vector<std::shared_ptr<Car>>& = {}) const;

	void showReceiptsInfo(const std::shared_ptr<Receipt>& = nullptr, const std::vector<std::shared_ptr<Receipt>>& = {}) const;

private:
	std::vector<std::shared_ptr<User>> users_;

	std::vector<std::shared_ptr<Car>> cars_;

	std::vector<std::shared_ptr<Receipt>> receipts_;
};