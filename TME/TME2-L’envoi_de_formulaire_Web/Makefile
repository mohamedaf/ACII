#       Universite Pierre & Marie Curie 
#       Master d'informatique
#       Architecture des Clients Internet
#       Travaux sur Machine 2:  L'envoi de formulaire Web


XPDIR=/users/Etu1/3262731/STL/S2/ACII/expat-2.1.0

################################################################
#
# Extrait du Makefile de Expat
#
# Expat doesn't actually link itself into a library, so we
# have to refer to the individual objects that make up expat

XP_OBJ = $(XPDIR)/lib/xmltok.o \
         $(XPDIR)/lib/xmlrole.o \
         $(XPDIR)/lib/xmlparse.o

XP_INC =  -I$(XPDIR)/lib

################
# Adds support for checking lexical aspects of namespaces
XP_NS = -DXML_NS

################
# Adds support for processing DTDs
XP_DTD = -DXML_DTD

################
# Byte order macro
#This is for little endian machines

XP_BO = -DXML_BYTE_ORDER=12

# and this one is for big endian machines

#XP_BO = -DXML_BYTE_ORDER=21


################
# Define XML_Char as unsigned short
#XP_UNI = -DXML_UNICODE

################
# Define XML_Char as wchar_t
#XP_UNI_WC = -DXML_UNICODE_WCHAR_T

################
# Uncomment XP_MM if your system has a bcopy function but not memmove
#XP_MM = -D"memmove(d,s,l)=bcopy(s,d,l)"


XP_DEFINES = $(XP_NS) $(XP_DTD) $(XP_BO) $(XP_UNI) $(XP_UNI_WC) $(XP_MM)

################################################################

OPT = -O

CFLAGS = -Wall $(OPT) $(XP_INC) $(XP_DEFINES)

CC = cc $(CFLAGS)

BUT=sendform
INIT=InitConnexion
ANAL=AnalyseEntetes
SAUVE=SauveContenu
SAUVES=SauveContenus
U=split_url
P=peroraison
T=test.html

ALLC=$(BUT).c $U.c $(INIT).c $(ANAL).c $(SAUVE).c $(SAUVES).c $P.h $P.c 2_$(BUT).c 3_$(BUT).c 4_$(BUT).c 5_$(BUT).c 6_$(BUT).c m1_$(BUT).c m2_$(BUT).c m3_$(BUT).c m4_$(BUT).c m5_$(BUT).c

ALLO=$(XP_OBJ) $U.o $(INIT).o $(ANAL).o $(SAUVE).o $(SAUVES).o $P.o 2_$(BUT).o 3_$(BUT).o 4_$(BUT).o 5_$(BUT).o 6_$(BUT).o m1_$(BUT).o m2_$(BUT).o m3_$(BUT).o m4_$(BUT).o m5_$(BUT).o

$(BUT):	$(BUT).c $(ALLO)  $P.h
	$(CC) $< $(ALLO) -o $@

%.o:     %.c 
	$(CC) -c $< -o $@ 

test: $(BUT)
	@sed "s@/~esj@/~${USER}@" $T | ${BUT} 1 80

clean:
	@rm -f *.o $(BUT)
