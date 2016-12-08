#include <include/HammingDistanceLib.h>

#include <bitset>
#include <climits>
#include <numeric>

using namespace HammingDist;


HDISTANCELIB_API std::vector<distValue> HammingDist::hammingDistance(const blob& firstBlob, const blob& secondBlob, std::size_t groupSize)
{
	if (firstBlob.size() != secondBlob.size() || (firstBlob.size() % groupSize) != 0)
	{
		throw HammingDistEx();
	}

	std::vector<distValue> output;
	output.reserve(firstBlob.size() / groupSize);
	for (size_t i = 0; i < firstBlob.size(); i += groupSize)
	{
		std::slice slice(i, groupSize, 1);
		output.push_back( hammingDistance(firstBlob[slice], secondBlob[slice]) );
	}
	return output;
}

HDISTANCELIB_API distValue HammingDist::hammingDistance(const blob& firstBlob, const blob& secondBlob)
{
	if (firstBlob.size() != secondBlob.size())
	{
		throw HammingDistEx();
	}

	blob outBlob = firstBlob ^ secondBlob;
	distValue distance = 0;
	for (const blobType& e : outBlob)
	{
		std::bitset<CHAR_BIT> element(e);
		distance += element.count();
	}

	return distance;
}

HDISTANCELIB_API distValue HammingDist::getTotalGroupedDifference(const std::vector<distValue>& distVec)
{
	return std::accumulate( distVec.begin(), distVec.end(), 0, [](auto a, auto b) { return a + ( (b != 0) ? 1 : 0 ); } );
}

HDISTANCELIB_API distValue HammingDist::getTotalDifference(const std::vector<distValue>& distVec)
{
	return std::accumulate(distVec.begin(), distVec.end(), (distValue)0 );
}

HDISTANCELIB_API distValue HammingDist::hammingDistance(const std::string& firstBlob, const std::string& secondBlob)
{
	blob tempFirst(firstBlob.c_str(), firstBlob.size());
	blob tempSecond(secondBlob.c_str(), secondBlob.size());
	return getTotalGroupedDifference( hammingDistance(tempFirst, tempSecond, 1) );
}

