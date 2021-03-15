#include "../../inc/rds.hpp"

std::string Individual::generateName()
{
	return "";
}

Individual::Individual(House house)
{
	totalPossessionWeight = 0;
	totalPossessionVolume = 0;

	xPosition = house.getXPos();
	yPosition = house.getYPos();

	name = generateName();
	//id = ID::generateID();
}

void Individual::doTask(std::unordered_map<long long int, Resource> & resources)
{
     std::unordered_map<long long int, Resource>::iterator temp = resources.begin();


    for(temp; temp!=resources.end(); temp++)
        temp->second.use();
}

bool Individual::canAddPossession(Resource & possession){
    return (possessions.find(possession.getID()) != possessions.end());
}

void Individual::addPossession(Resource & possession)
{
    if(canAddPossession(possession))
        possessions.insert({possession.getID(), possession});

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

std::unordered_map<long long int, Resource&> Individual::getIndividualPossessions()
{
	return possessions;
}

long long int Individual::getID()
{
	return id;
}
