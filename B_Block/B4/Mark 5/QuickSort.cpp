#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

std::function<std::vector<int>(const std::vector<int>&)> quickSort = [](const std::vector<int>& data) -> std::vector<int> 
{
    if (data.size() <= 1) 
    {
        return data;
    }

    int pivot = data.front();

    std::vector<int> less;
    std::vector<int> equal;
    std::vector<int> greater;

    std::accumulate(data.begin(), data.end(), std::make_tuple(std::ref(less), std::ref(equal), std::ref(greater)), [&pivot](const auto& acc, const int val) 
    {
        auto& [less, equal, greater] = acc;

        if (val < pivot)
        {
            less.push_back(val);
        }
        else if (val == pivot) 
        {
            equal.push_back(val);
        }
        else
        {
            greater.push_back(val);
        }

        return acc;
    });

    auto sorted_less = quickSort(less);
    auto sorted_greater = quickSort(greater);

    sorted_less.insert(sorted_less.end(), equal.begin(), equal.end());
    sorted_less.insert(sorted_less.end(), sorted_greater.begin(), sorted_greater.end());

    return sorted_less;
};

TEST_CASE("quickSort")
{
    SUBCASE("Randomized Vector") 
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
}