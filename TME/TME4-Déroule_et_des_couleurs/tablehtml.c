#include "peroraison.h"

Display *dpy;

void HttpMuet(void *data, const char *name, const char **atts)
{
}

int index_attribute(const char *name, const char **atts)
{
  int j;
  for (j = 0; atts[j]; j+=2) if (!strcasecmp(atts[j], name)) return j+1;
  return 0;
}

liste_de_case *findCaseFromWindow(Window w, httptable *own)
{
  liste_de_ligne *q;
  liste_de_case *p;
  int i,j;

  for (q = own->premier, i=0; q ; q = q->next, i++)
    {
      for (p = q->premier,j=0; p ; p = p->next, j++)
	{
	  if (w == p->fenetre)
	    return p;
	}
    }
  return NULL;
}

liste_de_case *findCaseFromId(char *id, httptable *own)
{
  liste_de_ligne *q;
  liste_de_case *p;
  int n;

  id = index(id,'"');
  if (!id) return NULL;
  id++;
  n = index(id,'"')-id;

  for (q = own->premier; q ; q = q->next)
    {
      for (p = q->premier; p ; p = p->next)
	{
	  if (p->id && (strlen(p->id) == n) && !strncmp(id, p->id, n))
	      return p;
	}
    }

  return NULL;
}


void (*elements[27])(void *data, const char *name, const char **atts) = {
  &HttpMuet,   &HttpTable,  &HttpMuet, // @ A B
  &HttpMuet,   &HttpTd,     &HttpMuet, // C D E
  &HttpMuet,   &HttpMuet,   &HttpMuet, // F G H
  &HttpMuet,   &HttpMuet,   &HttpMuet, // I J K
  &HttpMuet,   &HttpMuet,   &HttpMuet, // L M N
  &HttpMuet,   &HttpMuet,   &HttpMuet, // O P Q
  &HttpTr,     &HttpMuet,   &HttpMuet, // R S T
  &HttpMuet,   &HttpMuet,   &HttpMuet, // U V W
  &HttpMuet,   &HttpMuet,   &HttpMuet  // X Y Z
};

void XMLCALL startElement(void *data, const char *name, const char **atts)
{
  elements[hash_balise(name+1)](data, name, atts);
}

void XMLCALL endElement(void *data, const char *name)
{
  httptable *own = (httptable *) data;
  if (!strcasecmp(name, "tr")) own->nb_tr++;
}

void add_line(httptable *t, liste_de_ligne *r)
{
      if (t->dernier)
	   t->dernier->next = r;
      else t->premier = r;
      t->dernier = r;
}

void add_cell(httptable *t, liste_de_case *r)
{
      if (t->dernier->dernier)
	   t->dernier->dernier->next = r;
      else t->dernier->premier = r;
      t->dernier->dernier = r;
}

#define RE_CSS_VAL "): *([^;]+)"

// Localise une propriete CSS et sa valeur.

int find_property_css(const char *style, const char *name, regmatch_t matches[])
{
 int n = strlen(name);
 {
  char re[n+strlen(RE_CSS_VAL)+2];
  regex_t re_style;
  re[0] = '(';
  strcpy(re+1,name);
  strcpy(re+n+1, RE_CSS_VAL);
  printf("re %s style %s\n", re, style);
  n = regcomp(&re_style, re, REG_EXTENDED);
  if (!n)
    return regexec(&re_style, style, 3, matches, REG_EXTENDED);
  exit(n);
 }
}

// Alloue la couleur specifie par un attribut Style:
// "background-color: NOM"

void style_bg_color(const char *property, liste_de_case *r)
{
  regmatch_t matches[3];
  char *p;
  int n;
  n = find_property_css(property, "background-color", matches);
  p = n ? "white" : strndup(property+matches[2].rm_so, matches[2].rm_eo-matches[2].rm_so);
  XAllocNamedColor(dpy,
		   DefaultColormap(dpy, DefaultScreen(dpy)),p, &r->bgcolor, &r->bgcolor);
}

int main(int argc, char *argv[])
{
  Window fen;
  XEvent e;
  XML_Parser phraseur = XML_ParserCreate("UTF-8");
  char buf[BUFSIZ];
  httptable own;
  int done;

  if ((dpy = XOpenDisplay(NULL)) == NULL)
    {fprintf(stderr, "%s: dispositif %s injoignable\n", argv[0],
	     XDisplayName(NULL));
      exit(2);}

  own.premier = NULL;
  own.dernier = NULL;
  own.nb_tr= 0;
  own.nb_td= 0;
  own.width= 100;
  own.height= 50;

  XML_SetUserData(phraseur, &own);
  XML_SetElementHandler(phraseur, startElement, endElement);

  do {
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    done = len < sizeof(buf);
    if (XML_Parse(phraseur, buf, len, done) == XML_STATUS_ERROR) {
      fprintf(stderr,
              "%s at line %d\n",
              XML_ErrorString(XML_GetErrorCode(phraseur)),
              (int) XML_GetCurrentLineNumber(phraseur));
      return 1;
    }
  } while (!done);
  XML_ParserFree(phraseur);

  // Partie graphique
  fen = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0,
				   own.width + (MARGIN<<1),
				   own.height + (MARGIN<<1),
				   0,
				   BlackPixel(dpy,DefaultScreen(dpy)),
				   WhitePixel(dpy,DefaultScreen(dpy)));

  /* L’appel de XSelectInput a pour effet que cette fenêtre réagira
     à tout événement au clavier en terminant l’application */
  XSelectInput(dpy,fen,KeyPressMask);
  create_td_window(&own, fen);
  XMapWindow(dpy, fen);
  XMapSubwindows(dpy, fen);
  while (1) {
      XNextEvent(dpy, &e);
      switch (e.type)
      {
      case KeyPress: fKeyPress(); break;
      case LeaveNotify: {fLeave(&e.xcrossing, &own); break;}
      case EnterNotify: {fEnter(&e.xcrossing, &own); break;}
      case ButtonPress: {fButtonPress(&e.xbutton, &own); break;}
      default: break;
      }
  }
  exit(0);
}
