#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mes_types.h"

PISTE ajoutePiste(PISTE piste, char nom[50], difficulte_t diff, int duree)
{
	PISTE tmp=malloc(sizeof(struct piste));
	strcpy(tmp->nom,nom);
	tmp->diff=diff;
	tmp->duree=duree;
	tmp->suiv=piste;
	return tmp;
}

PISTE liberePiste(PISTE piste)
{
	if(piste!=NULL)
	{
		piste->suiv=liberePiste(piste->suiv);
		free(piste);
	}
	return NULL;
}

REMONTEE ajouteRemontee(REMONTEE remontee, char nom[50], typeRemontee_t type, int tempsAttente, int duree)
{
	REMONTEE tmp=malloc(sizeof(struct remontee));
	strcpy(tmp->nom,nom);
	tmp->type=type;
	tmp->tempsAttente=tempsAttente;
	tmp->duree=duree;
	tmp->suiv=remontee;
	return tmp;
}

REMONTEE libereRemontee(REMONTEE remontee)
{
	if(remontee!=NULL)
	{
		remontee->suiv=libereRemontee(remontee->suiv);
		free(remontee);
	}
	return NULL;
}

GRAPHE libereGraphe(GRAPHE g)
{
	free(g.lieu);
	for(int i=0; i<g.taille; i++)
	{
		for(int j=0; j<g.taille; j++)
		{
			g.connection[i][j].pistes=liberePiste(g.connection[i][j].pistes);
			g.connection[i][j].remontees=libereRemontee(g.connection[i][j].remontees);
		}
		free(g.connection[i]);
	}
	free(g.connection);
	return g;
}