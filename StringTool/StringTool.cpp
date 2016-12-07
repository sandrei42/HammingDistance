#include <HammingDistanceLib.h>

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Hamming distance: " << HammingDist::hammingDistance( "a" , "b" ) << std::endl;
	return 0;
}