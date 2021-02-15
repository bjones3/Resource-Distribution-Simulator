//#include "../inc/ID.hpp"
#include "../inc/rds.hpp"

//#include <iostream>

ID::ID()
{
    id = -1;
}

long long int ID::generateID()
{
	id++;
	//std::cout << id << std::endl;
	return id;
}
