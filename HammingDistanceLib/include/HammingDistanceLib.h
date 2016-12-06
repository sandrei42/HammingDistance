#ifdef HAMMINGDISTANCELIB_EXPORTS
#define HDISTANCELIB_API __declspec(dllexport)
#else
#define HDISTANCELIB_API __declspec(dllimport)
#endif

class HDISTANCELIB_API HammingDistanceLib {
public:
	HammingDistanceLib();
};

HDISTANCELIB_API int hammingDistance(void);
