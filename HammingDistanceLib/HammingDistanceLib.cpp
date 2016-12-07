#include <include/HammingDistanceLib.h>

#include <bitset>
#include <climits>

using namespace HammingDist;

HDISTANCELIB_API distValue HammingDist::hammingDistance(const std::string& firstBlob, const std::string& secondBlob)
{
	blob tempFirst(firstBlob.c_str(), firstBlob.size());
	blob tempSecond(secondBlob.c_str(), secondBlob.size());
	return hammingDistance(tempFirst, tempSecond);
}

HDISTANCELIB_API distValue HammingDist::hammingDistance(const blob& firstBlob, const blob& secondBlob)
{
	distValue distance = 0;
	if (firstBlob.size() != secondBlob.size())
	{
		return -1;
	}

	blob outBlob = firstBlob ^ secondBlob;

	for (const unsigned char& e : outBlob)
	{
		std::bitset<CHAR_BIT> element(e);
		distance += element.count();
	}

	return distance;
}
