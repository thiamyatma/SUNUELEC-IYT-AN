#include <stdio.h>
#include "../Headers/tri.h"

void trier_noeuds_par_consommation(Noeud noeuds[], int n){
    int i;
    int j;
    int max;
    Noeud temporaire;

    for(i=0; i<n; i++){
        max = i;

        // recherche du plus grand consommateur
        for(j=i+1; j<n; j++){
            if(noeuds[j].energie_KWh > noeuds[max].energie_KWh){
                max = j;
            }
        }

        // Echanche des deux structure
        if (max !=i){
            temporaire = noeuds[i];
            noeuds[i] = noeuds[max];
            noeuds[max] = temporaire;
        }
    }
    
}