#include <iostream>
#include "Termux.h"

int main(int argc, char *argv[])
{
	
	char home_path[40];
	char pwd[4096];
	char temp[400];
	char prefix[400];
	char bin[400];
	char shell[400];
	
	TgetHomeDir(home_path, sizeof(home_path));
	std::cout << "termux home path is " << home_path << "\n";
	
	TgetCurrentDir(pwd, sizeof(pwd));
	std::cout << "termux current dir is " << pwd << "\n";
	
	TgetTempDir(temp , sizeof(temp));
	std::cout << "termux temp dir is " << temp << "\n";
	
	TgetPrefixDir(prefix , sizeof(prefix));
	std::cout << "termux prefix dir is " << prefix << "\n";
	
	TgetBinDir(bin , sizeof(bin));
	std::cout << "termux bin dir is " << bin << "\n";
	
	TgetShellDir(shell , sizeof(shell));
	std::cout << "termux shell dir is " << shell << "\n";
		
	
		
	return 0;
}
