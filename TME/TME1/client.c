#include "peroraison.h"

int main (int argc, char *argv[])
{
  int port;
  int desc;
  int n;
  char in[LINELENGTH];
  char *type;
  FILE *fdesc;

  strcpy(argv0,argv[0]);

  if (argc < 3)
    peroraison("argc", "nombre d'arguments incorrect", 3);

  if (!sscanf(argv[2],"%d",&port)) 
    peroraison("sscanf", "argument incorrect", 4);

  printf("Connexion sur %s sur le port %d\n", argv[1],port);
  desc = InitConnexion(argv[1], port);

  while (fgets(in,LINELENGTH,stdin))
    {
      if(!(strncmp(in,".\n",strlen(".\n"))))
	{printf("fin %d\n",(int)strlen("\n"));break;}
      printf("envoie de %s\n",in);
      fflush(NULL);
      if (write(desc, in, strlen(in)) <=0)
	peroraison("write","erreur sur la socket", 5);
    }  
	
  fdesc = fdopen(desc,"r");
  type = AnalyseEntetes(fdesc, &n);
  printf("recu document de type %s longeur %d\n", type, n);
  SauveContenu(type,fdesc);
  fclose(fdesc);
  exit (EXIT_SUCCESS);
}


