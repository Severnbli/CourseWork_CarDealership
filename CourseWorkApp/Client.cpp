#include "Client.h"

Client::Client(const std::string& mobileNumber, bool isDriverLicense)
{
	this->mobileNumber_ = mobileNumber;
	this->isDriverLicense_ = isDriverLicense;
}

Client::Client(const Client& other)
{
	this->mobileNumber_ = other.mobileNumber_;
	this->isDriverLicense_ = other.isDriverLicense_;
}

void Client::setMobileNumber(const std::string& mobileNumber)
{
	this->mobileNumber_ = mobileNumber;
}

std::string Client::getMobileNumber() const
{
	return this->mobileNumber_;
}

void Client::setStatusOfDriverLicense(bool isDriverLicense)
{
	this->isDriverLicense_ = isDriverLicense;
}

bool Client::getStatusOfDriverLicense() const
{
	return this->isDriverLicense_;
}


bool Client::isAdmin() const
{
	return false;
}

