#include "peroraison.h"

void HttpTd(void *data,  const char *name, const char **atts)
{
  int j;
  liste_de_case *l;
  httptable *own = ((httptable *) data);

  if(strcasecmp(name, "td"))
    return;

  l = (liste_de_case*) malloc(sizeof(liste_de_case));

  if (!l){
    fprintf(stderr, "malloc indisponible");
    exit(2);
  }

  l->onmouseover =  NULL;
  l->onmouseout =  NULL;
  l->rowspan = 1;
  l->colspan = 1;
  l->id =  NULL;
  l->next =  NULL;

  for (j = 0; atts[j]; j+=2) {
    if (!strcasecmp(atts[j], "style")) {
      style_bg_color(atts[j+1], l);
    } else if (!strcasecmp(atts[j], "onmouseover")) {
      l->onmouseover = strdup(atts[j+1]);
    } else if (!strcasecmp(atts[j], "onmouseout")) {
      l->onmouseout = strdup(atts[j+1]);
    } else if (!strcasecmp(atts[j], "id")) {
      l->id = strdup(atts[j+1]);
    } else if (!strcasecmp(atts[j], "colspan")) {
      l->colspan = (!atts[j+1] ? 1 : strtol(atts[j+1], NULL, 10));
    }
  }

  add_cell(own, l);
  if (!own->nb_tr)
    own->nb_td += l->colspan;
}
