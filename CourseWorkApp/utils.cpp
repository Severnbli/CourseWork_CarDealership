#include "utils.h"
#include <iostream>
#include <fstream>

namespace utils {

    template <typename T>
    std::vector<std::vector<T>> parseVector(const std::vector<T>& input, size_t subvectorSize) {
        std::vector<std::vector<T>> result;

        auto begin = input.begin();
        const auto end = input.end();

        while (begin != end) {
            auto subvectorEnd = begin + std::min(subvectorSize, static_cast<size_t>(std::distance(begin, end)));
            result.emplace_back(begin, subvectorEnd);
            begin = subvectorEnd;
        }

        return result;
    }

    void customTerminate(const char* info)
    {
        std::cerr << "Ошибка с " << info << '!';
        abort();
    }

    void rebuildFile(const std::string& nameOfFile) //пересоздание/создание файла
    {
        std::ofstream file(nameOfFile, std::ios::out);
        if (!file.is_open())
        {
            customTerminate("пересозданием файла");
        }
        file.close();
    }

}