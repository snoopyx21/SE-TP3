#include<dirent.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>



int recherche(const char* str, const char* fichier)
{
	int s_open;
	ssize_t s_read;
	char buf[128];
	int i;
	int a=0; //a=faux
	int nb=0; //indice de la chaine
	s_open=open(fichier,O_RDONLY);
	//if->raler
	while((s_read=read(s_open,buf,128))>0)
	{
		for(i=0;i<128;i++)
		{
			if(str[nb]=='\0')
			{
				a=2;//chaine presente dans le fichier
				break;
			}
			if(buf[i]==str[nb])//le premier char est pareil
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
			printf("%s\n",fichier); //alors il y a la chaine, on print et c'est fini
			return 0;
		}
	}
	if(s_read==-1)
	{
		perror("read");
		return -1;
	}
	return 0;
}
int main(int argc, char ** argv)
{
	if (argc < 3 )
	{
		printf("usage : ./executable chaine repertoire\n");
		return -1;
	}
	char* rep=argv[2];
	char* chaine=argv[1];
	DIR *dp;
	int s_recherche;
	struct dirent *dr; 
	int cl;
	char t[255];
	
	dp=opendir(rep);
	if(dp==NULL)
	{
		perror("opendir");
		return -1;
	}
	while((dr=readdir(dp))!=NULL)
	//mettre le chemin devant le nom de fichier
	{
		if(dr->d_name[0]!='.')
		{
			strcpy(t,rep);
			strcat(t,dr->d_name);
			s_recherche=recherche(chaine,t);
			if(s_recherche==-1)
				return -1;
			//printf("%s\t",dr->d_name);
		}	
	}
	cl=closedir(dp);
	if(cl==-1)
	{
		perror("closedir");
		return -1;
	}
	return 1;

}


