#include "peroraison.h"

void HttpTable(void *data, const char *name, const char **atts)
{
  int j;
  regmatch_t m[3];

  if(strcasecmp(name, "table"))
    return;

  if(!(j=index_attribute("style", atts)))
    return;

  if(!find_property_css(atts[j], "height", m)){
    /* strtol ici lit jusqua la fin du chiffre donc ici avant px */
    ((httptable *) data)->height = strtol(atts[j]+m[2].rm_so, NULL, 10);
  }
  if(!find_property_css(atts[j], "width", m)){
    ((httptable *) data)->width = strtol(atts[j]+m[2].rm_so, NULL, 10);
  }
}
