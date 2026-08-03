#ifndef ENERGIE_H
#define ENERGIE_H

#include "structures.h"


/*
 * Enregistre la consommation reelle des noeuds pour une heure donnee.
 *
 * Doit etre appele par la simulation APRES le delestage et le
 * retablissement, afin que le profil horaire reflete l'etat final :
 *
 *  - noeud ON  : consommation_horaire[heure] = puissance_kw
 *  - noeud OFF : consommation_horaire[heure] = 0
 *
 * C'est cet enregistrement qui alimente le calcul d'energie :
 * sans lui, energie_kwh reste a 0.
 *
 * Entrees :
 *  - noeuds[] : tableau des charges.
 *  - n_noeud  : nombre de charges.
 *  - heure    : heure simulee (0 a NB_POINTS_COURBE-1).
 *
 * Sortie :
 *  - noeuds[].consommation_horaire[heure] mis a jour.
 */
void enregistrer_consommation_horaire(
    Noeud noeuds[],
    int n_noeud,
    int heure
);


/*
 * Calcule l'energie consommee par un noeud.
 *
 * Integration du profil consommation_horaire[] :
 *
 *      E = somme ( P(h) * dt )     avec dt = 1 heure
 *
 * La puissance est supposee constante pendant l'heure simulee
 * (c'est exactement ce que modelise simuler_heure), le trapeze
 * se reduit donc a un rectangle par heure.
 *
 * Les heures non encore simulees valent 0 et n'ajoutent rien :
 * l'energie affichee correspond aux heures reellement simulees.
 *
 * Entrees :
 *  - noeud    : pointeur vers le noeud.
 *  - n_heures : nombre de points du profil (NB_POINTS_COURBE).
 *
 * Retour :
 *  - energie en kwh.
 */
float calcul_energie_noeud(
    Noeud *noeud,
    int n_heures
);


/*
 * Recalcule l'energie de tous les noeuds.
 *
 * Met a jour :
 *      noeuds[i].energie_kwh
 *
 * Le calcul est idempotent : il repart du profil horaire complet,
 * il n'y a donc pas de double comptage si la fonction est appelee
 * plusieurs fois.
 *
 * Entrees/sorties :
 *      noeuds[]
 */
void calculer_energie_tous_noeuds(
    Noeud noeuds[],
    int n_noeud,
    int n_heures
);


#endif
