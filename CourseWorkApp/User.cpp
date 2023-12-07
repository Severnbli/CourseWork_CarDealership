#include "User.h"
#include "utils.h"
#include <iostream>
#include <functional>

User::User(int)
{
	this->functionalSetUsername();
	this->functionalSetPassword();
}

User::User(const std::string& username, const std::string& password, const std::string& fio)
{
	this->username_ = username;
	this->password_ = password;
	this->fio_ = fio;
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

void User::functionalSetUsername()
{
	std::cout << "Имя пользователя (3 - 12 символа (ов)): ";
	while (true)
	{
		try {
			this->username_ = utils::checkStringInRange(3, 12, false);
			for (const auto& element : this->username_)
			{
				if (element >= 'А' && element <= 'я')
				{
					continue;
				}
				if (!isalnum(element) && element != '_')
				{
					throw std::runtime_error("Недопустимые символы!");
				}
			}
			return;
		}
		catch (const std::runtime_error& error)
		{
			std::cout << error.what() << " Попробуйте снова: ";
		}
	}
}


std::string User::getUsername() const
{
	return this->username_;
}

void User::setUnmodifiedPassword(const std::string& password)
{
	this->password_ = password;
}

void User::setPassword(const std::string& password)
{
	this->password_ = std::to_string(std::hash<std::string>()(password));
}

void User::functionalSetPassword()
{
	std::cout << "Пароль (8 - 16 символов): ";
	this->password_ = std::to_string(std::hash<std::string>()(utils::checkStringInRange(8, 16, false)));
}


std::string User::getPassword() const
{
	return this->password_;
}

void User::setFio(const std::string& fio)
{
	this->fio_ = fio;
}

void User::functionalSetFio()
{
	std::cout << "ФИО (до 30 символов): ";
	while (true)
	{
		try {
			this->fio_ = utils::checkStringInRange(0, 30, true);
			for (const auto& element : this->fio_)
			{
				if (!std::isalpha(element))
				{
					throw std::runtime_error("Недопустимые символы!");
				}
			}
			return;
		}
		catch (const std::runtime_error& error)
		{
			std::cout << error.what() << " Попробуйте снова: ";
		}
	}
}


std::string User::getFio() const
{
	return this->fio_;
}

