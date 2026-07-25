#include <stdio.h>
#include <stdlib.h>
#include "Headers/structures.h"

/*Cette fonction intergre la consommation d'un noeuds sur 24h ( Methode des trapèze)
Elle retourne L'énergie en KiloWatt Heure (KWH).*/
float calcul_energie_noeud(Noeud *noeud, PointCourbe courbe[], int n);

/*Cette procedure Met à jour le champ energie_KWh de chaque noeud*/
void calculer_energie_tous_noeuds(Noeud noeuds[], int n_noeud, PointCourbe courbe[], int n_courbe);

/*Cette fonction retourne la production totale disponible (solaire + réseau).
à une heure donnée.
Elle utilise une interpolation linéaire si heure ne correspond pas à un point exact*/
float calcul_production_disponible(PointCourbe courbe[], int n, int heure);