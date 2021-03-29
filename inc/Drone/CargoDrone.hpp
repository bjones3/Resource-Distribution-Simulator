#ifndef CARGODRONE_HPP
# define CARGODRONE_HPP

# include "../rds.hpp"

class CargoDrone : public Drone
{
	public:
		CargoDrone(int x, int y, long long int theId);
		bool		canLoadCargo(Resource & resource);
		void		loadCargo(Resource & resource);
		Resource	unloadCargo(Resource & resource);
};

#endif
