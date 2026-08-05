#include <stdio.h>
#include <stdlib.h>

#include "Headers/structures.h"
#include "Headers/menu.h"
#include "Headers/initialisation.h"

int main()
{
    Noeud noeuds[NB_NOEUDS];

    PointCourbe courbe[NB_POINTS_COURBE];

    Evenement events[MAX_EVENTS];

    int nb_events = 0;

    /*
        Initialisation du réseau
    */

    initialiser_noeuds(noeuds);

    initialiser_courbe(courbe);

    printf(
        "\n====================================\n"
    );

    printf(
        "  SYSTEME DE SUPERVISION RESEAU\n"
    );

    printf(
        "  ELECTRIQUE SUNUELEC IYT_AN\n"
    );

    printf(
        "====================================\n"
    );

    /*
        Lancement application
    */

    gestion_choix(
        noeuds,
        courbe,
        events,
        &nb_events
    );

    printf(
        "\nProgramme termine.\n"
    );

    return 0;
}
