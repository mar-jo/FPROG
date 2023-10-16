#include <iostream>
#include <functional>
#include <numeric>
#include <optional>
#include <string>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

auto fileStream = [](const std::string& fileName) -> std::optional<std::ifstream>
{
    std::ifstream File(fileName);

    return File ? std::make_optional(File) : std::nullopt;
};

auto readIntegersFromFile = [](const std::ifstream& file) -> std::optional<std::vector<int>>
{
    std::vector<int> values((std::istream_iterator<int>(file)), std::istream_iterator<int>());
    return values.empty() ? std::nullopt : std::make_optional(values);
};

auto sumIntegersFromVector = [](const std::vector<int>& values) -> std::optional<std::vector<int>>
{

};

TEST_CASE("Sum Integers from File")
{

}