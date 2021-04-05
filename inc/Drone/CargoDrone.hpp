#ifndef CARGODRONE_HPP
# define CARGODRONE_HPP

# include "../rds.hpp"

class CargoDrone : public Drone
{
	public:
		CargoDrone(int x, int y, long long int theId);
		bool		canLoadCargo(Resource & resource);
		void		loadCargo(std::list<Resource*> & resources);
		bool		canLoadCargo(std::list<Resource*> & resources);
		void		loadCargo(Resource * resource);
		Resource*	unloadCargo(long long int resource);
		std::list<Resource*>	unloadCargo(std::list<Resource*> resources);
		void		deliveryCheck(int roadConc);
		bool 		payloadExists(long long int pId);
		std::unordered_map<long long int, Resource*> getPayload();
		double 		getMaxVolume();
		double		getMaxWeight();

};

#endif
