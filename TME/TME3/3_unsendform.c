#include "peroraison.h"

#define MINELEM "^ *return +" \
	"this *\\. *elements\\[ *'([a-zA-Z0-9]*)' *\\] *\\. *value *\\. *" \
	"match *\\( */([^/]*)/ *\\) *!= *null *;"

// Nombre de paires de parentheses dans cette regexp + 1:
#define MATCHES 3

int submit_railleur_3 (httpform *own)
{
  static int done = 0;
  static regex_t re;
  char erreur[256];
  int n, nerreur;
  request *p;
  char *q;

  if (!done) {
    nerreur = regcomp(&re, MINELEM, REG_EXTENDED);
    if (nerreur) {
      regerror(nerreur, &re, erreur, 256);
      peroraison("regexp", "mauvaise regexp", 13);
    } else done = 1;
  }
  regmatch_t matches[MATCHES];
  if (!own->onsubmit || regexec(&re, own->onsubmit, MATCHES, matches, 0)) {
    printf("regexp pas reconnue\n");
    return 1;
  }
  n = (int)matches[1].rm_so;
  p = trouve_param(own, own->onsubmit, n, ((int)matches[1].rm_eo)-n);
  n = (int)matches[2].rm_so;
  q = own->onsubmit+n;
  n = (int)matches[2].rm_eo - n;
  if (!p) {
    return 2;
  } else {
    char regexp[n+1];
    regex_t re2;
    strncpy(regexp, q, n);
    regexp[n]=0;
    // Compter le nb de "(" pour allouer a minima le 4e arg de regexec
    n = 1;
    while ((q=index(q, '('))!=NULL) {n++;q++;}
    nerreur = regcomp(&re2, regexp, REG_EXTENDED);
    if (nerreur) {
      regerror(nerreur, &re2, erreur, 256);
      return 2;
    } else {
      regmatch_t matches[n];
      printf("Compare '%s' et '%s'\n", p->value, regexp);
      return regexec(&re2, p->value, n, matches, 0) ? 2 : 0;
    }
  }
}
