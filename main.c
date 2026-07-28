#include <stdio.h>
#include <stdlib.h>
#include "Headers/structures.h" 
#include "Headers/supervision.h"
// #include "Headers/fichier.h"
// #include "Headers/menu.h"

#include "Headers/initialisation.h"



int main(){
    Noeud noeuds[NB_NOEUDS];
    initialiser_noeuds(noeuds);
    int i;

    PointCourbe courbe[NB_POINTS_COURBE] ={
        /* Quelques données de la production solaire 
        pour le test */

        {0, 0.0, 15.0},
        {1, 0.0, 14.8},
        {2, 0.0, 14.5},
        {12, 14.8, 2.0},
        {18, 2.1, 14.0}          
    };

    float production;
    production = calcul_production_disponible(courbe, 5,12); /*On appele la fonction avec 3 parametres: courbe ,
     le tableau des données de production, 5, le nombre d'element dans le tableau, 
     12, l'heure recherché */

    printf("Production disponibl a 12h: %.2f KW\n", production);

    
    return 0;

        
}