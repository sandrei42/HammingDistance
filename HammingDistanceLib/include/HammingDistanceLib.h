#ifdef HAMMINGDISTANCELIB_EXPORTS
#define HDISTANCELIB_API __declspec(dllexport)
#else
#define HDISTANCELIB_API __declspec(dllimport)
#endif

#include <valarray>
#include <string>

namespace HammingDist
{

typedef char blobType;
typedef std::valarray< blobType > blob;
typedef unsigned long long distValue;

HDISTANCELIB_API distValue hammingDistance(const blob& firstBlob, const blob& secondBlob);

//Convenience functions

HDISTANCELIB_API distValue hammingDistance(const std::string& firstBlob, const std::string& secondBlob);

}
