#include "peroraison.h"

void XMLCALL HSelect(void *data, const char *name, const char **atts)
{
  int i;
  httpform* own = (httpform*) data;

  if(strcasecmp(name, "select"))
    return;

  i = index_attribute("name", atts);

  if(i && atts[i])
    own->current_name = strdup(atts[i]);

}


void XMLCALL HOption(void *data, const char *name, const char **atts)
{
  int i;
  httpform* own = (httpform*) data;

  if(strcasecmp(name, "option"))
    return;

  i = index_attribute("selected", atts);

  if(i && atts[i]){
    i = index_attribute("value", atts);
    if(i && atts[i])
      add_to_request_uri(own, own->current_name, atts[i]);
    else
      own->need_value = 1;
  }

}
