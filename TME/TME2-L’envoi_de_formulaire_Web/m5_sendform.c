#include "peroraison.h"

char * tire_reponse(int desc)
{
  char* buff[LINELENGTH];
  int code;
  int n=0;
  char *new;
  File *fdesc = fdopen(desc, "r");
  
  fgets(buf, LINELENGTH, fdesc);

  if(sscanf(buf, "HTTP1/1 %d", &code)){
    return "500";
  }

  if(code == 301 || code == 303){
    while (fgets(buf, LINELENGTH, fdesc)){
      char *ptr;
      int i,n;

      if (strlen(buf) <= 2)
	break;

      write(STDOUT_FILENO, buf, strlen(buf));
      fflush(NULL);
      i = strlen("Location: ");

      if (strncmp(buf, "Location: ", i))
	continue;
      
      ptr = index(buf, '\n');

      if (!ptr)
	break;

      n = ptr-buf-i;
      new = (char *)malloc((n+1)*sizeof(char));
      strncpy(new, buf+i, n);
      *(new+n+1) = 0;

      return new;
    }
    return "500"; // Redirect sans Location au fou
  }
  else if(code != 200){
    return "400";
  }
  else{
    SauveContenus(AnalyseEntetes(fdesc, &n), fdesc);
    return "200";
  }
}
