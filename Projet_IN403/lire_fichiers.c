#include <stdlib.h>
#include <stdio.h>

#include "mes_types.h"
#include "fonctions_liste.h"


GRAPHE construireGraphe(const char **argv)
{
	// Ouverture des fichiers
	FILE *fpiste, *fremontee, *flieu;
	if(!(fpiste=fopen(argv[1],"r")))
	{
		fprintf(stderr,"Erreur lors de l'ouverture de %s\n",argv[1]);
		exit(0);
	}
	if(!(fremontee=fopen(argv[2],"r")))
	{
		fprintf(stderr,"Erreur lors de l'ouverture de %s\n",argv[2]);
		exit(0);
	}
	if(!(flieu=fopen(argv[3],"r")))
	{
		fprintf(stderr,"Erreur lors de l'ouverture de %s\n",argv[3]);
		exit(0);
	}

	// Allocation de mémoire pour les tableaux et mise à NULL les listes
	GRAPHE g;
	fscanf(flieu,"%d",&g.taille);
	g.lieu=malloc(sizeof(LIEU)*g.taille);
	g.connection=malloc(sizeof(CONNECTION*)*g.taille);
	for(int i=0; i<g.taille; i++)
	{
		g.connection[i]=malloc(sizeof(CONNECTION)*g.taille);
		for(int j=0; j<g.taille; j++)
		{
			g.connection[i][j].pistes=NULL;
			g.connection[i][j].remontees=NULL;
		}
	}


	// Lecture dans le fichier lieu
	for(int i=0; i<g.taille; i++)
	{
		fscanf(flieu,"%d %s",&g.lieu[i].ID,g.lieu[i].nom);
	}

	// Ces variables vont permettre de lire dans les fichier piste et remontee
	int nb;
	int depart, fin, duree, tempsAttente, diffOuType;
	char nom[50];

	// Lecture dans le fichier piste
	fscanf(fpiste,"%d",&nb);
	for(int i=0; i<nb; i++)
	{
		fscanf(fpiste,"%d %d %s %d %d",&depart,&fin,nom,&duree,&diffOuType);
		g.connection[depart][fin].pistes=ajoutePiste(g.connection[depart][fin].pistes,nom,diffOuType,duree);
	}

	// Lecture dans le fichier remontee
	fscanf(fremontee,"%d",&nb);
	for(int i=0; i<nb; i++)
	{
		fscanf(fremontee,"%d %d %s %d %d %d",&depart,&fin,nom,&tempsAttente,&duree,&diffOuType);
		g.connection[depart][fin].remontees=ajouteRemontee(g.connection[depart][fin].remontees,nom,diffOuType,tempsAttente,duree);
	}

	// Fermeture des fichiers
	fclose(fpiste);
	fclose(fremontee);
	fclose(flieu);
	return g;	
}