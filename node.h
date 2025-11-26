#ifndef NODE_H
#define NODE_H

#define TAB_MAX 100

typedef struct {
    int data[TAB_MAX];
    int taille;
} Tableau;

typedef struct node {
    int racine;
    struct node *gauche;
    struct node *droite;
    Tableau *tab; // seulement pour les feuilles
} node;

/* Tableau utils */
void init_tableau(Tableau *t);
void ajouter_fin(Tableau *t, int valeur);
void retire_tab(Tableau *tab);
void afficher_tableau(Tableau *t);

/* Tree construction */
node* create_feuille(Tableau *tab);
node* create_node(int racine, node *gauche, node *droite);
node* liste_arbre(Tableau *tabs[]);

/* Fusion */
void fusion_liste(Tableau *tabs[], Tableau *res);

/* Tools */
int nb_liste(Tableau *tabs[]);
int reste_elements(Tableau *tabs[], int n_initial);
void compact_tabs(Tableau *tabs[]);
void free_arbre(node *r);

/* Debug */
void afficher_node(node *arbre);
void afficher_monotonies(Tableau *tabs[]);
void test_Q1();
void demo_algo_fonctionnel();
#endif
