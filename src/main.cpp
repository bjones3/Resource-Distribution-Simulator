#include "../inc/rds.hpp"
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char **argv, char **envp )
{
	//Prompt user for...
	//Simluation duration
	int months;
	std::cout << "How many months should the simulation run for?\n";
	std::cin >> months;

	//Map dimensions
	int mapWidth, mapHeight, blockSize;
	std::cout << "Enter the width (in blocks) of the world followed by the height (ex: 4 5).\n";
	std::cin >> mapWidth >> mapHeight;
	
	//Size of each block
	std::cout << "How wide should each block be?\n";
	std::cin >> blockSize;
	
	int xSize = mapWidth*blockSize+1; 
	int ySize = mapHeight*blockSize+1;
	
	//Create the map itself
	cityMap theMap( xSize, ySize, blockSize, 5, 3 );
	theMap.printMap();	//Show the map for debug purposes

	int myPipe[2];
	pipe(myPipe);
	
	int pid = fork();
	if(pid < 0)
	{
		std::cout << "Unable to fork\n";
		return 0;
	}
	else if(pid == 0)
	{
		dup2(myPipe[0],STDIN_FILENO);	//Read from this pipe
		close(myPipe[1]);
		
		//std::cout << "Forked child\n";
		std::string graphics = "ls";	//Change this to the path to the graphics exe
		char* args[2];
		args[0] = const_cast<char*>(graphics.c_str());
		args[1] = (char*)NULL;
		execvp(graphics.c_str(),args);
		std::cout << "Exec failed\n";
	}
	else
	{
		//std::cout << "Forked parent\n";
		dup2(myPipe[1],STDOUT_FILENO);	//Write to this pipe
		close(myPipe[0]);
	
		//Send the dimensions and the map itself to the graphics
		std::cout << xSize << " " << ySize << " ";
		theMap.printMap();
		
		Executive ex;
		ex.run(theMap, months);
		
		close(myPipe[1]);
	}
}

