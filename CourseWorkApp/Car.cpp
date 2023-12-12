#include "Car.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

int Car::dimensionality_ = 5;

Car::Car(int)
{
	this->functionalSetBrand();
	std::cout << '\n';
	this->functionalSetModel();
	std::cout << '\n';
	this->functionalSetYearOfManufacture();
	std::cout << '\n';
	this->functionalSetAmount();
	std::cout << '\n';
	this->functionalSetPrice();
}

Car::Car(const std::string& brand, const std::string& model, int yearOfManufacture, int amount, double price) 
{
	this->setBrand(brand);
	this->setModel(model);
	this->setYearOfManufacture(yearOfManufacture);
	this->setAmount(amount);
	this->setPrice(price);
}

Car::Car(const std::vector<std::string>& data)
{
	this->setInfoInVectorStringForm(data);
}

bool Car::operator<(const Car& other) const
{
	return this->amount_ < other.amount_;
}

Car::Car(const Car& other)
{
	this->brand_ = other.brand_;
	this->model_ = other.model_;
	this->yearOfManufacture_ = other.yearOfManufacture_;
	this->amount_ = other.amount_;
	this->price_ = other.price_;
}

void Car::setInfoInVectorStringForm(const std::vector<std::string>& donor) {
	if (donor.size() != dimensionality_) {
		utils::customTerminate("созданием объекта типа Car");
	}
	this->brand_ = donor[0];
	this->model_ = donor[1];
	this->yearOfManufacture_ = std::stoi(donor[2]);
	this->amount_ = std::stoi(donor[3]);
	this->price_ = std::stod(donor[4]);
}

std::vector<std::string> Car::getInfoInVectorStringForm()
{
	return { this->brand_, this->model_, std::to_string(this->yearOfManufacture_), std::to_string(this->amount_), std::to_string(price_) };
}

void Car::setBrand(const std::string& brand)
{
	this->brand_ = brand;
}

void Car::functionalSetBrand()
{
	std::cout << "Бренд (до 10 символов): ";
	this->brand_ = utils::checkStringInRange(0, 10);
}

std::string Car::getBrand() const
{
	return this->brand_;
}

void Car::setModel(const std::string& model)
{
	this->model_ = model;
}

void Car::functionalSetModel()
{
	std::cout << "Модель (до 7 символов): ";
	this->model_ = utils::checkStringInRange(0, 7);
}

std::string Car::getModel() const
{
	return this->model_;
}

void Car::setYearOfManufacture(int yearOfManufacture)
{
	this->yearOfManufacture_ = yearOfManufacture;
}

void Car::functionalSetYearOfManufacture()
{
	std::cout << "Год выпуска: ";
	this->yearOfManufacture_ = utils::checkIntInRange(1960, 2023);
}

int Car::getYearOfManufacture() const
{
	return this->yearOfManufacture_;
}

void Car::setAmount(int amount)
{
	this->amount_ = amount;
}

void Car::functionalSetAmount()
{
	std::cout << "Количество: ";
	this->amount_ = utils::checkIntPositive();
}

int Car::getAmount() const
{
	return this->amount_;
}

void Car::setPrice(double price)
{
	this->price_ = price;
}

void Car::functionalSetPrice()
{
	std::cout << "Цена: ";
	this->price_ = utils::checkDoublePositive();
}

double Car::getPrice() const
{
	return this->price_;
}

int Car::getDimensionality()
{
	return dimensionality_;
}

void Car::printInfoTableForm() const
{
	std::cout << '|' << std::setw(10) << this->brand_ << '|' << std::setw(7) << this->model_ << '|';
	std::cout << std::setw(8) << this->yearOfManufacture_ << '|' << std::setw(6) << this->amount_ << '|';
	std::cout << std::setw(15) << std::fixed << std::setprecision(2) << this->price_ << '|' << std::endl;
	std::cout << '+' << std::string(4, '-') << '+' << std::string(10, '-') << '+';
	std::cout << std::string(7, '-') << '+' << std::string(8, '-') << '+';
	std::cout << std::string(6, '-') << '+' << std::string(15, '-') << '+' << std::endl;
 }

bool compareByBrand(const Car& firstObject, const Car& secondObject)
{
	return firstObject.getBrand() < secondObject.getBrand();
}

bool compareByBrand(const std::shared_ptr<Car>& firstObject, const std::shared_ptr<Car>& secondObject)
{
	return firstObject->getBrand() < secondObject->getBrand();
}

bool compareByModel(const Car& firstObject, const Car& secondObject)
{
	return firstObject.getModel() < secondObject.getModel();
}

bool compareByModel(const std::shared_ptr<Car>& firstObject, const std::shared_ptr<Car>& secondObject)
{
	return firstObject->getModel() < secondObject->getModel();
}

bool compareByYearOfManufacture(const Car& firstObject, const Car& secondObject)
{
	return firstObject.getYearOfManufacture() < secondObject.getYearOfManufacture();
}

bool compareByYearOfManufacture(const std::shared_ptr<Car>& firstObject, const std::shared_ptr<Car>& secondObject)
{
	return firstObject->getYearOfManufacture() < secondObject->getYearOfManufacture();
}

bool compareByAmount(const Car& firstObject, const Car& secondObject)
{
	return firstObject.getAmount() < secondObject.getAmount();
}

bool compareByAmount(const std::shared_ptr<Car>& firstObject, const std::shared_ptr<Car>& secondObject)
{
	return firstObject->getAmount() < secondObject->getAmount();
}

bool compareByPrice(const Car& firstObject, const Car& secondObject)
{
	return firstObject.getPrice() < secondObject.getPrice();
}

bool compareByPrice(const std::shared_ptr<Car>& firstObject, const std::shared_ptr<Car>& secondObject)
{
	return firstObject->getPrice() < secondObject->getPrice();
}
