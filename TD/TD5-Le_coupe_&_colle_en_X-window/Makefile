#	Universite Pierre & Marie Curie
#	Master d'informatique
#	Architecture des Clients Internet Interactifs
#	Travaux Diriges 5:  Coupe & Colle
#	Emmanuel Saint-James

BUT=oulipo
H=peroraison.h
Q1=d1_$(BUT)
Q2=d2_$(BUT)
Q3=d3_$(BUT)
Q4=d4_$(BUT)
Q5=d5_$(BUT)

ALLC=$(BUT).c $(Q1).c $(Q2).c $(Q3).c $(Q4).c $(Q5).c
ALLO=$(BUT).o $(Q1).o $(Q2).o $(Q3).o $(Q4).o $(Q5).o

O=-Wall -O4

I=/usr/X11R6/include
L=/usr/X11R6/lib
l=X11

$(BUT): $(ALLO)
	gcc -L$L -l$l $(ALLO) -o $(BUT)

%.o:	%.c $(BUT).h
	gcc $O -I$I -c $< -o $@

$(BUT).h: $(H) $(ALLC) Makefile # en theorie ...
	@if [ -f $@ ] ; then mv $@ /tmp; else > /tmp/$@ ;fi
	@ cat $(H) > $@
	@awk -F[=\;{] '/^[a-zA-Z]/ {print "extern " $$1 ";"}' $(ALLC) >> $@
	@if diff $@ /tmp/$@ >/dev/null;then mv /tmp/$@ $@ ;else wc $@ ;fi

raz:
	rm -f $(ALLO) $(BUT) $(BUT).h


P1='-*-new century schoolbook-*-*-*-*-16-*-*-*-*-*-*-*'
P2='-*-lucida-*-*-*-*-17-*-*-*-*-*-*-*'
# essayer d'autres  choses.
P3='-*-*-*-*-*-*-20-*-*-*-*-*-*-*'

R1=Rodrigue Pour Cro�tre Ta Col�re Et Pour H�ter Ma Peine
R2=Chim�ne Pour Conserver Ma Gloire Et Finir Mon Ennui
R3=Rodrigue Pour Effacer Ma Honte Et Pour Te M�riter
R4=Comte   � Vaincre Sans P�ril On Triomphe Sans Gloire
R5=Diegue  Et Mourir Sans Vengeance ou Vivre Dans La Honte
R6=Chim�ne M\' Ordonner du Repos C\' Est Cro�tre Mes Malheurs

test:	$(BUT)
	(./$(BUT) $(P3) $(R1) &) ; (./$(BUT) $(P2) $(R2) &)

