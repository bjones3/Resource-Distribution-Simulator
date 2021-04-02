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

Building::Building(int x, int y, int roadx, int roady): xPos(x), yPos(y), xRoad(roadx), yRoad(roady)
{
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

void Building::addOccupant(Individual * occupant)
{
	occupants.insert({occupant->getID(), occupant});
	occupant->setBuilding(this);
}

bool Building::occupantExists(long long int occupant)
{
	return occupants.find(occupant) != occupants.end();
}

Individual* Building::removeOccupant(long long int occupant)
{
	Individual * who = occupants.find(occupant)->second;
	occupants.erase(occupant);

	who->setBuilding(nullptr);

	return who;
}

bool Building::canAddResource(Resource & resource)
{
	if (resource.getVolume() + contentVolume > contentVolumeCapacity)
		return false;
	return true;
}

void Building::addResource(Resource * resource)
{
	contentVolume += resource->getVolume();
	contents.insert({resource->getID(), resource});
	resource->setBuilding(this);
}

bool Building::resourceExists(long long int resource)
{
	return contents.find(resource) != contents.end();
}

Resource* Building::removeResource(long long int resource)
{
	Resource* what = contents.find(resource)->second;
    contents.erase(what->getID());

    what->setBuilding(nullptr);

    return what;
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

std::unordered_map<long long int, Resource*> Building::getContents()
{
	return contents;
}

std::unordered_map<long long int, Individual*> Building::getOccupants()
{
	return occupants;
}

int Building::getXPos()
{
	return xPos;
}

int Building::getYPos()
{
	return yPos;
}

int Building::getXRoad()
{
	return xRoad;
}

int Building::getYRoad()
{
	return yRoad;
}

long long int Building::getID()
{
	return id;
}

void Building::setID(long long int theID)
{
	id = theID;
}

std::list<Resource*> Building::removeResources(std::list<Resource*> resources)
{
	std::list<Resource*>::iterator iter = resources.begin();

	for(iter; iter!=resources.end();iter++)
	{
		removeResource(*iter)
	}
}
