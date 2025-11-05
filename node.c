#include <stdlib.h>
#include "node.h"
#define TAB_MAX 100

void create_feuille(int racine, int *tab){
    node* feuille = (node*)malloc(sizeof(node));
    if (feuille == NULL) {
        return;
    }
    feuille->racine = racine;
    feuille->gauche = NULL;
    feuille->droite = NULL;
    feuille->tab = tab;
    return feuille;
}
void create_node(int racine, node *gauche, node *droite, int* tab){
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return;
    }
    new_node->racine = racine;
    new_node->gauche = gauche;
    new_node->droite = droite;
    new_node->tab = tab;
    return new_node;
}

void ajt_element_fin(int **tab, int element) {
    int *temp = *tab;

    while (*temp != NULL) {
        temp++;
    }
    *temp = element;
    *(temp + 1) = NULL; 
}