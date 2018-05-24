PISTE ajoutePiste(PISTE piste, char nom[50], difficulte_t diff, int duree);

PISTE liberePiste(PISTE piste);

REMONTEE ajouteRemontee(REMONTEE remontee, char nom[50], typeRemontee_t type, int tempsAttente, int duree);

REMONTEE libereRemontee(REMONTEE remontee);

GRAPHE libereGraphe(GRAPHE g);