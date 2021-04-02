#include "../../inc/rds.hpp"

CargoDrone::CargoDrone(int x, int y, long long int theID) : Drone::Drone(x, y, theID)
{
	xPos = x;
	yPos = y;
	id = theID;
	maxVolume = 1000;
	maxWeight = 6000;
}

bool CargoDrone::canLoadCargo(Resource & resource)
{
	if (resource.getVolume() + contentVolume > maxVolume)
		return false;
	if (resource.getWeight() + contentWeight > maxWeight)
		return false;
	return true;
}

bool CargoDrone::canLoadCargo(std::list <Resource*> & resources)
{

	double volume = contentVolume;
	double weight = contentWeight;

	std::list<Resource*>::iterator iter = resouces.begin();

	for(iter;iter!=resources.end();iter++)
	{

		volume += (*iter)->getVolume();
		weight += (*iter)->getWeight()

		if(volume > maxVolume)
			return false;

		if(weight > max)
			return false;
	}

	return true;

}

void CargoDrone::loadCargo(Resource * resource)
{
    payload.insert({resource->getID(), resource});
}

void CargoDrone::loadCargo(std::list<Resource*> & resources)
{

	std::list<Resource*>::iterator iter = resources.begin();
	for(iter; iter!=resources.end();iter++)
	{

		loadCargo(*iter);

	}

}


Resource* CargoDrone::unloadCargo(long long int resource){
    Resource * what = payload.find(resource)->second;
	payload.erase(resource);
	return what;
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
			if(!theDrone->payloadExists(theDelivery.what.front()->getID()))
			{
				std::list<Resource*> what = theDelivery.what;
				Building* where = what->getBuilding();
				if(theDrone->isAdjacent(where))
				{
					if(!where->payloadExists(what.front()->getID())
					{
						//This should only occur if the individual thinks it's somewhere it's not, which should never occur
						std::cout << "ERROR: Individual/Building pairing is one-way.\n";
					}
					else if(!theDrone->canLoadCargo(what))
					{
						//This should never occur if we implement requests correctly
						//Passenger cannot be loaded; add a new path to pick them up later
						theDrone->createMoveList(where->getXRoad(),where->getYRoad(),roadConc);

						//We'll also need to drop them off
						theDrone->createMoveList(theDelivery.where->getXRoad(),theDelivery.where->getYRoad(),roadConc);
					}
					else
					{
						theDrone->loadCargo(what);
						where->removeResource(what);

						std::cout << "(" << theDrone->getID() << ") Picked up passenger "<< who->getID() << std::endl;
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
					}
					else
					{
						theDrone->unloadPassenger(who->getID());
						where->addOccupant(who);
						std::cout << "(" << theDrone->getID() << ") Dropped off passenger " << who->getID() << std::endl;

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

bool CargoDrone::payloadExists(long long int pId)
{
	return payload.find(pId) != payload.end();
}

std::unordered_map <long long int, Resource*> CargoDrone::getPayload()
{
	return payload;
}

double CargoDrone::getMaxVolume()
{

	return maxVolume;

}

double CargoDrone::getMaxWeight()
{

	return maxWeight;

}
