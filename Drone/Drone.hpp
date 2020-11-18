

#ifndef DRONE_HPP
#define DRONE_HPP

#include <list>
#include "../Resource/Resource.hpp"
#include "../Individual/Individual.hpp"
#include "CargoDrone.hpp"
#include "PassengerDrone.hpp"

class Drone
{

private:
  long long int id;
  double maxVolume;
  double maxWeight;
  std::list<Resource> payload;
  double contentVolume;
  double contentWeight;
  int xPos;
  int yPos;

public:
  Drone(int x, int y)
  {
    xPos = x;
    yPos = y;
    id = ID::generateID();

  }

int getXPosition()
{
  return xPos;
}

int getYPosition()
{

  return yPos;

}

long long int getID()
{

  return id;

}

};


#endif
