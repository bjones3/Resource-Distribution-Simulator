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
	
	
	//Populate building lists using the map
	FFCs 			= theMap.getFFC();
	offices 		= theMap.getOffices();
	houses 			= theMap.getHouses();
	allBuildings	= theMap.getBuildings();
	
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
			
			Agenda * agenda = new Agenda(janeDoe);
			
			//Create a random list of events for this individual's agenda
			for(int j = 0; j < EVENTS_PER_DAY * 30 * months; j++)
			{
				int buildingNumber = rand() % eventBuildings.size();
				Building* building = eventBuildings[buildingNumber];

				int resourceAmount = rand() % 6 + 1;
				std::list<int> resourceTypes;
				double totalWeight = 0;
				double totalVolume = 0;
				CargoDrone cd(0,0,0);
				double maxVolume = cd.getMaxVolume();
				double maxWeight = cd.getMaxWeight();
				for(int k = 0; k < resourceAmount; k++)
				{
					int resourceType = rand() % TOTAL_RESOURCE_TYPES;
					double theWeight = rTable.getValue(resourceType,WEIGHT_MAX);
					double theVolume = rTable.getValue(resourceType,VOLUME_MAX);
					if(totalWeight + theWeight <= maxWeight
					&& totalVolume + theVolume <= maxVolume)
					{
						totalWeight += theWeight;
						totalVolume += theVolume;
						resourceTypes.push_back(resourceType);
					}
				}
				Event* event = new Event(building,janeDoe,resourceTypes);
				agenda->addEvent(*event);
				eventsCreated++;
			}

			agendas.push_back(agenda);
			//break;	//Remove this to spawn more individuals in a house
		}
		//break;	//Remove this to spawn individuals in multiple houses
	}
	
	//Create the AI itself
	/*MainAI theAI( droneList, FFCs );

	//Determine plan for the first week
	for(int i = 0; i < EVENTS_TO_LOOKAHEAD; i++)
	{
	
	}
	*/
	//Activate graphics
	//

	//Begin simulation loop
	int currentTime = 0;
	int timePerStep = 1;//100;	//milliseconds
	int timeCount = 0;
	std::chrono::high_resolution_clock::time_point time1, time2;
	while( currentTime < months*30*24*60 )
	{
		//Get the time at the start of the loop
		time1 = std::chrono::high_resolution_clock::now();
	
		//Update drone positions
		moveDrones();
		
		//Attempt to execute events
		executeEvents(theMap.getRoadConc());

		//Load/unload a passenger when the drone stops
		checkDrones(theMap.getRoadConc());

		//if(!resourceList.empty())
			//std::cout << resourceList.front()->getXPos() << ", " << resourceList.front()->getYPos() << std::endl;

		//Pause the simulation until the next time step
		time2 = std::chrono::high_resolution_clock::now();
		timeCount = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
		std::this_thread::sleep_for( std::chrono::milliseconds( std::max(timePerStep-timeCount, 0) ) );
	
		currentTime++;
	}

	std::cout << "Simulation ended\n";
	std::cout << "Events completed: " << eventsCompleted << "/" << eventsCreated << std::endl;
};

void Executive::moveDrones()
{
	for(std::list<Drone*>::iterator droneIter = droneList.begin(); droneIter != droneList.end(); droneIter++)
	{
		(*droneIter)->move();
	}
}

void Executive::checkDrones(int roadConc)
{
	for(std::list<PassengerDrone*>::iterator droneIter = pDroneList.begin(); droneIter != pDroneList.end(); droneIter++)
	{
		PassengerDrone* theDrone = (*droneIter);
		theDrone->deliveryCheck(roadConc);
	}
	for(std::list<CargoDrone*>::iterator droneIter = cDroneList.begin(); droneIter != cDroneList.end(); droneIter++)
	{
		CargoDrone* theDrone = (*droneIter);
		theDrone->deliveryCheck(roadConc);
	}
}

