# Termux-API

a high level api to interact with termux, its currently in early stage and not fully implemented. 

***

## Getting Started
It is a termux only api so it should be compiled and used in a termux environment

<ins>**1. Downloading the repository:**</ins>

clone the repository with `git clone https://github.com/Byten01/Termux-API.git`.

Or go to `Code` and tap on `Download zip` to download it as a zip file

<ins>**2. Configuring the using the api:**</ins>

1. After downloading the repo go inside the directory and you'll have 2 dir named `include` and `src`.
2. here we are using dynamic linking and depending on the system it will produce a compiled binary to be dynamically liked by the main app. run the `CMakeLists.txt` to compile..
3. To use the API you need to include `Termux.h` in your code found in `include` and link with the compiled binary when compiling the code 

***

