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
• include -> the declaration of the apis to be included
• src -> the implementation of the apis
2. here we are using dynamic linking so all the source code should be converted to a single dynamic library file  to be dynamically linked by the app..to compile the source code go to `src` and we are going to use cmake to automate compilation.. follow these commands to do that
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

