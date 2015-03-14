#include "oulipo.h"

void fButtonPress(XButtonEvent *xbe)
{
  recepteur = False;
  x_root = xbe->x_root;
  y_root = xbe->y_root;
  ecrire("");
}


void fMotion(XButtonEvent *xbe)
{
  if (drag)
    XMoveWindow(dpy, drag, x_root, y_root);
}
