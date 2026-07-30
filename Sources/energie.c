#include <stdio.h>
#include <stdlib.h>
#include "../Headers/structures.h" //je remonte d'un dossier

/*Cette fonction intergre la consommation d'un noeuds sur 24h ( Methode des trapèze)
Elle retourne L'énergie en KiloWatt Heure (KWH).*/
float calcul_energie_noeud(Noeud *noeud, PointCourbe courbe[], int n){
    float energie = 0;
    int i;

    for(i=0; i< n-1; i++){
        float puissance1 = 0;
        float puissance2 = 0;

        // le noeud consomme uiniquement s'il est à ON
        if(noeud->etat == 1){
            puissance1 = noeud->puissance_KW;
            puissance2 = noeud->puissance_KW;

            // Methode des trapèze
            energie += ((puissance1 + puissance2)/2)*(courbe[i+1].heure - courbe[i].heure);

        }
        
    }
    return energie;
}

/*Cette procedure Met à jour le champ energie_KWh de chaque noeud*/
void calculer_energie_tous_noeuds(Noeud noeuds[], int n_noeud, PointCourbe courbe[], int n_courbe){
    int i;

    for(i=0; i<n_noeud; i++){
        noeuds[i].energie_KWh = calcul_energie_noeud(&noeuds[i], courbe, n_courbe);
    }

}

