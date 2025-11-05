#include <stdlib.h>
#include <stdio.h>
#include "node.h"

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

void afficher_feuille(node *arbre){
    if (arbre == NULL) {
        return;
    }
    printf("Feuille racine: %d\n", arbre->racine);
}
void afficher_node(node *arbre){
    if (arbre == NULL) {
        return;
    }
    printf("Node racine: %d\n", arbre->racine);
    if (arbre->gauche != NULL) {
        printf("Gauche racine: %d\n", arbre->gauche->racine);
    } else {
        printf("Gauche: NUL\n");
    }
    if (arbre->droite != NULL) {
        printf("Droite racine: %d\n", arbre->droite->racine);
    } else {
        printf("Droite: NULL\n");
    }
}
