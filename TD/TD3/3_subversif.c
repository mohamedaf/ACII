#include "peroraison.h"

char *SvnCommit(int argc, char *argv[], svn *own)
{
   entries *p;
   int n, desc;
   char buffet[1024];

   for (p=own->contenu; p; p=p->next)
      if (!strcmp(p->name, argv[2])) break;
   if (!p) {
     fprintf(stderr, "Fichier %s inconnu. Utiliser la commande add\n", argv[2]);
      exit(-1);
   }

   desc = InitConnexion(own->server, 80);

   if ( !p->schedule || !strcmp(p->schedule, "add") ) { // modifcation ou ajout
      int f;
      f = open(argv[2],O_RDONLY);
      if (f < 0)  {
	fprintf(stderr, "Fichier %s  introuvable\n", argv[2]);
	exit(-1);
      }
      write(desc, "PUT /", 5);
      write (desc, own->serverpath, strlen(own->serverpath));
      write(desc,"/", 1);
      write(desc, argv[2], strlen(argv[2]));
      write(desc, "\nHost: ", strlen("\nHost: "));
      write(desc, own->server, strlen(own->server));
      write(desc, "\nIf-Not-Modified-Since ", strlen("\nIf-Not-Modified-Since "));
      write(desc, "\n", 1);
      write(desc, p->committed_date, strlen(p->committed_date));
      write(desc, "\n\n", 2);

      while((n=read(f,buffet, 1024))) write(desc,buffet,n);
      close(f);
   }
   else if ( !strcmp(p->schedule, "delete") ) { //suppression
      write(desc, "DELETE /", 8);
      write (desc, own->serverpath, strlen(own->serverpath));
      write(desc,"/", 1);
      write(desc, argv[2], strlen(argv[2]));
      write(desc, "\nHost: ", strlen("\nHost: "));
      write(desc, own->server, strlen(own->server));
      write(desc, "\n\n", 2);
   } else {
     peroraison("SvnCommit", "Erreur dans svn/entires\n", -1);
   }
   n = read(desc, reponse_http, BUFSIZ-1);
   if (n <= 0) return NULL;
   reponse_http[n] = 0;
   return reponse_http;
}
