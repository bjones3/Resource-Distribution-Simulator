#include "Building.hpp"


#ifndef Office_HPP
#define Office_HPP

class Office: public Building
{

Office(int x, int y)
{

  xPos = x;
  yPos = y;
  volumeCapacity = 45000;
  occupantCapacity = 80;
  contentVolume = 0;

}

};




#endif
