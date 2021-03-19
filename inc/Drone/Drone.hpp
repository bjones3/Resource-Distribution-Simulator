#ifndef DRONE_HPP
# define DRONE_HPP

# include "../rds.hpp"

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
		std::list<int>		moveList;
		void 				moveUp(int destY);
		void 				moveDown(int destY);
		void 				moveLeft(int destX);
		void 				moveRight(int destX);
		const int			UP = -1;
		const int			DOWN = 1;
		const int			LEFT = -2;
		const int			RIGHT = 2;
		void 				getFirstIntersection(int & interX, int & interY, int roadConc);
		void 				getSecondIntersection(int & interX, int & interY, int & direction, int roadConc);


	public:
		Drone(int x, int y);
		long long int	getID();
		void			setDest(int xpos, int ypos);
		int				getXPosition();
		int				getYPosition();
		int				getXDest();
		int				getYDest();
		void			move();
		void			createMoveList(int destX, int destY, int roadConc);
};

#endif