void Executive::executeEvents(int roadConc)
{
	for(std::list<Individual*>::iterator indIter = peopleList.begin(); indIter != peopleList.end(); indIter++)
	{
		Individual* person = *indIter;
		Agenda* theAgenda = person->getAgenda();
		if(!theAgenda->getEvents().empty())
		{
			bool personInBuilding = theAgenda->inBuilding();
			std::list<Resource*> foundResources;
			std::list<int> neededTypes;
			bool resourcesInBuilding = theAgenda->canExecuteEvent(foundResources, neededTypes);
			
			//Make sure the individual is in the building
			if(!personInBuilding && person->getPassengerRequest() == nullptr)
			{
				//Not in the building, need a passenger drone
				std::cout << "(" << person->getID() << ") Event failure, request pDrone\n";
				
				Building* theBuilding = theAgenda->getEvents().front().getBuilding();
				
				//Request the drone
				requestPassengerDrone(theBuilding, person, roadConc);
			}
			
			//Make sure the needed resources are in the building
			if(personInBuilding && !resourcesInBuilding && person->getCargoRequest() == nullptr)
			{
				//Resources not in building, need a cargo drone
				std::cout << "(" << person->getID() << ") Event failure, request cDrone\n";
				
				//Spawn some resources at a fulfillment center
				std::list<Resource*> newResources;
				for(std::list<int>::iterator iter = neededTypes.begin(); iter != neededTypes.end(); iter++)
				{
					Resource* r = new Resource(*iter,generateID(),rTable);
					newResources.push_back(r);
					resourceList.push_back(r);
				}
				FFCs.front()->addResources(newResources);
				
				Building* theBuilding = theAgenda->getEvents().front().getBuilding();
				
				//Request the drone
				requestCargoDrone(theBuilding, person, newResources, roadConc);
			}
			
			//If no requests are needed, execute the event
			if(personInBuilding && resourcesInBuilding)
			{
				theAgenda->executeEvent(foundResources);
				eventsCompleted++;
				std::cout << "(" << person->getID() << ") Event success; " << eventsCompleted << "/" << eventsCreated << std::endl;	
			}
		}
		else //No more events left to execute
		{
			//Go home
			if(person->getBuilding() != person->getHome() && person->getPassengerRequest() == nullptr)
			{
				requestPassengerDrone(person->getHome(),person,roadConc);
			}
			
		}
	}
}

PassengerDrone* Executive::findPassengerDrone(Building* where, Individual* who, int & bestIndex1, int & bestIndex2)
{
	PassengerDrone* bestDrone = nullptr;
	for(std::list<PassengerDrone*>::iterator it = pDroneList.begin(); it != pDroneList.end(); it++)
	{	
		PassengerDrone* theDrone = *it;
		//If this drone cannot be full when it comes to pickup
		if(theDrone->getCapacity() > theDrone->getDeliveries().size())
		{
			//Determine if this person's locations are along this drone's path
			int index1 = -1; int index2 = -1;
			index1 = theDrone->posInPath(who->getBuilding()->getXRoad(),who->getBuilding()->getYRoad());
			if(index1 != -1)
				index2 = theDrone->posInPath(where->getXRoad(),where->getYRoad());

			//std::cout << "Person " << who->getID() << "'s move indices: "<< index1 << ", " << index2 << std::endl;
			
			//Determine if this drone is the best match
			if(index2 != -1)	//This drone will pickup and dropoff
			{
				if(bestIndex2 > index2 || bestIndex2 == -1)	//This drone is going to drop off sooner
				{
					bestIndex1 = index1;
					bestIndex2 = index2;
					bestDrone = theDrone;
				}
			}
			else if(index1 != -1)	//This drone will only pickup
			{
				if((bestIndex1 > index1 || bestIndex1 == -1)
				&& bestIndex2 == -1)	//This drone is going to pick up sooner
				{
					bestIndex1 = index1;
					bestDrone = theDrone;
				}
			}
			else	//A whole new set of movements would need to be created
			{
				//So this is more of a last resort than anything
				if(bestIndex1 == -1 && bestIndex2 == -1)
					bestDrone = theDrone;
			}
			
			//Drones that are idle (no deliveries) should take priority
			if(!theDrone->isMoving())
			{
				bestDrone = theDrone;
				break;
			}
		}
	}
	return bestDrone;
}

