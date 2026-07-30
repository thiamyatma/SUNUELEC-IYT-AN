#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    nb_coupes = delestage_automatique(noeuds,NB_NOEUDS,40.0,events,&nb_events);
    printf("Nombre de noeuds coupes: %d\n", nb_coupes);
    printf("\n==========EVENEMENTS=======\n");
    for(i=0; i<nb_events; i++){
        printf("Type : %s\n", events[i].type);
        printf("Noeuds: %s\n", events[i].noeud_id);
        printf("Message: %s\n", events[i].message);
        printf("Puissance coupee: %.2f KW\n", events[i].valeur);
        printf("---------------------------\n");
    }

    for(i =0; i< NB_NOEUDS; i++){
        printf("%s - %s - Etat : %d\n",
            noeuds[i].id,
            noeuds[i].nom,
            noeuds[i].etat);
    }

    printf("\n======RETABLISSEMENT=======\n");
    retablissement_progressif(noeuds, NB_NOEUDS, 15.0, events, &nb_events);

    for (i=0; i< NB_NOEUDS; i++){
        printf("%s - Etat : %d\n", noeuds[i].id, noeuds[i].etat);
    }

   

    
    return 0;

        
}