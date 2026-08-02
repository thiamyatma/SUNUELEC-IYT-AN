#include <stdio.h>
#include <stdlib.h>

#include "Headers/structures.h"
#include "Headers/menu.h"
#include "Headers/initialisation.h"
#include "Headers/energie.h"

int main()
{
    Noeud noeuds[NB_NOEUDS];
    PointCourbe courbe[NB_POINTS_COURBE];
    Evenement events[MAX_EVENTS];

    int nb_events = 0;


    // Initialisation des noeuds
    initialiser_noeuds(noeuds);
    initialiser_courbe(courbe);
    calculer_energie_tous_noeuds(noeuds, NB_NOEUDS, courbe, NB_POINTS_COURBE);



    // Lancement du menu
    gestion_choix(
        noeuds,
        courbe,
        events,
        &nb_events
    );


    return 0;
}