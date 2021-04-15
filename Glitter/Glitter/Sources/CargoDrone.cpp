#include "rds.hpp"

CargoDrone::CargoDrone(int x, int y, long long int theID) : Drone::Drone(x, y, theID)
{
	xPos = x;
	yPos = y;
	xDest = x;
	yDest = y;
	id = theID;
	maxVolume = 1000;
	maxWeight = 6000;
}

bool CargoDrone::canLoadCargo(Resource & resource)
{
	if(resource.getVolume() + contentVolume > maxVolume)
		return false;
	if(resource.getWeight() + contentWeight > maxWeight)
		return false;
	return true;
}

bool CargoDrone::canLoadCargo(std::list<Resource*> & resources)
{
	double volume = contentVolume;
	double weight = contentWeight;

	std::list<Resource*>::iterator iter;

	for(iter = resources.begin(); iter != resources.end(); iter++)
	{
		volume += (*iter)->getVolume();
		weight += (*iter)->getWeight();

		if(volume > maxVolume)
			return false;

		if(weight > maxWeight)
			return false;
	}

	return !resources.empty();
}

void CargoDrone::loadCargo(Resource * resource)
{
    payload.insert({resource->getID(), resource});
    resource->setDrone(this);
}

void CargoDrone::loadCargo(std::list<Resource*> & resources)
{
	std::list<Resource*>::iterator iter;
	for(iter = resources.begin(); iter != resources.end(); iter++)
		loadCargo(*iter);
}

Resource* CargoDrone::unloadCargo(long long int resource)
{
    Resource * what = payload.find(resource)->second;
	payload.erase(resource);
	what->setDrone(nullptr);
	return what;
}

std::list<Resource*> CargoDrone::unloadCargo(std::list<Resource*> resources)
{
	std::list<Resource*> rList;
	std::list<Resource*>::iterator iter = resources.begin();
	for(iter; iter!=resources.end(); iter++)
		rList.push_back(unloadCargo((*iter)->getID()));

	return rList;
}

void CargoDrone::deliveryCheck(int roadConc)
{
	if(canDeliveryCheck)
	{
		CargoDrone* theDrone = this;
		//Check all deliveries to see if any are adjacent
		std::list<Drone::Delivery> deliveries = theDrone->getDeliveries();
		for(std::list<Drone::Delivery>::iterator deliveryIter = deliveries.begin(); deliveryIter != deliveries.end(); deliveryIter++)
		{
			Drone::Delivery theDelivery = (*deliveryIter);

			//If the resources are not onboard
			if(!theDrone->payloadExists(theDelivery.what.front()->getID()))
			{
				std::list<Resource*> what = theDelivery.what;
				Building* where = what.front()->getBuilding();
				if(theDrone->isAdjacent(where))
				{
					if(!where->resourcesExist(what))
					{
						//This should only occur if the resource thinks it's somewhere it's not, which should never occur
						std::cout << "ERROR: Resource/Building pairing is one-way.\n";
					}
					else if(!theDrone->canLoadCargo(what))
					{
						//This should never occur if we implement requests correctly
						//Resources cannot be loaded; add a new path to pick them up later
						theDrone->createMoveList(where->getXRoad(), where->getYRoad(), roadConc);

						//We'll also need to drop them off
						theDrone->createMoveList(theDelivery.where->getXRoad(), theDelivery.where->getYRoad(), roadConc);
						
						std::cout << "(" << theDrone->getID() << ") Can't load resource "<< what.front()->getID() << std::endl;
					}
					else
					{
						theDrone->loadCargo(what);
						where->removeResources(what);

						std::cout << "(" << theDrone->getID() << ") Picked up resource "<< what.front()->getID() << std::endl;
					}
				}
			}
			else	//The resources are onboard
			{
				std::list<Resource*> what = theDelivery.what;
				Building* where = theDelivery.where;
				Individual* who = theDelivery.who;

				if(theDrone->isAdjacent(where))
				{
					if(!where->canAddResources(what))
					{
						//Resources cannot be unloaded, so drop them off later
						theDrone->createMoveList(where->getXRoad(), where->getYRoad(), roadConc);
						
						double volume = 0;
						std::list<Resource*>::iterator it;
						for(it = what.begin(); it != what.end(); it++)
							volume += (*it)->getVolume();
						
						std::cout << "(" << theDrone->getID() << ") Can't unload resource "<< what.front()->getID() << "; " << where->getMaxContentVolume() << ", " << where->getContentVolume() + volume << std::endl;
					}
					else
					{
						theDrone->unloadCargo(what);
						where->addResources(what);
						std::cout << "(" << theDrone->getID() << ") Dropped off resource " << what.front()->getID() << std::endl;

						theDrone->removeDelivery(who->getID());
						who->setCargoRequest(nullptr);
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
