#include "peroraison.h"

void XMLCALL HForm(void *data, const char *name, const char **atts)
{
  httpform *own = (httpform *) data;
  int j;

  if(strcasecmp(name, "form"))
    return;

  /* car plusieurs form peuvent exister donc compteur */
  own->numero--;
  if (own->numero) return;

  j = index_attribute("method",atts);
  own->method = (j && atts[j] && !strcasecmp(atts[j], "post")) ? "POST" : "GET";

  j = index_attribute("enctype",atts);
  own->enctype = (j && !strcmp(atts[j], CT_MFD)) ? CT_MFD : CT_AXWFU;

  j = index_attribute("action", atts);

  if (j) {
    /* alloe 4 kilo octet */
    char a[1<<12];
    char h[1<<12];
    char d[1<<12];
    char s[1<<12];

    j = split_url(atts[i], a, h, d, s, NULL);

    own->action = a ? strdup(a) : DEFAULTPROTOCOL;
    own->host = h ? strdup(h) : DEFAULTSERVER;
    own->dir = d ? strdup(d) : "";
    own->script = s ? strdup(s): DEFAULTSCRIPT;
  }

  printf("%s %s %s %s\n", own->action, own->host, own->dir, own->script);
}
