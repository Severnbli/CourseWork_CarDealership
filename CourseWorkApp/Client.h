#pragma once
#include <string>
#include <vector>
#include "User.h"


class Client: public User
{
public:
	Client() = default;

	Client(const std::string&, bool);

	Client(const std::string&, const std::string&, const std::string = "", const std::string = "", bool = false);

	Client(const std::vector<std::string>&);

	Client(const Client&);

	~Client() = default;

	void setInfoInVectorStringForm(const std::vector<std::string>&);

	std::vector<std::string> getInfoInVectorStringForm();

	void setMobileNumber(const std::string&);

	std::string getMobileNumber() const;

	void setStatusOfDriverLicense(bool);

	bool getStatusOfDriverLicense() const;

	bool isAdmin() const override;

private:
	static int dimensionality_;

	std::string mobileNumber_;

	bool isDriverLicense_ = false;
};
