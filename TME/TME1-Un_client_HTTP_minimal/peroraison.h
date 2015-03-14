#include <stdio.h>
#include <stdlib.h>		/* pour EXIT_SUCCESS, EXIT_FAILURE */
#include <ctype.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>		/* pour socket */
#include <netinet/in.h>		/* pour sockaddr_in et INET_ADDRSTRLEN */
#include <netdb.h>		/* pour gethostbyname */
#include <unistd.h>		/* pour read /write */
#include <arpa/inet.h>		/* pour inet_aton */
#include <time.h>		/* clair */
#include <string.h>		// pour strcmp
#define LINELENGTH 1024

extern char argv0[128];
extern int InitConnexion(char *, int);
extern void SauveContenu(char *, FILE *);
extern char * AnalyseEntetes(FILE *, int *n);
extern void peroraison (char *f, char *m, int n);

