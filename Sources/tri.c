#include <stdio.h>

#include "../Headers/tri.h"


/*
    Trie les noeuds par énergie consommée décroissante.

    Méthode :
    Tri par sélection.

    Le plus gros consommateur restant
    est placé au début du tableau.
*/

void trier_noeuds_par_consommation(
    Noeud noeuds[],
    int n
)
{

    if(n <= 1)
        return;


    for(int i = 0; i < n - 1; i++)
    {

        int max = i;


        /*
            Recherche du noeud
            ayant la plus grande énergie
            restante
        */

        for(int j = i + 1; j < n; j++)
        {

            if(noeuds[j].energie_kwh >
               noeuds[max].energie_kwh)
            {
                max = j;
            }

        }



        /*
            Échange des structures
        */

        if(max != i)
        {

            Noeud temporaire;


            temporaire = noeuds[i];

            noeuds[i] = noeuds[max];

            noeuds[max] = temporaire;

        }

    }

}