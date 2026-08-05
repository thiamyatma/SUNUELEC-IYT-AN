#ifndef SUPERVISION_H
#define SUPERVISION_H

#include "structures.h"

/*
 * Ecrit la date et l'heure courantes au format
 * "JJ/MM/AAAA HH:MM" dans date[].
 *
 * Entree :
 *  - date : tampon d'au moins 20 caracteres.
 */
void obtenir_horodatage(char date[]);


/*
 * Ecrit la date courante au format "JJ-MM-AAAA" dans date[].
 *
 * Utilisee pour nommer le rapport journalier
 * bilan_JJ-MM-AAAA.txt.
 *
 * Entree :
 *  - date : tampon d'au moins 11 caracteres.
 */
void obtenir_date_fichier(char date[]);


/*
 * Enregistre un evenement horodate dans events[].
 *
 * Centralise l'horodatage, la copie sure des chaines et le
 * controle de saturation du tableau.
 *
 * Entrees/sorties :
 *  - events[]  : tableau complete
 *  - nb_events : compteur incremente
 */
void ajouter_evenement(
    Evenement events[],
    int *nb_events,
    const char type[],
    const char id[],
    const char message[],
    float valeur
);


/*
 * Calcule la puissance active totale consommée.
 *
 * Additionne uniquement les noeuds dont l'etat est ON.
 *
 * Entrees :
 *  - noeuds[] : tableau des charges.
 *  - n : nombre de noeuds.
 *
 * Retour :
 *  - puissance totale en kw.
 */
float calcul_puissance_totale(
    Noeud noeuds[],
    int n
);


/*
 * Retourne la puissance disponible a une heure donnee.
 *
 * La valeur est obtenue par :
 *  production solaire + production reseau.
 *
 * Utilise une interpolation lineaire lorsque
 * l'heure demandee n'existe pas exactement.
 *
 * Entrees :
 *  - courbe[] : courbe de production.
 *  - n : nombre de points.
 *  - heure : heure reelle recherchee.
 *
 * Retour :
 *  - puissance disponible en kw.
 */
float calcul_production_disponible(
    PointCourbe courbe[],
    int n,
    int heure
);


/*
 * Effectue un delestage automatique.
 *
 * Coupe les charges :
 *  1) priorite 3
 *  2) puis priorite 2
 *
 * Les charges critiques (priorite 1)
 * ne sont jamais coupees automatiquement.
 *
 * Retour :
 *  - nombre de noeuds coupes.
 */
int delestage_automatique(
    Noeud noeuds[],
    int n,
    float deficit_kW,
    Evenement events[],
    int *nb_events
);


/*
 * Retablit progressivement les charges coupees.
 *
 * Le retablissement respecte :
 *  - seuil de securite 90 %
 *  - ordre inverse du delestage.
 */
void retablissement_progressif(
    Noeud noeuds[],
    int n,
    float marge_kW,
    Evenement events[],
    int *nb_events
);


/*
 * Calcule le taux de charge du reseau.
 *
 * Retour :
 *  taux en pourcentage.
 */
float calcul_taux_charge_pct(
    float p_charge,
    float p_dispo
);


/*
 * Delestage manuel demande par l'utilisateur.
 *
 * Recherche un noeud par identifiant
 * puis le passe a l'etat OFF.
 */
void delestage_manuel(
    Noeud noeuds[],
    int n,
    Evenement events[],
    int *nb_events
);


/*
 * Controle le facteur de puissance.
 *
 * Genere une alerte si cos_phi < 0.85.
 */
void verifier_facteur_puissance(
    Noeud noeuds[],
    int n,
    Evenement events[],
    int *nb_events
);

#endif
