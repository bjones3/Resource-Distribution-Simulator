#include "map.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
	std::ifstream inFile;
	inFile.open(argv[1]);

	//cityMap map = cityMap(10,10);
	cityMap map = cityMap(inFile);
	map.printMap();
}
