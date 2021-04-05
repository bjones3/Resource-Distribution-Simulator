#ifndef BUILDING_HPP
# define BUILDING_HPP

# include "../rds.hpp"
# include <unordered_map>

class Building
{
	protected:
		int						xPos;
		int						yPos;
		int						xRoad;
		int						yRoad;
		long long int			id;
    std::unordered_map<long long int, Individual*> occupants;
    std::unordered_map<long long int, Resource*> contents;
		int						occupantCapacity;
		double					contentVolumeCapacity;
		double					contentVolume;

	public:
		Building();
		Building(int x, int y, int roadx, int roady);
		int				getOccupantAmount();
		int				getOccupantCapacity();
		std::unordered_map<long long int, Individual*> getOccupants();
		std::unordered_map<long long int, Resource*> getContents();
		bool			canAddOccupant(Individual & occupant);
		void			addOccupant(Individual * occupant);
		bool 			occupantExists(long long int occupant);
		Individual*		removeOccupant(long long int occupant);
		bool			canAddResource(Resource & resource);
		bool			canAddResources(std::list<Resource*> resources);
		void			addResource(Resource * resource);
		void			addResources(std::list<Resource*> resources);
		bool			resourceExists(long long int resource);
		bool			resourcesExist(std::list<Resource*> resources);
		Resource*		removeResource(long long int resource);
		std::list<Resource*> removeResources(std::list<Resource*> resources);
		bool			canBringOccupant(Individual & occupant);
		bool			canBringContents(Resource & resource);
		int				getXPos();
		int				getYPos();
		int				getXRoad();
		int				getYRoad();
		long long int	getID();
		void			setID(long long int theID);
		double			getContentVolume();
		double			getMaxContentVolume();
};

#endif
