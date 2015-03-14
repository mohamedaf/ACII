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

/*liste chainee contenant attribut=valeur avec ça on construit apres la QueryString*/

request * add_to_request_uri(httpform *own, char *p, char *q)
{
    request *r = (request *) malloc(sizeof(request));
    if (!r) peroraison("Character Data", "Allocation impossible", 1);
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
// Retourne NULL si rien a encoder
// Une nouvelle chaine avec encodage sinon
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
 if (!n) return NULL;
 q = (char *) malloc(n+1+strlen(p)); // a rendre
 r = q;
 while(*p)
   {
     if (isdigit(*p) || isalpha(*p))
        *q++ = *p;
     else
        {
          *q++ = '%';
	  n = (*p >> 4);
	  *q++ = n + ((n<10) ? '0' : ('A'-10));
	  n = (*p & 0x0F);
	  *q++ = n + ((n<10) ? '0' : ('A'-10));
        }
     p++;
   }
 *q = 0;
 return r;
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
  int in = 1; // en phase de mise au point, ecrire sur le flux de sortie

  if (!((argc >= 2) && sscanf(argv[1],"%d",&own.numero)))
    own.numero = 1;

  own.action = NULL;
  own.host = NULL;
  own.dir = NULL;
  own.script = NULL;
  own.method = NULL;
  own.enctype = NULL;
  own.params = NULL;

  analyse_form(&own);

  if (own.method) {

    sscanf(argv[2],"%d",&in);
    if (in > 1) {
      //      lance_requete(&own, in); decommenter pour le TME
    } else {
      saisies_choisies(&own, in, "&");
    }
  }
  exit (0);
}
