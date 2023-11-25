#include "Date.h"

Date::Date(int day, int month, int year)
{
	this->setDay(day);
	this->setMonth(month);
	this->setYear(year);
}

Date::Date(const Date& other)
{
	this->day_ = other.day_;
	this->month_ = other.month_;
	this->year_ = other.year_;
}

void Date::setDay(int day)
{
	this->day_ = day;
}

int Date::getDay() const
{
	return this->day_;
}


void Date::setMonth(int month)
{
	this->month_ = month;
}

int Date::getMonth() const
{
	return this->month_;
}

void Date::setYear(int year)
{
	this->year_ = year;
}

int Date::getYear() const
{
	return this->year_;
}
