#include "Building.hpp"


#ifndef HOUSE_HPP
#define HOUSE_HPP

class House: public Building
{

House(int x, int y)
{

  xPos = x;
  yPos = y;
  volumeCapacity = 5000;
  occupantCapacity = 6;
  contentVolume = 0;

}

};




#endif
