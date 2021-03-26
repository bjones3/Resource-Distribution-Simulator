#include "../inc/rds.hpp"

#define INDIVIDUALS_SPAWNED_PER_HOUSE 	2
#define EVENTS_PER_DAY					6
#define EVENTS_TO_LOOKAHEAD				6

long long int Executive::generateID()
{
	static long long int id = -1;
	return ++id;
}

void Executive::run()
{
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
	std::list<Drone*> 				droneList;
	std::list<PassengerDrone*> 		pDroneList;
	std::list<CargoDrone*> 			cDroneList;
	std::list<Individual*> 			peopleList;
	//std::unordered_map<long long int,Individual*> populace;
	std::list<Agenda*> agendas;
	std::list<FulfillmentCenter*> 	mapFFC 		= theMap.getFFC();
	std::list<Office*> 				offices 	= theMap.getOffices();
	std::list<House*> 				houses 		= theMap.getHouses();
	std::list<Building*>			allBuildings= theMap.getBuildings();
	
	//Separate storage for buildings that are used for events (only offices and houses)
	std::vector<Building*> eventBuildings;

	for(std::list<Office*>::iterator iter = offices.begin(); iter != offices.end(); iter++)
		eventBuildings.push_back(*iter);

	for(std::list<House*>::iterator iter = houses.begin(); iter != houses.end(); iter++)
		eventBuildings.push_back(*iter);

	//Assign IDs to all buildings
	for(std::list<Building*>::iterator buildIter = allBuildings.begin(); buildIter != allBuildings.end(); buildIter++)
		(*buildIter)->setID(generateID());

	//Spawn individuals in the houses and generate their agendas
	for(std::list<House*>::iterator houseIter = houses.begin(); houseIter != houses.end(); houseIter++)
	{
		for(int i = 0; i < INDIVIDUALS_SPAWNED_PER_HOUSE; i++)
		{
			Individual * janeDoe = new Individual(*houseIter,generateID());
			peopleList.push_back(janeDoe);
			(*houseIter)->addOccupant(janeDoe);
			
			Agenda * agenda = new Agenda(*janeDoe);
			
			//Create a random list of events for this individual's agenda
			for(int j = 0; j < EVENTS_PER_DAY * 30 * months; j++)
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
			//break;	//Remove this to spawn more individuals
		}
		break;	//Remove this to spawn individuals in multiple houses
	}

	//Create initial drones
	for(int i = 0; i < 2; i++)
	{
		PassengerDrone* myDrone = new PassengerDrone(2+i,i*3+10,generateID());
		pDroneList.push_back(myDrone);
		droneList.push_back(myDrone);
	}
	
	//Create the AI itself
	MainAI theAI( droneList, mapFFC );

	//Determine plan for the first week
	for(int i = 0; i < EVENTS_TO_LOOKAHEAD; i++)
	{
	
	}

	//Activate graphics
	//

	
	
	//Initialize drone path (this will eventually be handled in the main loop when drones are given new paths)
	std::list<Drone*>::iterator droneIter = droneList.begin();
	std::list<Individual*>::iterator peopleIter = peopleList.begin();

	for(int i = 0; i < 2; i++)
	{
		Drone* theDrone = (*droneIter);
		Individual* theDude = (*peopleIter);
	
		theDrone->createRoute(houses.back(),theDude,theMap.getRoadConc());
		
		std::cout << "Person " << theDude->getID() << " needs Drone " << theDrone->getID() << ";\n(" << theDude->getXPos() << ", " << theDude->getYPos() << ") -> (" << theDrone->getXPos() << ", " << theDrone->getYPos() << ")\n";
		
		droneIter++;
		peopleIter++;
	}
	
	//(*droneIter)->createMoveList(6,10,theMap.getRoadConc());

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

		//Load/unload a passenger when the drone stops
		for(std::list<PassengerDrone*>::iterator droneIter = pDroneList.begin(); droneIter != pDroneList.end(); droneIter++)
		{
			PassengerDrone* theDrone = (*droneIter);
			if(theDrone->isMoving() && !theDrone->getRouteList().empty())
			{
				//Pick up the passenger and move to the passenger's destination
				if(theDrone->getPassengers().empty())
				{
					Individual* who = theDrone->getRoute().who;
					if(who->getBuilding()->occupantExists(who->getID())
					&& theDrone->isAdjacent(who->getBuilding()) 
					&& theDrone->canLoadPassenger(*who))
					{
						theDrone->loadPassenger(who);
						
						std::cout << "(" << theDrone->getID() << ") Picked up passenger "<< who->getID() << std::endl;
					}
				}
				else
				{
					Individual* who = theDrone->getRoute().who;
					Building* where = theDrone->getRoute().where;
					if(theDrone->passengerExists(who->getID())
					&& theDrone->isAdjacent(where)
					&& where->canAddOccupant(*who))
					{
						theDrone->unloadPassenger(who->getID());
						where->addOccupant(who);
						std::cout << "(" << theDrone->getID() << ") Dropped off passenger " << who->getID() << std::endl;
						
						theDrone->removeRoute();
						
						theDrone->createMoveList(6,10,theMap.getRoadConc());
					}
				}
			}
			else if(!theDrone->isMoving())
				return;
		}
		
		//Print the individual's position for testing
		//std::cout << firstDude->getXPos() << ", " << firstDude->getYPos() << std::endl;

		//Pause the simulation until the next time step
		time2 = std::chrono::high_resolution_clock::now();
		timeCount = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
		std::this_thread::sleep_for( std::chrono::milliseconds( std::max(timePerStep-timeCount, 0) ) );
	
		currentTime++;
	}

	std::cout << "Simulation ended\n";
};
