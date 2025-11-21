# Commands

Command to run in code directory on ipad to pull latest version from github  
```
git pull origin main
```

Compiling code  
```
gcc $( pkg-config --cflags gtk4 ) -o filename fileneme.c $( pkg-config --libs gtk4 )
``` 
running code  
```
./fileneme
```
