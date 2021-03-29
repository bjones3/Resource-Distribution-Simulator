#ifndef HOUSE_HPP
# define HOUSE_HPP

# include "../rds.hpp"

class House : public Building
{
	public:
		House(int x, int y, int roadx, int roady);
};

#endif
