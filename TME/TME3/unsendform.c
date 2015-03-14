#include "peroraison.h"

int index_attribute(const char *name, const char **atts)
{
  int j;
  for (j = 0; atts[j]; j+=2) if (!strcasecmp(atts[j], name)) return j+1;
  return 0;
}

void XMLCALL HInput(void *data, const char *name, const char **atts)
{
  httpform *own = (httpform *) data;

  if (own->method && (!strcasecmp(name,"input")))
    {
      int j = index_attribute("type", atts);
      HInput_and_Button(data, j ? atts[j] : "text", atts);
    }
}

void XMLCALL HButton(void *data, const char *name, const char **atts)
{ 
  httpform *own = (httpform *) data;

  if (own->method &&  (!strcasecmp(name,"button")))
    {
      int j = index_attribute("type", atts);
      HInput_and_Button(data, j ? atts[j] : "button", atts);
    }
}


void (*elements[27])(void *data, const char *name, const char **atts)
= {
  &HMuet,   &HMuet,   &HButton, // @ A B
  &HMuet,   &HMuet,   &HMuet, // C D E
  &HForm,   &HMuet,   &HMuet, // F G H
  &HInput,  &HMuet,   &HMuet, // I J K
  &HMuet,   &HMuet,   &HMuet, // L M N
  &HOption, &HMuet,   &HMuet, // O P Q
  &HMuet,   &HSelect, &HTextarea, // R S T
  &HMuet,   &HMuet,   &HMuet, // U V W
  &HMuet,   &HMuet,   &HMuet  // X Y Z
};

void XMLCALL startElement(void *data, const char *name, const char **atts)
{
  elements[hash_balise(name)](data, name, atts);
}

void XMLCALL endElement(void *data, const char *name)
{
  httpform *own = (httpform *) data;

  if ((!strcasecmp(name, "select")) ||(!strcasecmp(name, "textarea")))
      {
	own->current_name = NULL;
      }
}

request * add_input_request_uri(httpform *own, const char *att, const char **atts)
{
  int n = index_attribute("name", atts);
  int k = index_attribute(att, atts);

  return !(n && k && *atts[n]) ? NULL :
    add_to_request_uri(own, strdup(atts[n]), strdup(atts[k]));
}

request * add_to_request_uri(httpform *own, char *p, char *q)
{
    request *r = (request *) malloc(sizeof(request));
    if (!r) peroraison("Character Data", "Allocation impossible");
    r->name = p;
    r->value = q;
    r->isfile = 0;
    r->next = own->params;
    own->params = r;
    return r;
}

// Encodage des caracteres non alphanumeriques sous forme %HH, HH = code ASCII
// En fait ce n'est important que pour "&" "=" et " ", 
// afin que le serveur decode bien l'argument de la requete.
char * encode (char *p)
{
 char *r;
 char *q = p;
 int n = 0;

 while(*q) 
   {
     if (!(isdigit(*q) || isalpha(*q))) n+=2;
     q++;
   }
 if (!n) return p;
 q = (char *) malloc(n+1+strlen(p)); // a rendre
 r = q;
 while(*p)
   {
     if (isdigit(*p) || isalpha(*p))
        *q++ = *p;
     else
        {  
          *q++ = '%';
          *q++ = (*p >> 4) + '0';
          *q++ = ((*p & 0x0F)) + '0';
        }
     p++;
   }
 *q = 0;
 return r;
}

// une fonction qui separe procotole, serveur et path

void split_url(httpform *own)
{
  char *url, *q;
  url = own->action ? index(own->action, ':') : NULL;
  if (url)
  {
    *url = '\0';
    url++;
  } else {
    url = own->action;
    own->action = DEFAULTPROTOCOL;
  }

  if (url && !strncmp(url,"//",2))
  {
    own->host = url;
    q = url+2;
    while (*q && (*q != '/')) {*url++ =  *q++; }
    *url = '\0';
    url=q;
  }
  else own->host = DEFAULTSERVER;
  own->script = url ? url : DEFAULTSCRIPT;
}

// la fonction qui traite la balise form
void XMLCALL HForm(void *data, const char *name, const char **atts)
{
  httpform *own = (httpform *) data;
  int j;

  if (strcasecmp(name, "form")) return;

  own->numero--;
  if (own->numero) return;
  
  j = index_attribute("method", atts);
  own->method = (j && atts[j] && !strcasecmp(atts[j], "post")) ? "POST" : "GET";

  j = index_attribute("enctype", atts);      
  own->enctype = (j && !strcmp(atts[j], CT_MFD)) ? CT_MFD : CT_AXWFU;

  j = index_attribute("onsubmit", atts);
  if (j) own->onsubmit = strdup(atts[j]); // a rendre

  j = index_attribute("action", atts);
  if (j) own->action = strdup(atts[j]); // a rendre

  split_url(own);
}
void analyse_form(httpform *own)
{
  char buf[LINELENGTH];
  XML_Parser phraseur = XML_ParserCreate("ISO-8859-1");
  int done;

  own->need_value= 0;
  own->current_name = NULL;
  own->phraseur = &phraseur;

  XML_SetUserData(phraseur, own);
  XML_SetElementHandler(phraseur, startElement, endElement);
  XML_SetCharacterDataHandler(phraseur, HandlerCharacterData);
  do {
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    done = len < sizeof(buf);
    if (XML_Parse(phraseur, buf, len, done) == XML_STATUS_ERROR) {
      fprintf(stderr,
              "%s at line %ld\n",
              XML_ErrorString(XML_GetErrorCode(phraseur)),
              XML_GetCurrentLineNumber(phraseur));
      return ;
    }
  } while (!done);

  XML_ParserFree(phraseur);
}

int main(int argc, char *argv[])
{
  httpform own;
  int (*f)(httpform *own);
  int in = 1; // en phase de mise au point, ecrire sur le flux de sortie
  int type;

  if (!((argc >= 2) && sscanf(argv[1],"%d",&own.numero)))
    own.numero = 1; 

  if (!((argc >= 3) && sscanf(argv[2],"%d", &type)))
    type = 0; 
 
  switch (type) {
  case 1: f = &submit_railleur_1; break;
  case 2: f = &submit_railleur_2; break;
  case 3: f = &submit_railleur_3; break;
  default: printf("Submit inconnu\n"); exit(2);
  }

  own.action = NULL;
  own.host = NULL;
  own.script = NULL;
  own.method = NULL;
  own.enctype = NULL;
  own.params = NULL;
  own.onsubmit = NULL;

  analyse_form(&own);
  printf("Formulaire type %d\n", type);
  saisies_choisies(&own, in, "&");
  write(in, "\n", 1);
  if (!own.method || (type && f(&own))) {
    printf("Submit invalide: %s\n", own.onsubmit);
    exit(type);
  }
  write(in, own.onsubmit, strlen(own.onsubmit));
  write(in, " OK\n", 4);
  exit (0);
}
