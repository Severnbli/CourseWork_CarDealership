#pragma once
#include <string>

class Car
{
public:
	Car() = default;
	Car(const std::string&, const std::string&, int, int, double);
	Car(const Car&);
	~Car() = default;
	void setBrand(const std::string&);
	std::string getBrand() const;
	void setModel(const std::string&);
	std::string getModel() const;
	void setYearOfManufacture(int);
	int getYearOfManufacture() const;
	void setAmount(int);
	int getAmount() const;
	void setPrice(double);
	double getPrice() const;
private:
	std::string brand_ = "";
	std::string model_ = "";
	int yearOfManufacture_ = 0;
	int amount_ = 0;
	double price_ = 0.0;
};
