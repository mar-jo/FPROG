#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto selectionSort = [](const std::vector<int>& data) -> std::vector<int>
{
    return std::accumulate(data.begin(), data.end(), std::vector<int>(), [&](const std::vector<int>& acc, const int elem) -> std::vector<int> 
    {
        std::vector<int> new_acc = acc;
        
        if (new_acc.empty()) 
        {
            new_acc.push_back(elem);
        } 
        else 
        {
            auto insert_pos = std::upper_bound(new_acc.begin(), new_acc.end(), elem);
            new_acc.insert(insert_pos, elem);
        }
        
        return new_acc;
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