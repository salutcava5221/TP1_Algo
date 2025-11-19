#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#define TAB_MAX 100

node* create_feuille(int racine, int *tab){
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

node* create_node(int racine, node *gauche, node *droite, int* tab){
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->racine = racine;
    new_node->gauche = gauche;
    new_node->droite = droite;
    new_node->tab = tab;
    return new_node;
}

void ajt_element_fin(int **tab, int element) {
    int **temp = tab;
    while (temp != NULL) {
        temp++;
    }
    **temp = element;
    *(temp + 1) = NULL;
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
}


