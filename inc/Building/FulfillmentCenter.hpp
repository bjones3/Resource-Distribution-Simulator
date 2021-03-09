#ifndef FULFILLMENTCENTER_HPP
# define FULFILLMENTCENTER_HPP

# include "../rds.hpp"

class FulfillmentCenter : public Building
{
	private:
		int droneCapacity;
		std::list<Drone> drones;

	public:
		FulfillmentCenter(int x, int y);
		CargoDrone createResourceDrone();
		PassengerDrone createPassengerDrone();
		Resource createResource(Resource & resource);
};

#endif