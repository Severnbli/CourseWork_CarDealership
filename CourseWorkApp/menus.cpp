﻿#include "menus.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

int adminMenu(Manager&, std::shared_ptr<User>&);

int userMenu(Manager&, std::shared_ptr<User>&);

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
                break;
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
        catch (const utils::CustomExcept &error)
        {
            std::cout << error.what() << "\n\n";
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
            switch (utils::patternForMenus("АСА - Меню администратора " + authorizedUser->getUsername(), { 
                "Работа с профилями",
            	"Каталог",
            	"Генерация отчётов"
            }))
            {
            case 1:
            {
                manager.workingWithEmployeeProfile(authorizedUser);
                break;
            }
            case 2:
            {
                manager.workingEmployeeWithCatalog(authorizedUser);
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
            manager.customizeClientProfile(authorizedUser);
            break;
        }
        case 2:
        {
            manager.workingClientWithCatalog(authorizedUser);
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
            break;
        }
        case 0:
        {
            return 0;
        }
		}
	}
}

