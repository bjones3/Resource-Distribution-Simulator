#ifndef RDS_HPP
# define RDS_HPP

# include <list>
# include <string>

class Executive
{
	public:
		void run();
};

class ID
{
	private:
		long long int id;
		//static long long int id;

	public:
		ID();
		long long int generateID();
};

class Location
{
	private:
		int xPos, yPos;
};

class MainAI
{

};

class Drone
{
	protected:
		long long int		id;
		int					xPos, yPos;
		int					xDest, yDest;
		double				contentVolume;
		double				contentWeight;
		double				maxVolume;
		double				maxWeight;
		std::list<Resource>	payload;

	public:
		Drone(int x, int y);
		long long int	getID();
		void			setDest(int xpos, int ypos);
		void			drive();
		int				getXPosition();
		int				getYPosition();
		int				getXDest();
		int				getYDest();
};

class CargoDrone : public Drone
{
	public:
		CargoDrone(int x, int y, long long int newId);
		bool		canLoadCargo(Resource & resource);
		void		loadCargo(Resource & resource);
		Resource	unloadCargo(Resources & resource);
};

class PassengerDrone : public Drone
{
	private:
		int passengerCapacity;
		std::list<Individual> passengers;

	public:
		PassengerDrone(int x, int y);
		bool		canLoadPassenger(Individual & passenger);
		void		loadPassenger(Individual & passenger);
		Individual	unloadPassenger(Individual & passenger);
};

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

struct range
{
	double min;
	double max;
};

class Resource
{
	private:
		Building		building;
		Building		newBuilding;
		double			weight; //pounds
		double			volume; //cubic feet
		double			wearFactor; //between 0 and 1
		double			wear; //between 0 and 1
		double			minWear;
		long long int	id;
		struct range	weightRange;
		struct range	volumeRange;
		struct range	wearFactorRange;

	public:
		Resource();
		//Resource(const Resource & resource);
		double			genWeight(struct range inWeight);
		double			genVolume(struct range inVolume);
		double			genWearFactor(struct range inWearFactor);
		double			getWeight();
		double			getVolume();
		double			getWearFactor();
		double			getWear();
		bool			use();
		Building		getNextBuilding();
		Building		getBuilding();
		long long int	getID();
};

#endif

