#include "oulipo.h"

void clone (char *mot)
{
  XSetWindowAttributes xsaw;
  XCharStruct xcs;
  int s, a, d;

  XTextExtents(font, mot, strlen(mot), &s, &a, &d, &xcs);
  if ((xcs.width==0) || (a+d==0))
    printf("%ld dimensions nullles %d %d %d pour %s\n", fen, xcs.width, a, d, mot);

  drag = XCreateSimpleWindow(dpy, fen,
			     x_root, y_root,
			     10, 10, 0,
			     BlackPixel(dpy,DefaultScreen(dpy)),
			     WhitePixel(dpy,DefaultScreen(dpy)));

  if(!drag){
    printf("impossible de creer le clone\n");
    return;
  }

  xsaw.override_redirect = True;
  XChangeWindowAttributes(dpy, drag, CWOverrideRedirect, &xsaw);
  XMapWindow(dpy, drag);
  reecrire (gcinv, drag, 0, a+d, mot);
}
