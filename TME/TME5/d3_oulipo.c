#include "oulipo.h"

void fEnterNotify (XCrossingEvent *e)
{
  /* recepteur pour savoir qui est le premier et qui est
     le 2eme et eviter d'entrer dans une boucle infini */
  /* e->mode pour verifier pas de bouton enfonce "grab" */
  if ((!recepteur) || (e->mode==NotifyNormal))
  {
    int i;

    for(i=0; i<nb_LIGNES; i++){
      if(e->window == filles[i] ){
	last_sel = i;
	reecrire (gcinv, filles[last_sel], espacement,
		  ((3*espacement)/4), mots[last_sel]);
	break;
      }
    }
  }
}


void fLeaveNotify (XCrossingEvent *e)
{
  if ((!recepteur) || (e->mode==NotifyNormal))
    reecrire (gc, filles[last_sel], espacement,
	      ((3*espacement)/4), mots[last_sel]);
}
