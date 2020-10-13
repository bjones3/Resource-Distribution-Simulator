#include <stdlib.h>
#ifndef RESOURCE_HPP
#define RESOURCE_HPP

struct range
{
    double min;
    double max;
};


class Resource
{
    private:
        double weight; //pounds
        double volume; //cubic feet
        double wearFactor; //between 0 and 1
        double wear; //between 0 and 1
        struct range weightRange;
        struct range volumeRange;
        struct range wearFactorRange;

    public:
        Resource() {
            weightRange.min = 0.01; weightRange.max = 6000; //max load of a 20ft Uhaul
            volumeRange.min = 0.01; volumeRange.max = 1000; //max volume of second largest UHaul 
            wearFactorRange.min = 0; wearFactorRange.max = 1;
            weight = genWeight(weightRange);
            volume  = genVolume(volumeRange);
            wearFactor  = genWearFactor(wearFactorRange);
            wear = 1;
        }
/*
        Resource(const Resource & resource)
        {
            weight = resource.weight;
            volume = resource.volume;
            wearFactor = resource.wearFactor;
            wear = resource.wear;
        }
*/

        double genWeight(struct range inWeight){
            double f = (double) rand()/ RAND_MAX;
            return (f*(inWeight.max - inWeight.min) + inWeight.min);
        }
        double genVolume(struct range inVolume){
          double f = (double) rand()/ RAND_MAX;
          return (f*(inVolume.max - inVolume.min) + inVolume.min);        }
        double genWearFactor(struct range inWearFactor){
          double f = (double) rand()/ RAND_MAX;
          return (f*(inWearFactor.max - inWearFactor.min) + inWearFactor.min);        }

        double getWeight()
        {
            return weight;
        }

        double getVolume()
        {
            return volume;
        }
        double getWearFactor()
        {
            return wearFactor;
        }
        double getWear()
        {
            return wear;
        }
        bool use()
        {
            wear = wear*wearFactor;
            return (wear>0.001);
        }

};

#endif
