#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

TEST_CASE("Hamming distance for simple strings", "[basic]")
{
    std::string first("Andrei");
    std::string second("Andrei");

    REQUIRE(HammingDist::hammingDistance(first, second) == 0);
}


TEST_CASE("Hamming distance, template function", "[template]")
{
    std::vector<double> first = { 1.0, 2.0, 4.4, 999.91 };
    std::vector<double> second = { 1.0, 2.0, 4.4, 999.91 };

    REQUIRE(HammingDist::hammingDistance(first, second) == 0);
}