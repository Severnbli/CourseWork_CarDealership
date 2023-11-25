#include "Employee.h"

Employee::Employee(const std::string& position, double award)
{
	this->position_ = position;
	this->award_ = award;
}

Employee::Employee(const Employee& other)
{
	this->position_ = other.position_;
}

void Employee::setPosition(const std::string& position)
{
	this->position_ = position;
}

std::string Employee::getPosition() const
{
	return this->position_;
}

void Employee::setAward(double award)
{
	this->award_ = award;
}

double Employee::getAward() const
{
	return this->award_;
}


bool Employee::isAdmin() const
{
	return true;
}

