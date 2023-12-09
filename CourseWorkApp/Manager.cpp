
#include "Manager.h"
#include "User.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <memory>

Manager::Manager(const Manager& other)
{
	this->database_ = other.database_;
}

void Manager::beginRegistration()
{
	std::cout << "АСА - Регистрация\n\n";
	std::shared_ptr<User> registeredPerson = std::make_shared<Client>();
	database_.functionalCheckUsername(registeredPerson);
	std::cout << std::endl;
	registeredPerson->functionalSetPassword();
	database_.fullUpUsersVector(*std::dynamic_pointer_cast<Client>(registeredPerson));
	std::cout << "\nРегистрация успешна!\n\n";
	system("pause");	
}


void Manager::beginAuthorization(bool& isAuthorize, std::shared_ptr<User>& authorizedUser) const
{
	while (true)
	{
		std::cout << "АСА - Авторизация\n\n";
		Client client;
		client.functionalSetUsername();
		std::cout << std::endl;
		client.functionalSetPassword();
		for (const auto& user : database_.getUsersList())
		{
			if (user->getUsername() == client.getUsername() && user->getPassword() == client.getPassword())
			{
				isAuthorize = true;
				authorizedUser = user;
				system("cls");
				return;
			}
		}
		std::cout << "\nНе удалось найти аккаунт по введёным данным.\n\nЖелаете попробовать снова?\n"
			"1 - Да.\n0 - Нет.\n\nВыберите: ";
		if (!static_cast<bool>(utils::checkIntInRange(0, 1)))
		{
			isAuthorize = false;
			system("cls");
			return;
		}
		system("cls");
	}
}

void Manager::workingWithEmployeeProfile(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		switch (utils::patternForMenus("АСА - Меню работы с профилями", { "Настроить свой профиль",
			                               "Обозреватель других существующих профилей" }))
		{
		case 1:
		{
			this->customizeEmloyeeProfile(authorizedUser);
			return;
		}
		case 2:
		{
			this->workingWithProfiles(authorizedUser);
			return;
		}
		default:
		{
			break;
		}
		case 0:
		{
			return;
		}
		}
	}
}

void Manager::workingWithProfiles(std::shared_ptr<User>&)
{
	while (true)
	{
		std::cout << "АСА - Обозреватель профилей\n\n";
		this->database_.showUsersInfo();
		switch (utils::patternForMenus("", {"Сортировка", "Поиск","вф"}, false, false))
		{
		case 1:
			{
			break;
			}
		case 2:
			{
			break;
			}
		case 3:
			{
			break;
			}
		default:
			{
			break;
			}
		case 0:
			{
			return;
			}
		}
	}
}


void Manager::customizeEmloyeeProfile(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		std::cout << "АСА - Меню настройки профиля администратора " << "\n\n";
		this->database_.showUsersInfo(authorizedUser);
		std::cout << "\n\n";
		switch (utils::patternForMenus("Желаете ли изменить какой-нибудь параметр?", {"Логин", "Пароль", "ФИО"}, false, false))
		{
		case 1:
			{
			database_.functionalCheckUsername(authorizedUser);
			break;
			}
		case 2:
			{
			authorizedUser->functionalSetPassword();
			break;
			}
		case 3:
			{
			authorizedUser->functionalSetFio();
			break;
			}
		default:
		{
			break;
		}
		case 0:
		{
			system("cls");
			return;
		}
		}
		system("cls");
	}
}

int Manager::workingWithCatalog()
{
	std::cout << "АСА - Меню работы с каталогом\n\n";
	this->database_.showCarsInfo();
	system("pause");
	return 0;
}
