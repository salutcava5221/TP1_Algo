#include <stdio.h>
#include <stdlib.h>
#include "node.h"



int main(){

    Tableau t1;
    init_tableau(&t1);

    ajouter_fin(&t1, 4);
    ajouter_fin(&t1, 11);

    Tableau t2;
    init_tableau(&t2);
    ajouter_fin(&t2, 2);
    ajouter_fin(&t2, 3);

    node *t5 = create_feuille(5, &t1);
    node *t6 = create_feuille(8, &t2);

    afficher_feuille(t5);
    afficher_feuille(t6);



    node *n = create_node(10, t5, t6);
    //afficher_node(n);
    return 0;
}