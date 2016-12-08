#ifndef HAMMING_DISTANCE_LIB_H_20161208
#define HAMMING_DISTANCE_LIB_H_20161208

#ifdef HAMMINGDISTANCELIB_EXPORTS
#define HDISTANCELIB_API __declspec(dllexport)
#else
#define HDISTANCELIB_API __declspec(dllimport)
#endif

#include <valarray>
#include <string>
#include <vector>
#include <exception>

namespace HammingDist
{

typedef char blobType;					///< Underlining type for the memory blob
typedef std::valarray< blobType > blob; ///< A memory blob
typedef unsigned long long distValue;   ///< Output value for the hamming distance

//************************************
// Method:    HammingDistEx
// FullName:  HammingDist::HammingDistEx
// Access:    public 
// Description: Exception thrown by hammingDistance functions to denote an error in input data
//************************************
struct HammingDistEx : public std::exception
{
    const char* what() const noexcept
    {
        return "Error: Input blobs are of different sizes, or bad grouping size!";
    }
};

//************************************
// Method:    hammingDistance
// FullName:  HammingDist::hammingDistance
// Access:    public 
// Description: Computes the Hamming distance between two blobs, grouping the result by a multiplier of 8bits
// @param     const blob & firstBlob  - first memory blob for comparison
// @param     const blob & secondBlob - second memory blob for comparison
// @param     std::size_t groupSize   - grouping size multiplyer
//										Eg: groupSize of 1 will group the result every 8 bits
//											groupSize of 4 will group the result every 32 bits
// @returns   std::vector<HammingDist::distValue> - vector containg the group results,
//													the size of the vector will be size of the blob/groupSize
// @throws	  HammingDistEx - if the blobs are not equal or the grouping value doesn't exactly split the input
//************************************
HDISTANCELIB_API std::vector<distValue> hammingDistance(const blob& firstBlob, const blob& secondBlob, std::size_t groupSize);

//************************************
// Method:    hammingDistance
// FullName:  HammingDist::hammingDistance
// Access:    public 
// Description: Computes the bit wise Hamming distance between two blobs of memory
//				Hamming distance represents the number of bits that are different between the two blobs
//				Eg:   1010010100100 - first blob
//					  0110010000100 - second blob
//		              1100000100000 - difference (3 bits differ)
//					  Hamming distance: 3
// @param     const blob & firstBlob  - first memory blob for comparison
// @param     const blob & secondBlob - second memory blob for comparison
// @returns   distValue - number of bits which differ between the first and second blobs
//						  0 if the blobs are bitwise equal
// @throws	  HammingDistEx - if the blobs are not equal
//************************************
HDISTANCELIB_API distValue hammingDistance(const blob& firstBlob, const blob& secondBlob);

//************************************
// Method:    getTotalGroupedDifference
// FullName:  HammingDist::getTotalGroupedDifference
// Access:    public 
// Description: Convenience function to compute the total distance of grouped hamming distance result
//				It also reduces the distance value per group to 1
// @param     const std::vector<distValue> & distVec - distance vector
// @returns   distValue - total computed distance
//************************************
HDISTANCELIB_API distValue getTotalGroupedDifference(const std::vector<distValue>& distVec);

//************************************
// Method:    getTotalDifference
// FullName:  HammingDist::getTotalDifference
// Access:    public 
// Description: Convenience function to compute the total distance of grouped hamming distance result
// @param     const std::vector<distValue> & distVec - distance vector
// @returns   distValue - total computed distance
//************************************
HDISTANCELIB_API distValue getTotalDifference(const std::vector<distValue>& distVec);
 
//************************************
// Method:    hammingDistance
// FullName:  HammingDist::hammingDistance
// Access:    public 
// Description: Convenience function to compute the number of characters that are different between two strings
//				 NOTE: Assumes ASCII characters, UTF-8 strings are not supported
// @param     const std::string & firstBlob	 - first string
// @param     const std::string & secondBlob - second string
// @returns   distValue - number of characters which are different
// @throws	  HammingDistEx - if the strings are not equal
//************************************
HDISTANCELIB_API distValue hammingDistance(const std::string& firstBlob, const std::string& secondBlob);

}

#endif
