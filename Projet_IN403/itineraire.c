#include <stdio.h>
#include <stdlib.h>

#include "mes_types.h"

GRAPHE dijkstra(GRAPHE station, SKIEUR skieur, int *IDpere)
{
	GRAPHE chemin;
	int IDactuel;
	int IDsuiv=skieur.depart.ID;
	PISTE topPiste;
	PISTE tmpPiste;
	REMONTEE topRemontee;
	REMONTEE tmpRemontee;

	int *temps=malloc(sizeof(int)*station.taille);
	int *estTraite=malloc(sizeof(int)*station.taille);


	//Initialisation
	chemin.taille=station.taille;
	chemin.lieu=station.lieu;
	chemin.connection=malloc(sizeof(CONNECTION*)*chemin.taille);
	for(int i=0; i<chemin.taille; i++)
	{
		chemin.connection[i]=malloc(sizeof(CONNECTION)*chemin.taille);
		for(int j=0; j<chemin.taille; j++)
		{
			chemin.connection[i][j].pistes=NULL;
			chemin.connection[i][j].remontees=NULL;
		}
		if(i==skieur.depart.ID)
		{
			temps[i]=0;
			IDpere[i]=DEPART;
		}
		else
		{
			temps[i]=INFINI;
			estTraite[i]=FAUX;
			IDpere[i]=INDEFINI;
		}
	}


	while(IDsuiv!=INDEFINI)			// Début de l'algorithme
	{
		IDactuel=IDsuiv;
		estTraite[IDactuel]=VRAI;
		for(int i=0; i<station.taille; i++)		
		{
			if(!estTraite[i])	// Pour tout les sommets non traités
			{
				topPiste=NULL;
				if(station.connection[IDactuel][i].pistes!=NULL)		// On cherche la meilleure piste
				{
					topPiste=station.connection[IDactuel][i].pistes;
					tmpPiste=topPiste->suiv;
					while(tmpPiste!=NULL)
					{
						if(tmpPiste->duree+tmpPiste->duree*tmpPiste->diff*skieur.niveau < topPiste->duree+topPiste->duree*topPiste->diff*skieur.niveau) topPiste=tmpPiste;
						tmpPiste=tmpPiste->suiv;
					}
				}
				topRemontee=NULL;
				if(station.connection[IDactuel][i].remontees!=NULL)		// On cherche la meilleure remontee
				{
					topRemontee=station.connection[IDactuel][i].remontees;
					tmpRemontee=topRemontee->suiv;
					while(tmpRemontee!=NULL)
					{
						if((tmpRemontee->duree+tmpRemontee->tempsAttente) < (topRemontee->duree+topRemontee->tempsAttente)) topRemontee=tmpRemontee;
						tmpRemontee=tmpRemontee->suiv;
					}
				}

				// On compare les temps et on construit le graphe chemin
				if(topPiste!=NULL && topRemontee!=NULL)				// S'il y a une remontée et une piste
				{
					// On compare laquelle est plus rapide
					if((topPiste->duree+topPiste->duree*topPiste->diff*skieur.niveau) < (topRemontee->duree+topRemontee->tempsAttente))
					{
						// Si le temps est mieux en passant par ce sommet
						if((temps[IDactuel]+topPiste->duree+topPiste->duree*topPiste->diff*skieur.niveau < temps[i]) || (temps[i] == INFINI))
						{
							temps[i]=temps[IDactuel]+topPiste->duree+topPiste->duree*topPiste->diff*skieur.niveau;
							IDpere[i]=IDactuel;
							chemin.connection[IDactuel][i].pistes=topPiste;
						}
					}
					else
					{
						if((temps[IDactuel]+topRemontee->duree+topRemontee->tempsAttente < temps[i]) || (temps[i] == INFINI))
						{
							temps[i]=temps[IDactuel]+topRemontee->duree+topRemontee->tempsAttente;
							IDpere[i]=IDactuel;
							chemin.connection[IDactuel][i].remontees=topRemontee;
						}
					}
				}
				else if(topPiste!=NULL)				// S'il y a juste une piste
				{
					if((temps[IDactuel]+topPiste->duree < temps[i]) || (temps[i] == INFINI))
					{
						temps[i]=temps[IDactuel]+topPiste->duree+topPiste->duree*topPiste->diff*skieur.niveau;
						IDpere[i]=IDactuel;
						chemin.connection[IDactuel][i].pistes=topPiste;
					}
				}
				else if(topRemontee!=NULL)			// S'il y a juste une remontée
				{
					if((temps[IDactuel]+topRemontee->duree+topRemontee->tempsAttente < temps[i]) || (temps[i] == INFINI))
					{
						temps[i]=temps[IDactuel]+topRemontee->duree+topRemontee->tempsAttente;
						IDpere[i]=IDactuel;
						chemin.connection[IDactuel][i].remontees=topRemontee;
					}
				}
			}
		}
		IDsuiv=INDEFINI;
		for(int i=0; i<station.taille; i++)
		{
			if(!estTraite[i] && temps[i]!=INFINI)
			{
				if(IDsuiv==INDEFINI) IDsuiv=i;
				else if(temps[i] < temps[IDsuiv]) IDsuiv=i;
			}
		}
	}

	free(estTraite);
	free(temps);

	return chemin;
}

