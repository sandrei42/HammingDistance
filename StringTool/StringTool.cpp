#include <HammingDistanceLib.h>

#include <iostream>

#include <boost/program_options.hpp>

int main(int argc, char** argv)
{
	namespace po = boost::program_options;

	std::string first;
	std::string second;
	try
	{
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("first,f", po::value<std::string>(&first)->required(), "first string to compare to")
			("second,s", po::value<std::string>(&second)->required(), "second string to compare to")
			;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help"))
		{
			std::cout << desc << std::endl;
			return 0;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cout << "Unknown error!" << std::endl;
		return 1;
	}

	std::cout << "Hamming distance: " << HammingDist::hammingDistance( first , second ) << std::endl;
	return 0;
}
