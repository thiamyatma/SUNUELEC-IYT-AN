#include <stdio.h>

#include "../Headers/structures.h"
#include "../Headers/energie.h"

/*
    Enregistrement de la consommation reelle d'une heure.

    C'est ici que la simulation laisse une trace :
    un noeud coupe consomme 0 pendant cette heure,
    mais garde l'energie deja consommee les heures
    precedentes.
*/
void enregistrer_consommation_horaire(
    Noeud noeuds[],
    int n_noeud,
    int heure
)
{
    if(heure < 0 || heure >= NB_POINTS_COURBE)
    {
        return;
    }

    for(int i = 0; i < n_noeud; i++)
    {
        if(noeuds[i].etat == 1)
        {
            noeuds[i].consommation_horaire[heure] =
                noeuds[i].puissance_kW;
        }
        else
        {
            noeuds[i].consommation_horaire[heure] = 0.0f;
        }
    }
}


/*
    Calcul de l'energie consommee par un noeud.

    Energie = somme ( P(h) * 1 heure )

    La puissance est constante pendant l'heure simulee,
    l'integration se fait donc heure par heure sur le
    profil enregistre par la simulation.
*/
float calcul_energie_noeud(
    Noeud *noeud,
    int n_heures
)
{
    float energie = 0.0f;

    if(noeud == NULL || n_heures <= 0)
    {
        return 0.0f;
    }

    if(n_heures > NB_POINTS_COURBE)
    {
        n_heures = NB_POINTS_COURBE;
    }

    for(int h = 0; h < n_heures; h++)
    {
        /*
            Duree entre deux mesures : 1 heure.
            kw * h = kwh
        */
        float duree = 1.0f;

        energie +=
            noeud->consommation_horaire[h] * duree;
    }

    return energie;
}


/*
    Calcul energie de tous les noeuds.

    On ne fait qu'un calcul ici, rien n'est affiche :
    l'affichage se fait dans affichage.c et bilan.c
*/
void calculer_energie_tous_noeuds(
    Noeud noeuds[],
    int n_noeud,
    int n_heures
)
{
    for(int i = 0; i < n_noeud; i++)
    {
        noeuds[i].energie_kWh =
            calcul_energie_noeud(
                &noeuds[i],
                n_heures
            );
    }
}
