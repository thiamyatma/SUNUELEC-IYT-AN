#include <stdio.h>
#include <stdlib.h>
#include "Headers/structures.h"
#include "Headers/supervision.h"
#include <math.h>

/*Cette fonction somme et retourne les puissances 
de tous les noeuds à l'état ON*/ 
float calcul_puissance_totale(Noeud noeuds[], int n){

}

/*Cette fonction permet de couper les noeuds non critiques
(priorité 3 d'abord, puis 2) jusqu'a réabsorber le déficit
Elle retourne le nombre de noeuds coupés.
Chaque coupure est enregistrée dans le tableau d'évenement avec horodotage et raison*/
int delestage_automatique(Noeud noeuds[], int n, float deficit_KW, Evenement events[], int *nb_events);

/*Cette procedure permet de rétablir progressivement les noeuds délestés
dans l'ordre inverse (priorité d'abord) dès que la marge le permet.
Elle enregistre chaque rétablissement.
*/
void retablissement_progressif(Noeud noeuds[], int n, float marge_KW, Evenement events[], int *nb_events);

/*Cette fonction retourne le taux de charge en %. 
Elle génère une ALERTE CONSOLE si le taux est > 90%
ou une ALERTE CRITIQUE si le taux est > 100%.*/
float calcul_taux_charge_pct(float p_charge, float p_dispo);

