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
        occupants.insert({occupant.getID(), occupant});
}

//TODO: Change occupants list to a hash
Individual Building::removeOccupant(Individual & occupant)
{
    if(occupants.find(occupant.getID()) != occupants.end())
        occupants.erase(occupant.getID());
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
        contents.insert({resource.getID(), resource});
	}
}

Resource Building::removeResource(Resource & resource)
{
    if(contents.find(resource.getID()) != contents.end())
        contents.erase(resource.getID());
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

/*
=======
std::list<Resource> Building::getContents()
{
	return contents;
}

std::list<Individual> Building::getOccupants()
{
	return occupants;
}
*/

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

