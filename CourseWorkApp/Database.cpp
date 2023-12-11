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
	this->unloadInfoToFile(this->parseUsersVector(true), EMPLOYEES_FILE);
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

size_t Database::getUsersVectorSize() const
{
	return this->users_.size();
}

std::shared_ptr<User> Database::getUserByPositionInVector(size_t position)
{
	return this->users_.at(position);
}

void Database::updateAccessRights(const std::shared_ptr<User>& user)
{
	if (user->isAdmin())
	{
		return;
	}
	std::cout << "\nВы уверены в своих действиях?\nВся информация об аккаунте, как о клиенте, будет удалена.\n"
		"1 - Да.\n0 - Нет.\n\nВыберите: ";
	if (!static_cast<bool>(utils::checkIntInRange(0, 1)))
	{
		return;
	}
	const std::shared_ptr<Employee> employee = std::make_shared<Employee>();
	employee->setUsername(user->getUsername());
	employee->setUnmodifiedPassword(user->getPassword());
	employee->setFio(user->getFio());
	this->users_.erase(std::find(this->users_.begin(), this->users_.end(), user));
	this->users_.push_back(employee);
	std::cout << "\nПрава успешно выданы!\n\n";
	system("pause");
}

void Database::sortUsersVector()
{
	switch (utils::patternForMenus("АСА - Меню сортировки	\n\nВыберите параметр сортировки\n"
								"< - по убыванию, > - по возрастанию", {
		"Имя пользователя >",
		"Имя пользователя <",
		"ФИО >",
		"ФИО <",
		"Админ-права >",
		"Админ-права <",
		"Должность >",
		"Должность <",
		"Премия >",
		"Премия <",
		"Ном. телефона >",
		"Ном. телефона <",
		"Лицензия на авто >",
		"Лицензия на авто <"
	}))
	{
	case 1:
		{
		std::sort(this->users_.begin(), this->users_.end(), 
			[](const auto& a, const auto& b) 
			{ return compareUsersByUsername(a, b); });
		break;
		}
	case 2:
		{
		std::sort(this->users_.begin(), this->users_.end(),
			[](const auto& a, const auto& b)
			{ return compareUsersByUsername(b, a); });
		break;
		}
	case 3:
		{
		std::sort(this->users_.begin(), this->users_.end(),
			[](const auto& a, const auto& b)
			{ return compareUsersByFio(a, b); });
		break;
		}
	case 4:
		{
		std::sort(this->users_.begin(), this->users_.end(),
			[](const auto& a, const auto& b)
			{ return compareUsersByFio(b, a); });
		break;
		}
	case 5:
		{
		std::sort(this->users_.begin(), this->users_.end(),
			[](const auto& a, const auto& b)
			{ return compareUsersByAdmin(a, b); });
		break;
		}
	case 6:
		{
		std::sort(this->users_.begin(), this->users_.end(),
			[](const auto& a, const auto& b)
			{ return compareUsersByAdmin(b, a); });
		break;
		}
	case 7:
		{
		auto employeesVector = this->parseUsersVector(true);
		std::sort(employeesVector.begin(), employeesVector.end(),
			[](const auto& a, const auto& b)
			{ return compareEmployeesByPosition(std::dynamic_pointer_cast<Employee>(a), std::dynamic_pointer_cast<Employee>(b)); });
		this->users_.insert(this->users_.begin(), employeesVector.begin(), employeesVector.end());
		break;
		}
	case 8:
		{
		auto employeesVector = this->parseUsersVector(true);
		std::sort(employeesVector.begin(), employeesVector.end(),
			[](const auto& a, const auto& b)
			{ return compareEmployeesByPosition(std::dynamic_pointer_cast<Employee>(b), std::dynamic_pointer_cast<Employee>(a)); });
		this->users_.insert(this->users_.begin(), employeesVector.begin(), employeesVector.end());
		break;
		}
	case 9:
		{
		auto employeesVector = this->parseUsersVector(true);
		std::sort(employeesVector.begin(), employeesVector.end(),
			[](const auto& a, const auto& b)
			{ return compareEmployeesByAward(std::dynamic_pointer_cast<Employee>(a), std::dynamic_pointer_cast<Employee>(b)); });
		this->users_.insert(this->users_.begin(), employeesVector.begin(), employeesVector.end());
		break;
		}
	case 10:
		{
		auto employeesVector = this->parseUsersVector(true);
		std::sort(employeesVector.begin(), employeesVector.end(),
			[](const auto& a, const auto& b)
			{ return compareEmployeesByAward(std::dynamic_pointer_cast<Employee>(b), std::dynamic_pointer_cast<Employee>(a)); });
		this->users_.insert(this->users_.begin(), employeesVector.begin(), employeesVector.end());
		break;
		}
	case 11:
		{
		auto clientsVector = this->parseUsersVector(false);
		std::sort(clientsVector.begin(), clientsVector.end(),
			[](const auto& a, const auto& b)
			{ return compareClientsByMobileNumber(std::dynamic_pointer_cast<Client>(a), std::dynamic_pointer_cast<Client>(b)); });
		this->users_.insert(this->users_.begin(), clientsVector.begin(), clientsVector.end());
		break;
		}
	case 12:
		{
		auto clientsVector = this->parseUsersVector(false);
		std::sort(clientsVector.begin(), clientsVector.end(),
			[](const auto& a, const auto& b)
			{ return compareClientsByMobileNumber(std::dynamic_pointer_cast<Client>(b), std::dynamic_pointer_cast<Client>(a)); });
		this->users_.insert(this->users_.begin(), clientsVector.begin(), clientsVector.end());
		break;
		}
	case 13:
		{
		auto clientsVector = this->parseUsersVector(false);
		std::sort(clientsVector.begin(), clientsVector.end(),
			[](const auto& a, const auto& b)
			{ return compareClientsByDriverLicense(std::dynamic_pointer_cast<Client>(a), std::dynamic_pointer_cast<Client>(b)); });
		this->users_.insert(this->users_.begin(), clientsVector.begin(), clientsVector.end());
		break;
		}
	case 14:
		{
		auto clientsVector = this->parseUsersVector(false);
		std::sort(clientsVector.begin(), clientsVector.end(),
			[](const auto& a, const auto& b)
			{ return compareClientsByMobileNumber(std::dynamic_pointer_cast<Client>(b), std::dynamic_pointer_cast<Client>(a)); });
		this->users_.insert(this->users_.begin(), clientsVector.begin(), clientsVector.end());
		break;
		}
	default:
		{
		break;
		}
	case 0:
		{
		break;
		}
	}
}

