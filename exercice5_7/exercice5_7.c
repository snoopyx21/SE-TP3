#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;
    struct stat st_file;
    if ( stat(argv[1], &st_file) < 0) return 1;
    switch( st_file.st_mode&S_IFMT)
    {
        case S_IFREG : 
            printf("Fichier ordinaire \n");
            break;
        case S_IFBLK :
            printf("Fichier peripherique (mode bloc)\n");
            break;
        case S_IFCHR :
            printf("Fichier peripherique (mode caractere) \n");
            break;
        case S_IFDIR :
            printf("Repertoire \n");
            break;
        case S_IFLNK :
            printf("Lien symbolique \n");
            break;
        default :
            printf("Non reconnu \n");
            break;

    }
    printf("Permissions sur le fichier \n");
    
    if ((st_file.st_mode&S_IRUSR)) 
        printf("r");
    else
        printf("-");
    if ((st_file.st_mode&S_IWUSR)) 
        printf("w");
    else
        printf("-");
    if ((st_file.st_mode&S_IXUSR)) 
        printf("x");
    else
        printf("-");
     
    
    if ((st_file.st_mode&S_IRGRP)) 
        printf("r");
    else
        printf("-");
    if ((st_file.st_mode&S_IWGRP)) 
        printf("w");
    else
        printf("-");
    if ((st_file.st_mode&S_IXGRP)) 
        printf("x");
    else
        printf("-");
   

    if ((st_file.st_mode&S_IROTH)) 
        printf("r");
    else
        printf("-");
    if ((st_file.st_mode&S_IWOTH)) 
        printf("w");
    else
        printf("-");
    if ((st_file.st_mode&S_IXOTH)) 
        printf("x");
    else
        printf("-");
    
    printf("\n \n"); 
    return 0;
}
