#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/recherche.h"

Noeud* recherche_noeud_par_id(Noeud noeuds[], int n, char *id){
    int i;
    
    for(i=0; i<n; i++){
        if(strcmp(noeuds[i].id, id)== 0){ // ca compare l'id du noeud actuel avec l'id recherché
            return &noeuds[i]; // cela retourne l'adresse du noeud trouvé
        }
    }
    return NULL;
}