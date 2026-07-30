#include <stdio.h>
#include <stdlib.h>
#include "Headers/structures.h" 
#include "Headers/supervision.h"
// #include "Headers/fichier.h"
// #include "Headers/menu.h"

#include "Headers/initialisation.h"



int main(){
    Noeud noeuds[NB_NOEUDS];
    initialiser_noeuds(noeuds);
    int i;
    Evenement events[MAX_EVENTS];
    int nb_events = 0;
    int nb_coupes;

    nb_coupes = delestage_automatique(noeuds,NB_NOEUDS,13.0,events,&nb_events);
    printf("Nombre de noeuds coupes: %d\n", nb_coupes);

    for(i =0; i< NB_NOEUDS; i++){
        printf("%s - %s - Etat : %d\n",
            noeuds[i].id,
            noeuds[i].nom,
            noeuds[i].etat);
    }

   

    
    return 0;

        
}