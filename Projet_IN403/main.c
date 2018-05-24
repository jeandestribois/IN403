#include <stdio.h>
#include <stdlib.h>

#include "mes_types.h"
#include "lire_fichiers.h"
#include "fonctions_liste.h"
#include "interface.h"
#include "itineraire.h"



int main(int argc, char const *argv[])
{
	if(argc!=4)
	{
		fprintf(stderr,"Pas assez d'argument donné lors de l'execution\nUsage correct : %s <fichier_piste> <fichier_remontée> <fichier_lieu>\n",argv[0]);
		exit(0);
	}
	GRAPHE station=construireGraphe(argv);

	SKIEUR skieur=demandeInfo(station);

	int *IDpere;
	IDpere=malloc(sizeof(int)*station.taille);

	GRAPHE chemin=dijkstra(station,skieur,IDpere);

	int ret=itineraire(chemin,skieur,IDpere);

	if(ret==-1) printf("\nImpossible de trouver un itineraire pour ce trajet\n");
	
	free(IDpere);	
	station=libereGraphe(station);
	for(int i=0; i<chemin.taille; i++) free(chemin.connection[i]);
	free(chemin.connection);


	exit(0);
}