#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/structures.h" 
#include "Headers/supervision.h"
#include "Headers/energie.h"
// #include "Headers/fichier.h"
// #include "Headers/menu.h"
#include "Headers/recherche.h"

#include "Headers/initialisation.h"



int main(){
    int i;
    Noeud noeuds[NB_NOEUDS];
    initialiser_noeuds(noeuds);

    PointCourbe courbe[24];

    Noeud *resultat;
    resultat = recherche_noeud_par_id(noeuds, NB_NOEUDS, "N05");
    if(resultat != NULL){
        printf("Noeud trouve: %s - %s\n" , resultat->id, resultat->nom);
    }
    else{
        printf("Noeud Introuvable\n");
    }

    return 0;

        
}