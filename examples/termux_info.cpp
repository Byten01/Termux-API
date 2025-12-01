
#include <iostream>


#include "Termux.h"



// an example of using the turinfo api to gain some information


int main(int argc, char *argv[])
{
	char Version[40];
	char last_cmd[100];
	int Pid;
	
	TgetVersionInfo(Version, sizeof(Version));
	TgetLastCmdExecutedPath(last_cmd, sizeof(last_cmd));
	TgetPid(&Pid);
	
	std::cout << "termux version: " << Version << "\n";
	std::cout << "last shell command executed: " << last_cmd << "\n";
	std::cout << "Current process id: " << Pid << "\n";
}