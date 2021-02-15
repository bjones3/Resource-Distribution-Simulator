#include "../../inc/rds.hpp"

FulfillmentCenter::FulfillmentCenter(int x, int y) : Building::Building(x, y)
{
	contentVolumeCapacity = 500000;
	droneCapacity = 100;
}

CargoDrone FulfillmentCenter::createResourceDrone()
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
}