#ifndef SPEAKER_HPP
#define SPEAKER_HPP

class Speaker: public ElectronicItem
{


Speaker()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 0.015;
  weightRange.max = 40;
  volumeRange.min = 0.01;
  volumeRange.max = 10;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
