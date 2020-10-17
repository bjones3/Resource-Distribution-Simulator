#ifndef FURNITURE_HPP
#define FURNITURE_HPP

class Furniture : public Resources {

    Furniture(){
        wearFactorRange.min = 0.9995;
        wearFactorRange.max = 0.9999;
        weightRange.min = 1;
        weightRange.max = 800;
        volumeRange.min = 1;
        volumeRange.max = 100; //based on 11x3x3 5 person sofa
        wear = 1;
        minWear = 0.01;

        weight = genWeight(weightRange);
        volume  = genVolume(volumeRange);
        wearFactor  = genWearFactor(wearFactorRange);
    }
};


#endif
