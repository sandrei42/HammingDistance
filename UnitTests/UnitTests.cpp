#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

TEST_CASE("Hamming distance is 42", "[basic]")
{
	HammingDist::blob firstBlob = { 3 };
	HammingDist::blob secondBlob = { 0 };
	REQUIRE( HammingDist::hammingDistance(firstBlob, secondBlob) == 0 );
}
