#include "../../inc/rds.hpp"

CargoDrone::CargoDrone(int x, int y, long long int newId) : Drone::Drone(x, y)
{
	xPos = x;
	yPos = y;
	id = newId;//ID::generateID();
	maxVolume = 1000;
	maxWeight = 6000;
}

bool CargoDrone::canLoadCargo(Resource & resource)
{
	if (resource.getVolume() + contentVolume > maxVolume)
		return false;
	if (resource.getWeight() + contentVolume > maxWeight)
		return false;
	return true;
}

void CargoDrone::loadCargo(Resource & resource)
{
	if (canLoadCargo(resource))
		payload.push_back(resource);
}

//NEEDS WORK
Resource CargoDrone::unloadCargo(Resource & resource)
{
	/*std::list<Resource>::iterator temp = payload.begin();
	for (temp; temp != payload.end(); temp++)
	{
		if(*temp.getID() == resource.getID())
		{
			payload.erase(temp);
			return resource;
		}
	}*/
}