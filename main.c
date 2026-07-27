#include <stdio.h>
#include <stdlib.h>
#include "Headers/structures.h" 
// #include "Headers/fichier.h"
// #include "Headers/menu.h"

#include "Headers/initialisation.h"



int main(){
    Noeud noeuds[NB_NOEUDS];
    initialiser_noeuds(noeuds);
    int i;

    for(i = 0; i < NB_NOEUDS; i++){

        printf("ID : %s\n", noeuds[i].id);
        printf("Nom : %s\n", noeuds[i].nom);
        printf("Puissance : %.2f kW\n", noeuds[i].puissance_KW);
        printf("Priorite : %d\n", noeuds[i].priorite);
        printf("Etat : %d\n", noeuds[i].etat);
        printf("Energie : %.2f kWh\n", noeuds[i].energie_KWh);
        printf("Cos Phi : %.2f\n", noeuds[i].cos_phi);
        printf("-------------------------\n");

    }

    
        return 0;
    
}