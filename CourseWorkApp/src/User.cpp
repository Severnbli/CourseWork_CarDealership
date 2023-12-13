#include "../header/User.h"
#include "../header/utils.h"
#include <iostream>
#include <functional>


User::User()
{
	this->uniqueId_ = utils::generationRandomHash();
}

User::User(int)
{
	this->functionalSetUsername();
	this->functionalSetPassword();
	this->uniqueId_ = utils::generationRandomHash();
}

User::User(const std::string& username, const std::string& password, const std::string& fio)
{
	this->username_ = username;
	this->password_ = password;
	this->fio_ = fio;
	this->uniqueId_ = utils::generationRandomHash();
}

User::User(const User& other)
{
	this->username_ = other.username_;
	this->password_ = other.password_;
	this->fio_ = other.fio_;
	this->uniqueId_ = other.uniqueId_;
}

bool User::operator<(const User& other) const
{
	return this->username_ < other.username_;
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
				if (element >= 'А' && element <= 'я')
				{
					continue;
				}
				if (!std::isalpha(element) && element != ' ')
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

void User::setUniqueId_(const std::string& uniqueId)
{
	this->uniqueId_ = uniqueId;
}

std::string User::getUniqueId() const
{
	return this->uniqueId_;
}

bool compareUsersByUsername(const User& firstObject, const User& secondObject)
{
	return firstObject.getUsername() < secondObject.getUsername();
}

bool compareUsersByUsername(const std::shared_ptr<User>& firstObject, const std::shared_ptr<User>& secondObject)
{
	return firstObject->getUsername() < secondObject->getUsername();
}

bool compareUsersByFio(const User& firstObject, const User& secondObject)
{
	return firstObject.getFio() < secondObject.getFio();
}

bool compareUsersByFio(const std::shared_ptr<User>& firstObject, const std::shared_ptr<User>& secondObject)
{
	return firstObject->getFio() < secondObject->getFio();
}

bool compareUsersByAdmin(const User& firstObject, const User& secondObject)
{
	return static_cast<short>(firstObject.isAdmin()) < static_cast<short>(secondObject.isAdmin());
}

bool compareUsersByAdmin(const std::shared_ptr<User>& firstObject, const std::shared_ptr<User>& secondObject)
{
	return static_cast<short>(firstObject->isAdmin()) < static_cast<short>(secondObject->isAdmin());
}
