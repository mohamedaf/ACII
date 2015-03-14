/**@file initclient.c
* Question 3: Accepte la connection d'un nouveau client sur une nouvelle socket.
*/

#include "peroraison.h"

int initclient(int desc, struct mra *s,  fd_set *z)
{
 int d,error;
 struct sockaddr_in sadr;
 socklen_t sn=sizeof(struct sockaddr_in);
 //pointeur vers la structure generique sockaddr
 /* sockaddr_in pas obligatoire mais plus propre */
 struct sockaddr *sa = (struct sockaddr *) &sadr;
 d = accept(desc, sa, &sn);
 if (d != -1) {
   // mettre la socket dans l'ensemble des descripteurs
   FD_SET(d,z);
   // init info client: le descritpeur
   s->desc = d;
   // init info client: date dernière action
   s->timeOfLastEvent = time(NULL);
   // init info client: adresse du client
   /* inet_ntoa passe d'une representation binaire a une representation ASCII */
   strcpy(s->host,inet_ntoa(sadr.sin_addr));
   {
	char hostname[NI_MAXHOST], hostsrvs[NI_MAXSERV];
	if ((error=getnameinfo(sa, sn,
			       hostname, sizeof(hostname),
			       hostsrvs, sizeof(hostsrvs),
			       NI_NUMERICHOST | NI_NUMERICSERV)))
	  peroraison("getnameinfo",(char *)gai_strerror(error));
	printf("Acceptation de %d depuis %s, sur le port %s\n",d,hostname,hostsrvs);
   }
 }
 return d;
}
