#include "rds.hpp"

FulfillmentCenter::FulfillmentCenter(int x, int y, int roadx, int roady) : Building::Building(x, y, roadx, roady)
{
	contentVolumeCapacity = 500000;
	droneCapacity = 100;
}

/*CargoDrone FulfillmentCenter::createResourceDrone()
{
	//return new CargoDrone(xPos, yPos, 0);
}

PassengerDrone FulfillmentCenter::createPassengerDrone()
{
	//return new PassengerDrone(xPos, yPos);
}

Resource FulfillmentCenter::createResource(Resource & resource)
{
	return resource;
}*/
