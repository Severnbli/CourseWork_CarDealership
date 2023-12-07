#include "Employee.h"
#include "utils.h"
#include <iostream>

int Employee::dimensionality_ = 5;

Employee::Employee(int)
{
	this->functionalSetUsername();
	this->functionalSetPassword();
	this->functionalSetFio();
	this->functionalSetPosition();
	this->functionalSetAward();
}

Employee::Employee(const std::string& position, double award)
{
	this->position_ = position;
	this->award_ = award;
}

Employee::Employee(const std::string& username, const std::string& password, const std::string& fio, const std::string& position, double award)
{
	this->setUsername(username);
	this->setPassword(password);
	this->setFio(fio);
	this->position_ = position;
	this->award_ = award;
}


Employee::Employee(const std::vector<std::string>& data)
{
	this->setInfoInVectorStringForm(data);
}

Employee::Employee(const Employee& other) : User(other)
{
	this->position_ = other.position_;
	this->award_ = other.award_;
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
}

std::vector<std::string> Employee::getInfoInVectorStringForm() {
	return { this->getUsername(), this->getPassword(), this->getFio(), this->position_, std::to_string(award_) };
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
