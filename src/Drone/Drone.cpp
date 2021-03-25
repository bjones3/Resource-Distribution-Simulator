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
	bool pathFinished = false;
	
	//First intersection
	Movement firstMove = createMovement(xPos, yPos, xDest, yDest, roadConc);
	pathFinished = checkForPos(xPos, yPos, xDest, yDest, firstMove);
	moveList.push_back(firstMove);
	
	//Last intersection (needs to be created to calculate the second and third intersections)
	Movement lastMove = createMovement(xDest, yDest, firstMove.x, firstMove.y, roadConc);//xPos, yPos, roadConc);
	
	//Second intersection
	Movement secondMove( firstMove.x, firstMove.y, firstMove.dir );
	if(lastMove.x != firstMove.x && !pathFinished)
	{
		direction = LEFT;
		if(firstMove.x < lastMove.x)
			direction *= -1;
			
		secondMove.x = lastMove.x;
		secondMove.y = lastMove.y;
		secondMove.dir = direction;
		
		pathFinished = checkForPos(firstMove.x, firstMove.y, xDest, yDest, secondMove);
		moveList.push_back(secondMove);
	}
	
	//Third intersection
	Movement thirdMove( secondMove.x, secondMove.y, secondMove.dir );
	if(lastMove.y != firstMove.y && !pathFinished)
	{
		direction = UP;
		if(firstMove.y < lastMove.y)
			direction *= -1;

		thirdMove.x = lastMove.x;
		thirdMove.y = lastMove.y;
		thirdMove.dir = direction;
		
		pathFinished = checkForPos(secondMove.x, secondMove.y, xDest, yDest, thirdMove);
		moveList.push_back(thirdMove);
	}
	
	//Last intersection (needs to be placed last in the list)
	if(!pathFinished)
	{
		lastMove.dir *= -1;
		if(lastMove.dir == RIGHT || lastMove.dir == LEFT)
			lastMove.x = xDest;
		else
			lastMove.y = yDest;

		moveList.push_back(lastMove);
	}
	
	if(DEBUG)
	{
		std::cout << "List: \n";
		
		for(std::list<Movement>::iterator temp = moveList.begin(); temp != moveList.end(); temp++)
			std::cout << (*temp).x << ", " << (*temp).y << ", " << (*temp).dir << std::endl;
		
		std::cout << "Movement: \n";
	}
}

bool Drone::checkForPos(int startx, int starty, int targetx, int targety, Movement& move)
{
	//Check to see if the target is even on the same axis that we're moving on
	if(startx == targetx && abs(move.dir) == DOWN)
	{
		if((move.dir == DOWN && targety >= starty) || (move.dir == UP && targety <= starty))
		{
			move.y = targety;
			return true;
		}
	}
	else if(starty == targety && abs(move.dir) == RIGHT)
	{
		if((move.dir == RIGHT && targetx >= startx) || (move.dir == LEFT && targetx <= startx))
		{
			move.x = targetx;
			return true;
		}
	}
	
	//This movement won't intersect the target
	return false;
}

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

bool Drone::isAdjacent(Building* where)
{
	return(where->getXPos() == xPos && abs(where->getYPos() - yPos) <= 1) || (where->getYPos() == yPos && abs(where->getXPos() - xPos) <= 1);
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