void Database::searchInUsersVector()
{
	while (true)
	{
		std::vector<std::shared_ptr<User>> foundUsers;
		std::vector<std::shared_ptr<User>> foundСoincidences;
		switch(utils::patternForMenus("АСА - Меню поиска\n\nВыберите параметр поиска", {
			"Имя пользователя",
			"ФИО",
			"Админ-права",
			"Должность",
			"Премия",
			"Ном. телефона",
			"Лицензия на авто"
		}, true, false))
		{
		case 1:
			{
			std::cout << '\n';
			Client client;
			client.functionalSetUsername();
			for (const auto& user : this->users_)
			{
				if (foundUsers.empty() && user->getUsername() == client.getUsername())
				{
					foundUsers.push_back(user);
				}
				else if (user->getUsername().find(client.getUsername()) != std::string::npos)
				{
					foundСoincidences.push_back(user);
				}
			}
			break;
			}
		case 2:
			{
			std::cout << '\n';
			Client client;
			client.functionalSetFio();
			for (const auto& user : this->users_)
			{
				if (user->getFio().find(client.getFio()) != std::string::npos)
				{
					foundUsers.push_back(user);
				}
			}
			break;
			}
		case 3:
			{
			std::cout << '\n';
			std::cout << "Выберите характер поиска:\n"
				"1 - Админ-права.\n0 - Пользовательские права.\n\nВыберите: ";
			foundUsers = this->parseUsersVector(static_cast<bool>(utils::checkIntInRange(0, 1)), false);
			break;
			}
		case 4:
			{
			std::cout << '\n';
			Employee employee;
			employee.functionalSetPosition();
			const auto employees = this->parseUsersVector(true, false);
			for (const auto& element : employees)
			{
				if (std::dynamic_pointer_cast<Employee>(element)->getPosition() == employee.getPosition())
				{
					foundUsers.push_back(element);
				}
				else if (std::dynamic_pointer_cast<Employee>(element)->getPosition().find(employee.getPosition()) != std::string::npos)
				{
					foundСoincidences.push_back(element);
				}
			}
			break;
			}
		case 5:
			{
			std::cout << '\n';
			Employee employee;
			employee.functionalSetAward();
			const auto employees = this->parseUsersVector(true, false);
			for (const auto& element : employees)
			{
				if (std::dynamic_pointer_cast<Employee>(element)->getAward() == employee.getAward())
				{
					foundUsers.push_back(element);
				}
				else if (std::to_string(std::dynamic_pointer_cast<Employee>(element)->getAward()).find(std::to_string(employee.getAward())) != std::string::npos)
				{
					foundСoincidences.push_back(element);
				}
			}
			break;
			}
		case 6:
			{
			std::cout << '\n';
			Client client;
			client.functionalSetMobileNumber();
			const auto clients = this->parseUsersVector(false, false);
			for (const auto& element : clients)
			{
				if (std::dynamic_pointer_cast<Client>(element)->getMobileNumber() == client.getMobileNumber())
				{
					foundUsers.push_back(element);
				}
			}
			break;
			}
		case 7:
			{
			std::cout << '\n';
			Client client;
			client.functionalSetStatusOfDriverLicense();
			const auto clients = this->parseUsersVector(false, false);
			for (const auto& element : clients)
			{
				if (std::dynamic_pointer_cast<Client>(element)->getStatusOfDriverLicense() == client.getStatusOfDriverLicense())
				{
					foundUsers.push_back(element);
				}
			}
			break;
			}
		default:
			{
			continue;
			}
		case 0:
			{
			return;
			}
		}
		system("cls");
		std::cout << "АСА - Меню поиска - найденные записи\n\n";
		if (!foundUsers.empty())
		{
			this->showUsersInfo(nullptr, foundUsers);
		}
		if (!foundСoincidences.empty())
		{
			std::cout << "\n\nНайденные похожие:";
			this->showUsersInfo(nullptr, foundСoincidences);
		}
		if (foundUsers.empty() && foundСoincidences.empty())
		{
			std::cout << "Ни одной записи не было найдено!";
		}
		std::cout << "\n\n";
		system("pause");
	}
}

