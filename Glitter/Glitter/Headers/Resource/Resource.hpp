#ifndef RESOURCE_HPP
# define RESOURCE_HPP

# include "../rds.hpp"

struct range
{
    double min;
    double max;
};

//RESOURCE TYPES
#define GENERIC_ITEM 0
#define ELECTRONIC_ITEM 1
#define CAMERA 2
#define CELLPHONE 3
#define COMPUTER 4
#define MUSIC_INSTRUMENT 5
#define PRINTER 6
#define SPEAKER 7
#define TV 8
#define VIDEO_GAME 9
#define BATHROOM_ITEM 10
#define CLOTHING_ITEM 11
#define FOOD_ITEM 12
#define FURNITURE_ITEM 13
#define HARDWARE_ITEM 14
#define HOUSEHOLD_ITEM 15
#define KITCHEN_ITEM 16
#define SPORTS_ITEM 17
#define TOTAL_RESOURCE_TYPES 18

//OFFSETS
#define WEAR_FACTOR_MIN 0
#define WEAR_FACTOR_MAX 1
#define WEIGHT_MIN 2
#define WEIGHT_MAX 3
#define VOLUME_MIN 4
#define VOLUME_MAX 5
#define WEAR 6
#define WEAR_MIN 7
#define TOTAL_OFFSETS 8

class ResourceTable
{
	public:
		double values[TOTAL_RESOURCE_TYPES*TOTAL_OFFSETS];
		std::string names[TOTAL_RESOURCE_TYPES];
		
		std::string getName( int theType )
		{
			return names[theType];
		}
		
		double getValue( int theType, int offset )
		{
			return values[theType*TOTAL_OFFSETS + offset];
		}
		
		ResourceTable()
		{
			names[GENERIC_ITEM] = "Generic Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*GENERIC_ITEM] = 0;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*GENERIC_ITEM] = 1;
			values[WEIGHT_MIN + TOTAL_OFFSETS*GENERIC_ITEM] = 0.01;
			values[WEIGHT_MAX + TOTAL_OFFSETS*GENERIC_ITEM] = 6000;	//Max load of a 20ft Uhaul
			values[VOLUME_MIN + TOTAL_OFFSETS*GENERIC_ITEM] = 0.01;
			values[VOLUME_MAX + TOTAL_OFFSETS*GENERIC_ITEM] = 1000;	//Max volume of 2nd largest Uhaul
			values[WEAR + TOTAL_OFFSETS*GENERIC_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*GENERIC_ITEM] = 0.001;

			names[ELECTRONIC_ITEM] = "Electronic Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 0.05;
			values[WEIGHT_MAX + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 60;
			values[VOLUME_MIN + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 0.001;
			values[VOLUME_MAX + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 17.5;
			values[WEAR + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*ELECTRONIC_ITEM] = 0.01;

			names[CAMERA] = "Camera";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*CAMERA] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*CAMERA] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*CAMERA] = 0.015;
			values[WEIGHT_MAX + TOTAL_OFFSETS*CAMERA] = 2;
			values[VOLUME_MIN + TOTAL_OFFSETS*CAMERA] = 0.01;
			values[VOLUME_MAX + TOTAL_OFFSETS*CAMERA] = 0.1;
			values[WEAR + TOTAL_OFFSETS*CAMERA] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*CAMERA] = 0.01;

