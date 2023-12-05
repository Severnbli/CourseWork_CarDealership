#include "Manager.h"
#include "User.h"
#include "checks.h"
#include "menus.h"
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
	std::cout << "Введите логин: ";
	std::string username;
	while (true)
	{
		try
		{
			std::cin >> username;
			if (!database_.isValidUsername(username))
			{
				throw std::runtime_error("Такое имя пользователя занято. Попробуйте снова: ");
			}
			break;
		}
		catch (const std::runtime_error &error)
		{
			std::cout << error.what();
		}
	}
	std::cout << "Введите пароль: ";
	std::string password;
	std::cin >> password;
	std::cout << "Введите ФИО: ";
	std::string fio;
	std::cin >> fio;
	database_.fullUpUsersVector(Client(username, password, fio));
	std::cout << "\nРегистрация успешна!\n\n";
	system("pause");
}


void Manager::beginAuthorization(bool& isAuthorize, std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		std::cout << "АСА - Авторизация\n\n";
		std::cout << "Введите логин: ";
		std::string username;
		std::cin >> username;
		std::cout << "Введите пароль: ";
		std::string password;
		std::cin >> password;
		for (const auto& user : database_.getUsersList())
		{
			if (user->getUsername() == username && user->getPassword() == password)
			{
				isAuthorize = true;
				authorizedUser = user;
				system("cls");
				return;
			}
		}
		std::cout << "\nНе удалось найти аккаунт по введёным данным.\n\nЖелаете попробовать снова?\n"
			"1 - Да.\n0 - Нет.\n\nВыберите: ";
		if (!checkIntInRange(0, 1))
		{
			isAuthorize = false;
			system("cls");
			return;
		}
		system("cls");
	}
}

int Manager::workingWithProfiles(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		switch (patternForMenus("АСА - Меню работы с профилями", { "Настроить свой профиль",
			"Настроить другие существующие профили" }))
		{
		case 1:
		{
			this->customizeAuthorizedUserProfile(authorizedUser);
			break;
		}
		case 2:
		{
			this->database_.showUsersInfo();
			system("pause");
			break;
		}
		default:
		{
			std::cout << "Ошибка! Выход из системы...";
			system("pause");
			return 1;
		}
		case 0:
		{
			return 0;
		}
		}
	}
}

int Manager::customizeAuthorizedUserProfile(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		std::cout << "АСА - Меню настройки своего профиля\n\n";
		this->database_.showUsersInfo(authorizedUser);
		std::cout << "\n\n";
		switch (patternForMenus("Желаете ли изменить какой-нибудь параметр?", {"Логин", "Пароль", "ФИО"}, false, false))
		{
		case 1:
			{
			std::cout << "Введите новый логин: ";
			std::string newUsername;
			while (true)
			{
				try
				{
					std::cin >> newUsername;
					if (!database_.isValidUsername(newUsername))
					{
						throw std::runtime_error("Такое имя пользователя занято. Попробуйте снова: ");
					}
					break;
				}
				catch (const std::runtime_error& error)
				{
					std::cout << error.what();
				}
			}
			authorizedUser->setUsername(newUsername);
			system("cls");
			break;
			}
		case 2:
			{
			std::cout << "Введите новый пароль: ";
			std::string newPassword;
			std::cin >> newPassword;
			authorizedUser->setPassword(newPassword);
			system("cls");
			break;
			}
		case 3:
			{
			std::cout << "Введите новое ФИО: ";
			std::string newFIO;
			std::cin >> newFIO;
			authorizedUser->setFio(newFIO);
			system("cls");
			break;
			}
		default:
		{
			system("cls");
			std::cout << "Ошибка! Выход из системы...";
			system("pause");
			return 1;
		}
		case 0:
		{
			system("cls");
			return 0;
		}
		}
	}
}

int Manager::workingWithCatalog()
{
	std::cout << "АСА - Меню работы с каталогом\n\n";
	this->database_.showCarsInfo();
	system("pause");
	return 0;
}
