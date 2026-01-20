# Library

libpoppler-glib-dev
gtk4

# Commands

Command to run in code directory on ipad to pull latest version from github  
```
git pull origin main
```

Compiling code manually  
```
gcc $( pkg-config --cflags gtk4 ) -o filename fileneme.c $( pkg-config --libs gtk4 )
``` 

# Configuring automatic compiling with CMake

CMake is used to generate Makefile.

If you add a new file that you want to compile automatically, you have to add a line in CMakeLists.txt like follows:
```
add_executable(executableName fileName.c)
```
When you have made a change in CMakeLists.txt, you need to generate a new Makefile. Navigate to the build directory and run the following command:
```
cmake ..
```
(.. means directory above)


# Compile automatically with Make

If CMakeLists.txt contains a file and you have an up to date Makefile, you should be able to compile it.
Navigate to the build directory and run the following:
```
make
```
this will make executables for all files included in CMakeLists.txt.


To delete all generated executables, run the following command:
```
make clean
```

# Running

running executable(in build directory)  
```
./fileName
```
