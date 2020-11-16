#include "map.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{	
	cityMap map = cityMap(22,22);
	map.printMap();
	/*
	//Attempt to open an input file
	if(argc >= 2)
	{
		std::ifstream inFile;
		inFile.open(argv[1]);

		if(inFile.is_open())
		{
			cityMap map = cityMap(inFile);
			map.printMap();
		}
		else
			std::cout << "Unable to open file.\n";
	}
	else	//No input file provided, generate the map via user input
	{
		int xSize, ySize;
		std::cout << "Map width: ";
		std::cin >> xSize;
		std::cout << "Map height: ";
		std::cin >> ySize;
		
		std::string str = "";
		std::cout << "Would you like to choose the distribution (y or n)?: ";
		while(str[0] != 'y' && str[0] != 'n')
		{
			if(str != "")
			{
				std::cin.clear();
				std::cout << "Valid input includes 'y' or 'n': ";
			}
			std::getline (std::cin,str);
			str[0] = tolower(str[0]);
		}
		
		if(str[0] == 'n')
		{
			//Random generation
			double val = (rand() % 100)/100.0;
			std::cout << "\n" << val << std::endl;
			cityMap map = cityMap(xSize,ySize);
			map.printMap();
		}
		else
		{
			//std::cout << "\nNumber of "
		}
	}*/
}
