#ifndef RESOURCE_HPP
# define RESOURCE_HPP

#include "../rds.hpp"

struct range
{
	double min;
	double max;
};

class Building;

class Resource
{
	private:
		Building		*building;
		Building		*newBuilding;
		double			weight; //pounds
		double			volume; //cubic feet
		double			wearFactor; //between 0 and 1
		double			wear; //between 0 and 1
		double			minWear;
		long long int	id;
		struct range	weightRange;
		struct range	volumeRange;
		struct range	wearFactorRange;

	public:
		Resource();
		//Resource(const Resource & resource);
		double			genWeight(struct range inWeight);
		double			genVolume(struct range inVolume);
		double			genWearFactor(struct range inWearFactor);
		double			getWeight();
		double			getVolume();
		double			getWearFactor();
		double			getWear();
		bool			use();
		Building		getNextBuilding();
		Building		getBuilding();
		long long int	getID();
};

#endif
