#include "peroraison.h"

/* button, checkbox, file, hidden, image, password, radio, submit et text */

void XMLCALL HMuet(void *data, const char *name, const char **atts)
{
}

XML_StartElementHandler inputtype[27]
= {
  &HMuet,       &HMuet,    &HInputButton,  // @ A B
  &HInputCheckbox, &HMuet, &HMuet,         // C D E
  &HInputFile,  &HMuet,    &HInputHidden,  // F G H
  &HInputImage, &HMuet,    &HMuet,         // I J K
  &HMuet,       &HMuet,    &HMuet,         // L M N
  &HMuet,       &HInputPassword, &HMuet,   // O P Q
  &HInputRadio, &HInputSubmit, &HInputText,// R S T
  &HMuet,       &HMuet,    &HMuet,         // U V W
  &HMuet,       &HMuet,    &HMuet          // X Y Z
};

void XMLCALL HInput_and_Button(void *data, const char *type, const char **atts)
{
  httpform *own = (httpform *) data;
  if (own->numero) return;

  inputtype[hash_input_type(type)](data, type, atts);
}


void XMLCALL HInputText(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"text")) return;
  add_input_request_uri((httpform *) data, "value", atts);
}

void XMLCALL HInputCheckbox(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"checkbox")) return;
  add_input_request_uri((httpform *) data, "checked", atts);
}

void XMLCALL HInputButton(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"button")) return;
  add_input_request_uri((httpform *) data, "value", atts);
}

void XMLCALL HInputHidden(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"hidden")) return;
  add_input_request_uri((httpform *) data, "value", atts);
}

void XMLCALL HInputImage(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"image")) return;
  add_input_request_uri((httpform *) data, "value", atts);
}

void XMLCALL HInputPassword(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"password")) return;
  add_input_request_uri((httpform *) data, "value", atts);
}

void XMLCALL HInputSubmit(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"submit")) return;
  add_input_request_uri((httpform *) data, "value", atts);
}

void XMLCALL HInputRadio(void *data, const char *name, const char **atts)
{
  if (strcasecmp(name,"radio")) return;
  add_input_request_uri((httpform *) data, "checked", atts);
}


void XMLCALL HInputFile(void *data, const char *name, const char **atts)
{
  httpform *own = (httpform *) data;

  if (strcasecmp(name,"file")) return;
  if (!add_input_request_uri(own, "value", atts)) return;
  own->params->isfile = 1;
  own->method = "POST";
  own->enctype = CT_MFD;
}

