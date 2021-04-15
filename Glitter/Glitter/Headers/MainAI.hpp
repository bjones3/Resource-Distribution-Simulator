#ifndef MAIN_AI_HPP
#define MAIN_AI_HPP

#include "rds.hpp"

class MainAI
{
	public:
		MainAI( std::list<Drone*> droneList, std::list<FulfillmentCenter*> ffcList );
		void generateDrone( char type, long long int location );
		void generateResource( int type );
		
	private:
		int operationsPerMinute;
		int operations;
		std::list<Drone*> droneList;
		std::list<FulfillmentCenter*> ffcList;
		//std::queue<Agenda> ;
		//ResourceTable* resTable;
};

#endif
