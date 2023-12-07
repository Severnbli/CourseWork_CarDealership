#include <string>
#include <iostream>
#include <limits>

#define UNCORRECTED_INPUT "Ввод неверный!"
#define TRY_AGAIN " Попробуйте снова: "

namespace utils
{
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
					throw std::runtime_error(UNCORRECTED_INPUT);
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
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
					else
					{
						throw std::runtime_error(UNCORRECTED_INPUT);
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
				std::cout << UNCORRECTED_INPUT;
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << TRY_AGAIN;
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
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return enteredNumber;
			}
			catch (const std::runtime_error& error)
			{
				std::cout << error.what();
			}
			std::cout << TRY_AGAIN;
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
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return enteredNumber;
			}
			catch (const std::runtime_error& error)
			{
				std::cout << error.what();
			}
			std::cout << TRY_AGAIN;
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
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return enteredNumber;
			}
			catch (const std::runtime_error& error)
			{
				std::cout << error.what();
			}
			std::cout << TRY_AGAIN;
		}
	}

	int checkIntLength(int length) {
		while (true) {
			try {
				int enteredNumber = checkInt();
				int bufferForManipulation = enteredNumber;
				for (int i = 0; i < length; i++) {
					if (bufferForManipulation == 0) {
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
					bufferForManipulation /= 10;
				}
				if (bufferForManipulation > 9) {
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return enteredNumber;
			}
			catch (const std::runtime_error& error) {
				std::cerr << error.what();
			}
			std::cout << TRY_AGAIN;
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
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
					counter++;
				}
				for (bool isFirstPoint = true;; counter++) {
					if (bufferInput[counter] == '\0') {
						break;
					}
					if (bufferInput[counter] == '.') {
						if (bufferInput[counter + 1] == '\0' || !isFirstPoint) {
							throw std::runtime_error(UNCORRECTED_INPUT);
						}
						isFirstPoint = false;
						counter += 2;
					}
					if (!isdigit(bufferInput[counter])) {
						throw std::runtime_error(UNCORRECTED_INPUT);
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
			std::cout << TRY_AGAIN;
		}
	}

	double checkDoubleInRange(double floor, double roof) {
		while (true) {
			try {
				double enteredNumber = checkDouble();
				if (enteredNumber < floor || enteredNumber > roof) {
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return enteredNumber;
			}
			catch (const std::runtime_error& error) {
				std::cerr << error.what();
			}
			std::cout << TRY_AGAIN;
		}
	}

	double checkDoublePositive()
	{
		while (true)
		{
			try
			{
				double enteredNumber = checkDouble();
				if (enteredNumber < 0)
				{
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return enteredNumber;
			}
			catch (const std::runtime_error& error)
			{
				std::cout << error.what();
			}
			std::cout << TRY_AGAIN;
		}
	}

	std::string checkString(bool isSpaces) {
		while (true) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::string bufferForCheck;
			std::getline(std::cin, bufferForCheck);
			try {
				if (!isSpaces && bufferForCheck.find(' ') != std::string::npos) {
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return bufferForCheck;
			}
			catch (std::runtime_error& error) {
				std::cout << error.what() << TRY_AGAIN;
				std::cin.putback('\n');
			}
		}
	}

	std::string checkStringInRange(int floor, int roof, bool isSpaces)
	{
		while (true)
		{
			try
			{
				std::string bufferForCheck = checkString(isSpaces);
				if (bufferForCheck.size() < floor || bufferForCheck.size() > roof)
				{
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return bufferForCheck;
			}
			catch (const std::runtime_error &error)
			{
				std::cout << error.what() << TRY_AGAIN;
			}
		}
	}
}
