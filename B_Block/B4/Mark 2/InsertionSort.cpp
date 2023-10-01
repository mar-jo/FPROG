#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto findInsert = [](const std::vector<int>& data) {
    return [&data](const int& value)
    {
        return std::lower_bound(data.begin(), data.end(), value);
    };
};

auto insertElement = [](const std::vector<int>& data) {
    return [&data](const int& value)
    {
        std::vector<int> copy;
        std::copy(data.begin(), data.end(), std::back_inserter(copy));

        auto insertionPoint = findInsert(copy)(value);
        copy.insert(insertionPoint, value);

        return copy;
    };
};

auto insertionSort = [](const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), std::vector<int>{},
        [](const std::vector<int> acc, const int& value) {
            return insertElement(acc)(value);
        });
};

TEST_CASE("findInsert")
{
    std::vector<int> inputData = {1, 2, 3, 5, 6, 7};

    SUBCASE("Find start value") {
        auto expectedPos = findInsert(inputData)(0);
        CHECK_EQ(expectedPos, inputData.begin());
    }

    SUBCASE("Find middle value") {
        auto expectedPos = findInsert(inputData)(4);
        CHECK_EQ(expectedPos, inputData.begin() + 3);
    }

    SUBCASE("Find last value") {
        auto expectedPos = findInsert(inputData)(8);
        CHECK_EQ(expectedPos, inputData.end());
    }

    SUBCASE("Empty data") {
        std::vector<int> emptyData;

        auto expectedPos = findInsert(emptyData)(3);
        CHECK_EQ(expectedPos, emptyData.end());
    }
}

TEST_CASE("insertElement")
{
    std::vector<int> inputData = {1, 2, 3, 5, 6, 7};

    SUBCASE("Insert start value") {
        auto result = insertElement(inputData)(0);
        std::vector<int> expectedInsert = {0, 1, 2, 3, 5, 6, 7};
        CHECK_EQ(expectedInsert, result);
    }

    SUBCASE("Insert middle value") {
        auto result = insertElement(inputData)(4);
        std::vector<int> expectedInsert = {1, 2, 3, 4, 5, 6, 7};
        CHECK_EQ(expectedInsert, result);
    }

    SUBCASE("Insert last value") {
        auto result = insertElement(inputData)(8);
        std::vector<int> expectedInsert = {1, 2, 3, 5, 6, 7, 8};
        CHECK_EQ(expectedInsert, result);
    }

    SUBCASE("Empty data") {
        std::vector<int> emptyData;

        auto result = insertElement(emptyData)(3);
        std::vector<int> expectedInsert = {3};
        CHECK_EQ(expectedInsert, result);
    }
}

TEST_CASE("Ultimate Final Test")
{
    std::vector<int> inputData = {3, 8, 1, 7, 4, 9, 5, 6, 6, 2};

    std::vector<int> outputSort = insertionSort(inputData);
    std::vector<int> expectedSort = {1, 2, 3, 4, 5, 6, 6, 7, 8, 9};

    CHECK_EQ(expectedSort, outputSort);
}