int itineraire(GRAPHE chemin, SKIEUR skieur, int *IDpere)
{
	int IDactuel=skieur.arrivee.ID;
	int tempsTotal=0;
	int nbLieu=1;
	int temps=0;

	while(IDpere[IDactuel]!=DEPART)		// Boucle nous permettant d'obtenir le nombre de lieu à passer
	{
		if(IDpere[IDactuel]==INDEFINI) return -1;		// Si il n'existe pas de chemin
		IDactuel=IDpere[IDactuel];
		nbLieu++;
	}
	LIEU *lieux=malloc(sizeof(LIEU)*nbLieu);
	IDactuel=skieur.arrivee.ID;

	for(int i=nbLieu-1; i>=0; i--)		// Boucle initialisant le tableau lieux[]
	{
		lieux[i]=chemin.lieu[IDactuel];
		IDactuel=IDpere[IDactuel];
	}
	printf("\n\nDépart de : %s\n",chemin.lieu[lieux[0].ID].nom);

	for(int i=0; i<nbLieu-1; i++)		// Boucle affichant tout l'itinéraire à suivre
	{
		if(chemin.connection[lieux[i].ID][lieux[i+1].ID].pistes!=NULL)			// S'il doit prendre une piste
		{
			temps=chemin.connection[lieux[i].ID][lieux[i+1].ID].pistes->duree+chemin.connection[lieux[i].ID][lieux[i+1].ID].pistes->duree*chemin.connection[lieux[i].ID][lieux[i+1].ID].pistes->diff*skieur.niveau;
			tempsTotal+=temps;
			printf("Prenez la piste : %s\t(durée : %d minutes et %d secondes)\n",chemin.connection[lieux[i].ID][lieux[i+1].ID].pistes->nom,temps/60,temps%60);
		}
		else if(chemin.connection[lieux[i].ID][lieux[i+1].ID].remontees!=NULL)	// S'il doit prendre une remontée mécanique
		{
			temps=chemin.connection[lieux[i].ID][lieux[i+1].ID].remontees->duree+chemin.connection[lieux[i].ID][lieux[i+1].ID].remontees->tempsAttente;
			tempsTotal+=temps;
			printf("Prenez ");
			switch(chemin.connection[lieux[i].ID][lieux[i+1].ID].remontees->type)		// Pour lui indiquer quel type de remontée
			{
				case TELESKI: printf("le teleski "); break;
				case TELESIEGE: printf("le telesiege "); break;
				case OEUF: printf("l'oeuf "); break;
				case TELECABINE: printf("la telecabine "); break;
			}
			printf("%s\t\t(durée : %d minutes et %d secondes)\n",chemin.connection[lieux[i].ID][lieux[i+1].ID].remontees->nom,temps/60,temps%60);
		}
	}
	printf("\nVous êtes arrivé à %s en %d minutes et %d secondes\n", chemin.lieu[lieux[nbLieu-1].ID].nom,tempsTotal/60,tempsTotal%60);
	printf("\nAu revoir.\n");

	free(lieux);

	return 0;
}