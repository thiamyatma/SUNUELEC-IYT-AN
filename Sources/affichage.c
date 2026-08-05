#include <stdio.h>

#include "../Headers/affichage.h"

/*
    Affiche un titre de section
*/
void afficherEnteteEcran(
    const char* titre
)
{
    printf("\n========== %s ==========\n",
           titre);
}


/*
    Affiche un noeud individuel
*/
void afficherUnNoeudEcran(
    const Noeud* noeud,
    float puissance_inst
)
{
    printf(
        "%s - %-12s | %5.2f kw | Priorite %d | ",
        noeud->id,
        noeud->nom,
        puissance_inst,
        noeud->priorite
    );

    if(noeud->etat == 1)
    {
        printf("ON ");
    }
    else
    {
        printf("OFF");
    }

    printf(
        " | Energie : %8.2f kwh\n",
        noeud->energie_kWh
    );
}


/*
    Affiche la liste complète des noeuds.

    L'affichage d'une ligne est délégué à
    afficherUnNoeudEcran() pour éviter de
    dupliquer le format.
*/
void afficherListeNoeuds(
    Noeud noeuds[],
    int n
)
{
    afficherEnteteEcran("ETAT DES NOEUDS");

    for(int i = 0; i < n; i++)
    {
        afficherUnNoeudEcran(
            &noeuds[i],
            noeuds[i].puissance_kW
        );
    }
}
