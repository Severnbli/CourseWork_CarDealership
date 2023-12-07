#include "menus.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

int adminMenu(Manager&, std::shared_ptr<User>&);

int userMenu(Manager&, std::shared_ptr<User>&);

namespace utils
{
    int patternForMenus(std::string name, std::vector<std::string> fields, bool isClearBefore,
        bool isClearAfter)
    {
        if (isClearBefore)
        {
            system("cls");
        }
        std::cout << name << "\n\n";
        int counter = 1;
        for (std::string& field : fields)
        {
            std::cout << counter++ << " - " << field << ".\n";
        }
        std::cout << "0 - Выход.\n\nВыберите: ";
        int choice = checkIntInRange(0, fields.size());
        if (isClearAfter)
        {
            system("cls");
        }
        return choice;
    }
}

int mainMenu(Manager& manager)
{
    while (true)
    {
        try
        {
            switch (utils::patternForMenus("Автоматизированная система автосалона",
                { "Регистрация", "Вход в систему"}))
            {
            case 1:
            {
                manager.beginRegistration();
                break;
            }
            case 2:
            {
                bool isAuthorize;
                std::shared_ptr<User> authorizedUser;
                manager.beginAuthorization(isAuthorize, authorizedUser);
                if (isAuthorize)
                {
                    if (authorizedUser->isAdmin())
                    {
                        adminMenu(manager, authorizedUser);
                    }
                    else
                    {
                        userMenu(manager, authorizedUser);
                    }
                }
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
        catch (const std::runtime_error &error)
        {
            std::cout << "\n\n" << error.what() << "\n\n";
            system("pause");
        }
    }
}

int adminMenu(Manager& manager, std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
        try
        {
            switch (utils::patternForMenus("АСА - Меню администратора " + authorizedUser->getUsername(), { "Работа с профилями", "Каталог",
                "Добавление авто","Просмотр продаж", "Генерация отчётов" }))
            {
            case 1:
            {
                manager.workingWithProfiles(authorizedUser);
                break;
            }
            case 2:
            {
                manager.workingWithCatalog();
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
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
        catch (const std::runtime_error& error)
        {
            std::cout << "\n\n" << error.what() << "\n\n";
            system("pause");
        }
	}
}

int userMenu(Manager& manager, std::shared_ptr<User>& authorizedUser)
{
	while (true)
	{
		switch (utils::patternForMenus("АСА - Меню пользователя " + authorizedUser->getUsername(), {"Настройка профиля", "Каталог", 
			                               "Избранное", "История покупок"}))
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
        case 4:
        {
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

