#ifndef KITCHENITEM_HPP
#define KITCHENITEM_HPP

class KitchenItem: public Resource
{


KitchenItem()
{
  wearFactorRange.min = 0.70;
  wearFactorRange.max = 0.9999;
  weightRange.min = 0.1;
  weightRange.max = 20;
  volumeRange.min = 0.005;
  volumeRange.max = 0.15;
  wear = 1;
  minWear = 0.05;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
