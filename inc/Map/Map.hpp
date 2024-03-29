
#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include "../rds.hpp"

#define FACT_SIZE 	4
#define WORK_SIZE 	3
#define HOME_SIZE	1

#define NONE		0
#define ROAD		1
#define FACT		2
#define WORK		3
#define HOME		4
#define INTER		5


class cityMap
{
	public:
		struct Pos
		{
			int x;
			int y;

			void setPos(int xpos,int ypos)
			{
				x = xpos;
				y = ypos;
			}
		};
	
		cityMap(std::ifstream & inFile)
		{
			if (!inFile.is_open())
				std::cout << "Error on file open.\n";
			inFile >> xSize >> ySize;
			init();
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					int type;
					inFile >> type;
					map[i][j] = type;
				}
			}
		}

		cityMap(int newXSize, int newYSize)
			: xSize( newXSize ), ySize( newYSize )
		{
			init();
			roadConc = 10;
			generateRoad( roadConc );
			generateFactory( 5 );
			generateWorkplace( 3 );
			generateHouse();
		}

		cityMap(int newXSize, int newYSize, int roadCount, int factoryCount, int workCount)
			: xSize( newXSize ), ySize( newYSize ), roadConc( roadCount ), factoryConc( factoryCount), workConc( workCount )
		{
			init();
			generateRoad( roadConc );
			generateFactory( factoryConc );
			generateWorkplace( workConc );
			generateHouse();
		}


		std::list<Building*> getBuildings()
		{
			return buildings;
		}
		std::list<House*> getHouses()
		{
			return houses;
		}
		std::list<Office*> getOffices()
		{
			return offices;
		}

		std::list<FulfillmentCenter*> getFFC()
		{
			return ffc;
		}

		void printMap()
		{
			for (int i = 0; i < ySize; i++)
			{
				for (int j = 0; j < xSize; j++)
				{
					std::cout << map[j][i] << " ";
				}
				std::cout << std::endl;
			}
		}
		
		Pos findIntersection(int xPos, int yPos)
		{
			int roadX = xPos;
			int roadY = yPos;
			int horizontal = false;
			//Check adjacent positions for a road
			if(checkType(xPos+1,yPos,ROAD))
			{
				roadX = xPos+1;
				roadY = yPos;
			}
			else if(checkType(xPos-1,yPos,ROAD))
			{
				roadX = xPos-1;
				roadY = yPos;
			}
			else if(checkType(xPos,yPos+1,ROAD))
			{
				roadX = xPos;
				roadY = yPos+1;
				horizontal = true;
			}
			else if(checkType(xPos,yPos-1,ROAD))
			{
				roadX = xPos;
				roadY = yPos-1;
				horizontal = true;
			}			
			
			//Determine nearest intersection
			Pos loc;
			loc.setPos(-1,-1);
			int dist = roadConc;
			if(horizontal)
			{
				//Check right
				for(int i = 1; i < roadConc; i++)
				{
					if(roadX+i >= xSize)
						break;
					
					if(checkType(roadX+i,roadY,INTER))
					{
						loc.setPos(roadX+i,roadY);
						dist = i;
						break;
					}
				}
				//Check left
				for(int i = 1; i < roadConc; i++)
				{
					if(roadX-i < 0)
						break;
					
					if(checkType(roadX-i,roadY,INTER) && i < dist)
					{
						loc.setPos(roadX-i,roadY);
						dist = i;
						break;
					}
				}
			}
			else
			{
				//Check down
				for(int i = 1; i < roadConc; i++)
				{
					if(roadY+i >= ySize)
						break;
					
					if(checkType(roadX,roadY+i,INTER))
					{
						loc.setPos(roadX,roadY+i);
						dist = i;
						break;
					}
				}
				//Check up
				for(int i = 1; i < roadConc; i++)
				{
					if(roadY-i < 0)
						break;
					
					if(checkType(roadX,roadY-i,INTER) && i < dist)
					{
						loc.setPos(roadX,roadY-i);
						break;
					}
				}
			}
			
			if(loc.x == -1 || loc.y == -1)
				std::cout << "Could not find intersection.\n";
			
			return loc;
		}
		
		int getRoadConc()
		{
			return roadConc;
		}

	private:
		int** map;
		int xSize;
		int ySize;
		int roadConc;
		int factoryConc;
		int workConc;
		std::list<Building*> buildings;
		std::list<Office*> offices;
		std::list<House*> houses;
		std::list<FulfillmentCenter*> ffc;
		//std::list<Intersection*> intersections;

		/**
		 * Initializes the map's grid using xSize and ySize.
		 */
		void init()
		{
			srand(0);//time(NULL));
			map = new int*[xSize];
			for (int i = 0; i < xSize; i++)
			{
				map[i] = new int[ySize];
			}
		}

		/**
		 * Returns whether the provided position in the grid matches the given type.
		 */
		bool checkType(int xpos, int ypos, int type)
		{
			if(!validPos(xpos, ypos))
				return false;

			return map[xpos][ypos] == type;
		}
		bool checkType(struct Pos p, int type)
		{
			return checkType(p.x,p.y,type);
		}

		/**
		 * Checks if the position is within the bounds of the grid.
		 */
		bool validPos(int xpos, int ypos)
		{
			return xpos < xSize && xpos >= 0 && ypos < ySize && ypos >= 0;
		}

		/**
		 * Populates the grid with ROAD, forming a window-pane pattern of "conc" width.
		 */
		void generateRoad(int conc)
		{
			int type = ROAD;
			for (int i = 0; i < xSize; i++)
			{
				for (int j = 0; j < ySize; j++)
				{
					if(i % conc == 0 || j % conc == 0)
					{
						if(i % conc == 0 && j % conc == 0)
						{
							//Intersection* inter = new Intersection(i,j);
							//intersections.push_back(inter); 
							map[i][j] = INTER;
						}
						else
							map[i][j] = type;
					}
				}
			}
		}

		void generateFactory(int conc)
		{
			generateBuilding(conc, FACT_SIZE, FACT_SIZE, FACT);
		}

		void generateWorkplace(int conc)
		{
			generateBuilding(conc, WORK_SIZE, WORK_SIZE, WORK);
		}

		void generateHouse()
		{
			generateBuilding(1, HOME_SIZE, HOME_SIZE, HOME);
		}

		void generateBuilding(int conc, int width, int height, int type)
		{
			int buildAttempts = 0;
			int buildingX;
			int buildingY;
			bool placedThisRow;
			for(int j = 0; j < ySize; j++)
			{
				placedThisRow = false;
				for(int i = 0; i < xSize; i++)
				{
					//Store each corner of the building into an array
					struct Pos corner[4];
					corner[0].setPos(i,j);
					corner[1].setPos(i+width-1,j);
					corner[2].setPos(i,j+height-1);
					corner[3].setPos(i+width-1,j+height-1);

					//Check to see if any of the corners are adjacent to a road
					std::vector<struct Pos> adjacents;
					for(int p = 0; p < 4; p++)
					{
						int xPos = corner[p].x;
						int yPos = corner[p].y;

						if(checkType(xPos+1,yPos,ROAD)
						|| checkType(xPos-1,yPos,ROAD)
						|| checkType(xPos,yPos+1,ROAD)
						|| checkType(xPos,yPos-1,ROAD))
						{
							adjacents.push_back(corner[p]);
						}
					}

					//If at least one edge is near a road
					if(adjacents.size() > 1)
					{
						//Ensure there is an empty region here
						bool empty = true;
						for(int k = i; k < i+width; k++)
							for(int l = j; l < j+height; l++)
								if(!checkType(k,l,NONE))
									empty = false;

						//And there is space available for this building
						if(empty)
						{
							//Place the building at an interval determined by concentration
							if(buildAttempts % conc == 0)
							{
								placedThisRow = true;
								for(int k = i; k < i+width; k++)
									for(int l = j; l < j+height; l++)
										map[k][l] = type;

								//Using the road-adjacent corners, determine a location for the building object
								struct Pos p;
								int p1 = 0;
								int p2 = 0;
								while(p1 == p2 ||
								(adjacents[p1].x != adjacents[p2].x
								&& adjacents[p1].y != adjacents[p2].y) )
								{
									p1 = rand() % adjacents.size();
									p2 = rand() % adjacents.size();
								}

								int p1_x = adjacents[p1].x;
								int p1_y = adjacents[p1].y;
								int p2_x = adjacents[p2].x;
								int p2_y = adjacents[p2].y;
								if(p1_x == p2_x)
									p.setPos(p1_x,std::min(p1_y,p2_y)+rand() % height);
								else 	//p1_y == p2_y must be true for it to have escaped the while()
									p.setPos(std::min(p1_x,p2_x)+rand() % width,p1_y);

								buildingX = p.x;
								buildingY = p.y;
								
								//Determine nearest road position
								int roadX, roadY;
								if(checkType(p.x+1,p.y,ROAD))
								{
									roadX = p.x+1;
									roadY = p.y;
								}
								else if(checkType(p.x-1,p.y,ROAD))
								{
									roadX = p.x-1;
									roadY = p.y;
								}
								else if(checkType(p.x,p.y+1,ROAD))
								{
									roadX = p.x;
									roadY = p.y+1;
								}
								else
								{
									roadX = p.x;
									roadY = p.y-1;
								}
								
								//DEBUG: See where buildings are located
								map[p.x][p.y] = 8;

								if(type == FACT)
								{
									FulfillmentCenter* f = new FulfillmentCenter(buildingX,buildingY,roadX,roadY);
									buildings.push_back(f);
									ffc.push_back(f);
								}
								else if(type == WORK)
								{
									Office* o = new Office(buildingX,buildingY,roadX,roadY);
									buildings.push_back(o);
									offices.push_back(o);
								}
								else if(type == HOME)
								{
									House* h = new House(buildingX,buildingY,roadX,roadY);
									buildings.push_back(h);
									houses.push_back(h);
								}
							}
							i += width-1;
							buildAttempts++;
						}
					}
				}
				if(placedThisRow)
					j += height-1;
			}
		}

};

#endif
