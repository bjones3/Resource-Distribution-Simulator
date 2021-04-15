#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "rds.hpp"

class Location
{
	public:
		Location(int xpos, int ypos);
		int getXPos();
		int getYPos();
	
	private:
		int xPos, yPos;
};

#endif
