#ifndef BUILDING_HPP
# define BUILDING_HPP

#include <unordered_map>
#include "../rds.hpp"
#include "../Individual/Individual.hpp"
#include "../Resource/Resource.hpp"

class Building
{
    protected:
        int						xPos;
        int						yPos;
        long long int			id;
        std::unordered_map<long long int, Individual> occupants;
        std::unordered_map<long long int, Resource> contents;
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
        Individual		removeOccupant(Individual & occupant);
        bool			canAddResource(Resource & resource);
        void			addResource(Resource & resource);
        Resource		removeResource(Resource & resource);
        bool			canBringOccupant(Individual & occupant);
        bool			canBringContents(Resource & resource);
        int				getXPos();
        int				getYPos();
        long long int	getID();
};

#endif
