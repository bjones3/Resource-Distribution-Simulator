#include "../../inc/rds.hpp"

std::string Individual::generateName()
{
	return "";
}

Individual::Individual()
{
	totalPossessionWeight = 0;
	totalPossessionVolume = 0;

	home = nullptr;
	currentBuilding = nullptr;
	currentDrone = nullptr;

	name = generateName();
	//id = ID::generateID();
}

Individual::Individual(House* house)
{
	totalPossessionWeight = 0;
	totalPossessionVolume = 0;

	home = house;
	currentBuilding = home;
	currentDrone = nullptr;

	name = generateName();
	//id = ID::generateID();
}

void Individual::doTask(std::list<Resource> & resources)
{
	std::list<Resource>::iterator temp = resources.begin();

	for(temp; temp!=resources.end(); temp++)
		temp->use();
}

void Individual::addPossession(Resource & possession)
{
	possessions.push_back(possession);

	totalPossessionWeight += possession.getWeight();
	totalPossessionVolume += possession.getVolume();
}

double Individual::getPossessionVolume()
{
	return totalPossessionVolume;
}

double Individual::getPossessionWeight()
{
	return totalPossessionWeight;
}

std::list<Resource> Individual::getIndividualPossessions()
{
	return possessions;
}

long long int Individual::getID()
{
	return id;
}

int Individual::getXPos()
{
	if(currentBuilding != nullptr)
		return currentBuilding->getXPos();
	else if(currentDrone != nullptr)
		return currentDrone->getXPos();
	else	//This should never occur, unless we allow free-roaming citizens
		return 0;
}

int Individual::getYPos()
{
	if(currentBuilding != nullptr)
		return currentBuilding->getYPos();
	else if(currentDrone != nullptr)
		return currentDrone->getYPos();
	else	//This should never occur, unless we allow free-roaming citizens
		return 0;
}

Building* Individual::getBuilding()
{
	return currentBuilding;
}

void Individual::setBuilding(Building* newBuilding)
{
	currentBuilding = newBuilding;
}

Drone* Individual::getDrone()
{
	return currentDrone;
}

void Individual::setDrone(Drone* newDrone)
{
	currentDrone = newDrone;
}
