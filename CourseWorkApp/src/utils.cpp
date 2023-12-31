﻿#include "../header/utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#define UNCORRECTED_INPUT "Ввод неверный!"
#define TRY_AGAIN " Попробуйте снова: "

namespace utils {

    /*template <typename T>
    std::vector<std::vector<T>> parseStringVectorBySize(const std::vector<T>& input, size_t subvectorSize) {
        std::vector<std::vector<T>> result;
        auto begin = input.begin();
        const auto end = input.end();
        while (begin != end) {
            auto subvectorEnd = begin + std::min(subvectorSize, static_cast<size_t>(std::distance(begin, end)));
            result.emplace_back(begin, subvectorEnd);
            begin = subvectorEnd;
        }
        return result;
    }*/

    std::vector<std::vector<std::string>> parseStringVectorBySize(const std::vector<std::string>& input, int subVectorSize)
    {
        std::vector<std::vector<std::string>> result;
        auto begin = input.begin();
        const auto end = input.end();
        while (begin != end) {
            auto subVectorEnd = begin + std::min(subVectorSize, static_cast<int>(std::distance(begin, end)));
            result.emplace_back(begin, subVectorEnd);
            begin = subVectorEnd;
        }
        return result;
    }


    /*template <typename T>
    std::vector<T> parseVectorByStringCondition(const std::vector<T>& input, std::string(*checkCondition)(), const std::string& condition)
    {
        std::vector<T> recipient;
        auto begin = input.begin();
        while (begin != input.end())
        {
            if (begin->checkCondition() == condition)
            {
                recipient.emplace_back(begin);
                input.erase(begin);
            }
            else 
            {
                begin++;
            }
        }
        return recipient;
    }*/

    void customTerminate(const char* info)
    {
        std::cerr << "Ошибка с " << info << '!';
        abort();
    }

