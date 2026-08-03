#ifndef RECHERCHE_H
#define RECHERCHE_H

#include "structures.h"


/*
 * Recherche sequentielle d'un noeud par son identifiant.
 *
 * Entrees :
 *      noeuds[] : tableau des noeuds.
 *      n        : nombre de noeuds.
 *      id       : identifiant recherche (ex: "N05").
 *
 * Retour :
 *      Adresse du noeud trouve.
 *      NULL si aucun noeud ne correspond.
 *
 * Le pointeur retourne permet de modifier directement
 * le noeud trouve dans le tableau.
 */
Noeud* recherche_noeud_par_id(
    Noeud noeuds[],
    int n,
    const char *id
);


#endif