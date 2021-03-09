#include "../../inc/rds.hpp"

/*
protected:
	int xPos;
	int yPos;
	long long int id;
	std::list<Individual> occupants;
	std::list<Resource> contents;
	int occupantCapacity;
	double contentVolumeCapacity;
	double contentVolume;
*/

Building::Building()
{
	xPos = -1;
	yPos = -1;
	id = -1;
	occupantCapacity = 0;
	contentVolumeCapacity = 0;
	contentVolume = 0;
}

Building::Building(int x, int y)
{
	xPos = x;
	yPos = y;
	id = -1;//id = ID::generateID();
	occupantCapacity = 0;
	contentVolumeCapacity = 0;
	contentVolume = 0;
}

int Building::getOccupantAmount()
{
	return occupants.size();
}

int Building::getOccupantCapacity()
{
	return occupantCapacity;
}

bool Building::canAddOccupant(Individual & occupant)
{
	if(occupants.size() == occupantCapacity)
		return false;
	if(occupant.getPossessionVolume() + contentVolume > contentVolumeCapacity)
		return false;
	return true;
}

void Building::addOccupant(Individual & occupant)
{
	if(canAddOccupant(occupant))
		occupants.push_front(occupant);
}

//TODO: Change occupants list to a hash
Individual Building::removeOccupant(Individual & occupant)
{
	/*std::list<Individual>::iterator temp = std::find(occupants.begin(),occupants.end(),occupant);
	Individual removedOccupant = *temp;
	for()
		if(*temp.getID() == occupant.getID())
			occupants.remove(*temp);
	return removedOccupant;*/
}

bool Building::canAddResource(Resource & resource)
{
	if (resource.getVolume() + contentVolume > contentVolumeCapacity)
		return false;
	return true;
}

void Building::addResource(Resource & resource)
{
	if (canAddResource(resource))
	{
		contentVolume += resource.getVolume();
		contents.push_front(resource);
	}
}

Resource Building::removeResource(Resource & resource)
{
	/*std::list<Resource>::iterator temp = std::find(contents.begin(),contents.end(),resource);
	Resource removedResource = *temp;
	contents.remove(*temp);
	contentVolume -= resource.getVolume();
	return removedResource;*/
}

bool Building::canBringOccupant(Individual & occupant)
{
	if(occupants.size() == occupantCapacity)
		return false;
	if(occupant.getPossessionVolume() + contentVolume > contentVolumeCapacity)
		return false;
	return true;
}

bool Building::canBringContents(Resource & resource)
{
	if(resource.getVolume() + contentVolume > contentVolumeCapacity)
		return false;
}

int Building::getXPos()
{
	return xPos;
}

int Building::getYPos()
{
	return yPos;
}

long long int Building::getID()
{
	return id;
}