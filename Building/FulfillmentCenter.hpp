#include "Building.hpp"


#ifndef FULFILLMENTCENTER_HPP
#define FULFILLMENTCENTER_HPP

class FulfillmentCenter: public Building
{

FulfillmentCenter(int x, int y)
{

  xPos = x;
  yPos = y;

}

CargoDrone createResourceDrone()
{

 return new CargoDrone(xPos,yPos);

}

PassengerDrone createPassengerDrone()
{

  return new PassengerDrone(xPos,yPos);

}

Resource createResource(Resource & resource)
{

  return resource;

}

};




#endif
