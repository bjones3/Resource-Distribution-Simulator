#include "../../inc/rds.hpp"

PassengerDrone::PassengerDrone(int x, int y, long long int theID) : Drone::Drone(x, y, theID)
{
	xPos = x;
	yPos = y;
	id = theID;
	passengerCapacity = 12;
	maxVolume = 48;
	maxWeight = 1000;
}

bool PassengerDrone::canLoadPassenger(Individual & passenger)
{
    if (passengers.size() == passengerCapacity)
        return false;
    if (passenger.getPossessionVolume() + contentVolume > maxVolume)
        return false;
    if (passenger.getPossessionWeight() + contentWeight > maxWeight)
        return false;
    return true;
}

void PassengerDrone::loadPassenger(Individual * passenger)
{
	Building* fromWhere = passenger->getBuilding();
	if(fromWhere != nullptr)
		Individual* ind = fromWhere->removeOccupant(passenger->getID());
	
	passenger->setDrone(this);
	
    passengers.insert({passenger->getID(), passenger});
    //std::unordered_map<long long int, Resource&> temp = passenger->getIndividualPossessions();
    //std::unordered_map<long long int, Resource&>::iterator iter = temp.begin();
    /*for (iter; iter!= temp.end(); iter++)
      {
      payload.push_back(iter*);
      }*/
}

bool PassengerDrone::passengerExists(long long int passenger)
{
	return passengers.find(passenger) != passengers.end();
}

Individual* PassengerDrone::unloadPassenger(long long int passenger)
{
	Individual * who = passengers.find(passenger)->second;
	passengers.erase(passenger);
	
	who->setDrone(nullptr);
	
	return who;
	/*std::list<Individual>::iterator temp1 = passengers.begin();

	Individual ind = passenger;

	for (temp1; temp1!=passengers.end(); temp1++)
		if (*temp1.getID() == passenger.getID())
			passengers.erase(temp1);

	std::list<Resource>::iterator temp2 = payload.begin();
	std::list<Resource> possessions = passenger.getIndividualPossessions();
	std::list<Resource>::iterator temp3 = possessions.begin();

	for (temp2; temp2 != payload.end(); temp2++)
		for(temp3; temp3!=possessions.end();temp3++)
			if(*temp2.getID() == *temp3.getID())
				payload.erase(temp2);

	return ind;*/
}

std::unordered_map<long long int, Individual*> PassengerDrone::getPassengers()
{
	return passengers;
}

