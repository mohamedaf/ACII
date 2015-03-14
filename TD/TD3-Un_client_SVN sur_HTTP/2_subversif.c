#include "peroraison.h"

void update_entries(svn *svnentries)
{
  if(!svnentries)
    return;

  File *f;
  entries *tmp = svnentries->next;

  f = fopen("entries-new.xml", "w+");

  fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n", f);
  fputs("<wc-entries\n  xmlns=\"svn:\">\n", f);

  fputs("<entry\n", f);

  if(svnentries->committed_rev)
    fprintf(f, "  committed-rev=\"%s\"\n", svnentries->committed_rev);

  fputs("  name=\"\"", f);

  if(svnentries->committed_date)
    fprintf(f, "  committed-date=\"%s\"\n", svnentries->committed_date);

  fprintf(f, "  url=\"http://%s/%s/\"\n", svnentries->server, svnentries->serverpath);

  if(svnentries->last-author)
    fprintf(f, "  last-author=\"%s\"\n", svnentries->last_author);

  fprintf(f, "  kind=\"dir\"\n");

  if(svnentries->revision)
    fprintf(f, "  revision=\"%s\" />\n", svnentries->revision);

  while(tmp){
    fprintf(fout, "\t<entry name='%s' kind='%s' ", p->name, p->kind);

    if (tmp->committed_rev)
      fprintf(fout, "committed-rev='%s' ", tmp->committed_rev);
    if (tmp->committed_date)
      fprintf(fout, "committed-date='%s' ", tmp->committed_date);
    if (tmp->last_author)
      fprintf(fout, "last-author='%s' ", tmp->last_author);
    if (tmp->schedule)
      fprintf(fout, "schedule='%s' ", tmp->schedule);
    if (tmp->revision)
      fprintf(fout, "revision='%s' ", tmp->revision);
    
    fputs("/>\n", f);

    tmp = tmp->next;
  }

  fputs("</wc-entries>" ,f);
  fclose(f);
}

char *SvnAdd(int argc, char *argv[], svn *own)
{
  int i;
  entries *en = own->contenu;

  for (i=2; i<argc; i++) {
    /* Eviter d'ajouter un fichier qui l'est deja */
    while(en){
      if (!strcmp(en->name, argv[i]))
	break;
      en = en->next;
    }
         
    if (!en) {
      en = (entries *) malloc (sizeof(entries));
      
      en->name = argv[i];
      en->revision = "0"; 
      en->committed_rev = NULL;
      en->committed_date = NULL;
      en->last_author = NULL;
      
      /* On suppose que c'est bien un fichier */
      en->kind ="file";
      en-> schedule = "add";
      en->next= own->contenu;
      own->contenu = p;
    } 
  }

  update_entries(own);
  return NULL;
}


char *SvnDelete(int argc, char *argv[], svn *own)
{
  int i;
  entries *en;

  if(!own)
    return NULL;

  en = own->contenu;
  
  for (i=2; i<argc; i++){
    while(en){
      if(!strcasecmp(argv, en->name)){
	en->schedule = strdup("delete");
	break;
      }
      en = en->next;
    }
  }

  update_entries(own);
  
  return NULL;
}
