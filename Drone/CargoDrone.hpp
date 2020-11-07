#ifndef CARGODRONE_HPP
#define CARGODRONE_HPP


class CargoDrone : public Drone
{

public:

  CargoDrone(int x, int y)
  {

    xPos = x;
    yPos = y;
    id = ID::generateID();

    maxVolume = 1000;
    maxWeight = 6000;

    contentVolume = 0;
    contentWeight = 0;

  }

  bool canLoadCargo(Resource & resource)
  {

    if(resource.getVolume() + contentVolume > maxVolume)
    {

      return false;

    }

    if(resource.getWeight() + contentVolume > maxWeight)
    {

      return false;

    }

    return true;
  }

void loadCargo(Resource & resource)
{

  payload.push_back(resource);

}

Resource unloadCargo(Resources & resource)
{

  std::list<Resource>::iterator temp = payload.begin();
  for(temp;temp!=payload.end();temp++)
  {

    if(*temp.getID() == resource.getID())
    {

      payload.erase(temp);

      return resource;

    }

  }

}


}


#endif
