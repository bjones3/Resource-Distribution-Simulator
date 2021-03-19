#ifndef BUILDING_HPP
# define BUILDING_HPP

# include "../rds.hpp"

class Building
{
	protected:
		int						xPos;
		int						yPos;
		int						roadX;
		int						roadY;
		long long int			id;
		std::list<Individual>	occupants;
		std::list<Resource>		contents;
		int						occupantCapacity;
		double					contentVolumeCapacity;
		double					contentVolume;

	public:
		Building();
		Building(int x, int y);
		int				getOccupantAmount();
		int				getOccupantCapacity();
		bool			canAddOccupant(Individual & occupant);
		void			addOccupant(Individual & occupant);
		//TODO: Change occupants list to a hash
		Individual		removeOccupant(Individual & occupant);
		bool			canAddResource(Resource & resource);
		void			addResource(Resource & resource);
		Resource		removeResource(Resource & resource);
		bool			canBringOccupant(Individual & occupant);
		bool			canBringContents(Resource & resource);
		std::list<Resource> getContents();
		std::list<Individual> getOccupants();
		int				getXPos();
		int				getYPos();
		long long int	getID();
};

#endif
