#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <ranges>
#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"

auto createBuckets = [](const size_t size)
{
    return std::vector<std::vector<float>>(size);
};

auto determineIndex = [](const float value, const size_t size)
{
    return static_cast<size_t>(value * size);
};

auto fillDataIntoBuckets = [](const std::vector<float>& data)
{
    auto buckets = createBuckets(data.size());
    for (const auto& value : data)
    {
        buckets.at(determineIndex(value, data.size())).push_back(value);
    }
    return buckets;
};

auto lazilySortBuckets = [](const std::vector<std::vector<float>>& data)
{
    return data | std::views::transform([](const std::vector<float>& bucket) {
        auto sortedBucket = bucket;
        std::ranges::sort(sortedBucket);
        return sortedBucket;
    });
};

auto concatenateToOneDimension = [](auto dataView)
{
    return std::vector<float>(dataView | std::views::join);
};

auto bucketSort = [](const std::vector<float>& data)
{
    auto buckets = fillDataIntoBuckets(data);
    auto lazilySortedDataView = lazilySortBuckets(buckets);
    return concatenateToOneDimension(lazilySortedDataView);
};

TEST_CASE("createBuckets")
{
    const size_t size = 5;

    SUBCASE("Check outer Vector")
    {
        auto buckets = createBuckets(size);
        CHECK_EQ(size, buckets.size());
    }

    SUBCASE("Check inner Vector")
    {
        auto buckets = createBuckets(size);
        for(const auto& bucket : buckets)
        {
            CHECK(bucket.empty());
        }
    }
}

TEST_CASE("determineIndex")
{
    SUBCASE("Test with two whole values")
    {
        const size_t output = determineIndex(3.0f, 2);
        const size_t expected = 6;

        CHECK_EQ(expected, output);
    }

    SUBCASE("Test with float and size_t value")
    {
        const size_t output = determineIndex(3.0f, static_cast<size_t>(2.4));
        const size_t expected = static_cast<size_t>(3.0f * static_cast<size_t>(2.4));

        CHECK_EQ(expected, output);
    }
}

TEST_CASE("fillDataIntoBuckets")
{
    SUBCASE("Each value in its own bucket")
    {
        const std::vector<float> data = {0.1f, 0.4f, 0.7f};
        auto buckets = fillDataIntoBuckets(data);

        const size_t index = determineIndex(0.1f, data.size());
        CHECK_EQ(1, buckets[index].size());

        const size_t indexTwo = determineIndex(0.4f, data.size());
        CHECK_EQ(1, buckets[indexTwo].size());

        const size_t indexThree = determineIndex(0.7f, data.size());
        CHECK_EQ(1, buckets[indexThree].size());
    }

    SUBCASE("Multiple values in a single bucket")
    {
        const std::vector<float> data = {0.1f, 0.15f};
        auto buckets = fillDataIntoBuckets(data);

        CHECK_EQ(2, buckets[0].size());
        CHECK_EQ(0, buckets[1].size());
    }
}

TEST_CASE("lazilySortBuckets")
{
    SUBCASE("Single unsorted bucket")
    {
        std::vector<std::vector<float>> buckets = {{0.9f, 0.2f, 0.5f}};
        auto sortedBucketsView = lazilySortBuckets(buckets);
        auto sortedBuckets = std::vector<std::vector<float>>(sortedBucketsView.begin(), sortedBucketsView.end());

        CHECK_EQ(0.2f, sortedBuckets[0][0]);
        CHECK_EQ(0.5f, sortedBuckets[0][1]);
        CHECK_EQ(0.9f, sortedBuckets[0][2]);
    }

    SUBCASE("Multiple unsorted buckets")
    {
        std::vector<std::vector<float>> buckets = {{0.9f, 0.2f}, 
                                                   {0.35f, 0.12f}, 
                                                   {0.71f, 0.65f}};
        auto sortedBucketsView = lazilySortBuckets(buckets);
        auto sortedBuckets = std::vector<std::vector<float>>(sortedBucketsView.begin(), sortedBucketsView.end());

        CHECK_EQ(0.2f, sortedBuckets[0][0]);
        CHECK_EQ(0.9f, sortedBuckets[0][1]);

        CHECK_EQ(0.12f, sortedBuckets[1][0]);
        CHECK_EQ(0.35f, sortedBuckets[1][1]);

        CHECK_EQ(0.65f, sortedBuckets[2][0]);
        CHECK_EQ(0.71f, sortedBuckets[2][1]);
    }
}

TEST_CASE("concatenateToOneDimension")
{
        SUBCASE("Single Bucket")
    {
        std::vector<std::vector<float>> buckets = {{0.1f, 0.2f, 0.3f}};
        auto result = concatenateToOneDimension(buckets);

        CHECK_EQ(3, result.size());
        CHECK_EQ(0.1f, result[0]);
        CHECK_EQ(0.2f, result[1]);
        CHECK_EQ(0.3f, result[2]);
    }

    SUBCASE("Multiple Buckets")
    {
        std::vector<std::vector<float>> buckets = {{0.1f, 0.2f, 0.3f}, 
                                                   {0.4f, 0.5f}, 
                                                   {0.6f, 0.7f, 0.8f, 0.9f}};
        auto result = concatenateToOneDimension(buckets);

        CHECK_EQ(9, result.size());
        CHECK_EQ(0.1f, result[0]);
        CHECK_EQ(0.2f, result[1]);
        CHECK_EQ(0.3f, result[2]);
        CHECK_EQ(0.4f, result[3]);
        CHECK_EQ(0.5f, result[4]);
        CHECK_EQ(0.6f, result[5]);
        CHECK_EQ(0.7f, result[6]);
        CHECK_EQ(0.8f, result[7]);
        CHECK_EQ(0.9f, result[8]);
    }
}

TEST_CASE("Ultimate Final Test")
{
    std::vector<float> inputData = {0.42, 0.32, 0.33, 0.52, 0.37, 0.47, 0.51, 0.78, 0.12, 0.03, 0.66, 0.98};

    std::vector<float> outputSort = bucketSort(inputData);
    std::vector<float> expectedSort = {0.03, 0.12, 0.32, 0.33, 0.37, 0.42, 0.47, 0.51, 0.52, 0.66, 0.78, 0.98};

    CHECK_EQ(expectedSort, outputSort);
}