#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto bubbleSort = [](const std::vector<int> &data) {
    return std::accumulate(data.begin(), data.end() - 1, data, [](const std::vector<int>& acc, const int& a) 
    {
        return std::accumulate(acc.begin() + 1, acc.end(), acc, [&a](const std::vector<int>& inner_acc, const int& b) 
        {
            std::vector<int> new_data = inner_acc;

            auto it_a = std::find(new_data.begin(), new_data.end(), a);
            auto it_b = std::find(it_a + 1, new_data.end(), b);

            if (it_b == new_data.end()) 
            {
                return new_data;
            }

            *it_a = std::min(a, *it_b);
            *it_b = std::max(a, *it_b);

            return new_data;
        });
    });
};

TEST_CASE("bubbleSort")
{
    SUBCASE("Randomized Vector") 
    {
        std::vector<int> inputData = {5, 2, 8, 1, 9, 3, 7, 4, 6};

        std::vector<int> sortedData = bubbleSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Already sorted vector") 
    {
        std::vector<int> inputData = {1, 2, 3, 4, 5};

        std::vector<int> sortedData = bubbleSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5};

        CHECK_EQ(expectedOutput, sortedData);
    }

    SUBCASE("Reverse sorted vector") 
    {
        std::vector<int> inputData = {5, 4, 3, 2, 1};

        std::vector<int> sortedData = bubbleSort(inputData);
        std::vector<int> expectedOutput = {1, 2, 3, 4, 5};

        CHECK_EQ(expectedOutput, sortedData);
    }
}
