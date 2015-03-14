/** @file serveur.c
* Fichier pricipal du du serveur HTTP1.1
*
* Universite Pierre & Marie Curie 
* Master d'informatique
* Architecture des Clients Internet Interactifs
* Travaux Diriges 1:  un serveur HTTP minimal
* argv[1]: numero de port
*/

#include "peroraison.h"

struct mra clients [MAXCONNEX]; //!< Tableau des clients

/** Tableau de pointeurs sur fonctions de traitement.
* Reference les fonctions de traitement des
* balises HTML.
* 
* \param[in] int : socket de communication avec le client
* \param[in] struct mra *: structure des info client
* \param[in] char *: pointeur sur debut de ligne 
*/
void (*requetes[27])(int,struct mra *,char *)={
  &HttpErro,	&HttpErro,  &HttpErro, // @ A B
  &HttpErro,	&HttpErro,  &HttpErro, // C D E
  &HttpErro,	&HttpGET,   &HttpHEAD,  // F G H
  &HttpErro,	&HttpErro,  &HttpErro, // I J K
  &HttpErro,	&HttpErro,  &HttpErro, // L M N
  &HttpOPTIONS,	&HttpPOST,  &HttpErro, // O P Q
  &HttpErro,	&HttpErro,  &HttpErro, // R S T
  &HttpErro,	&HttpErro,  &HttpErro, // U V W
  &HttpErro,	&HttpErro,  &HttpErro  // X Y Z
};

/** Fonction pour message d'acceptation HTTP universel.
* Envoie la version du protocole HTTP implemente par le 
* serveur au client.
*/
void HttpOK (int desc, struct mra *s, char *buf)
{
  printf("HttpOK\n");
  write(desc, HTTPNUM, strlen(HTTPNUM));
  write(desc, " 200 OK\n", 8); 
  write(desc, buf, strlen(buf)); 
} 

/** Fonction pour message d'erreur HTTP universel.
*
*/
void HttpErro (int desc, struct mra *s, char *buf)
{ 
  printf("HttpErro : %s\n", buf);
  write(desc, HTTPNUM, strlen(HTTPNUM));
  write(desc, " 500 ", 5); 
  write(desc, buf, strlen(buf)); 
}

/** Fonction pour message d'information HTTP OPTIONS.
* Envoit la liste des options implementees par le serveur
* au client.
*/
void HttpOPTIONS (int desc,  struct mra *s, char *buf)
{
  printf("HttpOPTIONS\n");
  if (strncmp(buf, "OPTIONS", strlen("OPTIONS")))
    HttpErro(desc, s,"Incompris");
  else 
    HttpOK (desc, s, "Allow: HEAD GET OPTIONS POST\n");
}

/** Boucle principale du serveur HTTP.*/
int main (int argc, char *argv[])
{
  int desc=0;				// socket du serveur
  int port;				// port du serveur
  struct sockaddr_in sadr;		// adresse du serveur
  fd_set z,s;				// ensembles de descripteurs de socket
  char buf[REQUETEMAX];			// buffet de lecture
  int md,maxcli,i,n,d=0;                

  strcpy(argv0,argv[0]);				

  //recuperation du no de port
  if ((argc != 2) || !sscanf(argv[1],"%d",&port)) 
    peroraison("scanf", "argument incorrect");

  // creation socket
  if ((desc = socket (AF_INET, SOCK_STREAM, 0)) == -1)	
    peroraison("socket", "plus de descripteur disponible");

  // liaison pour n'importe quelle adresse locale
  sadr.sin_family = AF_INET;			// type de protocole
  sadr.sin_port = htons (port);			// numero de port
  sadr.sin_addr.s_addr = htons (INADDR_ANY);	// adresse IP du serveur

  //liaison de la socket dans le systeme
  if (bind (desc,(struct sockaddr *) &sadr, sizeof(struct sockaddr_in)))
    peroraison("bind", "socket impossible ‚à lier");

  // mise en attente de clients
  if (listen (desc, MAXCONNEX))
    peroraison("listen", "socket sourde");

  FD_ZERO(&z);		// mise a zero de l'ensemble de descripteurs
  FD_SET(desc, &z);	// mise de la socket dans un ensemble de descripteurs

  // cette variable contient en permanence le plus grand des descripteurs +1
  md=desc+1;

  //  cette variable contient en permanence le nombre de clients connectes
  maxcli=0;

  while (1)
  { 
    // recopie TOTALE de la structure z pour partir d'un marquage nul      
    s=z;
    ecoute( md, &s);								//Question 2
    // repondre d'abord aux anciens clients: ça fait de la place s'ils meurent
    for (i=0;i<maxcli;) 
    { 
	  printf("traiter le client numero %d\n",i);
	  d=clients[i].desc;
	  if (!(FD_ISSET(d,&s)))	//si d n'est pas dans l'ensemble s
	    i++;			//passer au client suivant
	  else
	  { 
	    n=read(d, &buf, REQUETEMAX-1);	//lire la requête
		if(n > 0)							//requête non vide
		  { 
		  buf[n]=0;
		  printf("Requete depuis %s\n----\n%s\n----\n",clients[i].host,buf);
		  requetes[hash(buf)](d,&clients[i],buf);		//Question 4,5,6
		  }
		//requete vide , i.e. EOF ou erreur
		FD_CLR(d,&z);		//enlever le client de l'ensemble
		printf("Deconnexion de: %s\n",clients[i].host);
		close(d);						
		maxcli--;						
		clients[i]=clients[maxcli];
	  }
	}//for

	// accepter les nouveaux clients
	if (FD_ISSET(desc,&s))		
	{ 
	  if (maxcli==MAXCONNEX)
	    HttpErro(d,NULL,"trop de clients");
	  else
	    {
	      d=initclient(desc,&clients[maxcli], &z);		//Question 3
	      printf("Connexion %i depuis: %s\n", d, clients[maxcli].host);
	      if (d > 0) {
		if (d>=md) md=d+1;
		maxcli++;
		sleep(1);
		HttpOK(d,NULL,""); 
	      }
	    }
	  }
    }//while
  exit (EXIT_SUCCESS);
}
