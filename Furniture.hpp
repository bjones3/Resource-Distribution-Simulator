struct range{
    double min;
    double max;
};

class Furniture : public Resources {
        struct range weightRange{10, 1000}; //numbers off the top of my head
        struct range volumeRange{1, 729}; //assumed cubic feet; max is a 9 by 9 by 9 bouncy house
        struct range wearFactorRange{0.5, .99}; //range off the top of my ead

        Furniture(double inWeight, double inVolume, double inWearFactor){
            weight = genWeight(weightRange);
            volume  = genVolume(volumeRange);
            wearFactor  = genWearFactor(wearFactorRange);
            wear = 1;
        }

        virtual double genWeight(struct range inWeight){
           return (rand() % inWeight.max + inWeight.min);
        }
        virtual double genVolume(struct range inVolume){
           return (rand() % inVolume.max + inVolume.min);
        }
        virtual double genWearFactor(struct range inWearFactor){
           return (rand() % inWearFactor.max + inWearFactor.min);
        }
}

