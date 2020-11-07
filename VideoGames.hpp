#ifndef VIDEOGAMES_HPP
#define VIDEOGAMES_HPP

class VideoGames: public ElectronicItem
{


VideoGames()
{
  wearFactorRange.min = 0.8;
  wearFactorRange.max = 0.999;
  weightRange.min = 0.25;
  weightRange.max = ;
  volumeRange.min = 1;
  volumeRange.max = 7;
  wear = 1;
  minWear = 0.01;

  weight = genWeight(weightRange);
  volume  = genVolume(volumeRange);
  wearFactor  = genWearFactor(wearFactorRange);
}
};
#endif
