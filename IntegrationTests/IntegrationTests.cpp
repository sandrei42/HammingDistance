#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

TEST_CASE("Hamming distance for simple strings", "[basic]")
{
    std::string first("This is a test string.");
    std::string second("This is a test string.");

    REQUIRE(HammingDist::hammingDistance(first, second) == 0);

    std::string third("this is a test string.");

    REQUIRE(HammingDist::hammingDistance(first, third) > 0);
}

TEST_CASE("Hamming distance for utf-8 strings", "[basic]")
{
    std::string first("șțăîâȘȚĂÎÂ");
    std::string second("șțăîâȘȚĂÎÂ");

    REQUIRE(HammingDist::hammingDistance(first, second) == 0);

    std::string third("sțăîâȘȚĂÎÂ");
    //This fails, because we don't support UTF-8 yet.
    REQUIRE(HammingDist::hammingDistance(first, third) > 0);
}

TEST_CASE("Hamming distance for different size strings", "[basic][exception]")
{
    std::string first("This is a test string.");
    std::string second("This is a test string");

    REQUIRE_THROWS(HammingDist::hammingDistance(first, second));
}

TEST_CASE("Hamming distance, template function", "[template][exception]")
{
    std::vector<long long> first = { 1, 2, 4, 999 };
    std::vector<long long> second = { 1, 2, 44, 999, 91 };

    REQUIRE_THROWS(HammingDist::hammingDistance(first, second));
}

