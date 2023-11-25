#include "User.h"

User::User(const std::string& username, const std::string& password, const std::string& fio)
{
	this->setUsername(username);
	this->setPassword(password);
	this->setFio(fio);
}

User::User(const User& other)
{
	this->username_ = other.username_;
	this->password_ = other.password_;
	this->fio_ = other.fio_;
}

void User::setUsername(const std::string& username)
{
	this->username_ = username;
}

std::string User::getUsername() const
{
	return this->username_;
}

void User::setPassword(const std::string& password)
{
	this->password_ = password;
}

std::string User::getPassword() const
{
	return this->password_;
}

void User::setFio(const std::string& fio)
{
	this->fio_ = fio;
}

std::string User::getFio() const
{
	return this->fio_;
}

