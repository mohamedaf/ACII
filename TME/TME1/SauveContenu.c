#include "peroraison.h"

void SauveContenu(char *buff, FILE *fdesc)
{
  FILE* f;
  char *b[LINELENGTH];
  int n;
  char *sousType = AnalyseEntetes(fdesc, &n);
  time_t t = time(NULL);

  /* A modifier, ajouter la date a concatener avant le sousType */

  f = fopen(sousType, "w+");

  /*La fonction appelé au dessus a déjà lu les entetes*/

  while(fread(b, LINELENGTH, qfdesc)){
    fwrite(b, sizeof(char), LINELENGTH, f);
  }

  fclose(f);
}
