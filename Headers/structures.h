#ifndef STRUCTURES_H
#define STRUCTURES_H

/*=========================================================
 * Constantes générales
 *=========================================================*/

#define NB_NOEUDS          12
#define NB_POINTS_COURBE   24
/*
 * MAX_EVENTS : une journee complete peut generer plusieurs
 * delestages et retablissements par heure. 500 laisse une
 * marge confortable pour une simulation 24 h.
 */
#define MAX_EVENTS         500

/*=========================================================
 * Seuils du réseau
 *=========================================================*/

/*
 * SEUIL_ALERTE_PCT    : 90 %
 * SEUIL_DELESTAGE_PCT : 100 %
 *
 * Le rétablissement est effectué à partir de 90 % afin
 * d'éviter les oscillations ON/OFF du réseau.
 */

#define SEUIL_ALERTE_PCT      90.0f
#define SEUIL_DELESTAGE_PCT  100.0f

/*
 * Facteur de puissance minimal admis.
 */

#define COS_PHI_MIN 0.85f

/*=========================================================
 * Structure Noeud
 *=========================================================*/

typedef struct
{
    char id[4];              /* ex : N01 */
    char nom[30];            /* nom du noeud */

    float puissance_kw;      /* puissance nominale */

    int priorite;            /* 1 = critique
                                2 = important
                                3 = normal */

    int etat;                /* 1 = ON
                                0 = OFF */

    float energie_kwh;       /* énergie consommée */

    float cos_phi;  
    float consommation_horaire[NB_POINTS_COURBE];
             /* facteur de puissance */

} Noeud;

/*=========================================================
 * Structure PointCourbe
 *=========================================================*/

typedef struct
{
    int heure;

    float p_solaire_kw;
    float p_reseau_kw;

    float p_charge_kw;

    float taux_charge;

} PointCourbe;

/*=========================================================
 * Structure Evenement
 *=========================================================*/

typedef struct
{
    char horodatage[20];

    char type[20];

    char noeud_id[4];

    char message[100];

    float valeur;

} Evenement;

#endif