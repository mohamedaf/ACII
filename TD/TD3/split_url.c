#include "peroraison.h"

// Analyse une URL terminee par un espace ou la fin de la chaine comme dans:
// http://serveur/repertoire/fichier.php?x=1&z=33 HTTP/1.1
// retourne un code d'erreur HTTP si pb
// l'opposee de la longueur de l'URL si ok.
// Isole le serveur, le repertoire, le dir, le fichier, la query-string
// et les copie dans les 5 pointeurs fournis en arguments
// Pas de copie quand un pointeur vaut NULL.

int split_url(const char *url, char* protocol, char *server, char *dir, char *file, char *qs)
{
  int n=0, l=0, m=0;
  char *q, *p;

  p = index(url, ' ');
  l = m = p ? p-url : strlen(url);
  if (l > ((1<<12)-4)) return 413;
  // Chercher la Query-String eventuelle
  q = index(url, '?');
  if (q) {
    n = q-url;
    if (qs) {
      strncpy(qs, q+1, l-n-1);
      qs[l-n] = 0;
    }
    l = n;
  } else {
    if (qs) *qs = 0;
  }
  // Chercher le protocole eventuel avec son serveur
  p = index(url, ':');
  if (p && (*(++p)=='/') && (*(++p)=='/')) {
    n = (p-2)-url;
    if (protocol) {
      strncpy(protocol, url, n);
      protocol[n] = 0;
    }
    l-=n+3;
    ++p;
    q = index(p+1, '/');
    if (!q) q = p;
    n = q-p;
    if (server) {
	strncpy(server, p, n);
	server[n] = 0;
    }
    l-=n;
  }
  // Chercher le dernier / 
  // (on suppose qu'il n'y en a pas dans la query-string)
  p = rindex(q ? q : url, '/');
  // Chemin relatif interdit
  if (!p) return 400;
  n=p-q+1;
  if (dir) {
    strncpy(dir, q, n);
    dir[n] = 0;
  }
  l-= n;
  if (file) {
    strncpy(file, p+1, l);
    file[l] = 0;
  }
  printf("%s %s %s %s %s %d\n", protocol, server, dir, file, qs, m);
  return 0-m;
}
