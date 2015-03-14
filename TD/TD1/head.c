#include "peroraison.h"

// Implemente la requete HEAD (sans allouer de memoire)

void HttpHEAD (int desc, struct mra *s, char *buf)
{
  struct stat sts;
  int i;

  /*Je verifie que les 5 premiers caracteres sont bien HEAD*/

  if (strncmp(buf, "HEAD ", strlen("HEAD "))) {
    HttpErro(desc, s, "Incompris" SEP SEP);
    return;
  }
  buf+=strlen("HEAD ");
  i = split_url(buf, NULL, NULL, NULL, NULL, NULL);

  if (i > 0) {
    // Mauvaise Requete
    HttpErro(desc, s, "Incompris" SEP SEP);
    return;
  }
  printf("%s %d\n", buf, i);
  // Remplacer espace, saut de ligne ou "?" par une fin de la chaine
  /* il colle un zero a la fin de l'url */
  /* (0-i) donne la longueur de la requete positif */
  *(buf+(0-i)-1) = 0;
  printf("%s--- %d\n", buf, i);
  if ( stat (buf, &sts) != 0) {
    HttpErro(desc, s, "Fichier introuvable" SEP SEP);
    return;
  }

  HttpOK (desc, s, "Last-Modified: ");
  write(desc, ctime(&sts.st_mtime), 25);
  /* envois d'un double return pour dire que c'est fini */
  write(desc, SEP SEP, strlen(SEP SEP));
}
