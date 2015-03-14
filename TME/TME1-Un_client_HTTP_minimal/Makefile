#	Universite Pierre & Marie Curie 
#	Master d'informatique
#	Architecture des Clients Internet Interactifs
#	Travaux sur machine 1:  un client HTTP minimal

C=client
P=peroraison
I=InitConnexion
A=AnalyseEntetes
S=SauveContenu

ALLC= $P.h $C.c $P.c $I.c $A.c $S.c 
ALLO=$C.o $P.o $I.o $A.o $S.o

W=all
O=3
COMP=gcc -W$W -O$O 
#COMP=gcc -g

$C:	$(ALLO) $P.h
	$(COMP) $(ALLO) -o $@

%.o:	%.c $P.h
	$(COMP) -c $< -o $@ 

test: $C
	./client 127.0.0.1 80
raz:
	rm $(ALLO) $C *~
clean:
	rm $(ALLO) $C *~

