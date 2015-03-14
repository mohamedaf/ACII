#include "peroraison.h"

void XMLCALL HTextarea(void *data, const char *name, const char **atts)
{
  int i;
  httpform *own = (httpform*) data;

  if(strcasetmp(name, "textarea"))
    return;

  /* Che pas pk .. */
  if(own->numero)
    return;

  i = index_attribute("name", atts);

  if(i && atts[i]){
    own->current_name = strdup(atts[i]);
    own->need_value = 1;
  }
}


void XMLCALL HandlerCharacterData(void *data, const char *text, int len)
{
  httpform *own = (httpform*) data;
  char *n;

  if(own->need_value && len){
    n = (char*) malloc(len+1);
    strncpy(n, text, len);
    n[len] = '\0';
    add_to_request_uri(own, own->current_name, n);
    own->need_value = 0;
  }
}
