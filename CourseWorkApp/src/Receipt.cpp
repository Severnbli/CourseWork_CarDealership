#include "../header/Receipt.h"
#include "../header/utils.h"
#include <ctime>
#include <iomanip>
#include <iostream>

size_t Receipt::dimensionality_ = Car::getDimensionality() + 6 + Date::getDimensionality(); 

Receipt::Receipt(const std::vector<std::string>& donor)
{
    this->setInfoInVectorStringForm(donor);
}

Receipt::Receipt(std::pair<std::shared_ptr<Client>, std::shared_ptr<Car>> objects)
{
    time_t rawTime;
    time(&rawTime);
    struct tm timeInfo;
    localtime_s(&timeInfo, &rawTime);
    date_.setDay(timeInfo.tm_mday);
    date_.setMonth(timeInfo.tm_mon + 1);
    date_.setYear(timeInfo.tm_year + 1900);
    this->client_ = *objects.first;
    this->car_ = *objects.second;
    this->car_.setAmount(1);
}

Receipt::Receipt(const Receipt& other)
{
    this->date_ = other.date_;
    this->client_ = other.client_;
    this->car_ = other.car_;
}

bool operator<(const Receipt& first, const Receipt& second)
{
    return first.date_ < second.date_;
}

void Receipt::setInfoInVectorStringForm(const std::vector<std::string>& donor)
{
    if (donor.size() != dimensionality_)
    {
        utils::customTerminate("созданием объекта типа Receipt");
    }
    this->date_.setInfoInVectorStringForm(std::vector<std::string>(donor.begin(), donor.begin() + Date::getDimensionality()));
    this->client_.setInfoInVectorStringForm(std::vector<std::string>(donor.begin() + Date::getDimensionality(), donor.begin() + Date::getDimensionality() + this->client_.getDimensionality()));
    this->car_.setInfoInVectorStringForm(std::vector<std::string>(donor.begin() + Date::getDimensionality() + this->client_.getDimensionality(), donor.begin() + Date::getDimensionality() + this->client_.getDimensionality() + Car::getDimensionality()));
}

std::vector<std::string> Receipt::getInfoInVectorStringForm()
{
    std::vector<std::string> carInfo = this->car_.getInfoInVectorStringForm();
    std::vector<std::string> clientInfo = this->client_.getInfoInVectorStringForm();
    clientInfo.insert(clientInfo.end(), carInfo.begin(), carInfo.end());
    std::vector<std::string> dateInfo = this->date_.getInfoInVectorStringForm();
    dateInfo.insert(dateInfo.end(), clientInfo.begin(), clientInfo.end());
	return dateInfo;
}

size_t Receipt::getDimensionality()
{
    return dimensionality_;
}

void Receipt::printInfoTableForm() const
{
    std::cout << '|' << std::setw(10) << std::to_string(this->date_.getDay()) + '.' + std::to_string(this->date_.getMonth()) +
        '.' + std::to_string(this->date_.getYear());
    std::cout << '|' << std::setw(12) << this->client_.getUsername() << '|' << std::setw(30) << this->client_.getFio();
    std::cout << '|' << std::setw(13) << this->client_.getMobileNumber() << '|' << std::setw(10) << this->car_.getBrand();
    std::cout << '|' << std::setw(7) << this->car_.getModel() << '|' << std::setw(8) << this->car_.getYearOfManufacture();
    std::cout << '|' << std::fixed << std::setprecision(2) << std::setw(15) << this->car_.getPrice() << "|\n";
    std::cout << '+' << std::string(4, '-');
	std::cout << '+' << std::string(10, '-') << '+' << std::string(12, '-') << '+' << std::string(30, '-');
    std::cout << '+' << std::string(13, '-') << '+' << std::string(10, '-') << '+' << std::string(7, '-');
    std::cout << '+' << std::string(8, '-') << '+' << std::string(15, '-') << "+\n";
}

std::pair<Client, Car> Receipt::getInfo() const
{
    return { this->client_, this->car_ };
}

