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

using Matrix = std::vector<std::vector<double>>;
using Result = std::optional<Matrix>;
using Determinant = std::optional<double>;

auto determinant = [](const Matrix& matrix) -> Determinant
{
    if(matrix.size() != 2 && matrix.at(0).size() != 2)
    {
        return std::nullopt;
    }

    return matrix.at(0).at(0) * matrix.at(1).at(1) - matrix.at(0).at(1) * matrix.at(1).at(0);
};

auto invertMatrix = [](const Matrix& matrix) -> Result 
{
    Determinant det = determinant(matrix);

    if (!det.has_value() || det.value() == 0) 
    {
        return std::nullopt;
    }

    Matrix inverted = {
        {matrix.at(1).at(1) / det.value(), -matrix.at(0).at(1) / det.value()},
        {-matrix.at(1).at(0) / det.value(), matrix.at(0).at(0) / det.value()}
    };

    return inverted;
};

TEST_CASE("Inverted Matrix - Should Pass")
{
    Matrix matrix = {{4, 3}, {2, 1}};
    Result inverted = invertMatrix(matrix);

    Matrix expected_inverted = {{-0.5, 1.5}, {1, -2}};

    CHECK(inverted.has_value());
    
    CHECK_EQ(inverted.value()[0][0], expected_inverted[0][0]);
    CHECK_EQ(inverted.value()[0][1], expected_inverted[0][1]);
    CHECK_EQ(inverted.value()[1][0], expected_inverted[1][0]);
    CHECK_EQ(inverted.value()[1][1], expected_inverted[1][1]);
}

TEST_CASE("Inverted Matrix - Should Fail")
{
    Matrix matrix = {{2, 4}, {1, 2}};
    Result inverted = invertMatrix(matrix);

    CHECK_FALSE(inverted.has_value());
}