#ifndef FICHIER_H
#define FICHIER_H

#include "structures.h"


/*=========================================================
 * Structure utilisée pour le bilan journalier
 *=========================================================*/

typedef struct
{
    float prod_solaire;
    float prod_reseau;

    float consommation_totale;

    float taux_couverture_pv;

    int nb_delestages;

    int nb_retablissements;

} DonneesBilan;



/*=========================================================
 * Chargement de la courbe CSV
 *=========================================================*/

/*
    Charge les données de production depuis un fichier CSV.

    Format attendu (séparateur virgule, pas de ligne d'entête) :
    heure,production_solaire,production_reseau

    Exemple :
    0,0.0,15.0
    1,0.0,14.8

    Fichier de référence : donnees/courbe.csv

    Entrees :
        nom_fichier : chemin du fichier CSV
        courbe[]    : tableau de sortie
        n_courbe    : nombre maximum de points

    Retour :
        nombre de points chargés
        0 en cas d'erreur
*/

int charger_courbe_csv(
    const char *nom_fichier,
    PointCourbe courbe[],
    int n_courbe
);



/*=========================================================
 * Gestion fichier binaire des noeuds
 *=========================================================*/

/*
    Sauvegarde les noeuds dans un fichier binaire.

    Retour :
        1 succès
        0 erreur
*/

int sauvegarder_noeuds(
    const char *nom_fichier,
    Noeud tableau[],
    int n_noeud
);



/*
    Charge les noeuds depuis un fichier binaire.

    Vérifie que le nombre d'éléments lus correspond
    au nombre attendu.

    Retour :
        1 succès
        0 fichier absent ou corrompu
*/

int charger_noeuds(
    const char *nom_fichier,
    Noeud tableau[],
    int n_noeud
);



/*=========================================================
 * Gestion journal événements
 *=========================================================*/

/*
    Ajoute un événement dans evenements.log.

    Le fichier est ouvert en mode ajout "a".

    Retour :
        1 succès
        0 erreur
*/

int ajouter_evenement_log(
    const char *nom_fichier,
    Evenement event
);



/*=========================================================
 * Génération rapport journalier
 *=========================================================*/

/*
    Génère le bilan énergétique.

    Contient :
        - consommation totale
        - production solaire
        - production réseau
        - taux couverture PV
        - nombre délestages
        - nombre rétablissements
        - consommation par noeud

    Retour :
        1 succès
        0 erreur
*/

int generer_bilan_journalier(
    const char *nom_fichier,
    const char *date,
    Noeud noeuds[],
    int n_noeud,
    DonneesBilan bilan
);


#endif