    void rebuildFile(const std::string& nameOfFile) // пересоздание / создание файла
    {
        std::ofstream file(nameOfFile, std::ios::out);
        if (!file.is_open())
        {
            customTerminate("пересозданием файла");
        }
        file.close();
    }

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
					if (charToCheck >= 'А' && charToCheck <= 'я')
					{
						throw std::runtime_error(UNCORRECTED_INPUT);

					}
					if (!isdigit(charToCheck))
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
			catch (const std::out_of_range)
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
				bool isPoint = false;
				for (;; counter++) {
					if (bufferInput[counter] == '\0') {
						break;
					}
					if (bufferInput[counter] == '.') {
						if (bufferInput[counter + 1] == '\0' || isPoint) {
							throw std::runtime_error(UNCORRECTED_INPUT);
						}
						isPoint = true;
						counter += 2;
						continue;
					}
					if (bufferInput[counter] >= 'А' && bufferInput[counter] <= 'я')
					{
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
					if (!isdigit(bufferInput[counter])) {
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
				}
				if (isPoint)
				{
					size_t pointPos = bufferInput.find('.');
					return std::stod(bufferInput.substr(0, pointPos + 3));
				}
				return stod(bufferInput);
			}
			catch (const std::runtime_error& error) {
				std::cout << error.what();
			}
			catch (const std::out_of_range) {
				std::cout << UNCORRECTED_INPUT;
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
			std::cin.putback('\n');
			try {
				if (!isSpaces && bufferForCheck.find(' ') != std::string::npos) {
					throw std::runtime_error(UNCORRECTED_INPUT);
				}
				return bufferForCheck;
			}
			catch (std::runtime_error& error) {
				std::cout << error.what() << TRY_AGAIN;
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
			catch (const std::runtime_error& error)
			{
				std::cout << error.what() << TRY_AGAIN;
			}
		}
	}

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
			std::cout << "\u001b[33m" << counter++ << "\u001b[37m" << " - " << field << ".\n";
		}
		std::cout << "\u001b[33m0\u001b[37m - Выход.\n\nВыберите: ";
		int choice = checkIntInRange(0, fields.size());
		if (isClearAfter)
		{
			system("cls");
		}
		return choice;
	}

	void patternForTableHeader(std::vector<std::pair<std::string, int>> header)
    {
		std::cout << '+' << std::string(4, '-');
		for (const auto& pair : header)
		{
			std::cout << '+' << std::string(pair.second, '-');
		}
		std::cout << "+\n|" << std::setw(4) << "№";
		for (const auto& pair : header)
		{
			std::cout << '|' << std::setw(pair.second) << pair.first;
		}
		std::cout << "|\n+" << std::string(4, '-');
		for (const auto& pair : header)
		{
			std::cout << '+' << std::string(pair.second, '-');
		}
		std::cout << "+\n";
    }

	bool areYouConfident()
    {
		std::cout << "Вы уверены в своих действиях?\n\u001b[33m1\u001b[37m - Да.\n"
			   "\u001b[33m0\u001b[37m- Нет.\n\nВыберите: ";
		return static_cast<bool>(checkIntInRange(0, 1));
    }

	std::string generationRandomHash()
    {
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distribution(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    	return std::to_string(std::hash<int>()(distribution(gen) + rand()));
    }

	void showLoadingAnimation(int iterations, int delay, std::string name) {
		const char symbols[] = { '-', '/', '|', '\\' };

    	const std::vector<std::string> colors = {
			"\u001b[31m",
			"\u001b[32m",
			"\u001b[33m",
			"\u001b[34m",
			"\u001b[35m",
			"\u001b[36m"
		};

		const std::vector<std::string> points = {
			".",
			"..",
			"..."
		};

    	for (int i = 0; i < iterations; ++i) {
			std::cout << colors[i % colors.size()] << symbols[i % sizeof(symbols)] << " \u001b[37m" << name << points[i % points.size()] << std::flush;
			stopSystem(delay);
			std::cout << "\r" << std::string(name.length() + 2 + 3, ' ') << "\r";
		}
	}

	void loading() {
		system("cls");

		constexpr int consoleWidth = 100;
		const std::string nameOfSystem = "Автоматизированная система \"Cars Company\" приветствует вас!";

		std::cout << std::setw((consoleWidth - 43) / 2) << std::setfill(' ') << '+' << std::string(nameOfSystem.length(), '=') << "+\n";
    	std::cout << std::setw((consoleWidth - 43) / 2) << std::setfill(' ') << ' ' << nameOfSystem << "\n";
		std::cout << std::setw((consoleWidth - 43) / 2) << std::setfill(' ') << '+' << std::string(nameOfSystem.length(), '=') << "+\n\n\n";

		std::cout << std::string(30, ' ') << "                           " << std::string(23, '$') << '\n';
		std::cout << std::string(30, ' ') << "                          $$$$$     $$     $$    $$\n";
		std::cout << std::string(30, ' ') << "                        $$$$$       $$      $$    $$\n";
		std::cout << std::string(30, ' ') << "                      $$$$$         $$       $$    $$\n";
		std::cout << std::string(30, ' ') << "                   $$$$$            $$        $$    $$\n";
		std::cout << std::string(30, ' ') << "             $$$$$$$$$$$$$$$$$$$$$$$$$         $$    $$\n";
		std::cout << std::string(30, ' ') << "       $$$$$$        $$             $$          $$$$$$$$\n";
		std::cout << std::string(30, ' ') << "  $$$$$$             $$             $$                 $$\n";
		std::cout << std::string(30, ' ') << "$$                   $$             $$                 $$\n";
		std::cout << std::string(30, ' ') << "$$        $$$$$      $$             $$        $$$$$    $$\n";
		std::cout << std::string(30, ' ') << "$$      $$$$$$$$$    $$             $$      $$$$$$$$$   $$\n";
		std::cout << std::string(30, ' ') << "$$$$$ $$$$     $$$ $$$$$$$$$$$$$$$$$$$$$$  $$$$    $$$  $$\n";
		std::cout << std::string(30, ' ') << "      $$$$     $$$                         $$$$    $$$$ \n";
		std::cout << std::string(30, ' ') << "       $$$$    $$$                         $$$$$   $$$$ \n";
		std::cout << std::string(30, ' ') << "        $$$$$ $$$                           $$$$$ $$$$ \n";
		std::cout << std::string(30, ' ') << "          $$$$$$                               $$$$$$ \n";

		std::cout << "\n\n";
		std::cout << std::setw((consoleWidth - 43) / 2 + 15) << std::setfill(' ') << ' ' << "Cars Company качество - это всё!\n\n";

		utils::showLoadingAnimation(25, 150, "Загрузка основных данных");
		utils::showLoadingAnimation(25, 150, "Загрузка дополнительных данных");
		utils::showLoadingAnimation(25, 150, "Загрузка картинок с котиками");

		system("cls");
    }

	void stopSystem(int delay)
    {
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}