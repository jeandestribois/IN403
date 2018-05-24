#define INFINI -1
#define FIN -1
#define INDEFINI -1
#define DEPART -2
#define VRAI 1
#define FAUX 0

typedef enum niveau					// Le niveau du skieur
{
	EXPERIMENTE,
	DEBUTANT
} niveau_t;

typedef enum difficulte 			// Difficultée des pistes
{
	VERT,
	BLEU,
	ROUGE,
	NOIR
} difficulte_t;

typedef enum typeRemontee
{
	TELESKI,
	TELESIEGE,
	OEUF,
	TELECABINE
} typeRemontee_t;

struct piste
{
	char nom[50];			// Le nom de la piste
	difficulte_t diff;		// La difficultée
	int duree;				// La durée de descente pour un skieur experimenté (en seconde)
	struct piste *suiv;		// Pour constituer une liste chaînée
};
typedef struct piste* PISTE;

struct remontee
{
	char nom[50];			// Le nom de la remontée
	int tempsAttente;		// Le temps d'attente moyen (en seconde)
	int duree;				// La durée de la remontée (en seconde)
	typeRemontee_t type;
	struct remontee *suiv;		// Pour constituer une liste chaînée
};
typedef struct remontee* REMONTEE;

typedef struct lieu
{
	char nom[50];			// Le nom du lieu
	int ID;					// Le numero correspondant au lieu (pour l'indice du tableau)

} LIEU;

typedef struct connection
{
	PISTE pistes;		// Les pistes connectées au lieu
	REMONTEE remontees;	// Les remontées connectées au lieu
} CONNECTION;

typedef struct graphe			// Représente le graph
{
	int taille;
	LIEU *lieu;
	CONNECTION **connection;	// Tableau à deux dimension pour représenter la matrice
} GRAPHE;

typedef struct skieur
{
	niveau_t niveau;		// Le niveau du skieur
	LIEU depart;			// L'arrivée
	LIEU arrivee;			// Le depart
} SKIEUR;