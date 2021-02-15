//# include <list>
//# include "../Resource.hpp"
//# include "../Individual/Individual.hpp"
//# include "CargoDrone.hpp"
//# include "PassengerDrone.hpp"

//#include "../../inc/Drone/Drone.hpp"
#include "../../inc/rds.hpp"

Drone::Drone(int x, int y)
{
	xPos = x;
	yPos = y;
	xDest = x;
	yDest = y;
	//id = ID::generateID();
}

void Drone::setDest(int xpos, int ypos)
{
	xDest = xpos;
	yDest = ypos;
	//drive();
}

void Drone::drive()
{

}

int Drone::getXPosition()
{
	return xPos;
}

int Drone::getYPosition()
{
	return yPos;
}

int Drone::getXDest()
{
	return xDest;
}

int Drone::getYDest()
{
	return yDest;
}

long long int Drone::getID()
{
	return id;
}