#include "rds.hpp"

PassengerDrone::PassengerDrone(int x, int y, long long int theID) : Drone::Drone(x, y, theID)
{
	xPos = x;
	yPos = y;
	xDest = x;
	yDest = y;
	id = theID;
	passengerCapacity = 12;
	maxVolume = 48;
	maxWeight = 1000;
}

bool PassengerDrone::canLoadPassenger(Individual & passenger)
{
    if (passengers.size() >= passengerCapacity)
        return false;
    if (passenger.getPossessionVolume() + contentVolume > maxVolume)
        return false;
    if (passenger.getPossessionWeight() + contentWeight > maxWeight)
        return false;
    return true;
}

void PassengerDrone::loadPassenger(Individual * passenger)
{
    passengers.insert({passenger->getID(), passenger});
 	passenger->setDrone(this);
    
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

int PassengerDrone::getCapacity()
{
	return passengerCapacity;
}

void PassengerDrone::deliveryCheck(int roadConc)
{
	if(canDeliveryCheck)
	{
		PassengerDrone* theDrone = this;
		//Check all deliveries to see if any are adjacent
		std::list<Drone::Delivery> deliveries = theDrone->getDeliveries();
		for(std::list<Drone::Delivery>::iterator deliveryIter = deliveries.begin(); deliveryIter != deliveries.end(); deliveryIter++)
		{
			Drone::Delivery theDelivery = (*deliveryIter);
			
			//If they're not onboard
			if(!theDrone->passengerExists(theDelivery.who->getID()))
			{
				Individual* who = theDelivery.who;
				Building* where = who->getBuilding();
				if(theDrone->isAdjacent(where))
				{
					if(!where->occupantExists(who->getID()))
					{
						//This should only occur if the individual thinks it's somewhere it's not, which should never occur
						std::cout << "ERROR: Individual/Building pairing is one-way.\n";
					}
					else if(!theDrone->canLoadPassenger(*who))
					{
						//This should never occur if we implement requests correctly 
						//Passenger cannot be loaded; add a new path to pick them up later
						theDrone->createMoveList(where->getXRoad(),where->getYRoad(),roadConc);
						
						//We'll also need to drop them off
						theDrone->createMoveList(theDelivery.where->getXRoad(),theDelivery.where->getYRoad(),roadConc);
						
						std::cout << "(" << theDrone->getID() << ") Can't load passenger "<< who->getID() << std::endl;
					}
					else
					{
						theDrone->loadPassenger(who);
						where->removeOccupant(who->getID());
						
						//std::cout << "(" << theDrone->getID() << ") Picked up passenger "<< who->getID() << std::endl;
					}
				}
			}
			else	//They're onboard
			{
				Individual* who = theDelivery.who;
				Building* where = theDelivery.where;					
				
				if(theDrone->isAdjacent(where))
				{
					if(!where->canAddOccupant(*who))
					{
						//Passenger cannot be unloaded, so drop them off later
						theDrone->createMoveList(where->getXRoad(),where->getYRoad(),roadConc);
						//std::cout << "(" << theDrone->getID() << ") Can't unload passenger "<< who->getID() << std::endl;
					}
					else
					{
						theDrone->unloadPassenger(who->getID());
						where->addOccupant(who);
						//std::cout << "(" << theDrone->getID() << ") Dropped off passenger " << who->getID() << std::endl;
						
						theDrone->removeDelivery(who->getID());
						who->setPassengerRequest(nullptr);
						//if(theDrone->getDeliveries().empty())
							//theDrone->createMoveList(6,10,roadConc);
					}
				}
			}
		}
	}
}
