#include "Car.h"

Car::Car(const std::string& brand, const std::string& model, int yearOfManufacture, int amount, double price) 
{
	this->setBrand(brand);
	this->setModel(model);
	this->setYearOfManufacture(yearOfManufacture);
	this->setAmount(amount);
	this->setPrice(price);
}

Car::Car(const Car& other)
{
	this->brand_ = other.brand_;
	this->model_ = other.model_;
	this->yearOfManufacture_ = other.yearOfManufacture_;
	this->amount_ = other.amount_;
	this->price_ = other.price_;
}

void Car::setBrand(const std::string& brand)
{
	this->brand_ = brand;
}

std::string Car::getBrand() const
{
	return this->brand_;
}

void Car::setModel(const std::string& model)
{
	this->model_ = model;
}

std::string Car::getModel() const
{
	return this->model_;
}

void Car::setYearOfManufacture(int yearOfManufacture)
{
	this->yearOfManufacture_ = yearOfManufacture;
}

int Car::getYearOfManufacture() const
{
	return this->yearOfManufacture_;
}

void Car::setAmount(int amount)
{
	this->amount_ = amount;
}

int Car::getAmount() const
{
	return this->amount_;
}

void Car::setPrice(double price)
{
	this->price_ = price;
}

double Car::getPrice() const
{
	return this->price_;
}


