#include "utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

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
					if (bufferInput[counter] >= 'А' && bufferInput[counter] <= 'я')
					{
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
					if (!isdigit(bufferInput[counter])) {
						throw std::runtime_error(UNCORRECTED_INPUT);
					}
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

	bool isYouConfident()
    {
		std::cout << "Вы уверены в своих действиях?\n1 - Да.\n0 - Нет.\n\nВыберите: ";
		return static_cast<bool>(checkIntInRange(0, 1));
    }
}