#ifndef SIMULATION_H
#define SIMULATION_H

#include "structures.h"
#include "energie.h"

/*
 * Simule le fonctionnement du reseau pendant une heure.
 *
 * Etapes :
 * 1. Lecture de la production disponible.
 * 2. Calcul de la puissance consommee.
 * 3. Calcul du taux de charge.
 * 4. Declenchement du delestage automatique si surcharge.
 * 5. Retablissement progressif si marge suffisante.
 * 6. Enregistrement des evenements.
 *
 * Entrees :
 *  - noeuds[] : charges du reseau.
 *  - n_noeud : nombre de charges.
 *  - courbe[] : production solaire + reseau.
 *  - heure : heure simulee (0.0 a 23.0).
 *
 * Entrees/Sorties :
 *  - noeuds[] : modification des etats ON/OFF.
 *  - events[] : historique des evenements.
 *  - nb_events : nombre actuel d'evenements.
 *
 * Sortie :
 *  - affichage du bilan de simulation.
 */
void simuler_heure(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int heure,
    Evenement events[],
    int *nb_events
);

#endif
