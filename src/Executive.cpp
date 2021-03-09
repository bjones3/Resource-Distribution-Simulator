#include "../inc/rds.hpp"

#include <stdio.h>
#include <thread>

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
