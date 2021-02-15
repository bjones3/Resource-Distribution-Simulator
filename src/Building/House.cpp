//#include "../../inc/Building/House.hpp"
#include "../../inc/rds.hpp"

House::House(int x, int y) : Building::Building(x, y)
{
	contentVolumeCapacity = 5000;
	occupantCapacity = 6;
}