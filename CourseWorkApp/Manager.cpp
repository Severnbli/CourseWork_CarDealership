
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
			break;
		}
		case 2:
		{
			this->workingWithProfiles(authorizedUser);
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

void Manager::customizeClientProfile(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		std::cout << "АСА - Меню настройки профиля клиента\n\n";
		this->database_.showUsersInfo(authorizedUser);
		std::cout << "\n\n";
		switch (utils::patternForMenus("Желаете ли изменить какой-нибудь параметр?",
			{ "Логин", "Пароль", "ФИО", "Номер телефона",
				"Наличие вод. удостоверения", "Удаление аккаунта" }, false, false))
		{
		case 1:
		{
			std::cout << '\n';
			database_.functionalCheckUsername(authorizedUser);
			break;
		}
		case 2:
		{
			std::cout << '\n';
			authorizedUser->functionalSetPassword();
			break;
		}
		case 3:
		{
			std::cout << '\n';
			authorizedUser->functionalSetFio();
			break;
		}
		case 4:
		{
			std::cout << '\n';
			std::dynamic_pointer_cast<Client>(authorizedUser)->functionalSetMobileNumber();
			break;
		}
		case 5:
		{
			std::cout << '\n';
			std::dynamic_pointer_cast<Client>(authorizedUser)->functionalSetStatusOfDriverLicense();
			break;
		}
		case 6:
			{
			std::cout << '\n';
			this->database_.deleteUser(authorizedUser);
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
		system("cls");
	}
}

void Manager::customizeEmloyeeProfile(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		std::cout << "АСА - Меню настройки профиля администратора\n\n";
		this->database_.showUsersInfo(authorizedUser);
		std::cout << "\n\n";
		switch (utils::patternForMenus("Желаете ли изменить какой-нибудь параметр?", 
			{ "Логин",
				"Пароль",
				"ФИО",
				"Должность",
				"Удаление аккаунта"
			}, false, false))
		{
		case 1:
		{
			std::cout << '\n';
			this->database_.functionalCheckUsername(authorizedUser);
			break;
		}
		case 2:
		{
			std::cout << '\n';
			authorizedUser->functionalSetPassword();
			break;
		}
		case 3:
		{
			std::cout << '\n';
			authorizedUser->functionalSetFio();
			break;
		}
		case 4:
		{
			std::cout << '\n';
			std::dynamic_pointer_cast<Employee>(authorizedUser)->functionalSetPosition();
			break;
		}
		case 5:
			{
			std::cout << '\n';
			this->database_.deleteUser(authorizedUser);
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
		system("cls");
	}
}

void Manager::workingWithProfiles(std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		system("cls");
		std::cout << "АСА - Обозреватель профилей\n\n";
		this->database_.showUsersInfo();
		switch (utils::patternForMenus("", {
			"Сортировка", 
			"Поиск",
			"Настройка аккаунтов",
			"Выдача прав администратора",
			"Очистить базу данных"
		}, false, false))
		{
		case 1:
			{
			this->database_.sortUsersVector();
			break;
			}
		case 2:
			{
			this->database_.searchInUsersVector();
			break;
			}
		case 3:
			{
			std::cout << "\nВведите номер редактируемого аккаунта: ";
			const size_t selectedNumber = utils::checkIntInRange(1, this->database_.getUsersVectorSize());
			system("cls");
			auto selectedUser = this->database_.getUserByPositionInVector(selectedNumber - 1);
			try
			{
				if (selectedUser->isAdmin())
				{
					this->customizeEmloyeeProfile(selectedUser);
				}
				else
				{
					this->customizeClientProfile(selectedUser);
				}
			}
			catch (const utils::CustomExcept &error)
			{
				std::cout << error.what() << "\n\n";
				system("pause");
			}
			break;
			}
		case 4:
			{
			std::cout << "\nВведите номер редактируемого аккаунта: ";
			this->database_.updateAccessRights(this->database_.getUserByPositionInVector(utils::checkIntInRange(1, this->database_.getUsersVectorSize()) - 1));
			break;
			}
		case 5:
			{
			std::cout << '\n';
				if (utils::isYouConfident())
				{
					this->database_.clearDatabase(authorizedUser->getUsername());
				}
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

void Manager::workingWithCatalog()
{
	std::cout << "АСА - Меню работы с каталогом\n\n";
	this->database_.showCarsInfo();
	switch (utils::patternForMenus("" , {"Сортировка", "Поиск"}))
	{
	case 1:
		{
		break;
		}
	case 2:
		{
		break;
		}
	default:
		{
		break;
		}
	case 0:
		{
		break;
		}
	}
	return;
}
