#include "../../inc/rds.hpp"

#define DEBUG false		//Controls whether or not to output drone positions

Drone::Drone(int x, int y)
{
	xPos = x;
	yPos = y;
	xDest = x;
	yDest = y;
	id = -1; //id = ID::generateID();
	contentVolume = 0;
	contentWeight = 0;
	maxVolume = 0;
	maxWeight = 0;
}

void Drone::setDest(int xpos, int ypos)
{
	xDest = xpos;
	yDest = ypos;
}

void Drone::createMoveList(int destX, int destY, int roadConc)
{
	xDest = destX;
	yDest = destY;
	int direction;
	
	//First intersection
	Movement firstMove = createMovement(xPos, yPos, xDest, yDest, roadConc);
	moveList.push_back(firstMove);
	
	//Last intersection (needs to be created to calculate the second and third intersections)
	Movement lastMove = createMovement(xDest, yDest, firstMove.x, firstMove.y, roadConc);//xPos, yPos, roadConc);
	
	//Second intersection
	if(firstMove.x < lastMove.x)
	{
		direction = RIGHT;
		//moveList.push_back(RIGHT);
		//moveList.push_back(interX2);
	}
	else
	{
		direction = LEFT;
		//moveList.push_back(LEFT);
		//moveList.push_back(interX2);
	}
	Movement secondMove( lastMove.x, lastMove.y, direction );
	moveList.push_back(secondMove);
	
	//Third intersection
	if(firstMove.y < lastMove.y)
	{
		direction = DOWN;
		//moveList.push_back(DOWN);
		//moveList.push_back(interY2);
	}
	else
	{
		direction = UP;
		//moveList.push_back(UP);
		//moveList.push_back(interY2);
	}
	Movement thirdMove( lastMove.x, lastMove.y, direction );
	moveList.push_back(thirdMove);
	
	//Last intersection (needs to be placed last in the list)
	lastMove.dir *= -1;			//moveList.push_back(-direction);
	if(lastMove.dir == RIGHT || lastMove.dir == LEFT)
		lastMove.x = xDest;		//moveList.push_back(xDest);
	else
		lastMove.y = yDest;		//moveList.push_back(yDest);
	
	moveList.push_back(lastMove);
	
	if(DEBUG)
	{
		std::cout << "List: \n";
		
		for(std::list<Movement>::iterator temp = moveList.begin(); temp != moveList.end(); temp++)
			std::cout << (*temp).x << ", " << (*temp).y << ", " << (*temp).dir << std::endl;
		
		std::cout << "Movement: \n";
	}
}

/*void Drone::getFirstIntersection(int & interX, int & interY, int roadConc)
{
	//On a horizontal road
	if(yPos % roadConc == 0)
	{
		interY = yPos;
		int diff = xDest - xPos;
		if(diff > 0)
		{
			 interX = xPos + roadConc - (xPos % roadConc);
			 moveList.push_back(RIGHT);
			 if(DEBUG)
			 	std::cout << "Intersection X: " << interX << std::endl;
		}
		else
		{
		 	interX = xPos - (xPos % roadConc);
		 	moveList.push_back(LEFT);
		 	if(DEBUG)
				std::cout << "Intersection X: " << interX << std::endl;
		}
		moveList.push_back(interX);
	}
	else	//Vertical road
	{
		interX = xPos;
		int diff = yDest - yPos;
		if(diff > 0)
		{
			 interY = yPos + roadConc - (yPos % roadConc);
			 moveList.push_back(DOWN);
			 if(DEBUG)
			 	std::cout << "Intersection Y: " << interY << std::endl;
		}
		else
		{
		 	interY = yPos - (yPos % roadConc);
		 	moveList.push_back(UP);
		 	if(DEBUG)
				std::cout << "Intersection Y: " << interY << std::endl;
		}
		moveList.push_back(interY);
	}
}

void Drone::getSecondIntersection(int & interX, int & interY, int & direction, int roadConc)
{
	//On a horizontal road
	if(yPos % roadConc == 0)
	{
		interY = yDest;
		int diff = xDest - xPos;
		if(diff < 0)
		{
			 interX = xDest + roadConc - (xDest % roadConc);
			 direction = RIGHT;
			 if(DEBUG)
			 	std::cout << "Intersection2 X: " << interX << std::endl;
		}
		else
		{
		 	interX = xDest - (xDest % roadConc);
		 	direction = LEFT;
		 	if(DEBUG)
				std::cout << "Intersection2 X: " << interX << std::endl;
		}
	}
	else	//Vertical road
	{
		interX = xDest;
		int diff = yDest - yPos;
		if(diff < 0)
		{
			 interY = yDest + roadConc - (yDest % roadConc);
			 direction = DOWN;
			 if(DEBUG)
			 	std::cout << "Intersection2 Y: " << interY << std::endl;
		}
		else
		{
		 	interY = yDest - (yDest % roadConc);
		 	direction = UP;
			if(DEBUG)
				std::cout << "Intersection2 Y: " << interY << std::endl;
		}
	}
}*/

