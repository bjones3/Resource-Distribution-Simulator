#ifndef HOUSE_HPP
# define HOUSE_HPP

# include "../rds.hpp"
#include "Building.hpp"


class House : public Building
{
	public:
		House(int x, int y);
};

#endif
