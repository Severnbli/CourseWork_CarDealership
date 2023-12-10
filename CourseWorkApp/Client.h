#pragma once
#include <string>
#include <vector>
#include "User.h"


class Client: public User
{
public:
	Client() = default;

	Client(int);

	Client(const std::string&, bool);

	Client(const std::string&, const std::string&, const std::string = "", const std::string = "", bool = false);

	Client(const std::vector<std::string>&);

	Client(const Client&);

	bool operator<(const Client&);

	void setInfoInVectorStringForm(const std::vector<std::string>&) override;

	std::vector<std::string> getInfoInVectorStringForm() override;

	void setMobileNumber(const std::string&);

	void functionalSetMobileNumber();

	std::string getMobileNumber() const;

	void setStatusOfDriverLicense(bool);

	void functionalSetStatusOfDriverLicense();

	bool getStatusOfDriverLicense() const;

	bool isAdmin() const override;

	int getDimensionality() override;

	void printInfoTableForm() const override;

private:
	static int dimensionality_;

	std::string mobileNumber_;

	bool isDriverLicense_ = false;
};

bool compareClientsByMobileNumber(const Client&, const Client&);

bool compareClientsByMobileNumber(const std::shared_ptr<Client>&, const std::shared_ptr<Client>&);

bool compareClientsByDriverLicense(const Client&, const Client&);

bool compareClientsByDriverLicense(const std::shared_ptr<Client>&, const std::shared_ptr<Client>&);