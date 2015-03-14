#include "peroraison.h"

Window deroulante[7] = {0,0,0,0,0,0,0};
char *rainbow[6] ={"red", "violet", "blue", "green", "yellow", "orange"};

void fButtonPress(XButtonEvent *e, httptable *own)
{
 if (!deroulante[0])
   Deroule(e,own);
 else
   Enroule(e,own);
}
