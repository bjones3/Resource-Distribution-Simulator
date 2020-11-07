#include "Building.hpp"


#ifndef OFFICE_HPP
#define OFFICE_HPP

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
