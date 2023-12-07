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

int checkIntLength(int length) {
	while (true) {
		try {
			int enteredNumber = checkInt();
			int bufferForManipulation = enteredNumber;
			for (int i = 0; i < length; i++) {
				if (bufferForManipulation == 0) {
					throw std::runtime_error("Ввод некорректен!");
				}
				bufferForManipulation /= 10;
			}
			if (bufferForManipulation > 9) {
				throw std::runtime_error("Ввод некорректен!");
			}
			return enteredNumber;
		}
		catch (const std::runtime_error& error) {
			std::cerr << error.what();
		}
		std::cout << " Попробуйте снова: ";
	}
}

double checkDouble() {
	while (true) {
		try {
			std::string bufferInput;
			std::cin >> bufferInput;
			int counter = 0;
			if (bufferInput[counter] == '-') {
				if (bufferInput[counter + 1] == '\0') {
					throw std::runtime_error("Неверный ввод!");
				}
				counter++;
			}
			for (bool isFirstPoint = true;; counter++) {
				if (bufferInput[counter] == '\0') {
					break;
				}
				if (bufferInput[counter] == '.') {
					if (bufferInput[counter + 1] == '\0' || !isFirstPoint) {
						throw std::runtime_error("Неверный ввод!");
					}
					isFirstPoint = false;
					counter += 2;
				}
				if (!isdigit(bufferInput[counter])) {
					throw std::runtime_error("Неверный ввод!");
				}
			}
			return stod(bufferInput);
		}
		catch (const std::runtime_error& error) {
			std::cerr << error.what();
		}
		catch (const std::out_of_range& error) {
			std::cerr << "Введённое слишком велико!";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << " Попробуйте ещё раз: ";
	}
}

double checkDoubleInRange(double floor, double roof) {
	while (true) {
		try {
			double enteredNumber = checkDouble();
			if (enteredNumber < floor || enteredNumber > roof) {
				throw std::runtime_error("Неверный ввод!");
			}
			return enteredNumber;
		}
		catch (const std::runtime_error& error) {
			std::cerr << error.what();
		}
		std::cout << " Попробуйте снова: ";
	}
}

std::string checkString(bool isSpaces) {
	while (true) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::string bufferForCheck;
		std::getline(std::cin, bufferForCheck);
		try {
			if (!isSpaces && bufferForCheck.find(' ') != std::string::npos) {
				throw std::runtime_error("Неверный ввод!");
			}
			return bufferForCheck;
		}
		catch (std::runtime_error& error) {
			std::cout << error.what() << " Попробуйте снова: ";
			std::cin.putback('\n');
		}
	}
}