std::vector<std::shared_ptr<User>> Database::parseUsersVector(bool isAdmin, bool isErase)
{
	std::vector<std::shared_ptr<User>> result;
	auto begin = this->users_.begin();
	while (begin != this->users_.end())
	{
		if ((*begin)->isAdmin() == isAdmin)
		{
			result.push_back(*begin);
			if (isErase)
			{
				begin = this->users_.erase(begin);
				continue;
			}
		}
		++begin;
	}
	return result;
}

size_t Database::getCarsVectorSize() const
{
	return this->cars_.size();
}

std::shared_ptr<Car> Database::getCarByPositionInVector(size_t position)
{
	return this->cars_.at(position);
}

void Database::sortCarsVector()
{
	switch(utils::patternForMenus("АСА - Меню сортировки	\n\nВыберите параметр сортировки\n"
								"< - по убыванию, > - по возрастанию", {
		"Бренд >",
		"Бренд <",
		"Модель >",
		"Модель <",
		"Год выпуска >",
		"Год выпуска <",
		"Количество на складе >",
		"Количество на складе <",
		"Цена >",
		"Цена <"
		}))
	{
	case 1:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByBrand(a, b);
			});
		break;
		}
	case 2:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByBrand(b, a);
			});
		break;
		}
	case 3:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByModel(a, b);
			});
		break;
		}
	case 4:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByModel(b, a);
			});
		break;
		}
	case 5:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByYearOfManufacture(a, b);
			});
		break;
		}
	case 6:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByYearOfManufacture(b, a);
			});
		break;
		}
	case 7:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByAmount(a, b);
			});
		break;
		}
	case 8:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByAmount(b, a);
			});
		break;
		}
	case 9:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByPrice(a, b);
			});
		break;
		}
	case 10:
		{
		std::sort(this->cars_.begin(), this->cars_.end(),
			[](const auto& a, const auto& b)
			{
				return compareByPrice(b, a);
			});
		break;
		}
	default:
		{
		break;
		}
	case 0:
		{
		break;
		}
	}
}

void Database::searchInCarsVector(const std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		std::vector<std::shared_ptr<Car>> foundCars;
		std::vector<std::shared_ptr<Car>> foundСoincidences;
		switch (utils::patternForMenus("АСА - Меню поиска\n\nВыберите параметр поиска", {
			"Бренд",
			"Модель",
			"Год выпуска",
			"Количество на складе",
			"Цена"
			}, true, false))
		{
		case 1:
			{
			Car car;
			car.functionalSetBrand();
				for (const auto& element : this->cars_)
				{
					if (element->getBrand() == car.getBrand())
					{
						foundCars.push_back(element);
					}
					else if (element->getBrand().find(car.getBrand()) != std::string::npos)
					{
						foundСoincidences.push_back(element);
					} 
				}
			break;	
			}
		case 2:
			{
			Car car;
			car.functionalSetModel();
			for (const auto& element : this->cars_)
			{
				if (element->getModel() == car.getModel())
				{
					foundCars.push_back(element);
				}
				else if (element->getModel().find(car.getModel()) != std::string::npos)
				{
					foundСoincidences.push_back(element);
				}
			}
			break;
			}
		case 3:
			{
			Car car;
			car.functionalSetYearOfManufacture();
			for (const auto& element : this->cars_)
			{
				if (element->getYearOfManufacture() == car.getYearOfManufacture())
				{
					foundCars.push_back(element);
				}
			}
			break;
			}
		case 4:
			{
			Car car;
			car.functionalSetAmount();
			for (const auto& element : this->cars_)
			{
				if (element->getAmount() == car.getAmount())
				{
					foundCars.push_back(element);
				}
			}
			break;
			}
		case 5:
			{
			Car car;
			car.functionalSetPrice();
			for (const auto& element : this->cars_)
			{
				if (element->getPrice() == car.getPrice())
				{
					foundCars.push_back(element);
				}
			}
			break;
			}
		default:
				{
				break;
				}
		case 0:
				{
			return;
				}
		}
		system("cls");
		std::cout << "АСА - Меню поиска - найденные записи\n\n";
		if (!foundCars.empty())
		{
			this->showCarsInfo(nullptr, foundCars);
		}
		if (!foundСoincidences.empty())
		{
			std::cout << "\n\nНайденные похожие:";
			this->showCarsInfo(nullptr, foundСoincidences);
		}
		if (foundCars.empty() && foundСoincidences.empty())
		{
			std::cout << "Ни одной записи не было найдено!";
		}
		std::cout << "\n\n";
		system("pause");
	}
}

