#ifndef INDIVIDUAL_HPP
# define INDIVIDUAL_HPP

# include "../rds.hpp"

class Individual
{
	private:
		int					xPosition;
		int					yPosition;
		std::string			name;
		long long int		id;
		std::unordered_map<long long int, Resource&>	possessions;
		double				totalPossessionWeight;
		double				totalPossessionVolume;
		//Agenda			schedule;

		std::string generateName();

	public:
		Individual(House house);
		void				doTask(std::unordered_map<long long int, Resource>	& resources);
		void				addPossession(Resource & possession);
        bool                canAddPossession(Resource & possession);
		double				getPossessionVolume();
		double				getPossessionWeight();
		void				movePosition(int newXPosition, int newYPosition);
		std::unordered_map<long long int, Resource&>	getIndividualPossessions();
		long long int		getID();
};

#endif
