#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

TEST_CASE("Hamming distance is 42", "[basic]")
{
    std::string first("Andrei");
    std::string second("Andrei");

    REQUIRE(HammingDist::hammingDistance(first, second) == 0);
}
