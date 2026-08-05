#ifndef BILAN_H
#define BILAN_H

#include "structures.h"

/*
 * Calcule la consommation totale journaliere.
 *
 * Additionne energie_kWh de tous les noeuds.
 *
 * Entrees :
 *      noeuds[] : tableau des charges
 *      n_noeud  : nombre de noeuds
 *
 * Retour :
 *      Energie totale en kwh
 */
float calcul_consommation_totale(
    Noeud noeuds[],
    int n_noeud
);


/*
 * Calcule la production totale disponible sur la journee.
 *
 * Utilise la methode des trapezes sur :
 *      solaire + reseau
 *
 * Entrees :
 *      courbe[] : points horaires
 *      n_courbe : nombre de points
 *
 * Retour :
 *      Energie produite en kwh
 */
float calcul_production_totale(
    PointCourbe courbe[],
    int n_courbe
);


/*
 * Calcule le taux de couverture solaire.
 *
 * Formule :
 *
 * (energie_solaire / energie_totale) * 100
 *
 */
float calcul_taux_couverture_pv(
    PointCourbe courbe[],
    int n_courbe
);


/*
 * Compte les evenements selon leur type.
 *
 * Retour :
 *      nombre d'evenements trouves.
 */
int compter_evenements(
    Evenement events[],
    int n_events,
    char type[]
);


/*
 * Recherche le noeud ayant la plus grande consommation.
 */
Noeud* noeud_plus_consommateur(
    Noeud noeuds[],
    int n_noeud
);


/*
 * Recherche le noeud ayant la plus faible consommation.
 */
Noeud* noeud_moins_consommateur(
    Noeud noeuds[],
    int n_noeud
);


/*
 * Affiche le bilan energetique journalier complet.
 *
 * Contient :
 *  - consommation totale
 *  - production solaire
 *  - production reseau
 *  - couverture PV
 *  - delestages
 *  - retablissements
 *  - plus gros consommateur
 *  - plus faible consommateur
 */
void bilan_journalier(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int n_courbe,
    Evenement events[],
    int n_events
);

#endif
