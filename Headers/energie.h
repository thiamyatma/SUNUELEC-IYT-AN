#ifndef ENERGIE_H
#define ENERGIE_H
#include "structures.h"
/*Le contrat d'opération qui permet la declaration de toutes les fonctions et procédure
 liées à energie.On pourra ensuite appeller ces fonctions dans les fichiers .c pour les utiliser*/

float calcul_energie_noeud(Noeud *noeud, PointCourbe courbe[], int n);
void calculer_energie_tous_noeuds(Noeud noeuds[], int n_noeud, PointCourbe courbe[], int n_courbe);


#endif // ENERGIE_H