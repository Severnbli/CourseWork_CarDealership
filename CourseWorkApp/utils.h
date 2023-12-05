#pragma once
#include <string>
#include <vector>

namespace utils {
	
	/*template <typename T>
	std::vector<std::vector<T>> parseVectorBySize(const std::vector<T>&, size_t);*/

	std::vector<std::vector<std::string>> parseVectorBySize(const std::vector<std::string>&, int);

	//template <typename T>
	//std::vector<T> parseVectorByStringCondition(const std::vector<T>&, std::string(*)(), const std::string&);

	void customTerminate(const char*);

	void rebuildFile(const std::string& nameOfFile);
}