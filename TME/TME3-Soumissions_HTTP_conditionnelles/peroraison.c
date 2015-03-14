#include "peroraison.h"

char argv0[128]="";

void peroraison (char *f, char *m)
{
  printf("%s: %s :", argv0, f);
  perror(m);
  exit (EXIT_FAILURE);
}
