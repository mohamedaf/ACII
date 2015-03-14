#include "peroraison.h"

char * AnalyseEntetes(FILE *f, int *n)
{
  char* buff = (char*) malloc(200*sizeof(char));
  char* sousType = NULL;
  char* tmp = NULL;

  while(fgets(buff, (200*sizeof(char)), f)){
    /* Affichage des entetes */
    printf("%s\n",buff);

    tmp = strsep(&buff, ": ");


    if(!strncmp(tmp,"Content-Type",12*sizeof(char)))
      strcpy(sousType, buff);
    else if(!strncmp(tmp,"Content-Length",14*sizeof(char)))
      *n = atoi(buff);
  }

  if(!sousType)
    strcpy(sousType,"html");

  return sousType;
}

/* strlen(buf) <= 2 ==> fon des entetes */
/* je vais jusqu'au premier caractère qui est soit espace soit \r soit \n */
