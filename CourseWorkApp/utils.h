#pragma once
#include <string>
#include <vector>

namespace utils {
	
	/*template <typename T>
	std::vector<std::vector<T>> parseStringVectorBySize(const std::vector<T>&, size_t);*/

	std::vector<std::vector<std::string>> parseStringVectorBySize(const std::vector<std::string>&, int);

	//template <typename T>
	//std::vector<T> parseVectorByStringCondition(const std::vector<T>&, std::string(*)(), const std::string&);

	void customTerminate(const char*);

	void rebuildFile(const std::string& nameOfFile);

	int checkInt();

	int checkIntInRange(int, int);

	int checkIntPositive();

	int checkIntNegative();

	int checkIntLength(int);

	double checkDouble();

	double checkDoubleInRange(double, double);

	double checkDoublePositive();

	std::string checkString(bool = true);

	std::string checkStringInRange(int, int, bool = true);

	int patternForMenus(std::string, std::vector<std::string>, bool = true, bool = true);

	void patternForTableHeader(std::vector<std::pair<std::string, int>>);

	class CustomExcept
	{
	public:
		CustomExcept()
		{
			this->content_ = "custom except";
		}
		CustomExcept(std::string content)
		{
			this->content_ = content;
		}
		CustomExcept(const CustomExcept& other)
		{
			this->content_ = other.content_;
		}
		~CustomExcept() = default;
		std::string what() const
		{
			return this->content_;
		}
	private:
		std::string content_;
	};

	bool areYouConfident();
}