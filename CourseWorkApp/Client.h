#pragma once
#include <string>
#include "User.h"


class Client: public User
{
public:
	Client() = default;
	Client(const std::string&, bool);
	Client(const Client&);
	~Client() = default;
	void setMobileNumber(const std::string&);
	std::string getMobileNumber() const;
	void setStatusOfDriverLicense(bool);
	bool getStatusOfDriverLicense() const;
	bool isAdmin() const override;
private:
	std::string mobileNumber_ = "";
	bool isDriverLicense_ = false;
};
