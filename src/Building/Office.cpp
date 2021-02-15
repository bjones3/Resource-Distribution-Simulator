//#include "../../inc/Building/Office.hpp"
#include "../../inc/rds.hpp"

Office::Office(int x, int y) : Building::Building(x, y)
{
	contentVolumeCapacity = 45000;
	occupantCapacity = 80;
}