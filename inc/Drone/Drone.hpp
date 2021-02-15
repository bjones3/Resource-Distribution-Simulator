#ifndef DRONE_HPP
# define DRONE_HPP

# include <list>
//# include "../Resource.hpp"
//# include "../Individual/Individual.hpp"
//# include "CargoDrone.hpp"
//# include "PassengerDrone.hpp"

class Drone
{
	private:
		long long int		id;
		int					xPos, xPos;
		int					xDest, yDest;
		double				contentVolume;
		double				contentWeight;
		double				maxVolume;
		double				maxWeight;
		std::list<Resource>	payload;

	public:
		Drone(int x, int y);
		long long int	getID();
		void			setDest(int xpos, int ypos);
		void			drive();
		int				getXPosition();
		int				getYPosition();
		int				getXDest();
		int				getYDest();
};

#endif