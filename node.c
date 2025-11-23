#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#define TAB_MAX 100

node* create_feuille(int racine, Tableau *tab){
    node* feuille = (node*)malloc(sizeof(node));
    if (feuille == NULL) {
        return NULL;
    }
    feuille->racine = racine;
    feuille->gauche = NULL;
    feuille->droite = NULL;
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
    printf("Feuille racine: %d\n", arbre->racine);
}

void afficher_node(node *arbre) { 
    if (arbre == NULL) {
        return;
    }

    // Afficher le noeud courant
    printf("Node racine: %d\n", arbre->racine);

    // Appel recursif sur le fils gauche
    if (arbre->gauche != NULL) {
        printf(" -> Descente gauche depuis %d\n", arbre->racine);
        afficher_node(arbre->gauche);
    } else {
        printf("Gauche: NULL\n");
    }

    // Appel recursif sur le fils droit
    if (arbre->droite != NULL) {
        printf(" -> Descente droite depuis %d\n", arbre->racine);
        afficher_node(arbre->droite);
    } else {
        printf("Droite: NULL\n");
    }

    // si on est dans une feuille on affiche son tableau
    if(arbre->droite==NULL && arbre->gauche==NULL){
        printf("Tableau de %d : ",arbre->racine);
        afficher_tableau(arbre->tab);
    }
}


void afficher_tableau(Tableau *t) {
    if(t->taille==0){
        printf("Tableau vide");
    }
    else{
        for (int i = 0; i < t->taille; i++) {
            if(i==0){
                printf("[ %d, ", t->data[i]);
            }
            else if(i+1>=t->taille){
                printf("%d ]", t->data[i]);
            }
            else{
                printf("%d, ", t->data[i]);
            }
        }
        printf("\n");
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

void test(){
    Tableau tab1;
    init_tableau(&tab1);
    ajouter_fin(&tab1, 10);
    ajouter_fin(&tab1, 20);
    ajouter_fin(&tab1, 30);
    
    node *feuille1 = create_feuille(5, &tab1);
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

    node *feuille1 = create_feuille(5, &t1);
    node *feuille2 = create_feuille(8, &t2);


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

    Tableau* tabs[2] = { &t1, &t2 };

    // AFFICHAGE DES MONOTONIES D'ENTREE
    afficher_monotonies(tabs, 2);

    Tableau fusion;
    init_tableau(&fusion);
    //appele de la fonction qui trie avec un arbre

    printf("Monotonie fusionnee : ");
    afficher_tableau(&fusion);
}
