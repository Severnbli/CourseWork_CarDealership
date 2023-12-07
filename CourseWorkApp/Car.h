#pragma once
#include <string>
#include <vector>

class Car
{
public:
	Car() = default;

	Car(int);

	Car(const std::string&, const std::string&, int, int, double);

	Car(const std::vector<std::string>&);

	Car(const Car&);

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

private:
	static int dimensionality_;

	std::string brand_;

	std::string model_;

	int yearOfManufacture_ = 0;

	int amount_ = 0;

	double price_ = 0.0;
};
