#include "peroraison.h"


void saisies_choisies(httpform *own, int desc, char *sep)
{
  request *p = own->params;
  char *codee = NULL;
  int n = 0;
  if (!p) return;
  while (1)
   {
     codee = encode(p->name);
     if (codee) {
       free(p->name);
       p->name = codee;
     }
     codee = encode(p->value);
     if (codee) {
       free(p->value);
       p->value = codee;
     }
     n+= strlen(p->name)+strlen(p->value)+1;
     p = p->next;
     if (!p) break;
     n++;
   }
  if (n) {
    char buf[n+1];
    int i = 0;
    p = own->params;
    while (1)
      {
	strcpy(buf+i, p->name);
	i+=strlen(p->name);
	buf[i++]='=';
	strcpy(buf+i, p->value);
	i+=strlen(p->value);
	free(p->name);
	free (p->value);
	p = p->next;
	if (!p) break;
	strcpy(buf+i, sep);
	i+=strlen(sep);
      }
    if (write(desc, buf, n) < 0)
	peroraison("write","erreur sur la socket", 5);
  }
}
