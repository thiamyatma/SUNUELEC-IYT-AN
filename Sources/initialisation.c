#include <stdio.h>
#include <string.h>

#include "../Headers/initialisation.h"

/*
    Initialise les 12 noeuds du réseau.
*/
void initialiser_noeuds(Noeud noeuds[])
{
    char ids[NB_NOEUDS][4] =
    {
        "N01","N02","N03","N04",
        "N05","N06","N07","N08",
        "N09","N10","N11","N12"
    };

    char noms[NB_NOEUDS][30] =
    {
        "Hopital",
        "Ecole",
        "Pompe Eau",
        "Marche",
        "Resid A",
        "Resid B",
        "Resid C",
        "Resid D",
        "Commerce 1",
        "Commerce 2",
        "Eclairage",
        "Divers"
    };

    float puissances[NB_NOEUDS] =
    {
        8.5,
        4.2,
        3.0,
        5.8,
        6.1,
        5.3,
        4.7,
        4.4,
        3.9,
        3.2,
        2.1,
        1.8
    };

    int priorites[NB_NOEUDS] =
    {
        1,1,1,
        2,2,2,
        3,3,3,3,
        2,
        3
    };

    for(int i = 0; i < NB_NOEUDS; i++)
    {
        strcpy(noeuds[i].id, ids[i]);

        strcpy(noeuds[i].nom, noms[i]);

        noeuds[i].puissance_kW =
            puissances[i];

        noeuds[i].priorite =
            priorites[i];

        noeuds[i].etat = 1;

        noeuds[i].energie_kWh = 0;

        noeuds[i].cos_phi = 0.86;

        /*
            Profil horaire initial vide.

            consommation_horaire[] est un HISTORIQUE :
            il est rempli heure par heure par la simulation
            (enregistrer_consommation_horaire).

            Le pre-remplir avec la puissance nominale
            ferait apparaitre 24 h de consommation avant
            meme la premiere simulation.
        */

        for(int h = 0; h < NB_POINTS_COURBE; h++)
        {
            noeuds[i].consommation_horaire[h] = 0.0f;
        }
    }
}


/*
    Initialise la courbe de production horaire.
*/

void initialiser_courbe(PointCourbe courbe[])
{
    float solaire[24] =
    {
        0.0,0.0,0.0,0.0,
        0.0,0.0,
        0.8,2.5,4.5,7.8,
        11.2,13.5,14.8,
        14.5,13.5,12.0,
        9.0,5.5,2.1,
        0.5,0.0,0.0,
        0.0,0.0
    };

    float reseau[24] =
    {
        15.0,14.8,14.5,14.2,
        13.8,13.5,
        14.2,12.5,12.0,10.0,
        6.0,3.5,2.0,
        2.5,3.5,5.0,
        8.0,10.5,14.0,
        14.5,15.0,14.8,
        14.5,14.2
    };

    for(int i = 0; i < NB_POINTS_COURBE; i++)
    {
        courbe[i].heure = i;

        courbe[i].p_solaire_kW =
            solaire[i];

        courbe[i].p_reseau_kW =
            reseau[i];

        courbe[i].p_charge_kW = 0;

        courbe[i].taux_charge = 0;
    }
}
