#ifndef MENU_H
#define MENU_H

#include "structures.h"


void afficher_menu();
void gestion_choix(
    Noeud noeuds[],
    PointCourbe courbe[],
    Evenement events[],
    int *nb_events
);

#endif // MENU_H
