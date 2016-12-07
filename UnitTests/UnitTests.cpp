#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

TEST_CASE("Hamming distance is 42", "[basic]")
{
	HammingDist::blob firstBlob = { 42 };
	HammingDist::blob secondBlob = { 42 };
	REQUIRE( HammingDist::hammingDistance(firstBlob, secondBlob) == 0 );
}

TEST_CASE("Hamming distance grouping", "[basic]")
{
	HammingDist::blob firstBlob = { 3 , 21 };
	HammingDist::blob secondBlob = { 0 , 21 };
	std::vector<HammingDist::distValue> output = HammingDist::hammingDistance(firstBlob, secondBlob, 1);
	REQUIRE(output[0] == 0);
	REQUIRE(output[1] == 0);
}
