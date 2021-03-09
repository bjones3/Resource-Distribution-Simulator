
#include "../../inc/rds.hpp"

Resource::Resource( int theType, ResourceTable & table )
{
	type = theType;
	name = table.getName( theType );
	
	wearFactorRange.min = table.getValue(theType,WEAR_FACTOR_MIN);
	wearFactorRange.max = table.getValue(theType,WEAR_FACTOR_MAX);
	weightRange.min = table.getValue(theType,WEIGHT_MIN);
	weightRange.max = table.getValue(theType,WEIGHT_MAX);
	volumeRange.min = table.getValue(theType,VOLUME_MIN);
	volumeRange.max = table.getValue(theType,VOLUME_MAX);
	wear = table.getValue(theType,WEAR);
	minWear = table.getValue(theType,WEAR_MIN);
	
  	weight = genWeight(weightRange);
  	volume  = genVolume(volumeRange);
  	wearFactor  = genWearFactor(wearFactorRange);
  	
  	//id = ID::generateID();
}

double Resource::genWeight(struct range inWeight)
{
    double f = (double) rand()/ RAND_MAX;
    return (f*(inWeight.max - inWeight.min) + inWeight.min);
}

double Resource::genVolume(struct range inVolume)
{
    double f = (double) rand()/ RAND_MAX;
    return (f*(inVolume.max - inVolume.min) + inVolume.min);        
}

double Resource::genWearFactor(struct range inWearFactor)
{
    double f = (double) rand()/ RAND_MAX;
    return (f*(inWearFactor.max - inWearFactor.min) + inWearFactor.min);
}

double Resource::getWeight()
{
	return weight;
}

double Resource::getVolume()
{
	return volume;
}

double Resource::getWearFactor()
{
	return wearFactor;
}

double Resource::getWear()
{
	return wear;
}

int Resource::getType()
{
	return type;
}
	
std::string Resource::getName()
{
	return name;
}

bool Resource::use()
{
	wear = wear*wearFactor;
    return (wear>=minWear);
}
/*
Building Resource::getNextBuilding()
	return nextBuilding;

Building Resource::getBuilding()
	return building;*/

long long int Resource::getID()
{
	return id;
}
