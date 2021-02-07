#ifndef ID_HPP
#define ID_HPP

//#include <iostream>

class ID
{
private:
	long long int id;
	//static long long int id;

public:
	ID()
	{
		id = -1;
	}

	long long int generateID()
	{
		id++;
		//std::cout << id << std::endl;
		return id;
	}

};

#endif
