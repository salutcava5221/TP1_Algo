#include <stdio.h>
#include <stdlib.h>
#include "node.h"



int main(){
    node *t5 = create_feuille(5, NULL);
    node *t6 = create_feuille(8, NULL);

    //afficher_feuille(t5);
    //afficher_feuille(t6);

    Tableau t;
    init_tableau(&t);

    ajouter_fin(&t, 1);
    ajouter_fin(&t, 2);
    ajouter_fin(&t, 3);

    afficher_tableau(&t);

    node *n = create_node(10, t5, t6, NULL);
    //afficher_node(n);
    return 0;
}