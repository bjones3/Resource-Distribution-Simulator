#ifndef ID_HPP
# define ID_HPP

# include "rds.hpp"

class ID
{
	private:
		long long int id;
		//static long long int id;

	public:
		ID();
		long long int generateID();
};

#endif