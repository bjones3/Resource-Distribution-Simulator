
#ifndef PASSENGERDONE_HPP
#define PASSENGERDROE_HPP

#include "Drone.hpp"

class PassengerDrone: public Drone
{

private:
  int passengerCapacity;
  std::list<Individual> passengers;

public:
  PassengerDrone(int x, int y)
  {

    xPos = x;
    yPos = y;
    ID = generateID();
    passengerCapacity = 12;
    maxVolume = 48;
    maxWeight = 1000;

  }

bool canLoadPassenger(Individual & passenger)
{

  if(passengers.size() == passengerCapacity)
  {
    return false;
  }
  if(passenger.getPossessionVolume() + contentVolume > maxVolume)
  {
    return false;
  }
  if(passenger.getPossessionWeight() + contentWeight > mexWeight)
  {
    return false;
  }
  return true;
}

void loadPassenger(Individual & passenger)
{

  passengers.push_back(passenger);
  std::list<Resource> temp = passenger.getIndividualPossessions();
  std::list<Resource>::iterator iter = temp.begin();
  for(iter; iter!= temp.end(); iter++)
  {

    payload.push_back(iter*);

  }
}

 Individual unloadPassenger(Individual & passenger)
 {

   std::list<Individual>::iterator temp1 = passengers.begin();

   Individual ind = passenger;

   for(temp1; temp1!=passengers.end(); temp1++)
   {

     if(*temp1.getID() == passenger.getID())
     {
       passengers.erase(temp1);
     }

   }

   std::list<Resource>::iterator temp2 = payload.begin();
   std::list<Resource> possessions = passenger.getIndividualPossessions();
   std::list<Resource>::iterator temp3 = possessions.begin();

   for(temp2; temp2!=payload.end(); temp2++)
   {

     for(temp3; temp3!=possessions.end();temp3++)
     {

       if(*temp2.getID() == *temp3.getID())
       {

         payload.erase(temp2);

       }

     }

   }


   return ind;
 }

};

#endif
