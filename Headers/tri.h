#ifndef TRI_H
#define TRI_H

#include "structures.h"

/*
 * Trie les noeuds par energie consommee decroissante.
 *
 * Algorithme utilise :
 *      Tri par selection.
 *
 * Principe :
 *      A chaque iteration, recherche le noeud ayant
 *      la plus grande energie restante puis l'echange
 *      avec la position courante.
 *
 * Entrees/sorties :
 *      noeuds[] : tableau des noeuds modifie sur place.
 *      n        : nombre de noeuds.
 *
 * Retour :
 *      Aucun.
 */
void trier_noeuds_par_consommation(
    Noeud noeuds[],
    int n
);

#endif
