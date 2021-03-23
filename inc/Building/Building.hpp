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
    std::unordered_map<long long int, Individual&> occupants;
    std::unordered_map<long long int, Resource&> contents;
		int						occupantCapacity;
		double					contentVolumeCapacity;
		double					contentVolume;

	public:
		Building();
		Building(int x, int y, int roadx, int roady);
		int				getOccupantAmount();
		int				getOccupantCapacity();
		bool			canAddOccupant(Individual & occupant);
		void			addOccupant(Individual & occupant);
		//TODO: Change occupants list to a hash
		Individual*		removeOccupant(Individual & occupant);
		bool			canAddResource(Resource & resource);
		void			addResource(Resource & resource);
		Resource		removeResource(Resource & resource);
		bool			canBringOccupant(Individual & occupant);
		bool			canBringContents(Resource & resource);
		std::unordered_map<long long int, Resource> getContents();
		int				getXPos();
		int				getYPos();
		int				getXRoad();
		int				getYRoad();
		long long int	getID();
};

#endif
