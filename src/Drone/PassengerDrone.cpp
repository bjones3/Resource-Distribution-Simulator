#include "../../inc/rds.hpp"

PassengerDrone::PassengerDrone(int x, int y) : Drone::Drone(x, y)
{
	xPos = x;
	yPos = y;
	//id = newId;//ID::generateID();
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

void PassengerDrone::loadPassenger(Individual & passenger)
{

    passengers.insert({passenger.getID(), passenger});
    std::unordered_map<long long int, Resource&> temp = passenger.getIndividualPossessions();
    std::unordered_map<long long int, Resource&>::iterator iter = temp.begin();
    /*for (iter; iter!= temp.end(); iter++)
      {
      payload.push_back(iter*);
      }*/
}

//NEEDS WORK
Individual PassengerDrone::unloadPassenger(Individual & passenger)
{
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
