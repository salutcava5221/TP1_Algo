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