void Database::clearDatabase(const std::string& username)
{
	this->cars_.clear();
	auto begin = this->users_.begin();
	while (begin != this->users_.end())
	{
		if ((*begin)->getUsername() != username)
		{
			begin = this->users_.erase(begin);
		} else
		{
			++begin;
		}
	}
}

void Database::deleteUser(std::shared_ptr<User>& user)
{
	auto findIterator = std::find(this->users_.begin(), this->users_.end(), user);
	if (findIterator == this->users_.end())
	{
		return;
	}
	if (!utils::isYouConfident())
	{
		return;
	}
	size_t counterOfEmployees = 0;
	if ((*findIterator)->isAdmin())
	{
		for (const auto& element : this->users_)
		{
			if (element->isAdmin())
			{
				counterOfEmployees++;
			}
		}
		if (counterOfEmployees == 1)
		{
			std::cout << "\nУдаление единственного администрирующего аккаунта недопустимо!\n\n";
			system("pause");
			return;
		}
	}
	this->users_.erase(findIterator);
	std::cout << '\n';
	throw utils::CustomExcept("Удаление аккаунта совершено успешно!");
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

void Database::functionalCheckUsername(std::shared_ptr<User>& user) const
{
	while (true)
	{
		try
		{
			Client client;
			client.functionalSetUsername();
			if (!this->isValidUsername(client.getUsername()))
			{
				throw std::runtime_error("Такое имя пользователя занято!");
			}
			user->setUsername(client.getUsername());
			break;
		}
		catch (const std::runtime_error& error)
		{
			std::cout << error.what() << " Попробуйте снова.\n";
		}
	}
}

void Database::showUsersInfo(const std::shared_ptr<User>& userReferense, const std::vector<std::shared_ptr<User>>& usersVector) const //печатает инфу о пользователе/ползователях
{
	if (!userReferense && this->users_.empty())
	{
		throw std::runtime_error("Нет ни одного зарегистрированного пользователя!");
	}
	utils::patternForTableHeader({
									{"ИМЯ ПОЛЬЗ.", 12 }, { "ФИО", 30 }, { "АДМ", 3 },
									{"ДОЛЖНОСТЬ", 12}, {"ПРЕМИЯ", 8}, {"МОБ. ТЕЛЕФОН", 13},
									{"ЛИЦ", 3}
	});
	int counter = 1;
	if (userReferense)
	{
		std::cout << '|' << std::setw(4) << counter++;
		userReferense->printInfoTableForm();
	}
	if(!usersVector.empty())
	{
		for (const auto& element : usersVector)
		{
			std::cout << '|' << std::setw(4) << counter++;
			element->printInfoTableForm();
		}
	}
	if (!userReferense && usersVector.empty())
	{
		for (const auto& user : this->users_)
		{
			std::cout << '|' << std::setw(4) << counter++;
			user->printInfoTableForm();
		}
	}
}

void Database::showCarsInfo(const std::shared_ptr<Car>& carReferense, const std::vector<std::shared_ptr<Car>>& carsVector) const
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
	if (!carsVector.empty())
	{
		for (const auto& element : carsVector)
		{
			std::cout << '|' << std::setw(4) << counter++;
			element->printInfoTableForm();
		}
	}
	if (!carReferense && carsVector.empty())
	{
		for (const auto& car : this->cars_)
		{
			std::cout << '|' << std::setw(4) << counter++;
			car->printInfoTableForm();
		}
	}
}

