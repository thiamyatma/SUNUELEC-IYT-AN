#include <stdio.h>
#include "../Headers/affichage.h"


void afficherListeNoeuds(Noeud noeuds[], int n)
{
    int i;

    printf("\n====== ETAT DES NOEUDS ======\n");

    for(i=0; i<n; i++)
    {
        printf("%s - %s | %.2f KW | Priorite %d | ",
            noeuds[i].id,
            noeuds[i].nom,
            noeuds[i].puissance_KW,
            noeuds[i].priorite
        );

        if(noeuds[i].etat == 1)
            printf("ON\n");
        else
            printf("OFF\n");
    }
}