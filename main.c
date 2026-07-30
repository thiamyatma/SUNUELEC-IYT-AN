#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/structures.h" 
#include "Headers/supervision.h"
#include "Headers/energie.h"
// #include "Headers/fichier.h"
// #include "Headers/menu.h"

#include "Headers/initialisation.h"



int main(){
    int i;
    Noeud noeuds[NB_NOEUDS];
    initialiser_noeuds(noeuds);

    PointCourbe courbe[24];

    for(i = 0; i < 24; i++){
        courbe[i].heure = i;

    }

    calculer_energie_tous_noeuds(noeuds, NB_NOEUDS, courbe, 24);
    for(i=0; i< NB_NOEUDS; i++){
        printf("%s - %s: %.2f KWh\n", noeuds[i].id, noeuds[i].nom, noeuds[i].energie_KWh);
    }
    
    return 0;

        
}