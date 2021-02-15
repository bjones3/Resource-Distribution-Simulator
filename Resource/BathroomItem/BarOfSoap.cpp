#include "BarOfSoap.h"

BarOfSoap::BarOfSoap()
{

  wearFactorRange.min = 0.4;
  wearFactorRange.max = 0.5;
  weightRange.min = 0.20;
  weightRange.max = 0.25;
  volumeRange.min = 0.005;
  volumeRange.max = 0.01;
  wear = 1;
  minWear = 0.05;

  weight = genWeight(weightRange);
  volume = genVolume(volumeRange);
  wearFactor = genWearFactor(wearFactorRange);

}
