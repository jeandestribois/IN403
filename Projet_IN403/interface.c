#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mes_types.h"

SKIEUR demandeInfo(GRAPHE g)
{
	int choix;
	SKIEUR skieur;
	printf("\nBonjour, quel niveau avez vous ?\n\nTapez 0 pour experimenté\nTapez 1 pour debutant\n");
	scanf("%d",&choix);
	while(choix!=0 && choix!=1)
	{
		printf("\nLe niveau demandé n'est pas reconnu\n\nRappel :\tTapez 0 pour Débutant\n\t\tTapez 1 pour experimenté\n");
		scanf("%d",&choix);
	}
	printf("Vous avez choisi %d\n",choix);
	skieur.niveau=choix;
	printf("\n\nD'où partez vous ?\n");
	printf("Tapez :\n");
	for(int i=0; i<g.taille; i++)
	{
		printf("%d pour %s\n",g.lieu[i].ID,g.lieu[i].nom);
	}
	scanf("%d",&choix);
	while(choix<0 || choix>g.taille)
	{
		printf("\nLe lieu renseigné n'est pas reconnu\nRappel :\nTapez :\n");
		for(int i=0; i<g.taille; i++)
		{
			printf("%d pour %s\n",g.lieu[i].ID,g.lieu[i].nom);
		}
		scanf("%d",&choix);
	}
	printf("Vous avez choisi %s\n",g.lieu[choix].nom);
	skieur.depart.ID=choix;
	strcpy(skieur.depart.nom,g.lieu[choix].nom);
	printf("\nOù souhaitez vous arriver ?\n");
	printf("Tapez :\n");
	for(int i=0; i<g.taille; i++)
	{
		printf("%d pour %s\n",g.lieu[i].ID,g.lieu[i].nom);
	}
	scanf("%d",&choix);
	while(choix<0 || choix>g.taille)
	{
		printf("\nLe lieu renseigné n'est pas reconnu\nRappel :\nTapez :\n");
		for(int i=0; i<g.taille; i++)
		{
			printf("%d pour %s\n",g.lieu[i].ID,g.lieu[i].nom);
		}
		scanf("%d",&choix);
	}
	printf("Vous avez choisi %s\n",g.lieu[choix].nom);
	skieur.arrivee.ID=choix;
	strcpy(skieur.arrivee.nom,g.lieu[choix].nom);

	if(skieur.depart.ID==skieur.arrivee.ID) printf("\nVous vous trouvez déjà là où vous souhaitez aller !\n\n");
	
	return skieur;
}