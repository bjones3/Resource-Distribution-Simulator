#ifndef CARGODRONE_HPP
# define CARGODRONE_HPP

# include "../rds.hpp"
#include "Drone.hpp"

class CargoDrone : public Drone
{
	public:
		CargoDrone(int x, int y, long long int newId);
		bool		canLoadCargo(Resource & resource);
		void		loadCargo(Resource & resource);
		Resource	unloadCargo(Resource & resource);
};

#endif
