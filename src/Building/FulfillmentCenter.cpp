#include "../../inc/Building/FulfillmentCenter.hpp"

FulfillmentCenter::FulfillmentCenter(int x, int y)
{
  xPos = x;
  yPos = y;
  volumeCapacity = 500000;
  occupantCapacity = 0;
  contentVolume = 0;
  std::list<Drone> drones;
  droneCapacity = 100;
}

CargoDrone FulfillmentCenter::createResourceDrone()
{

 return new CargoDrone(xPos,yPos);

}

PassengerDrone FulfillmentCenter::createPassengerDrone()
{

  return new PassengerDrone(xPos,yPos);

}

Resource FulfillmentCenter::createResource(Resource & resource)
{

  return resource;

}
