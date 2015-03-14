#include "peroraison.h"

void XMLCALL startElement(void *data, const char *name, const char **atts)
{
  svn *own = (svn*) data;
  entries *en;
  int i, j;
  
  /* pas besoin de verifier la valeur de l'attribut de la balise wc-entries */
  
  if(strcasecmp("entry",name))
    return;
  
  i=index_attribute("name", atts);
  j=index_attribute("kind", atts);
    
  if(!strcmp(atts[j],"dir") && (!*atts[i])){
    /* name est vide remplir donc la structure own */
    char server[64];
    char path[4096];
    
    i=index_attribute("url", atts);

    if(i)
      if(split_url(atts[i], NULL, server, path, NULL, NULL) <= 0){
	own->server = strdup(server);
	own->serverpath = strdup(path);
      }
    
    
    own->committed_rev = copy_attribute("committed_rev", atts);
    own->committed_date = copy_attribute("committed_date", atts);
    own->last_author = copy_attribute("last_author", atts);
    own->revision = copy_attribute("revision", atts);
  }
  else{
    /* name n'est pas vide nous ajoutant donc un element entries a la liste chainee */  
    en = (entries*) malloc(sizeof(entries));
    
    en->name = copy_attribute("name", atts);
    en->revision = copy_attribute("revision", atts);
    en->committed_rev = copy_attribute("committed_rev", atts);
    en->committed_date = copy_attribute("committed_date", atts);
    en->last_author = copy_attribute("last_author", atts);
    en->kind = copy_attribute("kind", atts);
    en->schedule = copy_attribute("schedule", atts);
    en->next = own->contenu;
    own->contenu = en;
  }
}


void XMLCALL endElement(void *data, const char *name)
{
  /* Reste vide pas besoin (rien a faire pour les fermetures des balises) */
}