Drone::Movement Drone::createMovement(int x1, int y1, int x2, int y2, int roadConc)
{
	int direction, interX, interY;
	
	//On a horizontal road
	if(yPos % roadConc == 0)
	{
		interY = y1;
		int diff = x2 - x1;
		if(diff > 0)
		{
			 interX = x1 + roadConc - (x1 % roadConc);
			 direction = RIGHT;
		}
		else
		{
		 	interX = x1 - (x1 % roadConc);
		 	direction = LEFT;
		}
	}
	else	//Vertical road
	{
		interX = x1;
		int diff = y2 - y1;
		if(diff > 0)
		{
			 interY = y1 + roadConc - (y1 % roadConc);
			 direction = DOWN;
		}
		else
		{
		 	interY = y1 - (y1 % roadConc);
		 	direction = UP;
		}
	}
	Movement m(interX, interY, direction);
	return m;
}

void Drone::move()
{
	//Stop moving if the destination has been reached
	if(xPos == xDest && yPos == yDest)
	{
		if(!moveList.empty() && DEBUG)
			std::cout << "Destination reached\n";
		
		while(!moveList.empty())
			moveList.pop_front();
	}
	
	//Otherwise, attempt to move in a direction according to the movement list
	if(!moveList.empty())
	{	
		switch(moveList.front().dir)
		{
			case -1://UP
				moveUp(moveList.front().y);//*(++moveList.begin()));
			break;
			case 1://DOWN
				moveDown(moveList.front().y);//*(++moveList.begin()));
			break;
			case -2://LEFT:
				moveLeft(moveList.front().x);//*(++moveList.begin()));
			break;
			case 2://RIGHT:
				moveRight(moveList.front().x);//*(++moveList.begin()));
			break;
		}
		if(DEBUG)
			std::cout << xPos << ", " << yPos << std::endl;
	}
}

void Drone::moveUp(int destY)
{
	if(yPos > destY)
	{
		yPos--;
	}
	else
	{
		moveList.pop_front();
	
		if(DEBUG)
			std::cout << "Done moving up\n";
			
		move();
	}
}

void Drone::moveDown(int destY)
{
	if(yPos < destY)
	{
		yPos++;
	}
	else
	{
		moveList.pop_front();
	
		if(DEBUG)
			std::cout << "Done moving down\n";
			
		move();
	}
}

void Drone::moveLeft(int destX)
{
	if(xPos > destX)
	{
		xPos--;
	}
	else
	{
		moveList.pop_front();
			
		if(DEBUG)
			std::cout << "Done moving left\n";
			
		move();
	}
}

void Drone::moveRight(int destX)
{
	if(xPos < destX)
	{
		xPos++;
	}
	else
	{
		moveList.pop_front();
	
		if(DEBUG)
			std::cout << "Done moving right\n";
		
		move();
	}
}

bool Drone::isMoving()
{
	return !moveList.empty();
}

std::list<Drone::Movement> Drone::getMoveList()
{
	return moveList;
}

int Drone::getXPos()
{
	return xPos;
}

int Drone::getYPos()
{
	return yPos;
}

int Drone::getXDest()
{
	return xDest;
}

int Drone::getYDest()
{
	return yDest;
}

long long int Drone::getID()
{
	return id;
}

#undef DEBUG