			names[CELLPHONE] = "Cellphone";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*CELLPHONE] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*CELLPHONE] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*CELLPHONE] = 0.015;
			values[WEIGHT_MAX + TOTAL_OFFSETS*CELLPHONE] = 2;
			values[VOLUME_MIN + TOTAL_OFFSETS*CELLPHONE] = 0.01;
			values[VOLUME_MAX + TOTAL_OFFSETS*CELLPHONE] = 0.1;
			values[WEAR + TOTAL_OFFSETS*CELLPHONE] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*CELLPHONE] = 0.01;

			names[COMPUTER] = "Computer";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*COMPUTER] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*COMPUTER] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*COMPUTER] = 2;
			values[WEIGHT_MAX + TOTAL_OFFSETS*COMPUTER] = 10;
			values[VOLUME_MIN + TOTAL_OFFSETS*COMPUTER] = 0.5;
			values[VOLUME_MAX + TOTAL_OFFSETS*COMPUTER] = 3;
			values[WEAR + TOTAL_OFFSETS*COMPUTER] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*COMPUTER] = 0.01;

			names[MUSIC_INSTRUMENT] = "Musical Instrument";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 5;
			values[WEIGHT_MAX + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 300;
			values[VOLUME_MIN + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 1;
			values[VOLUME_MAX + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 27;
			values[WEAR + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*MUSIC_INSTRUMENT] = 0.01;

			names[PRINTER] = "Printer";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*PRINTER] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*PRINTER] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*PRINTER] = 5;
			values[WEIGHT_MAX + TOTAL_OFFSETS*PRINTER] = 300;
			values[VOLUME_MIN + TOTAL_OFFSETS*PRINTER] = 1;
			values[VOLUME_MAX + TOTAL_OFFSETS*PRINTER] = 27;
			values[WEAR + TOTAL_OFFSETS*PRINTER] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*PRINTER] = 0.01;

			names[SPEAKER] = "Speaker";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*SPEAKER] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*SPEAKER] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*SPEAKER] = 0.015;
			values[WEIGHT_MAX + TOTAL_OFFSETS*SPEAKER] = 40;
			values[VOLUME_MIN + TOTAL_OFFSETS*SPEAKER] = 0.01;
			values[VOLUME_MAX + TOTAL_OFFSETS*SPEAKER] = 10;
			values[WEAR + TOTAL_OFFSETS*SPEAKER] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*SPEAKER] = 0.01;

			names[TV] = "Television";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*TV] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*TV] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*TV] = 5;
			values[WEIGHT_MAX + TOTAL_OFFSETS*TV] = 60;
			values[VOLUME_MIN + TOTAL_OFFSETS*TV] = 1;
			values[VOLUME_MAX + TOTAL_OFFSETS*TV] = 9;
			values[WEAR + TOTAL_OFFSETS*TV] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*TV] = 0.01;

			names[VIDEO_GAME] = "Video Game";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*VIDEO_GAME] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*VIDEO_GAME] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*VIDEO_GAME] = 0.25;
			values[WEIGHT_MAX + TOTAL_OFFSETS*VIDEO_GAME] = 1;
			values[VOLUME_MIN + TOTAL_OFFSETS*VIDEO_GAME] = 1;
			values[VOLUME_MAX + TOTAL_OFFSETS*VIDEO_GAME] = 7;
			values[WEAR + TOTAL_OFFSETS*VIDEO_GAME] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*VIDEO_GAME] = 0.01;

			names[BATHROOM_ITEM] = "Bathroom Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*BATHROOM_ITEM] = 0.6;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*BATHROOM_ITEM] = 0.98;
			values[WEIGHT_MIN + TOTAL_OFFSETS*BATHROOM_ITEM] = 0.03;
			values[WEIGHT_MAX + TOTAL_OFFSETS*BATHROOM_ITEM] = 3;
			values[VOLUME_MIN + TOTAL_OFFSETS*BATHROOM_ITEM] = 0.001;
			values[VOLUME_MAX + TOTAL_OFFSETS*BATHROOM_ITEM] = 0.15;
			values[WEAR + TOTAL_OFFSETS*BATHROOM_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*BATHROOM_ITEM] = 0.05;

			names[CLOTHING_ITEM] = "Clothing Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*CLOTHING_ITEM] = 0.8;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*CLOTHING_ITEM] = 0.99;
			values[WEIGHT_MIN + TOTAL_OFFSETS*CLOTHING_ITEM] = 0.06;
			values[WEIGHT_MAX + TOTAL_OFFSETS*CLOTHING_ITEM] = 8;
			values[VOLUME_MIN + TOTAL_OFFSETS*CLOTHING_ITEM] = 0.005;
			values[VOLUME_MAX + TOTAL_OFFSETS*CLOTHING_ITEM] = 0.5;
			values[WEAR + TOTAL_OFFSETS*CLOTHING_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*CLOTHING_ITEM] = 0.08;

			names[FOOD_ITEM] = "Food Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*FOOD_ITEM] = 0;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*FOOD_ITEM] = 0;
			values[WEIGHT_MIN + TOTAL_OFFSETS*FOOD_ITEM] = 0.2;
			values[WEIGHT_MAX + TOTAL_OFFSETS*FOOD_ITEM] = 30;
			values[VOLUME_MIN + TOTAL_OFFSETS*FOOD_ITEM] = 0.05;
			values[VOLUME_MAX + TOTAL_OFFSETS*FOOD_ITEM] = 1;
			values[WEAR + TOTAL_OFFSETS*FOOD_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*FOOD_ITEM] = 0.01;

			names[FURNITURE_ITEM] = "Furniture Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*FURNITURE_ITEM] = 0.9995;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*FURNITURE_ITEM] = 0.9999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*FURNITURE_ITEM] = 1;
			values[WEIGHT_MAX + TOTAL_OFFSETS*FURNITURE_ITEM] = 800;
			values[VOLUME_MIN + TOTAL_OFFSETS*FURNITURE_ITEM] = 1;
			values[VOLUME_MAX + TOTAL_OFFSETS*FURNITURE_ITEM] = 100;
			values[WEAR + TOTAL_OFFSETS*FURNITURE_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*FURNITURE_ITEM] = 0.01;

			names[HARDWARE_ITEM] = "Hardware Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*HARDWARE_ITEM] = 0;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*HARDWARE_ITEM] = 0.9999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*HARDWARE_ITEM] = 0.2;
			values[WEIGHT_MAX + TOTAL_OFFSETS*HARDWARE_ITEM] = 50;
			values[VOLUME_MIN + TOTAL_OFFSETS*HARDWARE_ITEM] = 0.2;
			values[VOLUME_MAX + TOTAL_OFFSETS*HARDWARE_ITEM] = 3;
			values[WEAR + TOTAL_OFFSETS*HARDWARE_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*HARDWARE_ITEM] = 0.01;

			names[HOUSEHOLD_ITEM] = "Household Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 0.6;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 0.9999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 0.1;
			values[WEIGHT_MAX + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 15;
			values[VOLUME_MIN + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 0.001;
			values[VOLUME_MAX + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 0.75;
			values[WEAR + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*HOUSEHOLD_ITEM] = 0.0001;

			names[KITCHEN_ITEM] = "Kitchen Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*KITCHEN_ITEM] = 0.7;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*KITCHEN_ITEM] = 0.9999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*KITCHEN_ITEM] = 0.1;
			values[WEIGHT_MAX + TOTAL_OFFSETS*KITCHEN_ITEM] = 20;
			values[VOLUME_MIN + TOTAL_OFFSETS*KITCHEN_ITEM] = 0.005;
			values[VOLUME_MAX + TOTAL_OFFSETS*KITCHEN_ITEM] = 0.15;
			values[WEAR + TOTAL_OFFSETS*KITCHEN_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*KITCHEN_ITEM] = 0.05;

			names[SPORTS_ITEM] = "Sports Item";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*SPORTS_ITEM] = 0.9;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*SPORTS_ITEM] = 0.999;
			values[WEIGHT_MIN + TOTAL_OFFSETS*SPORTS_ITEM] = 0.05;
			values[WEIGHT_MAX + TOTAL_OFFSETS*SPORTS_ITEM] = 15;
			values[VOLUME_MIN + TOTAL_OFFSETS*SPORTS_ITEM] = 0.03;
			values[VOLUME_MAX + TOTAL_OFFSETS*SPORTS_ITEM] = 0.5;
			values[WEAR + TOTAL_OFFSETS*SPORTS_ITEM] = 1;
			values[WEAR_MIN + TOTAL_OFFSETS*SPORTS_ITEM] = 0.001;

			/*
			names[] = "";
			values[WEAR_FACTOR_MIN + TOTAL_OFFSETS*] = ;
			values[WEAR_FACTOR_MAX + TOTAL_OFFSETS*] = ;
			values[WEIGHT_MIN + TOTAL_OFFSETS*] = ;
			values[WEIGHT_MAX + TOTAL_OFFSETS*] = ;
			values[VOLUME_MIN + TOTAL_OFFSETS*] = ;
			values[VOLUME_MAX + TOTAL_OFFSETS*] = ;
			values[WEAR + TOTAL_OFFSETS*] = ;
			values[WEAR_MIN + TOTAL_OFFSETS*] = ;
			*/
		}
};

class Resource
{
    private:
        int 			type;
        std::string 	name;
		Building*		currentBuilding;
		Drone*			currentDrone;
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
    	Resource( int theType, long long int theID, ResourceTable & table );
		double			genWeight(struct range inWeight);
		double			genVolume(struct range inVolume);
		double			genWearFactor(struct range inWearFactor);
		double			getWeight();
		double			getVolume();
		double			getWearFactor();
		double			getWear();
		bool			use();
		void			setBuilding(Building* newBuilding);
		Building*		getBuilding();
		void			setDrone(Drone* newDrone);
		Drone*			getDrone();
		long long int	getID();
		int 			getType();
		std::string 	getName();
		int				getXPos();
		int				getYPos();
};

#endif
