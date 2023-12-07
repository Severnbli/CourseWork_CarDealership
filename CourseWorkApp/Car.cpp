﻿#include "Car.h"
#include "utils.h"
#include <iostream>

int Car::dimensionality_ = 5;

Car::Car(int)
{
	this->functionalSetBrand();
	this->functionalSetModel();
	this->functionalSetYearOfManufacture();
	this->functionalSetAmount();
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

std::vector<std::string> Car::getInfoInVectorStringForm() {
	return { this->brand_, this->model_, std::to_string(this->yearOfManufacture_), std::to_string(this->amount_), std::to_string(price_) };
}

void Car::setBrand(const std::string& brand)
{
	this->brand_ = brand;
}

void Car::functionalSetBrand()
{
	std::cout << "Бренд (до 15 символов): ";
	this->brand_ = utils::checkStringInRange(0, 15);
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
