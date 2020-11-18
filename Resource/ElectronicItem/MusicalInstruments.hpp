#ifndef MUSICALINSTRUMENTS_HPP
#define MUSICALINSTRUMENTS_HPP

#include "ElectronicItem.hpp"

class MusicalInstruments: public ElectronicItem
{


MusicalInstruments()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 5;
  weightRange.max = 300;
  volumeRange.min = 1;
  volumeRange.max = 27;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
