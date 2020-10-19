#include <list>
#include "Resource.hpp"

#ifndef DRONE_HPP
#define DRONE_HPP


class Drone
{

private:
  std::string ID;
  double maxVolume;
  double maxWeight;
  std::list<Resource> payload;
  int xPos;
  int yPos;

public:
  Drone(int x, int y)
  {
    xPos = x;
    yPos = y;
    ID = generateID();

  }

int getXPosition()
{
  return xPos;
}

int getYPosition()
{

  return yPos;

}



};


#endif
