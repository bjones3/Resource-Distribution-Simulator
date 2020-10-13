#include <stdlib.h>
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

class Resource
{

struct range
{

  double min;
  double max;

};

private:
  double weight;
  double volume;
  double wearFactor;
  double wear;
//possibly add a "minWear factor for the minimum wear before it can no longer be used"


public:
  Resource(double weight, double volume, double wearFactor, double wear)
  {
    this.weight = weight;
    this.volume = volume;
    this.wearFactor = wearFactor;
    this.wear = wear;
    range.min = 0
    range.max =
  }

  Resource(const Resource & resource)
  {
    weight = resource.weight;
    volume = resource.volume;
    wearFactor = resource.wearFactor;
    wear = resource.wear;
  }

  double getWeight()
  {
    return weight;
  }

  double getVolume()
  {
    return volume;
  }
  double getWearFactor()
  {
    return wearFactor;
  }
  double getWear()
  {
    return wear;
  }
  double use()
  {
    wear = wear*wearFactor;
  }


};

#endif
