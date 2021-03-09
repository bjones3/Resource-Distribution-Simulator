#include "../inc/rds.hpp"

void Executive::run()
{
	ID id;

	//Prompt user for...
	//Simluation duration
	int months;
	std::cout << "How many months should the simulation run for?\n";
	std::cin >> months;


	//Map size
	int mapWidth, mapHeight;
	std::cout << "Enter the width of the world followed by the height (ex: 4 5).\n";
	std::cin >> mapWidth >> mapHeight;
	cityMap theMap( mapWidth, mapHeight );

	//AI creation
	std::list<FulfillmentCenter*> mapFFC = theMap.getFFC();
	std::list<Drone*> droneList;
	std::unordered_map populace;
	std::list<Agenda*> agendas;

	std::list<Office*> offices = theMap.getOffices();
	std::list<House*> houses = theMap.getHouses();
	std::list<Building*> officesAndHouses = theMap.getOffices();

	std::list<House*>::iterator houseIter0 = houses.begin();

	for(houseIter0; houseIter0 != houses.end(); houseIter0++)
	{
		officesAndHouses.push_back(houseIter0*);
	}

	std::list<House*>::iterator houseIter1 = houses.begin();

	for(houseIter1; houseIter1 != houses.end(); houseIter1++)
	{
		for(int i = 0; i < 4; i++)
		{
			Individual * janeDoe = new Individual(houseIter**);
			houseIter.addOccupant(janeDoe);
			Agenda * agenda = new Agenda(janeDoe);
			for(int j = 0; j < 6 * 30 * months; j++)
			{
				int buildingNumber = rand()%officesAndHouses.size();
				std::list<Building*>::iterator eventIter = officesAndHouses.begin();
				for(int k = 0; k < buildingNumber; k++)
				{
					eventIter++;
				}

				int resourceAmount = rand() % 6 + 1;
				std::list<int> resourceTypes;
				for(int k = 0; k < resourceAmount; k++)
				{
					int resourceType = rand() % TOTAL_RESOURCE_TYPES;
					resourceTypes.push_back(resourceType);

				}
				Event* event = new Event(eventIter*,janeDoe,resourceTypes);
				agenda.addEvent(event);
			}

			agendas.push_back(agenda);
		}
	}

	MainAI theAI( droneList, mapFFC );

	//Activate graphics
	//

	//Begin simulation loop
	int currentTime = 0;
	while( currentTime < months*30*24*60 )
	{
		std::cout << "One second has passed.\n";

		//


		//if()
			//break;

		//Pause the simulation
		std::this_thread::sleep_for( std::chrono::seconds(1) );
	}


};
