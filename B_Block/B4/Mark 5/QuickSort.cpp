#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <tuple>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto splitData = [](const std::vector<int>& data)
{
    return [&data](const int pivot) -> std::tuple<std::vector<int>, std::vector<int>>
    {
        std::vector<int> less, greater;

        std::accumulate(data.begin() + 1, data.end(), std::make_tuple(&less, &greater), [&pivot](const auto& acc, const int val) 
        {
            auto& [copy_less, copy_greater] = acc;

            if (val <= pivot)
            {
                copy_less->push_back(val);
            }
            else
            {
                copy_greater->push_back(val);
            }

            return acc;
        });

        return {less, greater};
    };
};

std::function<std::vector<int>(const std::vector<int>&)> quickSort = [](const std::vector<int>& data) -> std::vector<int> 
{
    if (data.size() <= 1) 
    {
        return data;
    }

    int pivot = data.front();
    auto [less, greater] = splitData(data)(pivot);

    auto sorted_less = quickSort(less);
    auto sorted_greater = quickSort(greater);

    sorted_less.push_back(pivot);
    sorted_less.insert(sorted_less.end(), sorted_greater.begin(), sorted_greater.end());

    return sorted_less;
};

TEST_CASE("quickSort")
{
    SUBCASE("Randomized Vector - even") 
    {
        std::vector<int> inputData = {5, 2, 8, 1, 3, 7, 4, 6};

        std::vector<int> sortedData = quickSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5, 6, 7, 8};
        
        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Randomized Vector - uneven") 
    {
        std::vector<int> inputData = {5, 2, 8, 1, 9, 3, 7, 4, 6};

        std::vector<int> sortedData = quickSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Already sorted vector") 
    {
        std::vector<int> inputData = {1, 2, 3, 4, 5};

        std::vector<int> sortedData = quickSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5};

        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Reverse sorted vector") 
    {
        std::vector<int> inputData = {5, 4, 3, 2, 1};

        std::vector<int> sortedData = quickSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5};

        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Single value vector") 
    {
        std::vector<int> inputData = {1};

        std::vector<int> sortedData = quickSort(inputData);
        std::vector<int> expectedOutput = {1};

        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Empty vector") 
    {
        std::vector<int> inputData = {};

        std::vector<int> sortedData = quickSort(inputData);
        std::vector<int> expectedOutput = {};

        CHECK_EQ(expectedOutput, sortedData);
    }
}