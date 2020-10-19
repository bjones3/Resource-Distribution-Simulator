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
  std::list<Individual> occupants;
  std::list<Resource> contents;
  int occupantCapacity;
  int contentCapacity;

  Building()
  {




  }


  void addOccupant(Individual occupant)
  {

    occupants.push_front(occupant);


  }

  Individual removeOccupant(Individual occupant)
  {
    std::list<Individual>::Iterator temp = std::find(occupants->begin(),occupants->end(),occupant));
    Individual removedOccupant = *temp;
    occupants->remove(temp);
    return removedOccupant;

  }



}

#endif
