#include "peroraison.h"

void envoyer_param_get(httpform *own, int desc) {
  write(desc, index(own->script,'?') ? "&" : "?", 1);

  saisies_choisies(own, desc, "&");

  write(desc, " ", 1);
  write(desc, DEFAULTVERSION, strlen(DEFAULTVERSION));
  write(desc, "\nHost: ", 7);
  write(desc, own->host, strlen(own->host));
  write(desc, "\n\n", 2);
}
