#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#define TAB_MAX 100


void update_tab(Tableau *tab) {
    if (tab == NULL || tab->taille <= 0) {
        return;
    }
    // Decale tous les elements vers la gauche
    for (int i = 1; i < tab->taille; i++) {
        tab->data[i - 1] = tab->data[i];
    }
    tab->taille--;
}


node* create_feuille(Tableau *tab){
    node* feuille = (node*)malloc(sizeof(node));
    if (feuille == NULL) {
        return NULL;
    }
    feuille->racine = tab->data[0];
    feuille->gauche = NULL;
    feuille->droite = NULL;
    update_tab(tab);
    feuille->tab = tab;
    return feuille;
}

node* create_node(int racine, node *gauche, node *droite){
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->racine = racine;
    new_node->gauche = gauche;
    new_node->droite = droite;
    new_node->tab = NULL;
    return new_node;
}

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

void afficher_feuille(node *arbre){
    if (arbre == NULL) {
        return;
    }
    printf("Feuille : %d\n", arbre->racine);
}

void afficher_node(node *arbre) { 
    if (arbre == NULL) {
        return;
    }

    // si on est dans une feuille on affiche son tableau
    if(arbre->droite==NULL && arbre->gauche==NULL){
        afficher_feuille(arbre);
        printf("Tableau de %d : ",arbre->racine);
        afficher_tableau(arbre->tab);
    }
    else{
        // Afficher le noeud courant
        printf("Node racine: %d\n", arbre->racine);

        // Appel recursif sur le fils gauche
        if (arbre->gauche != NULL) {
            printf(" -> Descente gauche depuis %d\n", arbre->racine);
            afficher_node(arbre->gauche);
        }

        // Appel recursif sur le fils droit
        if (arbre->droite != NULL) {
            printf(" -> Descente droite depuis %d\n", arbre->racine);
            afficher_node(arbre->droite);
        }
    }
}


void afficher_tableau(Tableau *t) {
    if(t->taille==0){
        printf("Tableau vide");
    }
    else{
        printf("[ ");
        for (int i = 0; i < t->taille; i++) {
            printf("%d", t->data[i]);
            if (i < t->taille - 1) {
                printf(", ");
            }
        }
        printf(" ]\n");
    }

}

void afficher_monotonies(Tableau **tabs, int n) {
    printf("Monotonies en entree :\n");
    for (int i = 0; i < n; i++) {
        printf("Liste %d : ", i+1);
        afficher_tableau(tabs[i]);
    }
    printf("\n");
}


int nb_liste(Tableau* tabs[]) {
    int count = 0;
    while (tabs[count] != NULL) {
        count++;
    }
    return count;
}


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
    int racine = (gauche->racine < droite->racine) ? gauche->racine : droite->racine;

    // Créer le nœud parent
    return create_node(racine, gauche, droite);
}

// Fonction principale
node* liste_arbre(Tableau* tabs[], Tableau* res) {
    int n = nb_liste(tabs);
    if (n <= 0) return NULL;

    node* arbre = liste_arbre_rec(tabs, 0, n - 1);
    afficher_node(arbre);
    return arbre;
}


void test(){
    Tableau tab1;
    init_tableau(&tab1);
    ajouter_fin(&tab1, 10);
    ajouter_fin(&tab1, 20);
    ajouter_fin(&tab1, 30);
    
    node *feuille1 = create_feuille(&tab1);
    afficher_feuille(feuille1);
    printf("tableau: ");
    afficher_tableau(feuille1->tab);
    printf("\n");
}

void test2(){
    Tableau t1;
    init_tableau(&t1);

    ajouter_fin(&t1, 4);
    ajouter_fin(&t1, 11);

    Tableau t2;
    init_tableau(&t2);
    ajouter_fin(&t2, 2);
    ajouter_fin(&t2, 3);

    node *feuille1 = create_feuille(&t1);
    node *feuille2 = create_feuille(&t2);


    node *n = create_node(10, feuille1, feuille2);
    node *arbre=create_node(10, n, NULL);

    afficher_node(arbre);
}

void test_Q1(){
    // LISTES D'ENTREE
    Tableau t1;
    init_tableau(&t1);
    ajouter_fin(&t1, 4);
    ajouter_fin(&t1, 11);

    Tableau t2;
    init_tableau(&t2);
    ajouter_fin(&t2, 2);
    ajouter_fin(&t2, 3);

    Tableau* tabs[3] = { &t1, &t2 ,NULL};

    // AFFICHAGE DES MONOTONIES D'ENTREE
    afficher_monotonies(tabs, 2);

    Tableau fusion;
    init_tableau(&fusion);
    //appele de la fonction qui trie avec un arbre

    //printf("Monotonie fusionnee : ");
    //afficher_tableau(&fusion);
    liste_arbre(tabs,&fusion);
    afficher_tableau(&fusion);
}
