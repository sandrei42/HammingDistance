#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

#include <random>
#include <functional>

TEST_CASE("Hamming distance", "[basic]")
{
    SECTION("empty values")
    {
        HammingDist::blob firstBlob;
        HammingDist::blob secondBlob;
        REQUIRE(HammingDist::hammingDistance(firstBlob, secondBlob) == 0);
    }

    SECTION("one value simple test")
    {
        HammingDist::blob firstBlob = { 42 };
        HammingDist::blob secondBlob = { 42 };
        REQUIRE(HammingDist::hammingDistance(firstBlob, secondBlob) == 0);
        REQUIRE(HammingDist::hammingDistance(secondBlob, firstBlob) == 0);
        secondBlob = { 43 };
        REQUIRE(HammingDist::hammingDistance(firstBlob, secondBlob) != 0);
        REQUIRE(HammingDist::hammingDistance(secondBlob, firstBlob) != 0);
    }

    SECTION("One value, cheking bits")
    {
        HammingDist::blob firstBlob = { 0 };
        char val = 0;
        for (size_t i = 1; i <= CHAR_BIT; ++i)
        {
            val <<= 1;
            val |= 1;
            HammingDist::blob secondBlob = { val };
            REQUIRE(HammingDist::hammingDistance(firstBlob, secondBlob) == i);
        }
    }

    SECTION("One value, cheking bits, rotate one")
    {
        HammingDist::blob firstBlob = { 0 };
        char val = 1;
        for (size_t i = 1; i <= CHAR_BIT; ++i)
        {
            HammingDist::blob secondBlob = { val };
            REQUIRE(HammingDist::hammingDistance(firstBlob, secondBlob) == 1);
            val <<= 1;
        }
    }
}

TEST_CASE("Hamming distance random", "[random]")
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 255);
    auto dice = std::bind(distribution, generator);

    size_t elements = dice();

    std::vector<HammingDist::blobType> tempData;
    for (size_t elem = 0; elem < elements; ++elem)
    {
        tempData.push_back(dice());
    }
    HammingDist::blob first(&tempData[0], elements);

    tempData.clear();
    for (size_t elem = 0; elem < elements; ++elem)
    {
        tempData.push_back(dice());
    }
    HammingDist::blob second(&tempData[0], elements);

    tempData.clear();
    for (size_t elem = 0; elem < elements; ++elem)
    {
        tempData.push_back(dice());
    }
    HammingDist::blob third(&tempData[0], elements);

    SECTION("Distance properties")
    {
        REQUIRE(HammingDist::hammingDistance(first, second) >= 0);
        REQUIRE(HammingDist::hammingDistance(first, second) == HammingDist::hammingDistance(second, first));
        REQUIRE(HammingDist::hammingDistance(first, second) <= HammingDist::hammingDistance(first, second)
                                                             + HammingDist::hammingDistance(second, third));
        if (HammingDist::hammingDistance(first, second) == 0)
        {
            REQUIRE((first - second).sum() == 0);
        }
    }
}

TEST_CASE("Hamming distance errors", "[exceptions]")
{
    SECTION("Simple size difference")
    {
        HammingDist::blob firstBlob = { 42 };
        HammingDist::blob secondBlob = { 42 , 41 };
        REQUIRE_THROWS(HammingDist::hammingDistance(firstBlob, secondBlob));
    }

    SECTION("Random sizes")
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, 255);
        auto dice = std::bind(distribution, generator);

        size_t elements = dice();

        std::vector<HammingDist::blobType> tempData;
        for (size_t elem = 0; elem < elements; ++elem)
        {
            tempData.push_back(dice());
        }
        HammingDist::blob first(&tempData[0], elements);

        do
        {
            elements = dice();
        } while (elements == first.size());
        tempData.clear();
        for (size_t elem = 0; elem < elements; ++elem)
        {
            tempData.push_back(dice());
        }
        HammingDist::blob second(&tempData[0], elements);

        REQUIRE_THROWS(HammingDist::hammingDistance(first, second));
    }
}

TEST_CASE("Hamming distance grouping", "[group][basic]")
{
    HammingDist::blob firstBlob = { 1 , 21 };
    HammingDist::blob secondBlob = { 0 , 21 };
    std::vector<HammingDist::distValue> output = HammingDist::hammingDistance(firstBlob, secondBlob, 1);
    REQUIRE(output[0] == 1);
    REQUIRE(output[1] == 0);
    output = HammingDist::hammingDistance(firstBlob, secondBlob, 2);
    REQUIRE(output[0] == 1);
}

TEST_CASE("Hamming distance on int values", "[group][int]")
{
    SECTION("Identical vectors")
    {
        std::vector<int> first = { 0, 1, 2, 3, 4, 5 };
        std::vector<int> second = { 0, 1, 2, 3, 4, 5 };

        size_t group = sizeof(int);

        HammingDist::blob firstBlob(reinterpret_cast<HammingDist::blobType*>(&first[0]), first.size()*group);
        HammingDist::blob secondBlob(reinterpret_cast<HammingDist::blobType*>(&second[0]), second.size()*group);

        std::vector<HammingDist::distValue> output = HammingDist::hammingDistance(firstBlob, secondBlob, group);

        REQUIRE(output.size() == first.size());
        REQUIRE(HammingDist::getTotalDifference(output) == 0);
        REQUIRE(HammingDist::getTotalGroupedDifference(output) == 0);
    }

    SECTION("Different vectors")
    {
        std::vector<int> first = { 0, 1, 2, 0, 4, 5 };
        std::vector<int> second = { 0, 1, 2, 3, 4, 5 };

        size_t group = sizeof(int);

        HammingDist::blob firstBlob(reinterpret_cast<HammingDist::blobType*>(&first[0]), first.size()*group);
        HammingDist::blob secondBlob(reinterpret_cast<HammingDist::blobType*>(&second[0]), second.size()*group);

        std::vector<HammingDist::distValue> output = HammingDist::hammingDistance(firstBlob, secondBlob, group);

        REQUIRE(output.size() == first.size());
        REQUIRE(HammingDist::getTotalDifference(output) == 2);
        REQUIRE(HammingDist::getTotalGroupedDifference(output) == 1);
    }
}

TEST_CASE("Hamming distance grouping erros", "[group][exceptions]")
{
    HammingDist::blob firstBlob = { 1 , 21 };
    HammingDist::blob secondBlob = { 0 , 21 , 43 };
    REQUIRE_THROWS( HammingDist::hammingDistance(firstBlob, secondBlob, 1) );
    secondBlob = firstBlob;
    REQUIRE_THROWS( HammingDist::hammingDistance(firstBlob, secondBlob, 3) );
}
