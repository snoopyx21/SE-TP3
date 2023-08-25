// fichier found_str_dir.c

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int recherche_str(const char* chaine, const char* fic)
{
    int s_open, s_close;
    ssize_t s_read;
    char buf[128];
    int i;
    int a=0; //a=faux
    int nb=0; //indice de la chaine
    s_open=open(fic,O_RDONLY);
    if (s_open <0)
    {
        perror("open");
        printf("%s\n",fic);
        exit(0);
    }
    while((s_read=read(s_open,buf,128))>0)
    {
	for(i=0;i<s_read;i++)
	{
	    if(chaine[nb]=='\0')
	    {
	         a=2;//chaine presente dans le fichier
		 break;
	    }
	    if(buf[i]==chaine[nb])//le premier char est pareil
	    {
	         a=1;//a=vrai
		 nb++;
	    }
	    else // si jamais dans la chaine un char est different on reinitialise
	    {
	         a=0;
		 nb=0;
	    }
	}
	if(a==2)
	{
	     printf("%s\n",fic); //alors il y a la chaine, on affiche le fichier dans lequel la chaine est contenu
	     return 0;
	}
   }
   if(s_read==-1)
   {
	perror("read");
        return -1;
    }
    s_close=close(s_open);
    if(s_close==-1) perror("close(s_open)");
    return 0;
}


void list_dir(const char* rep,const char* chaine)
{
    int s_rech;
    DIR* dir;
    struct dirent* ent;
    char new_rep[255];
    struct stat dir_stat;
    int s_cl;

    if ((dir=opendir(rep)) ==NULL) //ouverture du repertoire
    {
        exit(0);
    } 
    while((ent=readdir(dir))!=NULL) //lecture du repertoire
    {
        if(ent->d_name[0]!='.') 
        {
            strcpy(new_rep,rep); // on effectue une copie de rep dans new_rep et on concatene avec le fichier/repertoire trouvé
            strcat(new_rep,ent->d_name);
            if(stat(new_rep,&dir_stat) < 0)
            {
                perror("stat");
                exit(1);
            }

            switch(dir_stat.st_mode&S_IFMT)
            {
                case S_IFREG: // si c'est un fichier regulier
                    s_rech=recherche_str(chaine,new_rep);
                    if(s_rech==-1) 
                    {
                        printf("recherche de la chaine defectueuse. \n");
                        exit(0);
                    }
                    break;
                case S_IFDIR : // si c'est un repertoire
                    strcat(new_rep,"/");
                    list_dir(new_rep,chaine);
                    break;
                default : 
                    break;


            }
        }
    }
    s_cl=closedir(dir);
    if(s_cl==-1)
    {
        perror("closedir(dir)");
    }

}


int main(int argc, char** argv)
{
    if (argc < 3 )
    {
        printf("nombre d'arguments incorrects. \n");
	return -1;
    }
    char* rep=argv[2];
    char* chaine=argv[1];
    strcat(rep,"/");
    list_dir(rep,chaine);
    return 1;
}


