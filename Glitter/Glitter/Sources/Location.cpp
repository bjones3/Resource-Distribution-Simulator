#include "rds.hpp"

Location::Location(int xpos, int ypos)//: xpos(xPos), ypos(yPos)
  {
	xPos = xpos;
	yPos = ypos;
  }

int Location::getXPos()
  { return xPos; }

int Location::getYPos()
  { return yPos; }
  
