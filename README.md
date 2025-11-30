# Termux-API

a high level api to interact with termux, its currently in early stage and not fully implemented. 

***

## Getting Started
It is a termux only api so it should be compiled and used in a termux environment

<ins>**1. Downloading the repository:**</ins>

clone the repository with `git clone https://github.com/Byten01/Termux-API.git`.

Or you can download [this repo](https://github.com/Byten01/Termux-API/archive/refs/heads/main.zip) as a zip

<ins>**2. Configuring the using the api:**</ins>

1. After downloading the repo go inside the directory and you'll have 2 dir named `include` and `src`.
2. here we are using dynamic linking to be dynamically linked by the app where we are going to use the api..to compile the source code to shared objects follow these commands
```
cmake .
make -j$(nproc)
```
3. after that it will produce a shared object named `libTkernel.so` which will be the compiled binary..now set the environment variable named `LD_LIBRARY_PATH` to the path where the .so file is for example:
```
export LD_LIBRARY_PATH=xxx/yyy:$LD_LIBRARY_PATH
```
4. After that in your main program include the header named `Termux.h` which includes all the other internal headers
5. And then while compiling the app set the include directory to the `include` dir and linker directory to where your `libTkernel.so` exists..heres is the example, im using clang++ but you can use anything
```
clang++ test.cpp -o test -Lsrc -Iinclude -lTkernel
```

***

