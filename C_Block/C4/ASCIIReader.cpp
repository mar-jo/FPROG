#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <optional>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <memory>

template <typename T>
using Maybe = std::optional<T>;

auto readFile = [](const std::string& fileName) -> Maybe<std::string>
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        return std::nullopt;
    }

    return std::string((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
};

auto isASCII = [](const std::string& content) -> bool 
{
    return std::all_of(content.begin(), content.end(), [](char ch)
    {
        return static_cast<unsigned char>(ch) <= 127;
    });
};

auto processFileContent = [](const std::string& fileName) -> Maybe<std::string>
{
    Maybe<std::string> content = readFile(fileName);

    if (!content.has_value() || !isASCII(content.value()))
    {
        return std::nullopt;
    }

    return content;
};

int main() 
{
    Maybe<std::string> result = processFileContent("ascii.txt");

    if (result.has_value())
    {
        std::cout << "File content (ASCII Format): " << "\n";
        std::cout << result.value() << "\n";
    }
    else
    {
        std::cout << "Error while reading file..." << "\n";
    }

    return 0;
}