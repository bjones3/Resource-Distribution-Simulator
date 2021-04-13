#ifndef EXECUTIVE_HPP
# define EXECUTIVE_HPP

# include "rds.hpp"

# include <time.h>
# include <thread>
# define INDIVIDUALS_SPAWNED_PER_HOUSE 2

class Executive
{
	private:
		long long int 					generateID();
		std::list<Drone*> 				droneList;
		std::list<PassengerDrone*> 		pDroneList;
		std::list<CargoDrone*> 			cDroneList;
		std::list<Individual*> 			peopleList;
		//std::unordered_map<long long int,Individual*> populace;
		std::list<Agenda*> 				agendas;
		std::list<FulfillmentCenter*> 	FFCs;
		std::list<Office*> 				offices;
		std::list<House*> 				houses;
		std::list<Building*>			allBuildings;
		std::list<Resource*>			resourceList;
		ResourceTable					rTable;
		int								eventsCreated = 0;
		int								eventsCompleted = 0;

	public:
		void 							run(cityMap & theMap, int months);
		void							moveDrones();
		void							checkDrones(int roadConc);
		void 							executeEvents(int roadConc);
		PassengerDrone*					findPassengerDrone(Building* where, Individual* who, int & bestIndex1, int & bestIndex2);
		CargoDrone*						findCargoDrone(Building* where, std::list<Resource*> what, int & bestIndex1, int & bestIndex2);
		void							requestPassengerDrone(Building* where, Individual* who, int roadConc);
		void							requestCargoDrone(Building* where, Individual* who, std::list<Resource*> & what, int roadConc);
};

#endif
