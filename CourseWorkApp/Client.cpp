#include "Client.h"
#include "utils.h"
#include <iostream>

int Client::dimensionality_ = 5;

Client::Client()
{
	this->functionalSetUsername();
	this->functionalSetPassword();
	this->functionalSetMobileNumber();
	this->functionalSetStatusOfDriverLicense();
}


Client::Client(const std::string& mobileNumber, bool isDriverLicense)
{
	this->mobileNumber_ = mobileNumber;
	this->isDriverLicense_ = isDriverLicense;
}

Client::Client(const std::vector<std::string>& data) {
	this->setInfoInVectorStringForm(data);
}

Client::Client(const std::string& username, const std::string& password, const std::string fio, const std::string mobileNumber, bool isDriverLicense)
{
	this->setUsername(username);
	this->setPassword(password);
	this->setFio(fio);
	this->mobileNumber_ = mobileNumber;
	this->isDriverLicense_ = isDriverLicense;
}


Client::Client(const Client& other) : User(other)
{
	this->mobileNumber_ = other.mobileNumber_;
	this->isDriverLicense_ = other.isDriverLicense_;
}

void Client::setInfoInVectorStringForm(const std::vector<std::string>& donor) {
	if (donor.size() != dimensionality_) {
		utils::customTerminate("созданием объекта типа Client");
	}
	this->setUsername(donor[0]);
	this->setPassword(donor[1]);
	this->setFio(donor[2]);
	this->mobileNumber_ = donor[3];
	if (donor[4] == "true" || donor[4] == "1") {
		this->isDriverLicense_ = true;
	}
	else {
		this->isDriverLicense_ = false;
	}
}

std::vector<std::string> Client::getInfoInVectorStringForm() {
	return { this->getUsername(), this->getPassword(), this->getFio(), this->mobileNumber_, std::to_string(isDriverLicense_) };
}

void Client::setMobileNumber(const std::string& mobileNumber)
{
	this->mobileNumber_ = mobileNumber;
}

void Client::functionalSetMobileNumber()
{
	std::cout << "Номер телефона (+375...): ";
	while (true)
	{
		try
		{
			this->mobileNumber_ = utils::checkStringInRange(9, 9, false);
			for (const auto& element : this->mobileNumber_)
			{
				if (!std::isdigit(element))
				{
					throw std::runtime_error("Недопустимые символы!");
				}
			}
			return;
		}
		catch (const std::runtime_error &error)
		{
			std::cout << error.what() << " Попробуйте снова: ";
		}
	}
}


std::string Client::getMobileNumber() const
{
	return this->mobileNumber_;
}

void Client::setStatusOfDriverLicense(bool isDriverLicense)
{
	this->isDriverLicense_ = isDriverLicense;
}

void Client::functionalSetStatusOfDriverLicense()
{
	std::cout << "Лицензия на авто (1 - имеется, 0 - отсутствует): ";
	this->isDriverLicense_ = static_cast<bool>(utils::checkIntInRange(0, 1));
}

bool Client::getStatusOfDriverLicense() const
{
	return this->isDriverLicense_;
}

bool Client::isAdmin() const
{
	return false;
}

int Client::getDimensionality()
{
	return dimensionality_;
}

