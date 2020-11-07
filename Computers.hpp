#ifndef COMPUTERS_HPP
#define COMPUTERS_HPP

class Computers: public ElectronicItem: 
{


iC()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 2;
  weightRange.max = 10;
  volumeRange.min = 0.5;
  volumeRange.max = 3;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
