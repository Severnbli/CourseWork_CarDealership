#pragma once
#include <string>
#include "User.h"

class Employee: public User
{
public:
	Employee() = default;
	Employee(const std::string&, double);
	Employee(const Employee&);
	~Employee() = default;
	void setPosition(const std::string&);
	std::string getPosition() const;
	void setAward(double);
	double getAward() const;
	bool isAdmin() const override;
private:
	std::string position_ = "";
	double award_ = 0.0;
};
