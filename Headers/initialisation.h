#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "structures.h"


/*
 * Initialise les 12 noeuds du mini-reseau electrique.
 *
 * Remplit les champs :
 *  - identifiant du noeud ;
 *  - nom de la charge ;
 *  - puissance nominale en kw ;
 *  - niveau de priorite ;
 *  - etat initial (ON) ;
 *  - facteur de puissance cos_phi ;
 *  - energie consommee initialisee a 0.
 *
 * Donnees utilisees :
 *  Tableau initial fourni dans le cahier des charges.
 *
 * Entree :
 *  - tableau noeuds[] capable de contenir NB_NOEUDS elements.
 *
 * Sortie :
 *  - tableau de noeuds completement initialise.
 */

void initialiser_noeuds(Noeud noeuds[]);


/*
 * Initialise la courbe journaliere de production.
 *
 * Remplit pour chaque heure :
 *  - heure (0 a 23) ;
 *  - production solaire disponible ;
 *  - puissance fournie par le reseau national ;
 *  - valeurs de supervision initialisees a 0.
 *
 * Donnees utilisees :
 *  Courbe de production fournie dans le cahier des charges.
 *
 * Entree :
 *  - tableau courbe[] capable de contenir NB_POINTS_COURBE elements.
 *
 * Sortie :
 *  - courbe horaire complete.
 */

void initialiser_courbe(PointCourbe courbe[]);


#endif