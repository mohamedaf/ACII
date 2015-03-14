#include <stdio.h>
#include <stdlib.h>		/* pour EXIT_SUCCESS, EXIT_FAILURE */
#include <ctype.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>		/* pour socket */
#include <netinet/in.h>		/* pour sockaddr_in et INET_ADDRSTRLEN */
#include <netdb.h>		/* pour getnameinfo */
#include <unistd.h>		/* pour read /write */
#include <arpa/inet.h>		/* pour inet_aton */
#include <time.h>		/* clair */
#include <string.h>		/* pour strcmp */
#include <fcntl.h>		/* pour open */


#define LOCAL "127.0.0.1"
#define MAXCONNEX 10
#define MAXWAIT (30)
#define REQUETEMAX 1024
#define SEP "\n"
#define HTTPNUM "HTTP/1.1"

  // hash tres basique selon le premier caractère de la ligne émise
  
#define hash(b) (((*b >= 'A') && (*b <= 'Z')) ? (*b - 'A' + 1) : 0)


struct mra {
  int  desc;
  char host[16];
  time_t timeOfLastEvent;
};

extern void (*requetes[27])(int,struct mra *,char *);
extern int HttpInit (int desc, struct mra *s,  fd_set *z);
extern void HttpOK (int desc, struct mra *s, char *buf);
extern void HttpErro (int desc, struct mra *s, char *buf);
extern void HttpHEAD (int desc, struct mra *s, char *buf);
extern void HttpGET (int desc, struct mra *s, char *buf);
extern void HttpOPTIONS (int desc, struct mra *s, char *buf);
extern void HttpPOST (int desc, struct mra *s, char *buf);
extern void peroraison (char *f, char *m);
extern int split_url(const char *url, char* protocol, char *server, char *dir, char *file, char *qs);
void ecoute (int md, fd_set *s);
int initclient(int desc, struct mra *s,  fd_set *z);

extern char argv0[128];

// Peroraison.c :
//#include "peroraison.h"
// char argv0[128]="";
// void peroraison (char *f, char *m)
// {
//  printf("%s: %s :", argv0, f);
//  perror(m);
//  exit (EXIT_FAILURE);
// }
