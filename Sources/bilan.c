#include <stdio.h>
#include <string.h>
#include "../Headers/bilan.h"

void bilan_journalier(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int n_courbe,
    Evenement events[],
    int n_events
){
    float consommation_totale = 0;
    int i;
    //Calcul de la consommation totale
    for(i=0; i<n_noeud; i++){
        consommation_totale += noeuds[i].energie_KWh;
    }
    printf("Consommation totale: %.2f KWh\n", consommation_totale);

    // Calcul de la production solaire
    float production_solaire = 0;
    for(i=0; i<n_courbe; i++){
        production_solaire += courbe[i].p_solaire_KW;
    }
    printf("Production solaire totale: %.2f KWh\n", production_solaire);

    // Calcul de la production reseau
    float production_reseau = 0;
    for(i=0; i<n_courbe; i++){
        production_reseau += courbe[i].p_reseau_KW;

    }
    printf("Production reseau totale : %.2f KWh\n", production_reseau);

    // Calcul du taux de couverture solaire
    float taux_couverture_PV;
    taux_couverture_PV = (production_solaire / consommation_totale)*100;
    printf("Taux couverture PV : %.2f %%\n", taux_couverture_PV);

    // Trouver le plus gros consommateur;
    int max = 0;
    
    for(i=1; i<n_noeud; i++){
        if(noeuds[i].energie_KWh > noeuds[max].energie_KWh){
            max = i;
        }
    }


    // Trouver le plus petit consommateur;
    int min = 0;
    
    for(i=1; i<n_noeud; i++){
        if(noeuds[i].energie_KWh < noeuds[min].energie_KWh){
            min = i;
        }
    }

    // Affichage
   
    printf("Plus gros consommateur : %s - %s : %.2f KWh\n",
        noeuds[max].id,
        noeuds[max].nom,
        noeuds[max].energie_KWh);


    printf("Plus faible consommateur : %s - %s : %.2f KWh\n",
        noeuds[min].id,
        noeuds[min].nom,
        noeuds[min].energie_KWh);

    
    // Compter les evenement ( nb de delestage et nb de retablissement)
    int nb_delestages = 0;
    int nb_retablissements = 0;

    for(i = 0; i<n_events; i++){
        if(strcmp(events[i].type, "DELESTAGE")==0){
            nb_delestages++;
        }
        if(strcmp(events[i].type, "RETABLISSEMENT")==0){
            nb_retablissements++;

        }

    }
    printf("Nombre de delestages      : %d\n", nb_delestages);

    printf("Nombre de retablissements : %d\n", nb_retablissements); 

    printf("\n====== HISTORIQUE EVENEMENTS ======\n");
    for(i = 0; i < n_events; i++){
    
        printf("\nEvenement %d\n", i + 1);

        printf("Type : %s\n", events[i].type);

        printf("Noeud : %s\n", events[i].noeud_id);

        printf("Message : %s\n", events[i].message);

        printf("Puissance : %.2f KW\n", events[i].valeur);

        printf("-----------------------------\n");
    }
}

