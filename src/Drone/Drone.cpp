#include "../../inc/rds.hpp"

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
	int interX, interY, interX2, interY2, direction;
	getFirstIntersection(interX, interY, roadConc);
	getSecondIntersection(interX2, interY2, direction, roadConc);
	
	if(interX < interX2)
	{
		moveList.push_back(RIGHT);
		moveList.push_back(interX2);
	}
	else
	{
		moveList.push_back(LEFT);
		moveList.push_back(interX2);
	}
	
	if(interY < interY2)
	{
		moveList.push_back(DOWN);
		moveList.push_back(interY2);
	}
	else
	{
		moveList.push_back(UP);
		moveList.push_back(interY2);
	}
	
	moveList.push_back(-direction);
	if(direction == RIGHT || direction == LEFT)
		moveList.push_back(xDest);
	else
		moveList.push_back(yDest);
	
	std::cout << "List: \n";
	
	for(std::list<int>::iterator temp = moveList.begin(); temp != moveList.end(); temp++)
		std::cout << *temp << std::endl;
	
	std::cout << "Movement: \n";
}

void Drone::getFirstIntersection(int & interX, int & interY, int roadConc)
{
	//On a horizontal road
	if(yPos % roadConc == 0)
	{
		interY = yPos;
		int diff = xDest - xPos;
		if(diff > 0)
		{
			 interX = xPos + roadConc - (xPos % roadConc);
			 std::cout << "Intersection X: " << interX << std::endl;
			 moveList.push_back(RIGHT);
		}
		else
		{
		 	interX = xPos - (xPos % roadConc);
			std::cout << "Intersection X: " << interX << std::endl;
			moveList.push_back(LEFT);
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
			 std::cout << "Intersection Y: " << interY << std::endl;
			 moveList.push_back(DOWN);
		}
		else
		{
		 	interY = yPos - (yPos % roadConc);
			std::cout << "Intersection Y: " << interY << std::endl;
			moveList.push_back(UP);
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
			 std::cout << "Intersection2 X: " << interX << std::endl;
			 direction = RIGHT;
		}
		else
		{
		 	interX = xDest - (xDest % roadConc);
			std::cout << "Intersection2 X: " << interX << std::endl;
			direction = LEFT;
		}
	}
	else	//Vertical road
	{
		interX = xDest;
		int diff = yDest - yPos;
		if(diff < 0)
		{
			 interY = yDest + roadConc - (yDest % roadConc);
			 std::cout << "Intersection2 Y: " << interY << std::endl;
			 direction = DOWN;
		}
		else
		{
		 	interY = yDest - (yDest % roadConc);
			std::cout << "Intersection2 Y: " << interY << std::endl;
			direction = UP;
		}
	}
}


void Drone::move()
{
	if(!moveList.empty())
	{
		switch(moveList.front())
		{
			case -1://UP
				moveUp(*(++moveList.begin()));
			break;
			case 1://DOWN
				moveDown(*(++moveList.begin()));
			break;
			case -2://LEFT:
				moveLeft(*(++moveList.begin()));
			break;
			case 2://RIGHT:
				moveRight(*(++moveList.begin()));
			break;
		}
		std::cout << xPos << ", " << yPos << std::endl;
	}
}

void Drone::moveUp(int destY)
{
	if(yPos > destY)
	{
		yPos--;
		//std::cout << yPos << std::endl;
	}
	else
	{
		for(int i = 0; i < 2; i++)
			moveList.pop_front();
	
		std::cout << "Done moving up\n";
		move();
	}
}

void Drone::moveDown(int destY)
{
	if(yPos < destY)
	{
		yPos++;
		//std::cout << yPos << std::endl;
	}
	else
	{
		for(int i = 0; i < 2; i++)
			moveList.pop_front();
	
		std::cout << "Done moving down\n";
		move();
	}
}

void Drone::moveLeft(int destX)
{
	if(xPos > destX)
	{
		xPos--;
		//std::cout << xPos << std::endl;
	}
	else
	{
		for(int i = 0; i < 2; i++)
			moveList.pop_front();
	
		std::cout << "Done moving left\n";
		move();
	}
}

void Drone::moveRight(int destX)
{
	if(xPos < destX)
	{
		xPos++;
		//std::cout << xPos << std::endl;
	}
	else
	{
		for(int i = 0; i < 2; i++)
			moveList.pop_front();
	
		std::cout << "Done moving right\n";
		move();
	}
}

int Drone::getXPosition()
{
	return xPos;
}

int Drone::getYPosition()
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
