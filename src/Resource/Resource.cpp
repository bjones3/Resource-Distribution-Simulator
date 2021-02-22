#include "../../inc/rds.hpp"
#include "../../inc/Resource/Resource.hpp"

Resource::Resource()
{
	weightRange.min = 0.01;
	weightRange.max = 6000; //max load of a 20ft Uhaul
	volumeRange.min = 0.01;
	volumeRange.max = 1000; //max volume of second largest UHaul
	wearFactorRange.min = 0;
	wearFactorRange.max = 1;
	wear = 1;
	minWear = 0.001;

	weight = genWeight(weightRange);
	volume  = genVolume(volumeRange);
	wearFactor  = genWearFactor(wearFactorRange);

	//id = ID::generateID();
}
/*
Resource::Resource(const Resource & resource)
{
	weight = resource.weight;
	volume = resource.volume;
	wearFactor = resource.wearFactor;
	wear = resource.wear;
}
*/

double Resource::genWeight(struct range inWeight)
{
	double f = (double)rand() / RAND_MAX;
	return (f * (inWeight.max - inWeight.min) + inWeight.min);
}

double Resource::genVolume(struct range inVolume)
{
	double f = (double)rand() / RAND_MAX;
	return (f * (inVolume.max - inVolume.min) + inVolume.min);
}

double Resource::genWearFactor(struct range inWearFactor)
{
	double f = (double)rand() / RAND_MAX;
	return (f * (inWearFactor.max - inWearFactor.min) + inWearFactor.min);
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

bool Resource::use()
{
	wear = wear*wearFactor;
	return (wear>=minWear);
}

/*Building Resource::getNextBuilding()
{
	return nextBuilding;
}*/

Building Resource::getBuilding()
{
	return *building;
}

long long int Resource::getID()
{
	return id;
}
