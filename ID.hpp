#ifndef ID_HPP
#define ID_HPP



class ID
{
public:

static long long int ID_number = 0;

static long long int generateID()
{

  return ++ID_number;

}


private:


};


#endif
