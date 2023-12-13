#include "../header/Client.h"
#include <iomanip>
#include "../header/utils.h"
#include <iostream>

int Client::dimensionality_ = 6;

Client::Client(int) : User()
{
	this->functionalSetUsername();
	std::cout << '\n';
	this->functionalSetPassword();
	std::cout << '\n';
	this->functionalSetFio();
	std::cout << '\n';
	this->functionalSetMobileNumber();
	std::cout << '\n';
	this->functionalSetStatusOfDriverLicense();
}

Client::Client(const std::string& mobileNumber, bool isDriverLicense) : User()
{
	this->mobileNumber_ = mobileNumber;
	this->isDriverLicense_ = isDriverLicense;
}

Client::Client(const std::vector<std::string>& data)
{
	Client::setInfoInVectorStringForm(data);
}

Client::Client(const std::string& username, const std::string& password, const std::string fio, const std::string mobileNumber, bool isDriverLicense) : User()
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

bool Client::operator<(const Client& other)
{
	return this->mobileNumber_ < other.mobileNumber_;
}

void Client::setInfoInVectorStringForm(const std::vector<std::string>& donor) {
	if (donor.size() != dimensionality_) {
		utils::customTerminate("созданием объекта типа Client");
	}
	this->setUsername(donor[0]);
	this->setUnmodifiedPassword(donor[1]);
	this->setFio(donor[2]);
	this->mobileNumber_ = donor[3];
	if (donor[4] == "true" || donor[4] == "1") {
		this->isDriverLicense_ = true;
	}
	else {
		this->isDriverLicense_ = false;
	}
	this->setUniqueId_(donor[5]);
}

std::vector<std::string> Client::getInfoInVectorStringForm()
{
	return { this->getUsername(), this->getPassword(), this->getFio(), this->mobileNumber_, std::to_string(isDriverLicense_), this->getUniqueId() };
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
				if (element >= 'А' && element <= 'я')
				{
					throw std::runtime_error("Недопустимые символы!");
				}
				if (!std::isdigit(element))
				{
					throw std::runtime_error("Недопустимые символы!");
				}
			}
			this->mobileNumber_ = "+375" + this->mobileNumber_;
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

void Client::printInfoTableForm() const
{
	std::cout << "|" << std::setw(12) << this->getUsername() << '|' << std::setw(30)
		<< this->getFio() << '|' << std::setw(3);
	if (this->isAdmin())
	{
		std::cout << "Да";
	}
	else
	{
		std::cout << "Нет";
	}
	std::cout << '|' << std::string(12, ' ') << '|' << std::string(8, ' ')
		<< '|' << std::setw(13) << this->mobileNumber_ << '|' << std::setw(3);
	if (this->isDriverLicense_)
	{
		std::cout << "Да";
	}
	else
	{
		std::cout << "Нет";
	}
	std::cout << '|' << std::endl;
	std::cout << "+" << std::string(4, '-') << '+' << std::string(12, '-')
		<< '+' << std::string(30, '-') << '+' << std::string(3, '-') << '+';
	std::cout << std::string(12, '-') << '+' << std::string(8, '-') << '+'
		<< std::string(13, '-') << '+' << std::string(3, '-') << "+\n";
}

bool compareClientsByMobileNumber(const Client& firstObject, const Client& secondObject)
{
	return firstObject.getMobileNumber() < secondObject.getMobileNumber();
}

bool compareClientsByMobileNumber(const std::shared_ptr<Client>& firstObject, const std::shared_ptr<Client>& secondObject)
{
	return firstObject->getMobileNumber() < secondObject->getMobileNumber();
}

bool compareClientsByDriverLicense(const Client& firstObject, const Client& secondObject)
{
	return static_cast<short>(firstObject.getStatusOfDriverLicense()) < static_cast<short>(secondObject.getStatusOfDriverLicense());
}

bool compareClientsByDriverLicense(const std::shared_ptr<Client>& firstObject, const std::shared_ptr<Client>& secondObject)
{
	return static_cast<short>(firstObject->getStatusOfDriverLicense()) < static_cast<short>(secondObject->getStatusOfDriverLicense());
}

