#ifndef TV_HPP
#define TV_HPP

class TV: public ElectronicItem
{


TV()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 5;
  weightRange.max = 60;
  volumeRange.min = 1;
  volumeRange.max = 9;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
