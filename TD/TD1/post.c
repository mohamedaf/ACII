#include "peroraison.h"

void HttpPOST (int desc, struct mra *s, char *buf)
{
  struct stat sts;

  if (strncmp(buf, "POST ", strlen("POST "))) {
    HttpErro(desc, s, "Incompris" SEP SEP);
    return;
  }

  buf+=strlen("POST ");

  if ( stat (buf, &sts) != 0) {
    HttpErro(desc, s, "Fichier introuvable" SEP SEP);
    return;
  }

  if(!fork()) { /*processus fils*/

  }
}
