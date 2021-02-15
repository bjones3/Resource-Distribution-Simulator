#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <list>
#include <algorithm>
#include "../Individual/Individual.hpp"
#include "../Resource.hpp"
#include "../Drone/Drone.hpp"

class Building
{

protected:
  int xPos;
  int yPos;
  long long int id;
  std::list<Individual> occupants;
  std::list<Resource> contents;
  int occupantCapacity;
  double contentVolumeCapacity;
  double contentVolume;

public:
  Building(int x, int y);

  int getOccupantAmount();

  int getOccupantCapacity();
  
  bool canAddOccupant(Individual & occupant);

  void addOccupant(Individual & occupant);

	//TODO: Change occupants list to a hash
  Individual removeOccupant(Individual & occupant);

  bool canAddResource(Resource & resource);

  void addResource(Resource & resource);

  Resource removeResource(Resource & resource);

  bool canBringOccupant(Individual & occupant);

  bool canBringContents(Resource & resource);
  
  int getXPos();

  int getYPos();

  long long int getID();
};

#endif
