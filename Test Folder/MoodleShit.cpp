#include <iostream>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cmath>

using namespace std;

auto area = [](const auto width, const auto height) {
    return std::abs(width * height);
};

auto circumference = [](const auto width, const auto height) {
    return std::abs(2 * (width + height));
};

auto diagonal = [](const auto width, const auto height) {
    return std::sqrt(std::pow(width, 2) + std::pow(height, 2));
};

TEST_CASE ("Rectangle")
{
  auto Rectangle = rect(3,4);
  CHECK_EQ (12, rect.area());
  CHECK_EQ (14, rect.circumfence());
  CHECK_EQ (5, rect.diagonal());
} 