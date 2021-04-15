#include "rds.hpp"

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
	id = -1;
}

Individual::Individual(House* house, long long int theID)
{
	totalPossessionWeight = 0;
	totalPossessionVolume = 0;

	home = house;
	currentBuilding = home;
	currentDrone = nullptr;

	name = generateName();
	id = theID;
}

void Individual::doTask(std::list<Resource*> resources)
{
	std::list<Resource*>::iterator temp;
	for(temp = resources.begin(); temp != resources.end(); temp++)
	{
		Resource* what = *temp;
		if(!what->use())	//Returns false if the resource is worn out
		{
    		what->getBuilding()->removeResource(what->getID());
		}
	}
	
	/*if(resources.size() != schedule->getEvents().front().getTypesNeeded().size())
	{
		std::cout << "MISMATCH LENGTHS\n";
		exit(0);
	}*/
}

bool Individual::canAddPossession(Resource & possession){
    return (possessions.find(possession.getID()) != possessions.end());
}

void Individual::addPossession(Resource & possession)
{
    if(canAddPossession(possession))
    {
        possessions.insert({possession.getID(), possession});

		totalPossessionWeight += possession.getWeight();
		totalPossessionVolume += possession.getVolume();
	}
}

double Individual::getPossessionVolume()
{
	return totalPossessionVolume;
}

double Individual::getPossessionWeight()
{
	return totalPossessionWeight;
}

std::unordered_map<long long int, Resource&> Individual::getIndividualPossessions()
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

Building* Individual::getHome()
{
	return home;
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

Agenda* Individual::getAgenda()
{
	return schedule;
}

void Individual::setAgenda(Agenda* theAgenda)
{
	schedule = theAgenda;
}

PassengerDrone* Individual::getPassengerRequest()
{
	return passengerRequest;
}

void Individual::setPassengerRequest(PassengerDrone* theDrone)
{
	passengerRequest = theDrone;
}

CargoDrone* Individual::getCargoRequest()
{
	return cargoRequest;
}

void Individual::setCargoRequest(CargoDrone* theDrone)
{
	cargoRequest = theDrone;
}



