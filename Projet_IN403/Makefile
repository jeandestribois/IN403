test: clean build run

#Execution

run:
	./station piste.ski remontee.ski lieu.ski

#Edition de lien

build: main.o lire_fichiers.o fonctions_liste.o interface.o itineraire.o
	gcc -Wall main.o lire_fichiers.o fonctions_liste.o interface.o itineraire.o -o station

#Compilation

main.o: main.c lire_fichiers.h fonctions_liste.h interface.h itineraire.h mes_types.h
	gcc -c -Wall main.c

lire_fichiers.o: lire_fichiers.c fonctions_liste.h
	gcc -c -Wall lire_fichiers.c

fonctions_liste.o: fonctions_liste.c
	gcc -c -Wall fonctions_liste.c

interface.o: interface.c
	gcc -c -Wall interface.c

itineraire.o: itineraire.c
	gcc -c -Wall itineraire.c

#Clean

clean:
	rm -f *.o station

#Edition

edit:
	subl Makefile *.c *.h &