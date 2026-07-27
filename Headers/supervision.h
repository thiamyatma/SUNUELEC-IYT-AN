#ifndef SUPERVISION_H
#define SUPERVISION_H
#include "structures.h"

/*Contrat d'opération ,
 c'est à dire la déclarations de toutes les fonctions et procédures
  dont on a besoin pour la supervision*/
float calcul_puissance_totale(Noeud noeuds[], int n);
float calcul_production_disponible(PointCourbe courbe[], int n, int heure);
int delestage_automatique(Noeud noeuds[], int n, float deficit_KW, Evenement events[], int *nb_events);
void retablissement_progressif(Noeud noeuds[], int n, float marge_KW, Evenement events[], int *nb_events);
float calcul_taux_charge_pct(float p_charge, float p_dispo);

#endif // SUPERVISION_H