#include "peroraison.h"

void create_td_window(httptable *own, Window fen)
{
  liste_de_ligne *tmpl;
  liste_de_case *tmpc;
  int i, j;
  int width = (int) (own->width / own->nb_td);
  int height = (int) (own->height / own->nb_tr);
  unsigned long mask;

  tmpl = own->premier;
  i = MARGIN;

  while(tmpl){
    tmpc = tmpl->premier;
    j = MARGIN;

    while(tmpc){
      tmpc->fenetre = XCreateSimpleWindow(dpy, fen, j, i,
					  (width * tmpc->colspan) - BORDER,
					  (height * tmpc->rowspan) - BORDER,
					  BORDER,
					  WhitePixel(dpy,DefaultScreen(dpy)),
					  tmpc->bgcolor.pixel);
      mask=0;

      if(tmpc->onmouseover)
	mask |= EnterWindowMask;
      if(tmpc->onmouseout)
	mask |= LeaveWindowMask;
      if(mask)
	XSelectInput(dpy, tmpc->fenetre, mask|ButtonPressMask);

      j += width*tmpc->colspan;
      tmpc = tmpc->next;
    }
    i += (int) (own->height/own->nb_tr);
    tmpl = tmpl->next;
  }
}
