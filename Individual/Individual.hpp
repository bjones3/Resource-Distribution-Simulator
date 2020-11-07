#include "map.hpp"
#include "Resource.hpp"
#include <list>

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

class Individual
{
private:
  int xPosition;
  int yPosition;
  std::string name;
  long long int id;
  std::list<Resource> possessions;
  double totalPossessionWeight;
  double totalPossessionVolume;

  std::string generateName()
  {

    return "";

  }


public:

  Individual(House house)
  {

    possessionWeight = 0;
    possessionVolume = 0;

    xPosition = house.getXPosition();
    yPosition = house.getYPosition();

    name = generateName();

    id = ID::generateID();

  }

  void doTask(List<Resource> & resources)
  {

    std::list<Resource>::iterator temp = resources.begin();

    for(temp; temp!=resources.end(); temp++)
    {
      temp->use();
    }

  }

  void addPossession(Resource & possession)
  {

    possessions.push_back(possession);

    totalPossessionWeight += possession.getWeight;
    totalPossessionVolume += possession.getVolume;

  }

  double getPossessionVolume()
  {

    return totalPossessionVolume;

  }

  double getPossessionWeight()
  {

    return totalPossessionWeight;

  }

  void movePosition(int newXPosition, int newYPosition)
  {

    matriarch.requestDrone(newXPosition, newYPosition);

  }

  std::list<Resource> getIndividualPossessions()
  {

    return possessions;

  }

};
#endif
