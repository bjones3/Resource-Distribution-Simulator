#include <string>
#include <iostream>
#include <fstream>

class mapObject
{
	public:
		mapObject(std::string type = "street") : buildingType(type) {}

		void		setType(std::string type)
		{
			buildingType = type;
		}
		std::string	getType()
		{
			return buildingType;
		}
		int			getxPosition()
		{
			return xpos;
		}
		int			getyPosition()
		{
			return ypos;
		}

	private:
		std::string buildingType;
		int xpos;
		int ypos;
};

class cityMap
{
	public:
		cityMap(std::ifstream * inFile)
		{
			if (!inFile->is_open())
				std::cout << "error on file open" << std::endl;
			*inFile >> xSize >> ySize;
			map = new mapObject*[xSize];
			for (int i = 0; i < xSize; i++)
			{
				map[i] = new mapObject[ySize];
			}
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					std::string type;
					*inFile >> type;
					map[i][j].setType(type);
				}
			}
		}

		cityMap(int newXSize, int newYSize)
		{
			map = new mapObject*[newXSize];
			for (int i = 0; i < newXSize; i++)
			{
				map[i] = new mapObject[newYSize];
			}
			xSize = newXSize;
			ySize = newYSize;
		}

		void printMap()
		{
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					std::cout << map[i][j].getType() << " ";
				}
				std::cout << std::endl;
			}
		}
	private:
		mapObject** map;
		int xSize;
		int ySize;
};