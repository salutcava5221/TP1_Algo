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

/* ------------------------- TAB Liste Utilitaire ------------------------- */

int nb_liste(Tableau *tabs[]) {
    int count = 0;
    while (tabs[count] != NULL) {
        count++;
    }
    return count;
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

    // Déterminer la racine (minimum des deux), en vérifiant NULL
    int racine;
    if (gauche != NULL && droite != NULL) { 
        if (gauche->racine <= droite->racine) racine = gauche->racine; 
        else racine = droite->racine; 
    }

    else if (gauche != NULL) {
        racine = gauche->racine;
    }
    else if (droite != NULL) {
        racine = droite->racine;
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
    printf("Monotonies en entree :\n");
    for (int i = 0; i < n; i++) {
        printf("Liste %d : ", i+1);
        afficher_tableau(tabs[i]);
    }
    printf("\n");
}

//permet de savoir si au moins une des listes du tableau de listes contient au moins une valeur
int reste_elements(Tableau *tabs[], int n_initial) {
    for (int i = 0; i < n_initial; i++) {
        if (tabs[i] != NULL && tabs[i]->taille > 0) {
            return 1;
        }
    }
    return 0;
}

/* ------------------------- FUSION ------------------------- */

void fusion_liste(Tableau *listes[], Tableau *resultat) {
    //le nombre initial de listes
    int n_initial = nb_liste(listes);
    
    while (reste_elements(listes, n_initial)) {

        //Recupere les listes non vides pour l'arbre
        Tableau *non_vides[TAB_MAX];
        int count = 0;
        //recupere uniquement les listes non vide
        for (int i = 0; i < n_initial; i++) {
            //si la liste courant nes pas null et vide alors on l'ajoute a notre tableau non vide
            if (listes[i] != NULL && listes[i]->taille > 0) {
                non_vides[count] = listes[i];
                count++;
            }
        }
        non_vides[count] = NULL;
        
        // Si aucune liste non vide, sortir
        if (count == 0) break;
        
        // Construire l'arbre avec les listes non vides
        node *arbre = liste_arbre(non_vides);
        int valeur_min = arbre->racine;
        ajouter_fin(resultat, valeur_min);

        // Supprimer l'élément d'une seule liste
        int supprimer = 0;
        for (int i = 0; i < n_initial && !supprimer; i++) {
            if (listes[i] != NULL && 
                listes[i]->taille > 0 && 
                listes[i]->data[0] == valeur_min) {
                
                retire_tab(listes[i]);
                supprimer = 1;
                
                if (listes[i]->taille == 0) {
                    listes[i] = NULL;
                }
            }
        }

        free_arbre(arbre);
    }
}

void demo_algo_fonctionnel() {
    printf("=== DEMONSTRATION ALGORITHME FONCTIONNEL ===\n\n");
    
    // Test 1: Cas général
    printf("Test1 CAS GENERAL\n");
    Tableau t1, t2, t3, t4, res1;
    init_tableau(&t1); init_tableau(&t2); init_tableau(&t3); init_tableau(&t4); init_tableau(&res1);
    
    ajouter_fin(&t1, 1); ajouter_fin(&t1, 5); ajouter_fin(&t1, 9);
    ajouter_fin(&t2, 2); ajouter_fin(&t2, 6); ajouter_fin(&t2, 10);
    ajouter_fin(&t3, 3); ajouter_fin(&t3, 7); ajouter_fin(&t3, 11);
    ajouter_fin(&t4, 4); ajouter_fin(&t4, 8); ajouter_fin(&t4, 12);
    
    Tableau *tabs1[5] = {&t1, &t2, &t3, &t4, NULL};
    
    printf("Entree: ");
    afficher_monotonies(tabs1);
    fusion_liste(tabs1, &res1);
    printf("Sortie: "); afficher_tableau(&res1);
    
    // Test 2: Listes de tailles différentes
    printf("\nTest2 LISTES DE TAILLES DIFFERENTES\n");
    Tableau t5, t6, t7, res2;
    init_tableau(&t5); init_tableau(&t6); init_tableau(&t7); init_tableau(&res2);
    
    ajouter_fin(&t5, 1); ajouter_fin(&t5, 6);
    ajouter_fin(&t6, 2); ajouter_fin(&t6, 4); ajouter_fin(&t6, 7); ajouter_fin(&t6, 8);
    ajouter_fin(&t7, 3); ajouter_fin(&t7, 5);
    
    Tableau *tabs2[4] = {&t5, &t6, &t7, NULL};
    
    printf("Entree: ");
    afficher_monotonies(tabs2);
    fusion_liste(tabs2, &res2);
    printf("Sortie: "); afficher_tableau(&res2);
    
    // Test 3: Visualisation de l'arbre
    printf("\nTest3 VISUALISATION ARBRE\n");
    Tableau t8, t9, res3;
    init_tableau(&t8); init_tableau(&t9);
    init_tableau(&res3);
    
    ajouter_fin(&t8, 3); ajouter_fin(&t8, 7);
    ajouter_fin(&t9, 1); ajouter_fin(&t9, 5);
    
    Tableau *tabs3[3] = {&t8, &t9, NULL};
    node *arbre = liste_arbre(tabs3);
    afficher_monotonies(tabs3);
    printf("Arbre :\n");
    afficher_node(arbre);
    
    fusion_liste(tabs3,&res3);
    printf("Resultat:");
    afficher_tableau(&res3);
    free_arbre(arbre);
}

void test_Q1() {
    Tableau t1, t2, res;
    init_tableau(&t1);
    init_tableau(&t2);

    ajouter_fin(&t1, 4);
    ajouter_fin(&t1, 11);

    ajouter_fin(&t2, 4);
    ajouter_fin(&t2, 13);

    Tableau *tabs[3] = { &t1, &t2, NULL };
    node *arbre = liste_arbre(tabs);

    init_tableau(&res);// notre resultat
    afficher_node(arbre);

    fusion_liste(tabs, &res);
    printf("Apres fusion : ");
    afficher_tableau(&res);
}