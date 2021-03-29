#include "../../inc/rds.hpp"

House::House(int x, int y, int roadx, int roady) : Building::Building(x, y, roadx, roady)
{
	contentVolumeCapacity = 5000;
	occupantCapacity = 6;
}
