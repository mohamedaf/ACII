#include "peroraison.h"

char reponse_http[BUFSIZ];

int index_attribute(const char *name, const char **atts)
{
  int j;
  for (j = 0; atts[j]; j+=2) if (!strcasecmp(atts[j], name)) return j+1;
  return 0;
}


char * copy_attribute(const char *name, const char **atts)
{
  int j = index_attribute(name, atts);
  return !j ? NULL : strdup(atts[j]);
}

char *SvnMuet(int argc, char *argv[], svn *own)
{
  return NULL;
}

char *(*actions[27])(int argc, char *argv[], svn *own) = {
  &SvnAdd,   &SvnMuet,   &SvnMuet, // @ A B
  &SvnCommit,   &SvnDelete,   &SvnMuet, // C D E
  &SvnMuet,   &SvnMuet,   &SvnMuet, // F G H
  &SvnMuet,   &SvnMuet,   &SvnMuet, // I J K
  &SvnMuet,   &SvnMuet,   &SvnMuet, // L M N
  &SvnMuet,   &SvnMuet,   &SvnMuet, // O P Q
  &SvnMuet,   &SvnMuet,   &SvnMuet, // R S T
  &SvnUpdate, &SvnMuet,   &SvnMuet, // U V W
  &SvnMuet,   &SvnMuet,   &SvnMuet  // X Y Z
};

void phraser_xml(XML_Parser phraseur, int desc)
{
  char buf[BUFSIZ];
  int len;
  do {
    len = read(desc, buf, BUFSIZ);
    if (XML_Parse(phraseur, buf, len, (len <= 0)) == XML_STATUS_ERROR) {
      fprintf(stderr,
              "%s at line %d\n",
              XML_ErrorString(XML_GetErrorCode(phraseur)),
              ((int) XML_GetCurrentLineNumber(phraseur)));
      exit(1);
    }
  } while (len);
}

int main(int argc, char *argv[])
{
  XML_Parser phraseur = XML_ParserCreate("ISO-8859-1");
  svn own;
  own.contenu = NULL;
  own.server = NULL;
  own.serverpath = NULL;

  XML_SetUserData(phraseur, &own);
  XML_SetElementHandler(phraseur, startElement, endElement);
  phraser_xml(phraseur, open("entries.xml", O_RDONLY, 0));
  XML_ParserFree(phraseur);

  if (argc >= 2) {
    printf("%s",actions[hash_balise(argv[1])](argc, argv, &own));
  } else {
      exit(-1);
    }
 return 0;
}
