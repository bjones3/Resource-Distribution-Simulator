#include "../../inc/rds.hpp"

Office::Office(int x, int y, int roadx, int roady) : Building::Building(x, y, roadx, roady)
{
	contentVolumeCapacity = 45000;
	occupantCapacity = 80;
}
