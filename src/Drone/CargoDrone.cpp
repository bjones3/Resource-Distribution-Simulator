#include "../../inc/rds.hpp"

CargoDrone::CargoDrone(int x, int y, long long int theID) : Drone::Drone(x, y, theID)
{
	xPos = x;
	yPos = y;
	id = theID;
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

void CargoDrone::loadCargo(Resource * resource)
{
    payload.insert({resource->getID(), resource});
}

Resource* CargoDrone::unloadCargo(long long int resource){
    Resource * what = payload.find(resource)->second;
	payload.erase(resource);
	return what;


}
