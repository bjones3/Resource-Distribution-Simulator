#ifndef DRONE_HPP
# define DRONE_HPP

# include "../rds.hpp"

class Drone
{
	public:
		struct Delivery
		{
			Building* where;
			Individual* who;
			std::list<Resource*> what;
			Delivery(Building* wherem, Individual* whom)
			{
				where = wherem; who = whom;
			}
			
			Delivery(Building* wherem, Individual * whom, std::list<Resource*> whatm)
			{
				where = wherem; who = whom; what = whatm;
			}
			
			Delivery(const Delivery& d)
			{
				where = d.where; who = d.who; what = d.what;
			}
		};

		struct Movement
		{
			int dir;	//What direction the drone will be moving when reaching this point (UP, DOWN, LEFT, RIGHT)
			int x, y;	//The point the drone is moving towards

			Movement(int xpos, int ypos, int direction)
			{
				x = xpos; y = ypos; dir = direction;
			}

			Movement(const Movement& m)
			{
				x = m.x; y = m.y; dir = m.dir;
			}
		};

		Drone(int x, int y, long long int theID);
		long long int		getID();
		void				setDest(int xpos, int ypos);
		int					getXPos();
		int					getYPos();
		int					getXDest();
		int					getYDest();
		void				move();
		void				createMoveList(int destX, int destY, int roadConc);
		std::list<Movement>	getMoveList();
		bool				isMoving();
		bool				isAdjacent(Building* where);
		void				createDelivery(Building* where, Individual* who, int moveIndex1, int moveIndex2, int roadConc);
		void				createDelivery(Building* where, Individual* who, std::list<Resource*> what, int moveIndex1, int moveIndex2, int roadConc);
		void 				removeDelivery(long long int theID);
		std::list<Delivery> getDeliveries();
		void				deliveryCheck(int roadConc);
		int					posInPath(int x, int y);

	protected:
		const int			UP = -1;
		const int			DOWN = 1;
		const int			LEFT = -2;
		const int			RIGHT = 2;

		long long int		id;
		int					xPos, yPos;
		int					xDest, yDest;
		double				contentVolume;
		double				contentWeight;
		double				maxVolume;
		double				maxWeight;
		bool				canDeliveryCheck;

		std::list<Delivery> deliveries;
		std::unordered_map<long long int, Resource*> payload;
		std::list<Movement>	moveList;

		void 				moveUp(int destY);
		void 				moveDown(int destY);
		void 				moveLeft(int destX);
		void 				moveRight(int destX);
		Movement			createMovement(int x1, int y1, int x2, int y2, int roadConc);
		bool				checkForPos(int startx, int starty, int targetx, int targety, Movement& move);
		void				createDeliveryPath(Building* start, Building* finish, int moveIndex1, int moveIndex2, int roadConc);

};

#endif
