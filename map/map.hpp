#include <string>
#include <iostream>
#include <fstream>

class mapObject
{
	public:
		mapObject(int type = 0) : buildingType(type) {}

		void		setType(int type)
		{
			buildingType = type;
		}
		int	getType()
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
		int buildingType;
		int xpos;
		int ypos;
};

class cityMap
{
	public:
		cityMap(std::ifstream & inFile)
		{
			if (!inFile.is_open())
				std::cout << "error on file open" << std::endl;
			inFile >> xSize >> ySize;
			init();
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					int type;
					inFile >> type;
					map[i][j].setType(type);
				}
			}
		}

		cityMap(int newXSize, int newYSize) 
			: xSize( newXSize ), ySize( newYSize )
		{
			init();
			generateRoad( 10 );
			generateFactory( 5 );
			generateWorkplace( 3 );
			generateHouse();
		}
		
		cityMap(int newXSize, int newYSize, int roadCount, int factoryCount, int workCount) 
			: xSize( newXSize ), ySize( newYSize ), roadConc( roadCount ), facConc( factoryCount), workConc
		{
			init();
			generateRoad( roadConc );
			generateFactory( factoryConc );
			generateWorkplace( workConc );
			generateHouse();
		}
		
		void generateRoad(int conc)
		{
			int type = 1;
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					if(i % conc == 0 || j % conc == 0)
						map[i][j].setType(type);
				}
			}
		}
		
		void generateFactory(int conc)
		{
			int type = 2;
			int newFactory = 0;
			bool placedFactory;
			for (int i = 0; i < xSize; i++)
			{
				placedFactory = false;
				for (int j = 0; j < ySize; j++)
				{
					if(checkType(i,j,0))
					{
						if(checkType(i+1,j,1) || checkType(i,j+1,1) || checkType(i-1,j,1) || checkType(i,j-1,1))
						{
							bool empty = true;
							for(int k = i; k < i+4; k++)
								for(int l = j; l < j+4; l++)
									if(k >= xSize || l >= ySize || map[k][l].getType() != 0)
										empty = false;
							
							if(empty)
							{
								if(newFactory % conc == 0)
								{
									placedFactory = true;
									for(int k = i; k < i+4; k++)
										for(int l = j; l < j+4; l++)
											map[k][l].setType(type);
								}
								j += 3;
								newFactory++;
							}
						}
					}
				}
				if(placedFactory)
					i += 3;
			}
		}
		
		void generateWorkplace(int conc)
		{
			int type = 3;
			int newFactory = 0;
			bool placedFactory;
			for (int i = 0; i < xSize; i++)
			{
				placedFactory = false;
				for (int j = 0; j < ySize; j++)
				{
					if(checkType(i,j,0))
					{
						if(checkType(i+1,j,1) || checkType(i,j+1,1) || checkType(i-1,j,1) || checkType(i,j-1,1))
						{
							bool empty = true;
							for(int k = i; k < i+3; k++)
								for(int l = j; l < j+3; l++)
									if(k >= xSize || l >= ySize || map[k][l].getType() != 0)
										empty = false;
							
							if(empty)
							{
								if(newFactory % conc == 0)
								{
									placedFactory = true;
									for(int k = i; k < i+3; k++)
										for(int l = j; l < j+3; l++)
											map[k][l].setType(type);
								}
								j += 2;
								newFactory++;
							}
						}
					}
				}
				if(placedFactory)
					i += 2;
			}
		}
			
		void generateHouse()
		{
			int type = 4;
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					if(checkType(i,j,0))
						if(checkType(i+1,j,1) || checkType(i,j+1,1) || checkType(i-1,j,1) || checkType(i,j-1,1))	
							map[i][j].setType(type);
				}
			}
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
		int roadConc; 
		int facConc;
		int workConc;
		
		/**
		 * Initializes the map's grid using xSize and ySize.
		 */
		void init()
		{
			map = new mapObject*[xSize];
			for (int i = 0; i < xSize; i++)
			{
				map[i] = new mapObject[ySize];
			}
		}
		
		bool checkType(int xpos, int ypos, int type)
		{
			if(xpos >= xSize || xpos < 0 || ypos >= ySize || ypos < 0)
				return false;
				
			return map[xpos][ypos].getType() == type;
			
		}
};
