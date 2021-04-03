#ifndef INDIVIDUAL_HPP
# define INDIVIDUAL_HPP

# include "../rds.hpp"

class Individual
{
	private:
		std::string			name;
		long long int		id;
		std::unordered_map<long long int, Resource&>	possessions;
		double				totalPossessionWeight;
		double				totalPossessionVolume;
		Agenda*				schedule;
		House* 				home;
		Building*			currentBuilding;
		Drone*				currentDrone;
		PassengerDrone*		passengerRequest;
		CargoDrone*			cargoRequest;

		std::string generateName();

	public:
		Individual();
		Individual(House* house, long long int theID);
		void				doTask(std::list<Resource*> resources);
		void				addPossession(Resource & possession);
        bool                canAddPossession(Resource & possession);
		double				getPossessionVolume();
		double				getPossessionWeight();
		std::unordered_map<long long int, Resource&>	getIndividualPossessions();
		long long int		getID();
		int					getXPos();
		int					getYPos();
		Building*			getBuilding();
		Drone*				getDrone();
		void				setBuilding(Building* newBuilding);
		void				setDrone(Drone* newDrone);
		Agenda*				getAgenda();
		void				setAgenda(Agenda* theAgenda);
		PassengerDrone*		getPassengerRequest();
		void				setPassengerRequest(PassengerDrone* theDrone);
		CargoDrone*			getCargoRequest();
		void				setCargoRequest(CargoDrone* theDrone);
};

#endif
