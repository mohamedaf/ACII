#include <strings.h>
#include <stdio.h>
#include <stdlib.h>		/* pour EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h>		/* pour socket */
#include <netinet/in.h>		/* pour sockaddr_in et INET_ADDRSTRLEN */
#include <netdb.h>		/* pour gethostbyname */
#include <unistd.h>		/* pour read /write */
#include <fcntl.h>		/* pour open */
#include <arpa/inet.h>		/* pour inet_aton */
#include <time.h>		/* clair */
#include <ctype.h> /* pour isalpha et isdigit */
#include <errno.h> /* pour perror et errno */
#include "expat.h"

#define hash_balise(b) ((('a' <= *(b)) && (*(b) <= 'z')) ? (*(b)-'a'+1) : 0)
#define PROXY proxy
#define PROXY_PORT 1080
#define LINELENGTH 1024

typedef struct  entry {
  char *name;
  char *revision;
  char *committed_rev;
  char *committed_date;
  char *last_author;
  char *kind;
  char *schedule;
  struct entry *next;
} entries;


typedef struct {
  char *server;
  char *serverpath;
  char *revision;
  char *committed_rev;
  char *committed_date;
  char *last_author;
  entries * contenu;
  XML_Parser *phraseur;
} svn;

extern char reponse_http[BUFSIZ];
extern int split_url(const char *url, char* protocol, char *server, char *dir, char *file, char *qs);
extern int index_attribute(const char *name, const char **atts);
extern char * copy_attribute(const char *name, const char **atts);
extern char *SvnMuet(int argc, char *argv[], svn *own);
extern char *(*actions[27])(int argc, char *argv[], svn *own) ;
extern void phraser_xml(XML_Parser phraseur, int desc);
extern int main(int argc, char *argv[]);
extern char argv0[128];
extern void peroraison (char *f, char *m, int n);
extern int InitConnexion(char *serveur, int port;
extern void XMLCALL endElement(void *data, const char *name);
extern void XMLCALL startElement(void *data, const char *name, const char **atts);
extern void update_entries(svn *svnentries);
extern char *SvnDelete(int argc, char *argv[], svn *own);
extern char *SvnAdd(int argc, char *argv[], svn *own);
extern char *SvnCommit(int argc, char *argv[], svn *own);
extern char *SvnUpdate(int argc, char *argv[], svn *own);
