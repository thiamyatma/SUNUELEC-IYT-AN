#ifndef MENU_H
#define MENU_H

#include "structures.h"

/* Affiche le menu principal du superviseur.
   Entrees : aucune.
   Sortie  : les 12 options ecrites a l'ecran. */
void afficher_menu(void);

/* Boucle principale du programme : affiche le menu, lit le choix de
   l'utilisateur et declenche l'action correspondante jusqu'au choix 9.
   Une saisie non numerique est rejetee sans bloquer la boucle.
   Entrees/sorties : noeuds[] et courbe[], modifies par les
                     simulations et les delestages ;
                     events[] et *nb_events, completes au fil des
                     evenements.
   Sortie          : aucune valeur de retour. */
void gestion_choix(
    Noeud noeuds[],
    PointCourbe courbe[],
    Evenement events[],
    int *nb_events
);

#endif // MENU_H
