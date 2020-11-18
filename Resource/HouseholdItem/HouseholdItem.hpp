#ifndef HOUSEHOLDITEM_HPP
#define HOUSEHOLDITEM_HPP

#include "../Resource.hpp"

class HouseholdItem: public Resource
{


HouseholdItem{
  wearFactorRange.min = 0.6;
  wearFactorRange.max = 0.9999;
  weightRange.min = 0.1;
  weightRange.max = 15;
  volumeRange.min = 0.001;
  volumeRange.max = 0.7S;
  wear = 1;
  minWear = 0.0001;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
