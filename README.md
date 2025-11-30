# Termux-API

a high level api to interact with termux shell environment via C/C++. currently in early developmment with only some of the functions implemented

***

## Getting Started
It is a termux only api so it should be compiled and used in a termux environment, it is recommended to use android studio or any kind of android virtual machine if using other device than android termux for development

<ins>**1. Downloading the repository:**</ins>

clone the repository with this command 
```sh
git clone https://github.com/Byten01/Termux-API.git
```

Or you can download [this repo](https://github.com/Byten01/Termux-API/archive/refs/heads/main.zip) as a zip

<ins>**2. Configuring and using the api:**</ins>

1. inside the repo you'll have 2 directories
<ul>
    <li>include -> the declaration of the apis to be included</li>
    <li>src -> the implementation of the apis</li>
</ul>
2. Here, we are using dynamic linking, so all the source code will be compiled into a single dynamic library that the app will link to at runtime. To compile the source code, navigate to the `src` directory. We will use *CMake* to automate the compilation process. Follow these commands:
```sh
cmake .
make -j$(nproc)
```
**After that it will produce a file named `libTkernel.so` which will be the dynamic library**

3. Set the environment variable named `LD_LIBRARY_PATH` to the directory where the .so file is so application dynamic loader can load the `libTkernel.so` file. for example:
```sh
export LD_LIBRARY_PATH=path/to/lib:$LD_LIBRARY_PATH
```
4. In your application include the main Termux header
```c
#include "Termux.h"
``` 
5. Compile your application by setting the include path to include inside the repository, and the library path to where libTkernel.so is located. Then link the library:
```sh
clang++ example.cpp -o example -Lsrc -Iinclude -lTkernel
```

***



## Examples 

```c
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
```
**An example of getting termux directory paths**
***