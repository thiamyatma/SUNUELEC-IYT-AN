#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"

/*
 * Affiche un titre formaté pour les différentes sections
 * du programme.
 *
 * Entree :
 *      titre : texte a afficher.
 *
 * Sortie :
 *      affichage console.
 */
void afficherEnteteEcran(const char* titre);


/*
 * Affiche les informations d'un seul noeud.
 *
 * Entrees :
 *      noeud          : noeud a afficher.
 *      puissance_inst : puissance actuellement consommee.
 *
 * Sortie :
 *      informations du noeud a l'ecran.
 */
void afficherUnNoeudEcran(
    const Noeud* noeud,
    float puissance_inst
);


/*
 * Affiche l'etat actuel de tous les noeuds.
 *
 * Chaque ligne est produite par afficherUnNoeudEcran(),
 * le format n'est donc defini qu'a un seul endroit.
 *
 * Entrees :
 *      noeuds[] : tableau des noeuds.
 *      n       : nombre de noeuds.
 *
 * Sortie :
 *      affichage console.
 */
void afficherListeNoeuds(
    Noeud noeuds[],
    int n
);

#endif
