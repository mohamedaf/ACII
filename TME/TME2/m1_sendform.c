#include "peroraison.h"

void lance_requete(httpform *own, int port)
{
  int sock;
  char *p = NULL;

  while(){
    sock = InitConnexion(own->host ,port);

    if(!strcasecmp(own->method,"GET"))
      write(sock, "GET", 3);
    else if(!strcasecmp(own->method,"POST"))
      write(sock, "POST", 4);
    else
      peroraison("","Erreur la method n'est ni de type GET ni POST",0);

    write(sock, " ", 1);
    write(sock, own->action, strlen(own->action));
    write(sock, "://", 3);
    write(sock, own->host, strlen(own->host));
    write(sock, own->dir, strlen(own->dir));
    write(sock, own->script, strlen(own->script));

    if(!strcasecmp(own->method,"GET"))
      envoyer_param_get(own, desc);
    else if(!strcasecmp(own->method,"POST")){
      if(!strcasecmp(own->enctype, CT_MFD))
	envoyer_param_post_multipart(own, desc);
      else
	envoyer_param_post_application(own, desc);
    }

    p = tire_reponse(desc);

    if(strlen(p) <= 3)
      break;

    char a[1<<12];
    char h[1<<12];
    char d[1<<12];
    char s[1<<12];

    i = split_url(p, a, h, d, s, NULL);

    own->action = a ? strdup(a) : DEFAULTPROTOCOL;
    own->host = h ? strdup(h) : DEFAULTSERVER;
    own->dir = d ? strdup(d) : "";
    own->script = s ? strdup(s): DEFAULTSCRIPT;

    close(desc);
    printf("redirige %s\n", p);
  }
}
