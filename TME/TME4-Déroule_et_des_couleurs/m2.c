#include "peroraison.h"

void Deroule(XButtonEvent *e, httptable *own)
{
  int i;
  XColor bgcolor;
  int width = (int) (own->width / own->nb_td);
  int height = (int) (own->height / own->nb_tr);
  int mid_height = height>>1;

  int x = e->x_root -e->x + (BORDER<<1);
  int y = e->y_root -e->y + (BORDER<<1);

  XSetWindowAttributes xsaw;

  deroulante[0] = e->window;

  for(i=1; i<7; i++){
    XAllocNamedColor(dpy, DefaultColormap(dpy, DefaultScreen(dpy)),
		     rainbow[i-1], &bgcolor, &bgcolor);

    deroulante[i] = XCreateSimpleWindow(dpy, e->window, x, y,
					width + BORDER,
					mid_height,
					0,
					bgcolor.pixel,
					bgcolor.pixel);

    xsaw.override_redirect = True;

    XChangeWindowAttributes(dpy,deroulante[i], CWOverrideRedirect, &xsaw);
    XSelectInput(dpy,deroulante[i],ButtonPressMask);
    XMapWindow(dpy, deroulante[i]);

    y += mid_height;
  }
}
