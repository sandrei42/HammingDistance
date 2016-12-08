# HammingDistance
A Simple Hamming distance C++ library

###Prerequisites
* C++ [Visual Studio 2015](https://www.visualstudio.com/downloads/)
* [Boost](http://www.boost.org/)

###Structure
* Catch - submodule for Catch unit testing framework
* HammingDistanceLib - actual library
* IntegrationTests - Integration tests (ToDo: improve by adding actual integration tests, find a suitable tool)
* StringTool - Command line tool that computes Hamming distance of two strings
* UnitTest - Unit test for the hamming distance library
* HammingDistance.sln - Visual Studio solution containing all the projects

###Setup
1. Open *HammingDistance.sln* file
2. In the properties of the StringTool project, under Linker->General->Additional Library Directories update the Boost path location with your onw boost instalation location
3. Under Linker->Input->Additional Dependencies verify boost .lib filename
4. Under VC++ Directories->Include directories, update Boost include path
6. Check all configurations and platforms
5. Build solution

###HammingDistanceLib
* offers two functions `hammingDistance` under the `HammingDist` namespace
* Hamming distance is computed per bits
* Assumes the blobs are identical in size, if they differ an exception is thrown
* Grouping is offered so the Hamming distance can be computed at an arbitrary number of bytes
* There are several convenience functions

###UnitTest
* unit tests for the HammingDistanceLib

###IntegrationTests
* integration tests, currently only test the string hamming distance function

###StringTool
* Command line tool which takes as input two ANSI strings, and outputs the hamming distance in characters.
* Other encodings are not supported

####TODOs:
* [ ] Add CMake or makefile rules for cross compiling
* [ ] Create an install target
* [ ] Remove hard coded boost dependency
* [ ] Integration tests for StringTool
* [ ] Add more convenience functions
* [ ] Add UTF-8 support for string tool
