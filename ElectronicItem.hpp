#ifndef ELECTRONICITEM_HPP
#define ELECTRONICITEM_HPP

class ElectronicItem: public Resource
{


ElectronicItem()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 0.05;
  weightRange.max = 60;
  volumeRange.min = 0.001;
  volumeRange.max = 17.5;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
