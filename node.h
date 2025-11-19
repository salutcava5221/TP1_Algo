#define TAB_MAX 100

typedef struct Tableau{
    int data[TAB_MAX];   // stockage
    int taille;          // nb d’éléments utilisés
} Tableau;

typedef struct node{
    int racine;
    struct node* gauche;
    struct node* droite;
    Tableau *tab;
}node;



node* create_feuille(int racine, Tableau *tab);

void afficher_feuille(node *arbre);

node* create_node(int racine, node *gauche, node *droite);

void ajt_element_fin(int **tab, int element);

void enveler_racine_node(node *arbre, Tableau **tab);

void afficher_node(node *arbre);

void afficher_tableau(Tableau *t);

void init_tableau(Tableau *t);

void ajouter_fin(Tableau *t, int valeur);



