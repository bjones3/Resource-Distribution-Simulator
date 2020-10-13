class Furniture : public Resources {

    Furniture(){
        weightRange{10, 1000}; //numbers off the top of my head
        volumeRange{1, 729}; //assumed cubic feet; max is a 9 by 9 by 9 bouncy house
        wearFactorRange{0.5, .99}; //range off the top of my ead
            weightRange.min = 10; weightRange.max = 1000;
            volumeRange.min = 1; volumeRange.max = ;
            wearFactorRange.min = 0; wearFactorRange.max = 1;
        weight = genWeight(weightRange);
        volume  = genVolume(volumeRange);
        wearFactor  = genWearFactor(wearFactorRange);
        wear = 1;
    }
}

