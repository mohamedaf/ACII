#include "peroraison.h"

void ecoute (int md, fd_set *s){
  struct timeval tv;

  tv.tv_sec = MAXWAIT;
  tv.tv_usec = 0;

  if(select(md, s, NULL, NULL, &tv) == -1)
    peroraison("select","sélection erronée");

}
