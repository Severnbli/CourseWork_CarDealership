#include "Employee.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

int Employee::dimensionality_ = 6;

Employee::Employee(int) : User()
{
	this->functionalSetUsername();
	std::cout << '\n';
	this->functionalSetPassword();
	std::cout << '\n';
	this->functionalSetFio();
	std::cout << '\n';
	this->functionalSetPosition();
	std::cout << '\n';
	this->functionalSetAward();
}

Employee::Employee(const std::string& position, double award) : User()
{
	this->position_ = position;
	this->award_ = award;
}

Employee::Employee(const std::string& username, const std::string& password, const std::string& fio, const std::string& position, double award) : User()
{
	this->setUsername(username);
	this->setPassword(password);
	this->setFio(fio);
	this->position_ = position;
	this->award_ = award;
}

Employee::Employee(const std::vector<std::string>& data)
{
	Employee::setInfoInVectorStringForm(data);
}

Employee::Employee(const Employee& other) : User(other)
{
	this->position_ = other.position_;
	this->award_ = other.award_;
}

bool Employee::operator<(const Employee& other) const
{
	return this->award_ < other.award_;
}

void Employee::setInfoInVectorStringForm(const std::vector<std::string>& donor) {
	if (donor.size() != dimensionality_) {
		utils::customTerminate("созданием объекта типа Employee");
	}
	this->setUsername(donor[0]);
	this->setUnmodifiedPassword(donor[1]);
	this->setFio(donor[2]);
	this->position_ = donor[3];
	this->award_ = std::stod(donor[4]);
	this->setUniqueId_(donor[5]);
}

std::vector<std::string> Employee::getInfoInVectorStringForm()
{
	return { this->getUsername(), this->getPassword(), this->getFio(), this->position_, std::to_string(award_), this->getUniqueId() };
}

void Employee::setPosition(const std::string& position)
{
	this->position_ = position;
}

void Employee::functionalSetPosition()
{
	std::cout << "Должность (до 12 символов): ";
	this->position_ = utils::checkStringInRange(0, 12);
}

std::string Employee::getPosition() const
{
	return this->position_;
}

void Employee::setAward(double award)
{
	this->award_ = award;
}

void Employee::functionalSetAward()
{
	std::cout << "Премия: ";
	this->award_ = utils::checkDouble();
}

double Employee::getAward() const
{
	return this->award_;
}

bool Employee::isAdmin() const
{
	return true;
}

int Employee::getDimensionality()
{
	return dimensionality_;
}

void Employee::printInfoTableForm() const
{
	std::cout << "|" << std::setw(12) << this->getUsername() << '|' << std::setw(30)
		<< this->getFio() << '|' << std::setw(3);
	if (this->isAdmin())
	{
		std::cout << "Да";
	}
	else
	{
		std::cout << "Нет";
	}
	std::cout << '|' << std::setw(12) << this->position_ << '|' << std::setw(8) << std::fixed
		<< std::setprecision(2) << this->award_	<< '|' << std::string(13, ' ')
		<< '|' << std::string(3, ' ') << '|' << std::endl;
	std::cout << "+" << std::string(4, '-') << '+' << std::string(12, '-')
		<< '+' << std::string(30, '-') << '+' << std::string(3, '-') << '+';
	std::cout << std::string(12, '-') << '+' << std::string(8, '-') << '+'
		<< std::string(13, '-') << '+' << std::string(3, '-') << "+\n";
}

bool compareEmployeesByPosition(const Employee& firstObject, const Employee& secondObject)
{
	return firstObject.getPosition() < secondObject.getPosition();
}

bool compareEmployeesByPosition(const std::shared_ptr<Employee>& firstObject, const std::shared_ptr<Employee>& secondObject)
{
	return firstObject->getPosition() < secondObject->getPosition();
}

bool compareEmployeesByAward(const Employee& firstObject, const Employee& secondObject)
{
	return firstObject.getAward() < secondObject.getAward();
}

bool compareEmployeesByAward(const std::shared_ptr<Employee>& firstObject, const std::shared_ptr<Employee>& secondObject)
{
	return firstObject->getAward() < secondObject->getAward();
}