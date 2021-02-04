

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
  int xDest, yDest;

public:
  Drone(int x, int y)
  {
    xPos = x;
    yPos = y;
    xDest = x;
    yDest = y;
    id = ID::generateID();
  }

	void setDest(int xpos, int ypos)
	{
		xDest = xpos;
		yDest = ypos;
		//drive();
	}
	
	void drive()
	{
		
	}

	int getXPosition()
	{
	  return xPos;
	}

	int getYPosition()
	{
	  return yPos;
	}

	int getXDest()
	{
	  return xDest;
	}

	int getYDest()
	{
	  return yDest;
	}

	long long int getID()
	{
	  return id;
	}

};


#endif
