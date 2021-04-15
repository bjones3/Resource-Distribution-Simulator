#ifndef FOODITEM_HPP
#define FOODITEM_HPP

#include "../Resource.hpp"

class FoodItem: public Resource
{


FoodItem()
{
  wearFactorRange.min = 0;
  wearFactorRange.max = 0;
  weightRange.min = .2;
  weightRange.max = 30;
  volumeRange.min = 0.05;
  volumeRange.max = 1; //based on 11x3x3 5 person sofa
  wear = 1;
  minWear = 0;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
