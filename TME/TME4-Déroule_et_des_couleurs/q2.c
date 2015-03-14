#include "peroraison.h"


void HttpTr(void *data, const char *name, const char **atts)
{
  liste_de_ligne *l;

  if(strcasecmp(name, "tr"))
    return;

  l = (liste_de_ligne*) malloc(sizeof(liste_de_ligne));

  if (!l){
    fprintf(stderr, "malloc indisponible");
    exit(3);
  }

  l->premier = NULL;
  l->dernier = NULL;
  l->next = NULL;

  add_line(((httptable *) data), l);
}
