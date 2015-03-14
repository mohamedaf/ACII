#	Universite Pierre & Marie Curie 
#	Master d'informatique
#	Architecture des Clients Internet Interactifs
#	Travaux Diriges 1:  un serveur HTTP minimal

S=serveur
A=peroraison

C=initclient
E=ecoute
U=split_url
H=head
G=get
P=post

CFAIT=$S.c $A.h $A.c
CAFAIRE=$U.c $C.c $H.c $G.c $P.c $E.c
ALLC=$(CFAIT) $(CAFAIRE)
ALLO=$U.o $C.o $H.o $G.o $P.o $E.o $A.o $S.o

W=all
O=3
COMP=gcc -W$W -O$O 

tout: $(ALLO) $S

$S:	$(ALLO)
	$(COMP) $(ALLO) -o $@

%.o:	%.c $A.h
	$(COMP) -c $< -o $@ 

test:	tout
	./serveur 12000

clean:
	rm -f $(ALLO) $S *~
raz:
	rm -f $(ALLO) $S *~

kill:
	kill -9 `ps ax | grep 'serveur [1-9]'|awk '{print $$1}'`
