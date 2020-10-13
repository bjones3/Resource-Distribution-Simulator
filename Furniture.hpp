class Furniture : public Resources {

    Furniture(){
        wearFactorRange.min = 0.9995;
        wearFactorRange.max = 0.9999;  
        weightRange.min = 1;
        weightRange.max = 800; 
        volumeRange.min = 1;
        volumeRange.max = 100; //based on 11x3x3 5 person sofa
        wearFactorRange.min = 0;
        wearFactorRange.max = 1;
        wear = 1;

        weight = genWeight(weightRange);
        volume  = genVolume(volumeRange);
        wearFactor  = genWearFactor(wearFactorRange);
    }
};

