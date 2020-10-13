class Furniture : public Resources {

    Furniture(){
        weightRange{10, 1000}; //numbers off the top of my head
        volumeRange{1, 729}; //assumed cubic feet; max is a 9 by 9 by 9 bouncy house
        wearFactorRange{0.5, .99}; //range off the top of my ead
        weight = genWeight(weightRange);
        volume  = genVolume(volumeRange);
        wearFactor  = genWearFactor(wearFactorRange);
        wear = 1;
    }
}

