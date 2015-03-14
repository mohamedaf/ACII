#	Universite Pierre & Marie Curie
#	Master d'informatique
#	Architecture des Clients Internet Interactifs
#	Travaux sur Machine 5:  Glisse & Pose
#	Emmanuel Saint-James

BUT=oulipo
H=peroraison.h
S1=d1_$(BUT)
S2=d2_$(BUT)
S3=d3_$(BUT)
S4=d4_$(BUT)
Q1=m1_$(BUT)
Q2=m2_$(BUT)
Q3=m3_$(BUT)
Q4=m4_$(BUT)

ALLC=$(BUT).c $(Q1).c $(Q2).c $(Q3).c $(Q4).c $(S1).c $(S2).c $(S3).c $(S4).c
ALLO=$(BUT).o $(Q1).o $(Q2).o $(Q3).o $(Q4).o $(S1).o $(S2).o $(S3).o $(S4).o

O=-Wall -O3

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

R1=Rodrigue Pour Croître Ta Colère Et Pour Hâter Ma Peine
R2=Chimène Pour Conserver Ma Gloire Et Finir Mon Ennui
R3=Rodrigue Pour Effacer Ma Honte Et Pour Te Meriter
R4=Comte   À Vaincre Sans Péril On Triomphe Sans Gloire
R5=Diegue  Et Mourir Sans Vengeance ou Vivre Dans La Honte
R6=Chimène M\' Ordonner du Repos C\' Est Croître Mes Malheurs

test:	$(BUT)
	(./$(BUT) $(P3) $(R3) &) ; (./$(BUT) $(P2) $(R5) &)

