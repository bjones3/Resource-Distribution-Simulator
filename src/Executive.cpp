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

	//Map dimensions
	int mapWidth, mapHeight, blockSize;
	std::cout << "Enter the width (in blocks) of the world followed by the height (ex: 4 5).\n";
	std::cin >> mapWidth >> mapHeight;
	
	//Size of each block
	std::cout << "How wide should each block be?\n";
	std::cin >> blockSize;
	
	//Create the map itself
	cityMap theMap( mapWidth*blockSize+1, mapHeight*blockSize+1, blockSize, 5, 3 );
	theMap.printMap();	//Show the map for debug purposes
	
	
	//Create pointer lists for just about everything
	std::list<Drone*> droneList;
	//std::unordered_map<long long int,Individual*> populace;
	std::list<Agenda*> agendas;
	std::list<FulfillmentCenter*> mapFFC 		= theMap.getFFC();
	std::list<Office*> offices 					= theMap.getOffices();
	std::list<House*> houses 					= theMap.getHouses();
	
	//Separate storage for buildings that are used for events (only offices and houses)
	std::vector<Building*> eventBuildings;

	for(std::list<Office*>::iterator iter = offices.begin(); iter != offices.end(); iter++)
		eventBuildings.push_back(*iter);

	for(std::list<House*>::iterator iter = houses.begin(); iter != houses.end(); iter++)
		eventBuildings.push_back(*iter);

	//Spawn individuals in the houses and generate their agendas
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
		Drone* myDrone = new Drone(16,10);
		droneList.push_back(myDrone);
	}
	
	//Create the AI itself
	MainAI theAI( droneList, mapFFC );


	//Activate graphics
	//

	
	
	//Initialize drone path (this will eventually be handled in the main loop when drones are given new paths)
	std::list<Drone*>::iterator droneIter = droneList.begin();
	(*droneIter)->createMoveList(3,0,theMap.getRoadConc());


	//Begin simulation loop
	int currentTime = 0;
	int timePerStep = 250;	//milliseconds
	int timeCount = 0;
	std::chrono::high_resolution_clock::time_point time1, time2;
	while( currentTime < months*30*24*60 )
	{
		//Get the time at the start of the loop
		time1 = std::chrono::high_resolution_clock::now();
	
		//Update drone positions
		for(std::list<Drone*>::iterator droneIter = droneList.begin(); droneIter != droneList.end(); droneIter++)
		{
			(*droneIter)->move();
		}
		

		//Pause the simulation until the next time step
		time2 = std::chrono::high_resolution_clock::now();
		timeCount = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
		std::this_thread::sleep_for( std::chrono::milliseconds( std::max(timePerStep-timeCount, 0) ) );
	
		currentTime++;
	}

	std::cout << "Simulation ended\n";
};
