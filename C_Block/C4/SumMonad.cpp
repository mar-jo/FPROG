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
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

auto fileStream = [](const std::string& fileName) -> std::optional<std::shared_ptr<std::ifstream>>
{
    auto file = std::make_shared<std::ifstream>(fileName);

    if(!file->is_open())
    {
        return std::nullopt;
    }

    return file;
};

auto readIntegersFromFile = [](const std::optional<std::shared_ptr<std::ifstream>>& optFile) -> std::optional<std::vector<int>>
{
    if (!optFile.has_value())
    {
        return std::nullopt;
    }

    return std::vector<int>(std::istream_iterator<int>(*optFile->get()), std::istream_iterator<int>());
};

auto sumIntegersFromVector = [](const std::optional<std::vector<int>>& optValues) -> std::optional<int>
{
    if(!optValues.has_value() || optValues->empty()) 
    {
        return std::nullopt;
    }
    
    return std::make_optional(std::accumulate(optValues->begin(), optValues->end(), 0));
};

TEST_CASE("Sum Integers from File")
{
    auto result = sumIntegersFromVector(readIntegersFromFile(fileStream("sum.txt")));

    CHECK(result.has_value());
    CHECK_EQ(21, result);
}