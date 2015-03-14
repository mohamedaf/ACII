#include "peroraison.h"

/* definir notre regex pour la suite */
#define REGFORME "^ *return +" \
  "this *\\. *elements\\['([a-zA-Z0-9]+)'\\] *\\. *value *\\. *length"	\
  " *> *([0-9]+) *;"

request *trouve_param(httpform *own, char *js, int debut, int longueur)
{
  request *p;

  for(p=pwn->params; p; p=p->next){
    if(strlen(p->name) == longueur && (!strncmp(p->name, js+debut, longueur)))
      return p;
  }

  printf("Param inexistant !!\n");
  return NULL;
}


int submit_railleur_2(httpform *own)
{
  request *tmp;
  regex_t r;
  regmatch_t s[3];
  int n;

  if(regcomp(&r, REGFORME,  REG_EXTENDED)){
    peroraison("submit_railleur_1","regcomp failed !!\n", -1);
    return 1;
  }

  if(!own->onsubmit || regexec(&r, own->onsubmit, 3, s, 0)){
    printf("REGEX non reconnu !!");
    return 1;
  }

  p = trouve_param(httpform *own, char *js, (int) s[1].rm_so, ((int) s[1].rm_eo)-n);

  n = (int) s[2].rm_so;

  sscanf(own->onsubmit+n, "%d", &n);

  if(!p)
    return 1;

  return (strlen(p->value) >= n);
}
