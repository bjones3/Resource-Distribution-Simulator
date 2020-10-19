#ifndef CLOTHINGITEM_HPP
#define CLOTHINGITEM_HPP

class ClothingItem: public Resource
{


ClothingItem()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.99;
  weightRange.min = 0.06;
  weightRange.max = 8;
  volumeRange.min = 0.005;
  volumeRange.max = .5;
  wear = 1;
  minWear = 0.08;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
