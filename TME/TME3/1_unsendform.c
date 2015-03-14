#include "peroraison.h"

/* definir notre regex pour la suite */
#define REGFORME "^ *return +this\\. *elements\\. *length *> *1 *;"

/* cette fonction retourne 0 si elle contient au moins 1 saisie
   elle renvoie une autre valeur sinon */

int submit_railleur_1(httpform *own)
{
  regex_t r;

  if(regcomp(&r, REGFORME,  REG_EXTENDED)){
    peroraison("submit_railleur_1","regcomp failed !!\n", 11);
    return 11;
  }

  if (!own->onsubmit || regexec(&re, own->onsubmit, 0, NULL, 0))
    return 1;
  else return (own->params ? 0 : 1);
}
