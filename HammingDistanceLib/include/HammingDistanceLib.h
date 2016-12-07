#ifdef HAMMINGDISTANCELIB_EXPORTS
#define HDISTANCELIB_API __declspec(dllexport)
#else
#define HDISTANCELIB_API __declspec(dllimport)
#endif

#include <valarray>
#include <string>
#include <vector>

namespace HammingDist
{

typedef char blobType;
typedef std::valarray< blobType > blob;
typedef unsigned long long distValue;

HDISTANCELIB_API std::vector<distValue> hammingDistance(const blob& firstBlob, const blob& secondBlob, std::size_t groupSize);

HDISTANCELIB_API distValue hammingDistance(const blob& firstBlob, const blob& secondBlob);

//Convenience functions

HDISTANCELIB_API distValue getTotalGroupedDifference(const std::vector<distValue>& distVec);

HDISTANCELIB_API distValue getTotalDifference(const std::vector<distValue>& distVec);
 
HDISTANCELIB_API distValue hammingDistance(const std::string& firstBlob, const std::string& secondBlob);

}
