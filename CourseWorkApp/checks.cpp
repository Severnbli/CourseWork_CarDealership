#include "checks.h"
#include <string>
#include <iostream>
#include <limits>

int checkInt()
{
	while (true) 
	{
		try 
		{
			std::string bufferInput;
			std::cin >> bufferInput;
			if (bufferInput[0] == '0' && bufferInput[1] != '\0') 
			{
				throw std::runtime_error("Ввод некорректен!");
			}
			for (int counter = 0;; counter++) 
			{
				char& charToCheck = bufferInput[counter];
				if (charToCheck == '\0') 
				{
					break;
				}
				if (isdigit(charToCheck)) 
				{
					continue;
				}
				else if (charToCheck == '-' && counter > 0) 
				{
					throw std::runtime_error("Ввод некорректен!");
				}
				else 
				{
					throw std::runtime_error("Ввод некорректен!");
				}
			}
			return stoi(bufferInput);
		}
		catch (const std::runtime_error& error) 
		{
			std::cout << error.what();
		}
		catch (const std::out_of_range& error) 
		{
			std::cout << "Ввод некорректен!";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << " Попробуйте снова: ";
	}
}

int checkIntInRange(int floor, int roof)
{
	while (true) 
	{
		try 
		{
			int enteredNumber = checkInt();
			if (enteredNumber < floor || enteredNumber > roof) 
			{
				throw std::runtime_error("Ввод некорректен!");
			}
			return enteredNumber;
		}
		catch (const std::runtime_error& error) 
		{
			std::cout << error.what();
		}
		std::cout << " Попробуйте снова: ";
	}
}

int checkIntPositive()
{
	while (true) 
	{
		try 
		{
			int enteredNumber = checkInt();
			if (enteredNumber < 0) 
			{
				throw std::runtime_error("Ввод некорректен!");
			}
			return enteredNumber;
		}
		catch (const std::runtime_error& error) 
		{
			std::cout << error.what();
		}
		std::cout << " Попробуйте снова: ";
	}
}

int checkIntNegative()
{
	while (true) 
	{
		try 
		{
			int enteredNumber = checkInt();
			if (enteredNumber > 0) 
			{
				throw std::runtime_error("Ввод некорректен!");
			}
			return enteredNumber;
		}
		catch (const std::runtime_error& error) 
		{
			std::cout << error.what();
		}
		std::cout << " Попробуйте снова: ";
	}
}