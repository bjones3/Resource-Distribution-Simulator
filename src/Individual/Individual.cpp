#include "../../inc/rds.hpp"

std::string Individual::generateName()
{
	return "";
}

Individual::Individual()
{
	totalPossessionWeight = 0;
	totalPossessionVolume = 0;

	xPosition = 0;
	yPosition = 0;

	home = nullptr;
	currentBuilding = nullptr;

	name = generateName();
	//id = ID::generateID();
}

Individual::Individual(House* house)
{
	totalPossessionWeight = 0;
	totalPossessionVolume = 0;

	xPosition = house->getXPos();
	yPosition = house->getYPos();

	home = house;
	currentBuilding = home;

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

void Individual::movePosition(int newXPosition, int newYPosition)
{
	//matriarch.requestDrone(newXPosition, newYPosition);
}

std::list<Resource> Individual::getIndividualPossessions()
{
	return possessions;
}

long long int Individual::getID()
{
	return id;
}

Building* Individual::getBuilding()
{
	return currentBuilding;
}

void Individual::setBuilding(Building* newBuilding)
{
	currentBuilding = newBuilding;
}

