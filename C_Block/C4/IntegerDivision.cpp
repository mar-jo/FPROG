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

template <typename T>
using Maybe = std::optional<T>;

auto divide = [](const int numerator) 
{
    return [numerator](const int denominator) -> Maybe<int>
    {
        if (denominator == 0) 
        {
            return std::nullopt;
        }
        return numerator / denominator;
    };
};

TEST_CASE("Integer Division - Should Pass")
{
    int num = 10;
    int denom = 2;

    Maybe<int> result = divide(num)(denom);

    CHECK(result.has_value());
    CHECK_EQ(5, result.value());
}

TEST_CASE("Integer Division - Failure")
{
    int num = 10;
    int denom = 0;

    Maybe<int> result = divide(num)(denom);

    CHECK_FALSE(result.has_value());
}