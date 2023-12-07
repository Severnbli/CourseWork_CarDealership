#include "Database.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

Database::Database()
{
	try
	{
		this->loadUsersVector(CLIENTS_FILE);
	}
	catch (const std::runtime_error& error)
	{
		if (!strcmp(error.what(),NO_INFO_IN_FILE))
		{
			utils::rebuildFile(error.what());
		}
	}
	try
	{
		this->loadUsersVector(EMPLOYEES_FILE);
	}
	catch (const std::runtime_error& error)
	{
		if (!strcmp(error.what(), NO_INFO_IN_FILE))
		{
			utils::rebuildFile(error.what());
		}
		const std::string usernameOfSuperAdmin = "admin";
		const std::string passwordOfSuperAdmin = "adminadmin";
		this->fullUpUsersVector(Employee(usernameOfSuperAdmin, passwordOfSuperAdmin));
	}
	try
	{
		this->loadCarsVector(CARS_FILE);
	}
	catch (const std::runtime_error& error)
	{
		if (!strcmp(error.what(), NO_INFO_IN_FILE))
		{
			utils::rebuildFile(error.what());
		}
	}
}

Database::Database(const Database& other)
{
	this->users_ = other.users_;
	this->cars_ = other.cars_;
}

Database::~Database()
{
	std::vector<std::shared_ptr<User>> employees;
	auto begin = this->users_.begin();
	while (begin != this->users_.end())
	{
		if ((*begin)->isAdmin())
		{
			employees.push_back(*begin);
			begin = this->users_.erase(begin);
		}
		else
		{
			++begin;
		}
	}
	this->unloadInfoToFile(employees, EMPLOYEES_FILE);
	this->unloadInfoToFile(this->users_, CLIENTS_FILE);
	this->unloadInfoToFile(this->cars_, CARS_FILE);
}

std::vector<std::string> Database::loadInfoFromFile(const std::string& fileName) { // получение вектора строк (информация из файла)
	std::ifstream file(fileName, std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error(fileName);
	}
	if (file.peek() == EOF) {
		file.close();
		throw std::runtime_error(NO_INFO_IN_FILE);
	}
	std::vector<std::string> linesInFile;
	std::string buffer;
	while (std::getline(file, buffer)) {
		linesInFile.push_back(buffer);
	}
	file.close();
	return linesInFile;
}

void Database::loadUsersVector(const std::string& fileName)
{
	std::vector<std::string> donor = this->loadInfoFromFile(fileName);
	if (fileName == CLIENTS_FILE)
	{
		Client client;
		auto parsedVectors = utils::parseStringVectorBySize(donor, client.getDimensionality()); // разбиваем вектор с данными на кусочки
		for (const auto& parsedVector : parsedVectors) {
			this->users_.push_back(std::make_shared<Client>(parsedVector));
		}
	}
	else if (fileName == EMPLOYEES_FILE)
	{
		Employee employee;
		auto parsedVectors = utils::parseStringVectorBySize(donor, employee.getDimensionality());
		for (const auto& parsedVector : parsedVectors) {
			this->users_.push_back(std::make_shared<Employee>(parsedVector));
		}
	}
}

void Database::loadCarsVector(const std::string& fileName)
{
	std::vector<std::string> donor;
	try
	{
		donor = this->loadInfoFromFile(fileName);
	}
	catch (const std::runtime_error& error)
	{
		if (!std::strcmp(error.what(), NO_INFO_IN_FILE))
		{
			return;
		}
	}
	if (fileName == CARS_FILE)
	{
		auto parsedVectors = utils::parseStringVectorBySize(donor, Car::getDimensionality()); // разбиваем вектор с данными на кусочки
		for (const auto& parsedVector : parsedVectors) {
			this->cars_.push_back(std::make_shared<Car>(parsedVector));
		}
	}
}

template <typename T>
void Database::unloadInfoToFile(const std::vector<std::shared_ptr<T>>& donor, const std::string& fileName) { // выгрузка данных в файл
	std::ofstream file(fileName, std::ios::out);
	if (!file.is_open()) {
		utils::customTerminate("выгрузкой информации в файл");
	}
	for (const auto& element : donor) {
		const std::vector<std::string>& vectorOfData = element->getInfoInVectorStringForm();
		for (const auto& data : vectorOfData) {
			file << data << '\n';
		}
	}
	file.close();
}

void Database::fullUpUsersVector(const Client& object)
{
	this->users_.push_back(std::make_shared<Client>(object));
}

void Database::fullUpUsersVector(const Employee& object)
{
	this->users_.push_back(std::make_shared<Employee>(object));
}

template <typename T>
void Database::fullUpCarsVector(const T& object)
{
	this->cars_.push_back(std::make_shared<T>(object));
}

std::vector<std::shared_ptr<User>> Database::getUsersList() const
{
	return this->users_;
}

void Database::cleanAllVectors()
{
	this->cars_.clear();
	this->users_.clear();
}

bool Database::isValidUsername(const std::string& username) const
{
	for (const auto &user : this->users_)
	{
		if (username == user->getUsername())
		{
			return false;
		}
	}
	return true;
}

int Database::showUsersInfo(const std::shared_ptr<User>& userReferense) const //печатает инфу о пользователе/ползователях
{
	if (!userReferense && this->users_.empty())
	{
		throw std::runtime_error("Нет ни одного зарегистрированного пользователя!");
	}
	utils::patternForTableHeader({ {"ИМЯ ПОЛЬЗ.", 12}, {"ФИО", 30}, {"АДМ", 3} });
	int counter = 1;
	if (userReferense)
	{
		std::cout << '|' << std::setw(4) << counter++;
		userReferense->printInfoTableForm();
	}
	else
	{
		for (const auto& user : this->users_)
		{
			std::cout << '|' << std::setw(4) << counter++;
			user->printInfoTableForm();
		}
	}
	return counter - 1;
}

int Database::showCarsInfo(const std::shared_ptr<Car>& carReferense) const
{
	if (!carReferense && this->cars_.empty())
	{
		throw std::runtime_error("В каталоге не находится ни одного автомобиля!");
	}
	utils::patternForTableHeader({ {"БРЕНД", 10}, {"МОДЕЛЬ", 7}, {"ГОД_ВЫПУСКА", 11}, {"КОЛ_ВО", 6}, {"ЦЕНА", 12} });
	int counter = 1;
	if (carReferense)
	{
		std::cout << '|' << std::setw(4) << counter++;
		carReferense->printInfoTableForm();
	}
	else
	{
		for (const auto& car : this->cars_)
		{
			std::cout << '|' << std::setw(4) << counter++;
			car->printInfoTableForm();
		}
	}
	return counter - 1;
}

