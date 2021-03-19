#include "../inc/rds.hpp"

#define INDIVIDUALS_SPAWNED_PER_HOUSE 2

void Executive::run()
{
	ID id;

	//Prompt user for...
	//Simluation duration
	int months;
	std::cout << "How many months should the simulation run for?\n";
	std::cin >> months;


	//Map size
	int mapWidth, mapHeight, blockSize;
	std::cout << "Enter the width (in blocks) of the world followed by the height (ex: 4 5).\n";
	std::cin >> mapWidth >> mapHeight;
	
	std::cout << "How wide should each block be?\n";
	std::cin >> blockSize;
	
	cityMap theMap( mapWidth*blockSize+1, mapHeight*blockSize+1, blockSize, 5, 3 );
	
	/*std::ifstream inFile;
	inFile.open("map.txt");
	cityMap theMap = cityMap(inFile);
	inFile.close();*/
	
	//AI creation
	std::list<Drone*> droneList;
	//std::unordered_map<long long int,Individual*> populace;
	std::list<Agenda*> agendas;

	//Store into lists the building pointers created by the map
	std::list<FulfillmentCenter*> mapFFC = theMap.getFFC();
	std::list<Office*> offices = theMap.getOffices();
	std::list<House*> houses = theMap.getHouses();
	
	//Store the buildings that can be used for events
	std::vector<Building*> eventBuildings;

	for(std::list<Office*>::iterator iter = offices.begin(); iter != offices.end(); iter++)
		eventBuildings.push_back(*iter);

	for(std::list<House*>::iterator iter = houses.begin(); iter != houses.end(); iter++)
		eventBuildings.push_back(*iter);

	//Spawn individuals in the houses
	for(std::list<House*>::iterator houseIter = houses.begin(); houseIter != houses.end(); houseIter++)
	{
		for(int i = 0; i < INDIVIDUALS_SPAWNED_PER_HOUSE; i++)
		{
			Individual * janeDoe = new Individual(*(*houseIter));
			(*houseIter)->addOccupant(*janeDoe);
			Agenda * agenda = new Agenda(*janeDoe);
			//Create a random list of events for this individual's agenda
			for(int j = 0; j < 6 * 30 * months; j++)
			{
				int buildingNumber = rand() % eventBuildings.size();
				Building* building = eventBuildings[buildingNumber];

				int resourceAmount = rand() % 6 + 1;
				std::list<int> resourceTypes;
				for(int k = 0; k < resourceAmount; k++)
				{
					int resourceType = rand() % TOTAL_RESOURCE_TYPES;
					resourceTypes.push_back(resourceType);
				}
				Event* event = new Event(*building,*janeDoe,resourceTypes);
				agenda->addEvent(*event);
			}

			agendas.push_back(agenda);
		}
	}

	//Create initial drones
	int droneCount = 1;
	for(int i = 0; i < droneCount; i++)
	{
		Drone* myDrone = new Drone(1,30);
		droneList.push_back(myDrone);
	}
	

	MainAI theAI( droneList, mapFFC );

	//Activate graphics
	//

	/*std::list<FulfillmentCenter*>::iterator ffcIter = mapFFC.begin();
	ffcIter++;
	FulfillmentCenter myFFC = *(*ffcIter);

	cityMap::Pos pos = theMap.findIntersection(myFFC.getXPos(),myFFC.getYPos());
	std::cout << pos.x << ", " << pos.y << std::endl;
	std::cout << myFFC.getXPos() << ", " << myFFC.getYPos() << std::endl;
	*/
	
	theMap.printMap();
	
	//Initialize drone path
	std::list<Drone*>::iterator droneIter = droneList.begin();
	(*droneIter)->createMoveList(2,0,theMap.getRoadConc());


	//Begin simulation loop
	int currentTime = 0;
	while( currentTime < months*30*24*60 )
	{
		//std::cout << "One second has passed.\n";

		

		//Update drone positions
		for(std::list<Drone*>::iterator droneIter = droneList.begin(); droneIter != droneList.end(); droneIter++)
		{
			(*droneIter)->move();
		}
		

		//if()
			//break;

		//Pause the simulation
		std::this_thread::sleep_for( std::chrono::milliseconds(250) );
	}


};
