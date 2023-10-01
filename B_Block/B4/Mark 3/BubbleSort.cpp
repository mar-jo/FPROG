#include <iostream>
#include <string>
#include <vector>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto bubbleSort = [](const std::vector<int> &data) {
    std::vector<int> copy_data = data;

    std::for_each(copy_data.begin(), copy_data.end() - 1, [&copy_data](const int& a) 
    {
        std::for_each(copy_data.begin() + 1, copy_data.end(), [&copy_data, &a](const int& b) 
        {
            auto it_a = &a - copy_data.data();
            auto it_b = &b - copy_data.data();

            auto minimum = std::min(a, b);
            auto maximum = std::max(a, b);

            copy_data[it_a] = minimum;
            copy_data[it_b] = maximum;
        });
    });

    return copy_data;
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
