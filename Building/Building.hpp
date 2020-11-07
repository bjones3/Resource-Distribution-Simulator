#include <list>
#include "Individual.hpp"
#include "Resource.hpp"

#ifndef BUILDING_HPP
#define BUILDING_HPP

class Building
{

private:
  int xPos;
  int yPos;
  long long int id;
  std::list<Individual> occupants;
  std::list<Resource> contents;
  int occupantCapacity;
  double contentVolumeCapacity;
  double contentVolume;

public:
  Building(int x, int y)
  {

    xPos = x;
    yPos = y;
    contentVolume = 0;
    id = ID::generateID();

  }

  int getOccupantAmount()
  {

    return occupants.size();

  }



  int getOccupantCapacity()
  {

    return occupantCapacity;

  }

  void addOccupant(Individual & occupant)
  {

    occupants.push_front(occupant);

  }

  Individual removeOccupant(Individual & occupant)
  {
    std::list<Individual>::iterator temp = std::find(occupants->begin(),occupants->end(),occupant);
    Individual removedOccupant = *temp;
    occupants->remove(temp);
    return removedOccupant;

  }

  void addResource(Resource & resource)
  {

    contentVolume += resource.getVolume();
    contents.push_front(resource);

  }

  Resource removeResource(Resource & resource)
  {

    std::list<Resource>::iterator temp = std::find(contents->begin(),contents->end(),resource);
    Resource removedResource = *temp;
    contents->remove(temp);
    contentVolume -= resource.getVolume();
    return removedResource;

  }

  bool canBringOccupant(Individual & occupant)
  {

    if(occupants.size() == occupantCapacity)
    {
      return false;
    }

    if(occupant.getPossessionVolume() + contentVolume > contentVolumeCapacity)
    {
      return false;
    }

    return true;

  }

  bool canBringContents(Resource & resource)
  {

    if(resource.getVolume() + contentVolume > contentVolumeCapacity)
    {

      return false;

    }

  }
  int getXPos()
  {

    return xPos;

  }

  int getYPos()
  {

    return yPos;

  }

  long long int getID()
  {

    return id;

  }
}

#endif
