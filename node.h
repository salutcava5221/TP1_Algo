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


void update_tab(Tableau *tab);
node* create_feuille(Tableau *tab);

void afficher_feuille(node *arbre);

node* create_node(int racine, node *gauche, node *droite);

void ajt_element_fin(int **tab, int element);

void enveler_racine_node(node *arbre, Tableau **tab);

void afficher_node(node *arbre);

void afficher_tableau(Tableau *t);
void afficher_monotonies(Tableau **tabs, int n);

void init_tableau(Tableau *t);

void ajouter_fin(Tableau *t, int valeur);
void test();
void test2();
void test_Q1();

int nb_liste(Tableau* tabs[]);
node* fusion_liste(Tableau* tabs[],Tableau* res);



