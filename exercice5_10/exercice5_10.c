#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 3){
        printf("Nombre d'arguments instasfisants");
        return 1;
    }
     
