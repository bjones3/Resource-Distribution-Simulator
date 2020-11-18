#ifndef BATHROOMITEM_HPP
#define BATHROOMITEM_HPP

#include "../Resource.hpp"

class BathroomItem: public Resource
{


BathroomItem{
  wearFactorRange.min = 0.6;
  wearFactorRange.max = 0.98;
  weightRange.min = 0.03;
  weightRange.max = 3;
  volumeRange.min = 0.001;
  volumeRange.max = 0.15;
  wear = 1;
  minWear = 0.05;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
