#include <string.h>

#include "../Headers/recherche.h"

/*
    Recherche séquentielle d'un noeud
    par son identifiant.

    Exemple :
    id = "N05"

    Retour :
    - adresse du noeud trouvé
    - NULL si aucun noeud correspondant
*/

Noeud* recherche_noeud_par_id(
    Noeud noeuds[],
    int n,
    const char *id
)
{
    for(int i = 0; i < n; i++)
    {
        /*
            Comparaison des identifiants
        */

        if(strcmp(noeuds[i].id, id) == 0)
        {
            /*
                Retourne l'adresse réelle
                de la case du tableau.

                Toute modification faite
                sur ce pointeur modifiera
                directement le tableau.
            */

            return &noeuds[i];
        }
    }

    /*
        Aucun noeud trouvé
    */

    return NULL;
}
