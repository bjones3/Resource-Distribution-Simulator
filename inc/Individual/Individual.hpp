#ifndef INDIVIDUAL_HPP
# define INDIVIDUAL_HPP

# include <list>
# include <string>
# include "../Resource/Resource.hpp"
# include "../Building/House.hpp"
//# include "Agenda.hpp"

class Individual
{
	private:
		int					xPosition;
		int					yPosition;
		std::string			name;
		long long int		id;
		std::list<Resource>	possessions;
		double				totalPossessionWeight;
		double				totalPossessionVolume;
		//Agenda			schedule;

		std::string generateName();

	public:
		Individual(House house);
		void				doTask(std::list<Resource> & resources);
		void				addPossession(Resource & possession);
		double				getPossessionVolume();
		double				getPossessionWeight();
		void				movePosition(int newXPosition, int newYPosition);
		std::list<Resource>	getIndividualPossessions();
		long long int		getID();
};

#endif