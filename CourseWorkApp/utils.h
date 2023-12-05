#pragma once
#include <string>
#include <vector>

namespace utils {
	
	template <typename T>
	std::vector<std::vector<T>> parseVector(const std::vector<T>&, size_t);

	void customTerminate(const char*);

	void rebuildFile(const std::string& nameOfFile);
}