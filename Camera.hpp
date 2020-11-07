#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera: public ElectronicItem
{


Camera()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 0.015;
  weightRange.max = 2;
  volumeRange.min = 0.01;
  volumeRange.max = 0.1;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
