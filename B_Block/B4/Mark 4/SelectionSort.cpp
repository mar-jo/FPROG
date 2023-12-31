#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto calculateRemainingElements = [](const std::vector<int>& data)
{
    return [&data](const std::vector<int>& acc) -> std::vector<int>
    {
        std::vector<int> remaining_elements;

        std::copy_if(data.begin(), data.end(), std::back_inserter(remaining_elements), [&](const int& val) 
        {
            return std::find(acc.begin(), acc.end(), val) == acc.end();
        });

        return remaining_elements;
    };
};

auto findMinElement = [](const std::vector<int>& acc)
{
    return [acc](const std::vector<int>& remaining_elements) -> std::vector<int>
    {
        std::vector<int> copy_acc = acc;

        if (!remaining_elements.empty()) 
        {
            int min_val = *std::min_element(remaining_elements.begin(), remaining_elements.end());
            copy_acc.push_back(min_val);
        }

        return copy_acc;
    };
};

auto selectionSort = [](const std::vector<int>& data) -> std::vector<int>
{
    return std::accumulate(data.begin(), data.end(), std::vector<int>(), [&](const std::vector<int>& acc, const int&)
    {
        return findMinElement(acc)(calculateRemainingElements(data)(acc));
    });
};

TEST_CASE("selectionSort")
{
    SUBCASE("Randomized Vector") 
    {
        std::vector<int> inputData = {5, 2, 8, 1, 9, 3, 7, 4, 6};

        std::vector<int> sortedData = selectionSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Already sorted vector") 
    {
        std::vector<int> inputData = {1, 2, 3, 4, 5};

        std::vector<int> sortedData = selectionSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5};

        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Reverse sorted vector") 
    {
        std::vector<int> inputData = {5, 4, 3, 2, 1};

        std::vector<int> sortedData = selectionSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5};

        CHECK_EQ(expectedOutput, sortedData);
    }
}