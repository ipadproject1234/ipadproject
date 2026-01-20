#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    char path[200];
    getcwd(path, sizeof(path));
    while(path[strlen(path) - 1] != '/'){
        printf("%c\n", path[strlen(path) - 1]);
        path[strlen(path) - 1] = '\0';
    }
    strcat(path, "files");
    printf("%s\n", path);

    return 0;
}
