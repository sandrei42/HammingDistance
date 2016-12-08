#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>

#include <HammingDistanceLib.h>

#include <random>
#include <functional>

TEST_CASE("Hamming distance", "[basic]")
{
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

//ToDo Negative testing

TEST_CASE("Hamming distance grouping", "[basic]")
{
	HammingDist::blob firstBlob = { 1 , 21 };
	HammingDist::blob secondBlob = { 0 , 21 };
	std::vector<HammingDist::distValue> output = HammingDist::hammingDistance(firstBlob, secondBlob, 1);
	REQUIRE(output[0] == 1);
	REQUIRE(output[1] == 0);
	output = HammingDist::hammingDistance(firstBlob, secondBlob, 2);
	REQUIRE(output[0] == 1);
}
