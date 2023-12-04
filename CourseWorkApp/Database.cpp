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
			this->loadInfoFromUsersFile();
			this->loadInfoFromCarsFile();
			break;
		}
		catch (const std::runtime_error& error)
		{
			this->cleanAllVectors();
			makeRebuildFile(error.what());
		}
	}
}

Database::Database(const Database& other)
{
	this->users_ = other.users_;
	this->cars_ = other.cars_;
}

std::vector<std::string> Database::loadInfoFromFile(const std::string& fileName) { // получение вектора строк (информация из файла)
	std::ifstream file(fileName, std::ios::in);
	if (!file.is_open()) {
		throw std::runtime_error(fileName);
	}
	if (fileName == EMPLOYEES_FILE && file.peek() == EOF) {
		file.close();
		makeFirstAdminAccount();
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
		recipient.push_back(std::make_shared<T>(parsedVector);
	}
}

template <typename T>
void Database::unloadInfoToFile(const std::vector<std::shared_ptr<T>>& donor, const std::string& fileName) { // выгрузка данных в файл
	std::ofstream file(fileName, std::ios::out);
	if (!file.is_open()) {
		throw std::runtime_error(fileName);
	}
	for (const auto& element : donor) {
		const auto& vectorOfData = element->getInfoInVectorStringForm();
		for (const auto& data : vectorOfData) {
			file << data << '\n';
		}
	}
	file.close();
}

//void Database::loadInfoFromUsersFile()
//{
//	std::ifstream fileOfClients(CLIENTS_FILE, std::ios::in);
//	if (fileOfClients.is_open())
//	{
//		if (fileOfClients.peek() != EOF)
//		{
//			std::string username;
//			std::string password;
//			std::string fio;
//			std::string mobileNumber;
//			bool isDriverLicense;
//			while (std::getline(fileOfClients, username))
//			{
//				std::getline(fileOfClients, password);
//				std::getline(fileOfClients, fio);
//				std::getline(fileOfClients, mobileNumber);
//				std::string bufferForIsDriverLicense;
//				std::getline(fileOfClients, bufferForIsDriverLicense);
//				isDriverLicense = std::stoi(bufferForIsDriverLicense);
//				this->users_.push_back(std::make_shared<Client>(mobileNumber, isDriverLicense));
//				this->fullUpLastUserInfo(username, password, fio);
//			}
//		}
//		fileOfClients.close();
//	}
//	else
//	{
//		throw std::runtime_error(std::string(CLIENTS_FILE));
//	}
//	std::ifstream fileOfEmployees(EMPLOYEES_FILE, std::ios::in);
//	if (fileOfEmployees.is_open())
//	{
//		if (fileOfEmployees.peek() == EOF)
//		{
//			fileOfEmployees.close();
//			makeFirstAdminAccount();
//			return;
//		}
//		std::string username;
//		std::string password;
//		std::string fio;
//		std::string position;
//		double award;
//		while (std::getline(fileOfEmployees, username))
//		{
//			std::getline(fileOfEmployees, password);
//			std::getline(fileOfEmployees, fio);
//			std::getline(fileOfEmployees, position);
//			std::string bufferForAward;
//			std::getline(fileOfEmployees, bufferForAward);
//			award = std::stod(bufferForAward);
//			this->users_.push_back(std::make_shared<Employee>(position, award));
//			this->fullUpLastUserInfo(username, password, fio);
//		}
//	}
//	else
//	{
//		throw std::runtime_error(std::string(EMPLOYEES_FILE));
//	}
//}

//void Database::makeFirstAdminAccount()
//{
//	std::ofstream file(EMPLOYEES_FILE, std::ios::in);
//	if (file.is_open())
//	{
//		const std::string username = "admin";
//		const std::string password = "admin";
//		const std::string fio = "";
//		const std::string position = "";
//		const double award = 0.0;
//		file << username << '\n' << password << '\n' << fio << '\n' << position << '\n' << award << '\n';
//		this->users_.push_back(std::make_shared<Employee>(position, award));
//		this->fullUpLastUserInfo(username, password, fio);
//		file.close();
//		return;
//	}
//	throw std::runtime_error(std::string(EMPLOYEES_FILE));
//}

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

void Database::makeRebuildFile(const std::string& nameOfFile) //пересоздание/создание файла
{
	std::ofstream file(nameOfFile, std::ios::out);
	if (!file.is_open())
	{
		utils::customTerminate("пересозданием файла");
	}
	file.close();
}

void Database::cleanAllVectors()
{
	this->cars_.clear();
	this->users_.clear();
}

void Database::fullUpLastUserInfo(const std::string& username, const std::string& password, const std::string& fio) //заполнение последнего элемента вектора
{						
	this->users_[this->users_.size() - 1]->setUsername(username);
	this->users_[this->users_.size() - 1]->setPassword(password);
	this->users_[this->users_.size() - 1]->setFio(fio);
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

