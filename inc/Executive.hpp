#ifndef EXECUTIVE_HPP
# define EXECUTIVE_HPP

# include "rds.hpp"

# include <time.h>
#	include <thread>
# define INDIVIDUALS_SPAWNED_PER_HOUSE 2

class Executive
{
	private:
		long long int generateID();

	public:
		void run();

};

#endif
