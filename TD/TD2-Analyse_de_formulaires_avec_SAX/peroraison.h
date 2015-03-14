#include <stdio.h>
#include <stdlib.h>		/* pour EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h>		/* pour socket */
#include <netinet/in.h>		/* pour sockaddr_in et INET_ADDRSTRLEN */
#include <netdb.h>		/* pour gethostbyname */
#include <unistd.h>		/* pour read /write */
#include <arpa/inet.h>		/* pour inet_aton */
#include <time.h>		/* clair */
#include <string.h>		// pour strcmp
#include <ctype.h>		// pour isalpha et isdigit
#include <fcntl.h>
#include "expat.h"

#define DEFAULTVERSION "HTTP/1.1"
#define DEFAULTSERVER "localhost.localdomain"
#define DEFAULTPROTOCOL "http"
#define DEFAULTSCRIPT "SurVersion.php"
#define CLENGTH "Content-Length: "
#define CTYPE "Content-Type: "
#define CT_AXWFU "application/x-www-form-urlencoded"
#define CT_MFD "multipart/form-data"
#define LINELENGTH 512

#define hash_balise(b) (((*b >= 'a') && (*b <= 'z')) ? (*b - 'a' + 1) : 0)
#define hash_input_type(b) (((*b >= 'a') && (*b <= 'z')) ? (*b - 'a' + 1) : 0)

typedef struct  request_uri {
  char * name;
  char * value;
  int isfile;
  struct request_uri * next;
} request;

typedef struct {
  char *action;
  char *host;
  char *dir;
  char *script;
  char *method;
  char *enctype;
  char *current_name;
  int need_value;
  int numero;
  request * params;
  XML_Parser *phraseur;
} httpform;

extern char argv0[128];
extern void peroraison (char *f, char *m, int n);
int index_attribute(const char *name, const char **atts);
void XMLCALL HMuet(void *data, const char *name, const char **atts);
void XMLCALL HInput_and_Button(void *data, const char *type, const char **atts);
void XMLCALL HInput(void *data, const char *name, const char **atts);
void XMLCALL HButton(void *data, const char *name, const char **atts);
void XMLCALL HInputText(void *data, const char *name, const char **atts);
void XMLCALL HInputCheckbox(void *data, const char *name, const char **atts);
void XMLCALL HInputButton(void *data, const char *name, const char **atts);
void XMLCALL HInputHidden(void *data, const char *name, const char **atts);
void XMLCALL HInputImage(void *data, const char *name, const char **atts);
void XMLCALL HInputPassword(void *data, const char *name, const char **atts);
void XMLCALL HInputSubmit(void *data, const char *name, const char **atts);
void XMLCALL HInputRadio(void *data, const char *name, const char **atts);
void XMLCALL HInputFile(void *data, const char *name, const char **atts);
void XMLCALL HTextarea(void *data, const char *name, const char **atts);
void XMLCALL HSelect(void *data, const char *name, const char **atts);
void XMLCALL HOption(void *data, const char *name, const char **atts);
void XMLCALL HForm(void *data, const char *name, const char **atts);
void (*elements[27])(void *data, const char *name, const char **atts);
void XMLCALL startElement(void *data, const char *name, const char **atts);
void XMLCALL endElement(void *data, const char *name);
void XMLCALL HandlerCharacterData(void *data, const char *text, int len);
request * add_input_request_uri(httpform *own, const char *att, const char **atts);
request * add_to_request_uri(httpform *own, char *p, char *q);
char * encode (char *p);
int InitConnexion(char *server_name, int port);
void lance_requete(httpform *own, int desc);
void envoyer_param_get(httpform *own, int desc);
void envoyer_param_post_multipart(httpform *own, int desc);
void envoyer_param_post_application(httpform *own, int desc);
void analyse_form(httpform *own);
void saisies_choisies(httpform *own, int desc, char *sep);
void tire_reponse(httpform * own, int desc);
void tire_reponse_get(httpform * own, int desc);
void tire_reponse_post_application(httpform * own, int desc);
void tire_reponse_post_multipart(httpform * own, int desc);
int split_url(const char *url, char* protocol, char *server, char *dir, char *file, char *qs);
int main(int argc, char *argv[]);
