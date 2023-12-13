#pragma once
#include <memory>
#include <string>
#include <vector>

class Car
{
public:
	Car();

	Car(int);

	Car(const std::string&, const std::string&, int, int, double);

	Car(const std::vector<std::string>&);

	Car(const Car&);

	bool operator<(const Car&) const;

	void setInfoInVectorStringForm(const std::vector<std::string>&);

	std::vector<std::string> getInfoInVectorStringForm();

	void setBrand(const std::string&);

	void functionalSetBrand();

	std::string getBrand() const;

	void setModel(const std::string&);

	void functionalSetModel();

	std::string getModel() const;

	void setYearOfManufacture(int);

	void functionalSetYearOfManufacture();

	int getYearOfManufacture() const;

	void setAmount(int);

	void functionalSetAmount();

	int getAmount() const;

	void setPrice(double);

	void functionalSetPrice();

	double getPrice() const;

	static int getDimensionality();

	void printInfoTableForm() const;

private:
	static int dimensionality_;

	std::string brand_;

	std::string model_;

	int yearOfManufacture_ = 0;

	int amount_ = 0;

	double price_ = 0.0;

	std::string uniqueId_;
};

bool compareByBrand(const Car&, const Car&);

bool compareByBrand(const std::shared_ptr<Car>&, const std::shared_ptr<Car>&);

bool compareByModel(const Car&, const Car&);

bool compareByModel(const std::shared_ptr<Car>&, const std::shared_ptr<Car>&);

bool compareByYearOfManufacture(const Car&, const Car&);

bool compareByYearOfManufacture(const std::shared_ptr<Car>&, const std::shared_ptr<Car>&);

bool compareByAmount(const Car&, const Car&);

bool compareByAmount(const std::shared_ptr<Car>&, const std::shared_ptr<Car>&);

bool compareByPrice(const Car&, const Car&);

bool compareByPrice(const std::shared_ptr<Car>&, const std::shared_ptr<Car>&);
