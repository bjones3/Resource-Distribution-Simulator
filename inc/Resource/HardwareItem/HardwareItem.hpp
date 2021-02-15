#ifndef HARDWAREITEM_HPP
#define HARDWAREITEM_HPP

#include "../Resource.hpp"

class HardwareItem: public Resource
{


FoodItem()
{
  wearFactorRange.min = 0;
  wearFactorRange.max = 0.9999;
  weightRange.min = 0.2;
  weightRange.max = 50;
  volumeRange.min = 0.2;
  volumeRange.max = 3;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
