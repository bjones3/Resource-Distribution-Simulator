#ifndef CARGODRONE_HPP
# define CARGODRONE_HPP

# include "Drone.hpp"
# include "../Resource/Resource.hpp"

class CargoDrone : public Drone
{
	public:
		CargoDrone(int x, int y, long long int newId);
		bool		canLoadCargo(Resource & resource);
		void		loadCargo(Resource & resource);
		Resource	unloadCargo(Resource & resource);
};

#endif