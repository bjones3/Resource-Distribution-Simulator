#ifndef SPORTSITEM_HPP
#define SPORTSITEM_HPP

class SportsItem: public Resource
{


SportsItem{
  wearFactorRange.min = 0.9;
  wearFactorRange.max = 0.999;
  weightRange.min = 0.05;
  weightRange.max = 15;
  volumeRange.min = 0.03;
  volumeRange.max = 0.5;
  wear = 1;
  minWear = 0.001;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
