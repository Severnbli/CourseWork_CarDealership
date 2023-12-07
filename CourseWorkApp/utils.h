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

	std::string MD5(std::string data);

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
}