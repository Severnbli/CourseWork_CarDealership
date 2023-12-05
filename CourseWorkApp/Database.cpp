#include "Database.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

Database::Database()
{
	while (true)
	{
		try {
			this->loadVector(this->users_, CLIENTS_FILE);
			this->loadVector(this->users_, EMPLOYEES_FILE);
			this->loadVector(this->cars_, CARS_FILE);
			break;
		}
		catch (const std::runtime_error& error)
		{
			this->cleanAllVectors();
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
	this->unloadInfoToFile(this->users_, CLIENTS_FILE);
	this->unloadInfoToFile(this->users_, EMPLOYEES_FILE);
	this->unloadInfoToFile(this->cars_, CARS_FILE);
}

std::vector<std::string> Database::loadInfoFromFile(const std::string& fileName) { // получение вектора строк (информация из файла)
	std::ifstream file(fileName, std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error(fileName);
	}
	if (fileName == EMPLOYEES_FILE && file.peek() == EOF) { // создаём первый аккаунт админа
		file.close();
		const std::string usernameOfSuperAdmin = "admin";
		const std::string passwordOfSuperAdmin = "admin";
		Employee employee (usernameOfSuperAdmin, passwordOfSuperAdmin);
		this->fullUpUsersVector(employee);
	}
	std::vector<std::string> linesInFile;
	std::string buffer;
	while (std::getline(file, buffer)) {
		linesInFile.push_back(buffer);
	}
	file.close();
	return linesInFile;
}

template <typename T>
void Database::loadVector(std::vector<std::shared_ptr<T>>& recipient, const std::string& fileName) { // в объекте записываемого класса д.б. статическое поле dimensionality_
	auto donor = this->loadInfoFromFile(fileName);
	if (donor.empty()) {
		return;
	}
	auto parsedVectors = utils::parseVector(donor, T::dimensionality_); // разбиваем вектор с данными на кусочки
	for (const auto& parsedVector : parsedVectors) {
		recipient.push_back(std::make_shared<T>(parsedVector));
	}
}

template <typename T>
void Database::unloadInfoToFile(const std::vector<std::shared_ptr<T>>& donor, const std::string& fileName) { // выгрузка данных в файл
	std::ofstream file(fileName, std::ios::out);
	if (!file.is_open()) {
		utils::customTerminate("выгрузкой информации в файл");
	}
	for (const auto& element : donor) {
		const auto& vectorOfData = element->getInfoInVectorStringForm();
		for (const auto& data : vectorOfData) {
			file << data << '\n';
		}
	}
	file.close();
}

template <typename T, typename Y>
void Database::fullUpVector(const std::vector<std::shared_ptr<T>>& recipient, const Y& object)
{
	recipient.push_back(std::make_shared<Y>(object));
}

template <typename T>
void Database::fullUpUsersVector(const T& object)
{
	this->fullUpVector(this->users_, object);
}

void Database::fullUpCarsVector(const Car& object)
{
	this->fullUpVector(this->cars_, object);
}



std::vector<std::shared_ptr<User>> Database::getUsersList() const
{
	return this->users_;
}

//void Database::makeNewUser(const std::string& username, const std::string& password, const std::string& fio)
//{
//	std::string mobileNumber = "";
//	bool isDriverLicense = false;
//	this->users_.push_back(std::make_shared<Client>(mobileNumber, isDriverLicense));
//	this->fullUpLastUserInfo(username, password, fio);
//	std::ofstream file(CLIENTS_FILE, std::ios::app);
//	if (file.is_open())
//	{
//		file << username << '\n' << password << '\n' << fio << '\n' << mobileNumber << '\n' << isDriverLicense << '\n';
//		file.close();
//		return;
//	}
//	throw std::runtime_error(std::string(CLIENTS_FILE));
//}



//void Database::loadInfoFromCarsFile()
//{
//	std::ifstream file(CARS_FILE, std::ios::in);
//	if (file.is_open())
//	{
//		if (file.peek() != EOF)
//		{
//			std::string brand;
//			while (std::getline(file, brand))
//			{
//				std::string model;
//				std::getline(file, model);
//				std::string bufferForYearOfManufacture;
//				std::getline(file, bufferForYearOfManufacture);
//				int yearOfManufacture = std::stoi(bufferForYearOfManufacture);
//				std::string bufferForAmount;
//				std::getline(file, bufferForAmount);
//				int amount = std::stoi(bufferForAmount);
//				std::string bufferForPrice;
//				std::getline(file, bufferForPrice);
//				double price = std::stod(bufferForPrice);
//				this->cars_.push_back(std::make_shared<Car>(brand, model, yearOfManufacture, amount, price));
//			}
//		}
//		file.close();
//		return;
//	}
//	throw std::runtime_error(std::string(CARS_FILE));
//}

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
	int counter = 1;
	std::cout << "+----+------------+--------------------+-----+\n";
	std::cout << '|' << std::setw(4) << '#' << '|' << std::setw(12) << "ИМЯ_ПОЛЬЗ." << '|' << std::setw(20) << "ФИО" << '|'
		<< std::setw(5) << "АДМИН" << "|\n";
	std::cout << "+----+------------+--------------------+-----+\n";
	if (userReferense)
	{
		std::cout << '|' << std::setw(4) << counter++ << '|' << std::setw(12) << userReferense->getUsername() << "|"
			<< std::setw(20) << userReferense->getFio() << '|' << std::setw(5) << userReferense->isAdmin() << "|\n";
		std::cout << "+----+------------+--------------------+-----+\n";
		return 1;
	}
	for (const auto& user : this->users_)
	{
		std::cout << '|' << std::setw(4) << counter++ << '|' << std::setw(12) << user->getUsername() << "|"
			<< std::setw(20) << user->getFio() << '|' << std::setw(5) << user->isAdmin() << "|\n";
		std::cout << "+----+------------+--------------------+-----+\n";
	}
	return counter - 1;
}

int Database::showCarsInfo(const std::shared_ptr<Car>& carReferense) const
{
	if (!carReferense && this->cars_.empty())
	{
		throw std::runtime_error("В каталоге не находится ни одного автомобиля!");
	}
	int counter = 1;
	std::cout << "+----+---------------+----------+-----------+------+------------+\n";
	std::cout << '|' << std::setw(4) << '#' << '|' << std::setw(15) << "БРЕНД" << '|' << std::setw(10) << "МОДЕЛЬ" << '|'
		<< std::setw(11) << "ГОД_ВЫПУСКА" << '|' << std::setw(6) << "КОЛ-ВО" << '|' << std::setw(12) << "ЦЕНА" << "|\n";
	std::cout << "+----+---------------+----------+-----------+------+------------+\n";
	if (carReferense)
	{
		std::cout << '|' << std::setw(4) << counter++ << '|' << std::setw(15) << carReferense->getBrand() << '|'
			<< std::setw(10) << carReferense->getModel() << '|' << std::setw(11) << carReferense->getYearOfManufacture()
			<< '|' << std::setw(6) << carReferense->getAmount() << '|' << std::setw(12) << carReferense->getPrice() << "|\n";
		std::cout << "+----+---------------+----------+-----------+------+------------+\n";
		return 1;
	}
	for (const auto& car : this->cars_)
	{
		std::cout << '|' << std::setw(4) << counter++ << '|' << std::setw(15) << car->getBrand() << '|'
			<< std::setw(10) << car->getModel() << '|' << std::setw(11) << car->getYearOfManufacture()
			<< '|' << std::setw(6) << car->getAmount() << '|' << std::setw(12) << car->getPrice() << "|\n";
		std::cout << "+----+---------------+----------+-----------+------+------------+\n";
	}
	return counter - 1;
}

