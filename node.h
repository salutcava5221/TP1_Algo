typedef struct node{
    int racine;
    struct node* gauche;
    struct node* droite;
    int *tab;
}node;

node* create_feuille(int racine, int *tab);

void afficher_feuille(node *arbre);

node* create_node(int racine, node *gauche, node *droite, int* tab);

void ajt_element_fin(int **tab, int element);

void enveler_racine_node(node *arbre, int **tab);

void afficher_node(node *arbre);

void final(node *arbre,int **tab);





