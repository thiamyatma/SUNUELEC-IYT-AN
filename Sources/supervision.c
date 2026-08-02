#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/structures.h"
#include "../Headers/supervision.h" //Je remonte d'un dossier vers Headers
#include <math.h>

/*Cette fonction somme et retourne les puissances 
de tous les noeuds à l'état ON*/ 
float calcul_puissance_totale(Noeud noeuds[], int n){
    float somme = 0;
    int i;
    for (i=0; i<n; i++){
        if(noeuds[i].etat == 1){
            somme += noeuds[i].puissance_KW;
        }
    }
    return somme;



}

/*Cette fonction permet de couper les noeuds non critiques
(priorité 3 d'abord, puis 2) jusqu'a réabsorber le déficit
Elle retourne le nombre de noeuds coupés.
Chaque coupure est enregistrée dans le tableau d'évenement avec horodotage et raison*/
int delestage_automatique(Noeud noeuds[], int n, float deficit_KW, Evenement events[], int *nb_events){
    int i;
    int nb_coupes = 0;

    for (i=0; i<n; i++){
        if (noeuds[i].priorite== 3 && noeuds[i].etat ==1){
            noeuds[i].etat = 0;
            deficit_KW -= noeuds[i].puissance_KW;
            nb_coupes++;

            strcpy(events[*nb_events].type, "DELESTAGE");
            strcpy(events[*nb_events].noeud_id, noeuds[i].id);
            strcpy(events[*nb_events].message, "Coupure Automatique");
            events[*nb_events].valeur = noeuds[i].puissance_KW;
            (*nb_events)++ ;
            
            if (deficit_KW <=0){
                return nb_coupes;
            }
        }
    }
    // si deficit exite encore : delestage priorite 2
    for(i=0; i<n; i++){
        if (noeuds[i].priorite ==2 && noeuds[i].etat ==1){
            noeuds[i].etat = 0;
            deficit_KW -= noeuds[i].puissance_KW;
            nb_coupes++;

            if (deficit_KW <= 0){
                return nb_coupes;

                // Enregistrement de l'événement
                strcpy(events[*nb_events].type, "DELESTAGE");
                strcpy(events[*nb_events].noeud_id, noeuds[i].id);
                strcpy(events[*nb_events].message, "Coupure automatique");
                events[*nb_events].valeur = noeuds[i].puissance_KW;

                (*nb_events)++;
            }
        }
    }
    return nb_coupes;
}


/*Cette procedure permet de rétablir progressivement les noeuds délestés
dans l'ordre inverse (priorité d'abord) dès que la marge le permet.
Elle enregistre chaque rétablissement.
*/
// Retablissement des noeuds de priorité 2

void retablissement_progressif(Noeud noeuds[], int n, float marge_KW, Evenement events[], int *nb_events){
    int i;
    for (i=0; i<n; i++){
        if(noeuds[i].priorite == 2 && noeuds[i].etat ==0){
            if(marge_KW >= noeuds[i].puissance_KW){
                noeuds[i].etat = 1;
                marge_KW -= noeuds[i].puissance_KW;

                // Enregistrement de l'evenement retablissement
                strcpy(events[*nb_events].type, "RETABLISSEMENT");
                strcpy(events[*nb_events].noeud_id, noeuds[i].id);
                strcpy(events[*nb_events].message, "Retablissement automatique");
                events[*nb_events].valeur = noeuds[i].puissance_KW;

                (*nb_events)++;


            }
        }
    }
    // Rétablissement des noeuds de priorité 3
    for(i=0; i<n; i++){
        if (noeuds[i].priorite == 3 && noeuds[i].etat == 0){
            if (marge_KW >= noeuds[i].puissance_KW){
                noeuds[i].etat = 1;

                marge_KW -= noeuds[i].puissance_KW;

                // Enregistrment de l'événement retablissement
                 strcpy(events[*nb_events].type, "RETABLISSEMENT");
                strcpy(events[*nb_events].noeud_id, noeuds[i].id);
                strcpy(events[*nb_events].message, "Retablissement automatique");
                events[*nb_events].valeur = noeuds[i].puissance_KW;

                (*nb_events)++;
            }
        }
    }
}

/*Cette fonction retourne le taux de charge en %. p_charge est la puissance consommér par les noeuds actifs  
p_dispo est la production disponible ( solaire + reseau)
Cette fonction génère une ALERTE CONSOLE si le taux est > 90%
ou une ALERTE CRITIQUE si le taux est > 100%.*/
float calcul_taux_charge_pct(float p_charge, float p_dispo){
    float taux;
    if(p_dispo <=0){
        return 0;  // puisqu'on va diviser par p_dispo , donc elle ne devrait pas etre nulle
    }
    taux = (p_charge/p_dispo) * 100;  // le calcul du taux de charge

    if (taux > 100){
        printf("ALERTE CRITIQUE!!! : surcharge du reseau\n"); // cas ou p_charge > p_dispo

    }
    else if (taux > 90){
        printf("Alerte : reseau charge a plus de 90%%\n");

    }
    return taux;
}

/*Cette fonction retourne la production totale disponible (solaire + réseau).
à une heure donnée.
Elle utilise une interpolation linéaire si heure ne correspond pas à un point exact*/
float calcul_production_disponible(PointCourbe courbe[], int n, int heure){
    int i;
    for(i=0; i<n; i++){
        
        if (courbe[i].heure == heure){ //Ici on cherche l'heure demandé
            
            return courbe[i].p_solaire_KW + courbe[i].p_reseau_KW; //aditionne product solaire + reseau 

        }

    }
    return 0;
}

