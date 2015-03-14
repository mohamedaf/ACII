#include "peroraison.h"

void envoyer_param_post_application(httpform *own, int desc)
{
  char sep='\n';
  request *liste = own->params;
  char length=0;

  write(desc, "\nHost: ", 7);
  write(desc, own->host, strlen(own->host));
  write(desc, &sep, 1);
  write(desc, CTYPE, strlen(CTYPE));
  write(desc, CT_AXWFU, strlen(CT_AXWFU));
  write(desc, &sep, 1);
  
  while(liste){
    /* le 2 pour le = et le separateur */
    length += strlen(liste->name) + strlen(liste->value) + 2;
    liste = lists->next;
  }

  write(desc, CLENGTH, strlen(CLENGTH));
  write(desc, length, strlen(length));

  write(desc, "\n\n", 2);

  while(liste){
    write(desc, &sep, 1);
    write(desc, liste.name, strlen(liste.name));
    write(desc, "=", 1);
    write(desc, liste.value, strlen(liste.value));
    liste = lists->next;
    sep = '&';
  }

  write(desc, "\n\n", 2);
}
