#include <stdio.h>
#include "structures.h"
#include "initialisation.h"
#include "tri.h"

int main(void){
    Noeud n[NB_NOEUDS];
    initialiser_noeuds(n);

    /* Energies fictives, volontairement dans le desordre */
    float e[NB_NOEUDS] = {12.0f, 45.5f, 3.2f, 88.1f, 20.0f, 67.4f,
                          1.5f, 99.9f, 30.3f, 55.0f, 7.7f, 40.2f};
    for(int i=0;i<NB_NOEUDS;i++) n[i].energie_kWh = e[i];

    printf("Avant tri :\n");
    for(int i=0;i<NB_NOEUDS;i++)
        printf("  %s %-11s %6.2f kwh\n", n[i].id, n[i].nom, n[i].energie_kWh);

    trier_noeuds_par_consommation(n, NB_NOEUDS);

    printf("\nApres tri :\n");
    int ok = 1;
    for(int i=0;i<NB_NOEUDS;i++){
        printf("  %s %-11s %6.2f kwh\n", n[i].id, n[i].nom, n[i].energie_kWh);
        if(i>0 && n[i].energie_kWh > n[i-1].energie_kWh) ok = 0;
    }
    printf("\nOrdre decroissant : %s\n", ok ? "OUI" : "NON");
    return 0;
}
