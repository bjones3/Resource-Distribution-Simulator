#ifndef PASSENGERDRONE_HPP
# define PASSENGERDRONE_HPP

# include "../rds.hpp"

class PassengerDrone : public Drone
{
	private:
		int passengerCapacity;
		std::unordered_map<long long int, Individual*> passengers;


	public:
		PassengerDrone(int x, int y, long long int theID);
		bool		canLoadPassenger(Individual & passenger);
		void		loadPassenger(Individual * passenger);
		bool 		passengerExists(long long int passenger);
		Individual*	unloadPassenger(long long int passenger);
		std::unordered_map<long long int, Individual*> getPassengers();
		int			getCapacity();
};

#endif
