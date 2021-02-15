#include "Building.hpp"


#ifndef FULFILLMENTCENTER_HPP
#define FULFILLMENTCENTER_HPP

class FulfillmentCenter: 

public Building
{

FulfillmentCenter(int x, int y);

CargoDrone createResourceDrone();

PassengerDrone createPassengerDrone();

Resource createResource(Resource & resource);

private:
	int droneCapacity;


#endif
