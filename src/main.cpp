#include "../inc/rds.hpp"
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char **argv, char **envp )
{
	//int** droneInfo = new int*[100];
	
	int pid = fork();
	if(pid < 0)
	{
		std::cout << "Unable to fork\n";
		return 0;
	}
	else if(pid == 0)
	{
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
		//waitpid(pid,NULL,0);
		//std::cout << "Forked parent\n";
		Executive ex;
		ex.run();
	}
}

