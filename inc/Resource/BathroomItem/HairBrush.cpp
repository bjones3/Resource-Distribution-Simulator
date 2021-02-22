#include "HairBrush.h"

HairBrush::HairBrush()
{

  wearFactorRange.min = 0.95;
  wearFactorRange.max = 0.99;
  weightRange.min = 0.05;
  weightRange.max = 0.10;
  volumeRange.min = 0.01;
  volumeRange.max = 0.015;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume = genVolume(volumeRange);
  wearFactor = genWearFactor(wearFactorRange);

}
