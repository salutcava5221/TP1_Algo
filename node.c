#include <stdlib.h>
#include <stdio.h>
#include "node.h"

/* ------------------------- TABLEAU UTILS ------------------------- */

void init_tableau(Tableau *t) {
    t->taille = 0;
}

void ajouter_fin(Tableau *t, int valeur) {
    if (t->taille >= TAB_MAX) {
        printf("Erreur : tableau plein\n");
        return;
    }
    t->data[t->taille] = valeur;
    t->taille++;
}

void retire_tab(Tableau *tab) {
    if (tab==NULL || tab->taille == 0){
        return;
    } 
    for (int i = 1; i < tab->taille; i++){
        tab->data[i-1] = tab->data[i];
    }
    tab->taille--;
}

void afficher_tableau(Tableau *t) {
    if (t==NULL || t->taille == 0) {
        printf("Tableau vide\n");
        return;
    }
    printf("[ ");
    for (int i = 0; i < t->taille; i++) {
        printf("%d", t->data[i]);
        if (i < t->taille-1) printf(", ");
    }
    printf(" ]\n");
}

/* ------------------------- NODE CREATION ------------------------- */

node* create_feuille(Tableau *tab) {
    if (tab==NULL || tab->taille == 0) {
        return NULL;
    }

    node *f = malloc(sizeof(node));
    f->racine = tab->data[0];
    f->gauche = NULL;
    f->droite = NULL;
    f->tab = tab;
    return f;
}

node* create_node(int racine, node *gauche, node *droite) {
    node *n = malloc(sizeof(node));
    n->racine = racine;
    n->gauche = gauche;
    n->droite = droite;
    n->tab = NULL;
    return n;
}

/* ------------------------- TAB LISTS UTILS ------------------------- */

int nb_liste(Tableau *tabs[]) {
    int count = 0;
    while (tabs[count] != NULL) {
        count++;
    }
    return count;
}

// Décale tous les éléments vers la gauche à partir de la position "pos"
void decaler_gauche(Tableau *tabs[], int pos) {
    int n = nb_liste(tabs);
    for (int i = pos; i < n - 1; i++) {
        tabs[i] = tabs[i + 1];
    }
    tabs[n - 1] = NULL; // la dernière case devient vide
}

// Supprime les listes null dans le tableau de listes
void compact_tabs(Tableau *tabs[]) {
    for (int i = 0; i < nb_liste(tabs); i++) {
        if (tabs[i] == NULL) {
            decaler_gauche(tabs, i);
            i--; //car le tableau a perdu une liste
        }
    }
}

//permet de savoir si au moins une des listes du tableau de listes contient au moins une valeur
int reste_elements(Tableau *tabs[]) {
    int res=0;
    for (int i = 0; tabs[i] != NULL; i++) {
        if (tabs[i]->taille > 0){
            res= 1;
        }   
    }
    return res;
}

/* ------------------------- ARBRE RECURSIF ------------------------- */

node* liste_arbre_rec(Tableau* tabs[], int debut, int fin) {
    // Cas de base : aucune liste
    if (debut > fin) return NULL;

    // Cas de base : une seule liste
    if (debut == fin) {
        return create_feuille(tabs[debut]);
    }

    // Diviser en deux moitiés
    int milieu = (debut + fin) / 2;

    // Construire récursivement les deux sous-arbres
    node* gauche = liste_arbre_rec(tabs, debut, milieu);
    node* droite = liste_arbre_rec(tabs, milieu + 1, fin);

    // Déterminer la racine (minimum des deux)
    int racine;
    if(gauche->racine < droite->racine){
        racine=gauche->racine;
    }
    else{
        racine=droite->racine;
    }

    // Créer le nœud parent
    return create_node(racine, gauche, droite);
}

node* liste_arbre(Tableau *tabs[]) {
    int n = nb_liste(tabs);
    if (n == 0) {
        return NULL;
    }
    return liste_arbre_rec(tabs, 0, n-1);
}

void free_arbre(node *arbre) {
    if (arbre==NULL){
        return;
    } 
    free_arbre(arbre->gauche);
    free_arbre(arbre->droite);
    free(arbre);
}

void afficher_node(node *arbre) {
    if (arbre==NULL) {
        return;
    }

    if (arbre->gauche==NULL && arbre->droite==NULL) {
        printf("Feuille : %d\n", arbre->racine);
        printf("Tableau de %d : ", arbre->racine);
        afficher_tableau(arbre->tab);
        return;
    }

    printf("Node racine: %d\n", arbre->racine);

    if (arbre->gauche) {
        printf(" -> Descente gauche depuis %d\n", arbre->racine);
        afficher_node(arbre->gauche);
    }
    if (arbre->droite) {
        printf(" -> Descente droite depuis %d\n", arbre->racine);
        afficher_node(arbre->droite);
    }
}

void afficher_monotonies(Tableau *tabs[]) {
    int n = nb_liste(tabs);
    printf("Monotonies en entrée :\n");
    for (int i = 0; i < n; i++) {
        printf("Liste %d : ", i+1);
        afficher_tableau(tabs[i]);
    }
    printf("\n");
}

/* ------------------------- FUSION ------------------------- */

//note:fix si ya deux liste avec meme element debut
void fusion_liste(Tableau *listes[], Tableau *resultat) {
    while (reste_elements(listes)) {
        node *arbre = liste_arbre(listes);

        // Prendre la valeur minimale de la racine de l'arbre
        int valeur_min = arbre->racine;
        ajouter_fin(resultat, valeur_min);

        // Retirer cette valeur minimale de la liste correspondante
        for (int i = 0; listes[i] != NULL; i++) {
            if (listes[i]->taille > 0 && listes[i]->data[0] == valeur_min) {
                retire_tab(listes[i]);
                if (listes[i]->taille == 0) {
                    listes[i] = NULL;  // liste vide, supprimer
                }
            }
        }

        // Déplacer toutes les listes non-nulles à gauche
        compact_tabs(listes);

        // Libérer l'arbre
        free_arbre(arbre);
    }
}

void test_Q1() {
    Tableau t1, t2, res;
    init_tableau(&t1);
    init_tableau(&t2);

    ajouter_fin(&t1, 4);
    ajouter_fin(&t1, 11);

    ajouter_fin(&t2, 2);
    ajouter_fin(&t2, 3);

    Tableau *tabs[3] = { &t1, &t2, NULL };

    init_tableau(&res);// notre resultat

    fusion_liste(tabs, &res);

    printf("Apres fusion : ");
    afficher_tableau(&res);
}