CargoDrone* Executive::findCargoDrone(Building* where, std::list<Resource*> what, int & bestIndex1, int & bestIndex2)
{
	CargoDrone* bestDrone = nullptr;
	for(std::list<CargoDrone*>::iterator it = cDroneList.begin(); it != cDroneList.end(); it++)
	{	
		CargoDrone* theDrone = *it;
		
		double volume = 0;
		double weight = 0;
		//Determine how much weight and volume will be occupied by this delivery
		std::list<Resource*>::iterator iter;
		for(iter = what.begin(); iter != what.end(); iter++)
		{
			volume += (*iter)->getVolume();
			weight += (*iter)->getWeight();
		}
		
		//Determine how much weight and volume could be taken by the current deliveries
		std::list<Drone::Delivery> deliveries = theDrone->getDeliveries();
		for(std::list<Drone::Delivery>::iterator delivery = deliveries.begin(); delivery != deliveries.end(); delivery++)
		{
			std::list<Resource*> dWhat = (*delivery).what;
			for(iter = dWhat.begin(); iter != dWhat.end(); iter++)
			{
				volume += (*iter)->getVolume();
				weight += (*iter)->getWeight();
			}
		}
		
		//If this drone cannot be full when it comes to pickup
		if(theDrone->getMaxVolume() > volume && theDrone->getMaxWeight() > weight)
		{
			//Determine if the locations are along this drone's path
			int index1 = -1; int index2 = -1;
			index1 = theDrone->posInPath(what.front()->getBuilding()->getXRoad(),what.front()->getBuilding()->getYRoad());
			if(index1 != -1)
				index2 = theDrone->posInPath(where->getXRoad(),where->getYRoad());

			//std::cout << "Resource " << what.front()->getID() << "'s move indices: "<< index1 << ", " << index2 << std::endl;
			
			//Determine if this drone is the best match
			if(index2 != -1)	//This drone will pickup and dropoff
			{
				if(bestIndex2 > index2 || bestIndex2 == -1)	//This drone is going to drop off sooner
				{
					bestIndex1 = index1;
					bestIndex2 = index2;
					bestDrone = theDrone;
				}
			}
			else if(index1 != -1)	//This drone will only pickup
			{
				if((bestIndex1 > index1 || bestIndex1 == -1)
				&& bestIndex2 == -1)	//This drone is going to pick up sooner
				{
					bestIndex1 = index1;
					bestDrone = theDrone;
				}
			}
			else	//A whole new set of movements would need to be created
			{
				//So this is more of a last resort than anything
				if(bestIndex1 == -1 && bestIndex2 == -1)
					bestDrone = theDrone;
			}
			
			//Drones that are idle (no deliveries) should take priority
			if(!theDrone->isMoving())
			{
				bestDrone = theDrone;
				break;
			}
		}
	}
	return bestDrone;
}

void Executive::requestPassengerDrone(Building* where, Individual* who, int roadConc)
{
	int bestIndex1 = -1; int bestIndex2 = -1;
	PassengerDrone* bestDrone = findPassengerDrone(where, who, bestIndex1, bestIndex2);
	
	//A passenger drone was not found, create one
	if(bestDrone == nullptr)
	{
		FulfillmentCenter* theFFC = FFCs.front();
		PassengerDrone* myDrone = new PassengerDrone(theFFC->getXRoad(), theFFC->getYRoad(), generateID());
		pDroneList.push_back(myDrone);
		droneList.push_back(myDrone);
		bestDrone = myDrone;
	}
	
	//Add this person to the drone's delivery list and create the needed movements
	bestDrone->createDelivery(where, who, bestIndex1, bestIndex2, roadConc);

	std::cout << "Person " << who->getID() << " needs Drone " << bestDrone->getID() << ";\n(" << who->getXPos() << ", " << who->getYPos() << ") -> (" << where->getXPos() << ", " << where->getYPos() << ")\n";
		
	who->setPassengerRequest(bestDrone);
}

void Executive::requestCargoDrone(Building* where, Individual* who, std::list<Resource*> & what, int roadConc)
{
	int bestIndex1 = -1; int bestIndex2 = -1;
	CargoDrone* bestDrone = findCargoDrone(where, what, bestIndex1, bestIndex2);
	
	//A cargo drone was not found, create one
	if(bestDrone == nullptr)
	{
		FulfillmentCenter* theFFC = FFCs.front();
		CargoDrone* myDrone = new CargoDrone(theFFC->getXRoad(), theFFC->getYRoad(), generateID());
		cDroneList.push_back(myDrone);
		droneList.push_back(myDrone);
		bestDrone = myDrone;
	}
	
	//Add this resource list to the drone's delivery list and create the needed movements
	bestDrone->createDelivery(where, who, what, bestIndex1, bestIndex2, roadConc);

	Resource* whatF = what.front();
	std::cout << "Resource " << whatF->getID() << " needs Drone " << bestDrone->getID() << ";\n(" << whatF->getXPos() << ", " << whatF->getYPos() << ") -> (" << where->getXPos() << ", " << where->getYPos() << ")\n";
	
	who->setCargoRequest(bestDrone);
}
