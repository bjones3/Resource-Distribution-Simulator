#ifndef PASSENGERDRONE_HPP
# define PASSENGERDRONE_HPP

# include "Drone.hpp"

class PassengerDrone : public Drone
{
	private:
		int passengerCapacity;
		std::list<Individual> passengers;

	public:
		PassengerDrone(int x, int y);
		bool		canLoadPassenger(Individual & passenger);
		void		loadPassenger(Individual & passenger);
		Individual	unloadPassenger(Individual & passenger);
};

#endif