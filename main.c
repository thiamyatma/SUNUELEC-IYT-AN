#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/structures.h" 
#include "Headers/supervision.h"
#include "Headers/energie.h"
// #include "Headers/fichier.h"
// #include "Headers/menu.h"
#include "Headers/recherche.h"
#include "Headers/tri.h"
#include "Headers/bilan.h"
#include "Headers/initialisation.h"




int main(){
    int i;
    Noeud noeuds[NB_NOEUDS];
    initialiser_noeuds(noeuds);

    PointCourbe courbe[24];
    for (i=0; i<24; i++){
        courbe[i].heure = i;
        courbe[i].p_solaire_KW = 5.0;
        courbe[i].p_reseau_KW = 10.0;
    }

    calculer_energie_tous_noeuds(noeuds, NB_NOEUDS, courbe, 24);

    trier_noeuds_par_consommation(noeuds, NB_NOEUDS);
    printf("\n=======CLASSEMENT CONSOMMATION======\n");



    for(i=0; i< NB_NOEUDS; i++){
        printf("%d. %s - %s : %.2f KWh\n", i+1, noeuds[i].id, noeuds[i].nom, noeuds[i].energie_KWh);

    }

    Evenement events[MAX_EVENTS];
    int nb_events = 0;
    delestage_automatique(
    noeuds,
    NB_NOEUDS,
    20.0,
    events,
    &nb_events
    );  

    retablissement_progressif(
    noeuds,
    NB_NOEUDS,
    20.0,
    events,
    &nb_events
    );
    printf("\nNombre total événements : %d\n", nb_events);
    bilan_journalier(noeuds, NB_NOEUDS, courbe, 24, events, nb_events);

     Noeud noeuds[NB_NOEUDS];
    PointCourbe courbe[NB_POINTS_COURBE];
    Evenement events[MAX_EVENTS];

    int nb_events = 0;


    initialiser_noeuds(noeuds);


    gestion_choix(
        noeuds,
        courbe,
        events,
        &nb_events
    );




    return 0;

        
}