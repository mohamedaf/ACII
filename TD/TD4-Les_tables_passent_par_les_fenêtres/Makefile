#       Universite Pierre & Marie Curie 
#       Master d'informatique
#       Architecture des Clients Internet Interactifs
#       Travaux Diriges 4:  Les tables passent par les fenetres


XPDIR=/users/Etu1/3262731/STL/S2/ACII/expat-2.1.0

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
# bug endian
#XP_BO = -DXML_BYTE_ORDER=21

XP_DEFINES = $(XP_NS) $(XP_DTD) $(XP_BO)


################
# To get debugging, set this to -g
OPT = -O

CFLAGS = -Wall $(OPT) $(XP_INC) $(XP_DEFINES) 

I=/usr/X11R6/include
L=/usr/X11R6/lib
l=X11

CC = cc $(CFLAGS) -I$I

BUT=tablehtml
P=peroraison
T=test.html

ALLC=$(BUT).c $P.h q1.c q2.c q3.c q4.c q5.c
ALLO=$(XP_OBJ) q1.o q2.o q3.o q4.o q5.o


$(BUT):	$(BUT).c $(ALLO)  $P.h
	$(CC) -L$L -l$l $< $(ALLO) -o $@

%.o:     %.c 
	$(CC) -c $< -o $@ 

test: $(BUT) $T
	./$(BUT) < $T

raz:
	@rm -f *.o $(BUTS)

$(BUT).idx:	$(ALLC) $(P).h
	@awk -F'/\\*' '{print $$1}' $(ALLC) $(P).h | \
	tr "{}[]().,;:?<>#\t' =\!+%|\*&^-" "\012"| grep "^[A-Z].*[a-z]" | \
	grep -v $(BUT) | sort  -u | sed 's/True//g;/./s/^/\\par /g' > $(BUT).idx
	@wc  $(BUT).idx
