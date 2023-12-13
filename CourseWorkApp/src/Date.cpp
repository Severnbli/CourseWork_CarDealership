#include "../header/utils.h"
#include "../header/Date.h"
#include <iostream>

size_t Date::dimensionality_ = 3;

Date::Date(int day, int month, int year) {
    this->day_ = day;
    this->month_ = month;
    this->year_ = year;
}

Date::Date(const Date& other) {
    this->day_ = other.day_;
    this->month_ = other.month_;
    this->year_ = other.year_;
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        this->day_ = other.day_;
        this->month_ = other.month_;
        this->year_ = other.year_;
    }
    return *this;
}

bool Date::operator==(const Date& other) const {
    return this->day_ == other.day_ && this->month_ == other.month_ && this->year_ == other.year_;
}

bool Date::operator!=(const Date& other) const {
    return this->day_ != other.day_ || this->month_ != other.month_ || this->year_ != other.year_;
}

bool Date::operator<(const Date& other) const {
    if (this->year_ != other.year_) {
        return this->year_ < other.year_;
    }
    if (this->month_ != other.month_) {
        return this->month_ < other.month_;
    }
    return this->day_ < other.day_;
}

bool Date::operator>(const Date& other) const {
    if (this->year_ != other.year_) {
        return this->year_ > other.year_;
    }
    if (this->month_ != other.month_) {
        return this->month_ > other.month_;
    }
    return this->day_ > other.day_;
}

void Date::functionalSetInfo() {
    this->functionalSetDay();
    this->functionalSetMonth();
    this->functionalSetYear();
}

void Date::setInfo(int day, int month, int year)
{
    this->day_ = day;
    this->month_ = month;
    this->year_ = year;
}

void Date::setInfoInVectorStringForm(const std::vector<std::string>& donor)
{
	if (donor.size() != dimensionality_)
	{
        utils::customTerminate("созданием объекта типа Date");
	}
    this->day_ = std::stoi(donor[0]);
    this->month_ = std::stoi(donor[1]);
    this->year_ = std::stoi(donor[2]);
}

void Date::getInfo() const noexcept {
    std::cout << "Дата: " << this->day_ << '.' << this->month_
        << '.' << this->year_ << std::endl;
}

std::vector<std::string> Date::getInfoInVectorStringForm()
{
    return { std::to_string(this->day_), std::to_string(this->month_), std::to_string(this->year_) };
}


std::array<int, 3> Date::getFunctionalInfo() const noexcept {
    return { this->day_, this->month_, this->year_ };
}

void Date::getAdditionalInfo() noexcept {
    std::cout << "Дата: " << this->day_ << ", " << Date::defineMonth(this->month_)
        << ", " << this->year_ << '-';
    if (this->year_ % 4 == 0) {
        std::cout << "високосный";
    }
    else {
        std::cout << "не високосный";
    }
    std::cout << std::endl;
}

void Date::functionalSetDay() {
    std::cout << "\u001b[32m->\u001b[0m День: ";
    this->day_ = utils::checkIntInRange(1, 31);
}

void Date::setDay(int day)
{
    this->day_ = day;
}

int Date::getDay() const noexcept {
    return this->day_;
}

void Date::functionalSetMonth() {
    std::cout << "\u001b[32m->\u001b[0m Месяц: ";
    this->month_ = utils::checkIntInRange(1, 12);
}

void Date::setMonth(int month)
{
    this->month_ = month;
}

int Date::getMonth() const noexcept {
    return this->month_;
}

std::string Date::defineMonth(int month) {
    std::array<std::string, 12> months = { "январь",
                                          "февраль",
                                          "март",
                                          "апрель",
                                          "май",
                                          "июнь",
                                          "июль",
                                          "август",
                                          "сентябрь",
                                          "октябрь",
                                          "ноябрь",
                                          "декабрь" };
    return months[month - 1];
}

void Date::functionalSetYear(int ceil) {
    std::cout << "\u001b[32m->\u001b[0m Год: ";
    this->year_ = utils::checkIntInRange(1, ceil);
}

void Date::setYear(int year)
{
    this->year_ = year;
}

int Date::getYear() const noexcept {
    return this->year_;
}

std::string Date::defineYear(int year)
{
	if (year % 4 == 0)
	{
        return "високосный";
	}
    return "не високосный";
}

size_t Date::getDimensionality()
{
    return dimensionality_;
}
