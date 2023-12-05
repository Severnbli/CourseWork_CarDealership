#include "utils.h"
#include <iostream>
#include <fstream>

namespace utils {

    /*template <typename T>
    std::vector<std::vector<T>> parseVectorBySize(const std::vector<T>& input, size_t subvectorSize) {
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

    std::vector<std::vector<std::string>> parseVectorBySize(const std::vector<std::string>& input, int subVectorSize)
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

}