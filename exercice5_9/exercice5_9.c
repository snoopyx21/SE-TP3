#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;
    DIR* dp;
    struct dirent *d;
    dp=opendir(argv[1]);
    if (dp == NULL) {
        perror("opendir(argv[1])");
        return 1;
    } 
    while((d=readdir(dp)) != NULL)
    { 
       if(d->d_name[0] != '.'){
            printf("%s \n", d->d_name);
        }
    }
    closedir(dp);
    return 0;
} 
