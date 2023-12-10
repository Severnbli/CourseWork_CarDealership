#pragma once
#include <string>
#include <vector>
#include "User.h"

class Employee: public User
{
public:
	Employee() = default;

	Employee(int);

	Employee(const std::string&, double);

	Employee(const std::string&, const std::string&, const std::string & = "", const std::string & = "", double = 0.0);

	Employee(const std::vector<std::string>&);

	Employee(const Employee&);

	bool operator<(const Employee&) const;

	void setInfoInVectorStringForm(const std::vector<std::string>&) override;

	std::vector<std::string> getInfoInVectorStringForm() override;

	void setPosition(const std::string&);

	void functionalSetPosition();

	std::string getPosition() const;

	void setAward(double);

	void functionalSetAward();

	double getAward() const;

	bool isAdmin() const override;

	int getDimensionality() override;

	void printInfoTableForm() const override;

private:
	static int dimensionality_;

	std::string position_;

	double award_ = 0.0;
};

bool compareEmployeesByPosition(const Employee&, const Employee&);

bool compareEmployeesByPosition(const std::shared_ptr<Employee>&, const std::shared_ptr<Employee>&);

bool compareEmployeesByAward(const Employee&, const Employee&);

bool compareEmployeesByAward(const std::shared_ptr<Employee>&, const std::shared_ptr<Employee>&);