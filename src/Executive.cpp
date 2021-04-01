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
	
	
	//Create resource table
	ResourceTable rTable;
	
	
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
	int houseCounter = -1;	//Testing
	for(std::list<House*>::iterator houseIter = houses.begin(); houseIter != houses.end(); houseIter++)
	{
		houseCounter++;
		if(houseCounter != 0 && houseCounter != 7)	//This was for testing passenger pickup
			continue;
		for(int i = 0; i < INDIVIDUALS_SPAWNED_PER_HOUSE; i++)
		{
			Individual * janeDoe = new Individual(*houseIter,generateID());
			peopleList.push_back(janeDoe);
			(*houseIter)->addOccupant(janeDoe);
			
			Agenda * agenda = new Agenda(janeDoe);
			
			//Create a random list of events for this individual's agenda
			//for(int j = 0; j < EVENTS_PER_DAY * 30 * months; j++)
			//{
				int buildingNumber = rand() % eventBuildings.size();
				Building* building = houses.back();//*houseIter;//eventBuildings[buildingNumber];

				int resourceAmount = 1;//rand() % 6 + 1;
				std::list<int> resourceTypes;
				for(int k = 0; k < resourceAmount; k++)
				{
					int resourceType = 0;//rand() % TOTAL_RESOURCE_TYPES;
					resourceTypes.push_back(resourceType);
				}
				Event* event = new Event(building,janeDoe,resourceTypes);
				agenda->addEvent(*event);
			//}

			agendas.push_back(agenda);
			break;	//Remove this to spawn more individuals in a house
		}
		//break;	//Remove this to spawn individuals in multiple houses
	}

	//Create initial drones
	for(int i = 0; i < 2; i++)
	{
		//PassengerDrone* myDrone = new PassengerDrone(0,16,generateID());
		//pDroneList.push_back(myDrone);
		//droneList.push_back(myDrone);
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

	
	
	//Initialize drone path (this is now handled in the main loop when individuals fail their events)
	/*std::list<Drone*>::iterator droneIter = droneList.begin();
	std::list<Individual*>::iterator peopleIter = peopleList.begin();

	for(int i = 0; i < 1; i++)
	{
		Drone* theDrone = (*droneIter);
		Individual* theDude = (*peopleIter);
		Building* theBuilding = houses.back();
		if(i == 1)
			theBuilding = (*(houses.begin()));

		//Determine if this person's locations are along this drone's path
		int index1 = -1; int index2 = -1;		
		index1 = theDrone->posInPath(theDude->getBuilding()->getXRoad(),theDude->getBuilding()->getYRoad());
		if(index1 != -1)
			index2 = theDrone->posInPath(theBuilding->getXRoad(),theBuilding->getYRoad());
		
		std::cout << "Person " << theDude->getID() << "'s move indices: "<< index1 << ", " << index2 << std::endl;
		
		//Add this person to the drone's delivery list and create the needed movements
		theDrone->createDelivery(theBuilding,theDude,index1,index2,theMap.getRoadConc());
		
		std::cout << "Person " << theDude->getID() << " needs Drone " << theDrone->getID() << ";\n(" << theDude->getXPos() << ", " << theDude->getYPos() << ") -> (" << theBuilding->getXPos() << ", " << theBuilding->getYPos() << ")\n";
		
		//droneIter++;
		peopleIter++;
	}	*/
	//(*droneIter)->createMoveList(6,10,theMap.getRoadConc());

	//Initialize resources in buildings for testing purposes
	Building* firstHouse = houses.back();//peopleList.front()->getBuilding();
	Resource* testResource = new Resource(0,generateID(),rTable);
	Resource* testResource2 = new Resource(1,generateID(),rTable);
	firstHouse->addResource(testResource);
	//firstHouse->addResource(testResource2);


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
		moveDrones();
		
		//Attempt to execute events
		executeEvents(theMap.getRoadConc());

		//Load/unload a passenger when the drone stops
		checkDrones(theMap.getRoadConc());		

		//Pause the simulation until the next time step
		time2 = std::chrono::high_resolution_clock::now();
		timeCount = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
		std::this_thread::sleep_for( std::chrono::milliseconds( std::max(timePerStep-timeCount, 0) ) );
	
		currentTime++;
	}

	std::cout << "Simulation ended\n";
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
		if(theDrone->deliveryCheck())
		{
			//Check all deliveries to see if any are adjacent
			std::list<Drone::Delivery> deliveries = theDrone->getDeliveries();
			for(std::list<Drone::Delivery>::iterator deliveryIter = deliveries.begin(); deliveryIter != deliveries.end(); deliveryIter++)
			{
				Drone::Delivery theDelivery = (*deliveryIter);
				
				//If they're not onboard
				if(!theDrone->passengerExists(theDelivery.who->getID()))
				{
					Individual* who = theDelivery.who;
					Building* where = who->getBuilding();
					if(theDrone->isAdjacent(where))
					{
						if(!where->occupantExists(who->getID()))
						{
							//This should only occur if the individual thinks it's somewhere it's not, which should never occur
							std::cout << "ERROR: Individual/Building pairing is one-way.\n";
						}
						else if(!theDrone->canLoadPassenger(*who))
						{
							//This should never occur if we implement requests correctly 
							//Passenger cannot be loaded; add a new path to pick them up later
							theDrone->createMoveList(where->getXRoad(),where->getYRoad(),roadConc);
							
							//We'll also need to drop them off
							theDrone->createMoveList(theDelivery.where->getXRoad(),theDelivery.where->getYRoad(),roadConc);
						}
						else
						{
							theDrone->loadPassenger(who);
							where->removeOccupant(who->getID());
							
							std::cout << "(" << theDrone->getID() << ") Picked up passenger "<< who->getID() << std::endl;
						}
					}
				}
				else	//They're onboard
				{
					Individual* who = theDelivery.who;
					Building* where = theDelivery.where;					
					
					if(theDrone->isAdjacent(where))
					{
						if(!where->canAddOccupant(*who))
						{
							//Passenger cannot be unloaded, so drop them off later
							theDrone->createMoveList(where->getXRoad(),where->getYRoad(),roadConc);
						}
						else
						{
							theDrone->unloadPassenger(who->getID());
							where->addOccupant(who);
							std::cout << "(" << theDrone->getID() << ") Dropped off passenger " << who->getID() << std::endl;
							
							theDrone->removeDelivery(who->getID());
							who->setPassengerRequest(nullptr);
							//if(theDrone->getDeliveries().empty())
								//theDrone->createMoveList(6,10,roadConc);
						}
					}
				}
			}
		}
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
			bool resourcesInBuilding = theAgenda->canExecuteEvent(foundResources,neededTypes);
			
			//Make sure the individual is in the building
			if(!personInBuilding && person->getPassengerRequest() == nullptr)
			{
				//Not in the building, need a passenger drone
				std::cout << "Event failure, request pDrone\n";
				
				Building* theBuilding = theAgenda->getEvents().front().getBuilding();
				Drone* bestDrone = nullptr;
				int bestIndex1 = -1; int bestIndex2 = -1;
				for(std::list<PassengerDrone*>::iterator it = pDroneList.begin(); it != pDroneList.end(); it++)
				{	
					PassengerDrone* theDrone = *it;
					//If this drone cannot be full when it comes to pickup
					if(theDrone->getCapacity() > theDrone->getDeliveries().size())
					{
						//Determine if this person's locations are along this drone's path
						int index1 = -1; int index2 = -1;
						index1 = theDrone->posInPath(person->getBuilding()->getXRoad(),person->getBuilding()->getYRoad());
						if(index1 != -1)
							index2 = theDrone->posInPath(theBuilding->getXRoad(),theBuilding->getYRoad());
		
						std::cout << "Person " << person->getID() << "'s move indices: "<< index1 << ", " << index2 << std::endl;
						
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
				
				//A passenger drone was not found, create one
				if(bestDrone == nullptr)
				{
					FulfillmentCenter* theFFC = FFCs.front();
					PassengerDrone* myDrone = new PassengerDrone(theFFC->getXRoad(), theFFC->getYRoad(), generateID());
					std::cout << "test\n";
					pDroneList.push_back(myDrone);
					droneList.push_back(myDrone);
					bestDrone = myDrone;
				}
				
				//Add this person to the drone's delivery list and create the needed movements
				bestDrone->createDelivery(theBuilding, person, bestIndex1, bestIndex2, roadConc);
			
				std::cout << "Person " << person->getID() << " needs Drone " << bestDrone->getID() << ";\n(" << person->getXPos() << ", " << person->getYPos() << ") -> (" << theBuilding->getXPos() << ", " << theBuilding->getYPos() << ")\n";
					
				person->setPassengerRequest(bestDrone);
			}
			
			//Make sure the needed resources are in the building
			if(!resourcesInBuilding)
			{
				//Resources not in building, need a cargo drone
				std::cout << "Event failure, request cDrone\n";
			}
			
			//If no requests are needed, execute the event
			if(personInBuilding && resourcesInBuilding)
			{
				theAgenda->executeEvent(foundResources);
				std::cout << "Event success\n";
			}
		}
	}
}
