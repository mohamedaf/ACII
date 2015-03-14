#include "peroraison.h"

void Enroule(XButtonEvent *e, httptable *own)
{
  int i;
  XColor bgcolor;

  /* faire le truc alloc couleur */

  for(i=1; i<7; i++){
    if(e->window == deroulante[i]){
      XAllocNamedColor(dpy,
		       DefaultColormap(dpy, DefaultScreen(dpy)),
		       rainbow[i-1],
		       &bgcolor, &bgcolor);

      XSetWindowBackground(dpy, deroulante[0], bgcolor.pixel);
    }
    XDestroyWindow(dpy, deroulante[i]);
    deroulante[i]=0;
  }

  XUnmapWindow(dpy, deroulante[0]);
  XMapWindow(dpy, deroulante[0]);
  deroulante[0] = 0;
}
