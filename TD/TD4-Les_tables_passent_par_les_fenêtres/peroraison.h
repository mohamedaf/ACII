#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regex.h"
#include "expat.h"
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#define MARGIN 10
#define BORDER 2
#define LINELENGTH 512

#define hash_balise(b) (((*(b) >= 'a') && (*(b) <= 'z')) ? (*(b) - 'a' + 1) : 0)

typedef struct desc_case {
  int colspan;
  int rowspan;
  char *onmouseover;
  char *onmouseout;
  XColor bgcolor;
  char *id;
  Window fenetre;
  struct desc_case * next;
} liste_de_case;

typedef struct desc_ligne {
  struct desc_case * premier;
  struct desc_case * dernier;
  struct desc_ligne * next;
} liste_de_ligne;

typedef struct {
  int nb_tr;
  int nb_td;
  int width;
  int height;
  liste_de_ligne *premier;
  liste_de_ligne *dernier;
} httptable;

extern char argv0[128];
extern Display *dpy;
extern Window fen;
extern Window deroulante[7];
extern char *rainbow[6];

extern int index_attribute(const char *name, const char **atts);
extern liste_de_case *findCaseFromWindow(Window w, httptable *own);
extern liste_de_case *findCaseFromId(char *id, httptable *own);
extern void (*elements[27])(void *data, const char *name, const char **atts);
extern void HttpMuet(void *data, const char *name, const char **atts);
extern void XMLCALL startElement(void *data, const char *name, const char **atts);
extern void XMLCALL endElement(void *data, const char *name);

extern void HttpTable(void *data, const char *name, const char **atts);
extern void HttpTr(void *data, const char *name, const char **atts);
extern void HttpTd(void *data,  const char *name, const char **atts);
extern void add_line(httptable *t, liste_de_ligne *r);
extern void add_cell(httptable *t, liste_de_case *r);
extern int find_property_css(const char *style, const char *name, regmatch_t matches[]);
extern void style_bg_color(const char *property, liste_de_case *r);
extern void create_td_window(httptable *own, Window fen);
extern void fEnter(XCrossingEvent *e, httptable *own);
extern void fLeave(XCrossingEvent *e, httptable *own);
extern void fKeyPress();
extern void fButtonPress(XButtonEvent *e, httptable *own);
extern void Deroule(XButtonEvent *e, httptable *own);
extern void Enroule(XButtonEvent *e, httptable *own);
