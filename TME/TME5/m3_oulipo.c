#include "oulipo.h"

void fButtonRelease(XButtonEvent *xbe)
{
  int y = ((3*espacement)/4);
  ecrire(mots[last_sel]);
  mots[last_sel]= mot; // il faudrait libérer en fait
  XClearWindow(dpy, filles[last_sel]);
  reecrire(gcinv, xbe->window, espacement, y, mots[last_sel]);
  recepteur=True;
  XUngrabPointer(dpy, CurrentTime);
  XDestroyWindow(dpy, drag);
  drag = 0;
}
