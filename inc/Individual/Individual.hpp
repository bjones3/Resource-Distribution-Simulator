#ifndef INDIVIDUAL_HPP
# define INDIVIDUAL_HPP

# include "../rds.hpp"
#include "../Resource/Resource.hpp"
//#include "../Building/House.hpp"

class House;

class Individual
{
	private:
		int					xPosition;
		int					yPosition;
		std::string			name;
		long long int		id;
		std::unordered_map<long long int, Resource>	possessions;
		double				totalPossessionWeight;
		double				totalPossessionVolume;
		std::string         generateName();
		//Agenda			schedule;


	public:
		Individual (House house);
		void				doTask(std::unordered_map<long long int, Resource>	& resources);
        bool                canAddPossession(Resource & possession);
		void				addPossession(Resource & possession);
		double				getPossessionVolume();
		double				getPossessionWeight();
		void				movePosition(int newXPosition, int newYPosition);
		std::unordered_map<long long int, Resource>	getIndividualPossessions();
		long long int		getID();
};

#endif
