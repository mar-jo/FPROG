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

struct QuadraticSolution 
{
    double x1;
    double x2;
};

auto solve_quadratic = [](const double& a)
{
    return [a](const double& b)
    {
        return [a, b](const double& c) -> std::optional<QuadraticSolution> 
        {
            if (a == 0) 
            {
                return std::nullopt;
            }

            double discriminant = b * b - 4 * a * c;

            if (discriminant < 0) 
            {
                return std::nullopt;
            }

            QuadraticSolution solution;
            solution.x1 = (-b + std::sqrt(discriminant)) / (2 * a);
            solution.x2 = (-b - std::sqrt(discriminant)) / (2 * a);
            
            return solution;
        };
    };
};

TEST_CASE("Quadratic Solver - Should Pass")
{
    double a = 1, b = -3, c = 2;
    auto result = solve_quadratic(a)(b)(c);

    CHECK(result.has_value());
    CHECK_EQ(2, result->x1);
    CHECK_EQ(1, result->x2);
}

TEST_CASE("Quadratic Solver - Should Fail")
{
    double a = 1, b = 0, c = 1;
    auto result = solve_quadratic(a)(b)(c);

    CHECK_FALSE(result.has_value());
}