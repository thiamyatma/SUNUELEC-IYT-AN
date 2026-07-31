#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "gestion_fichier.h"

void afficherEnteteEcran(const char* titre);
void afficherUnNoeudEcran(const Noeud* noeud, float puissance_inst);
void afficherSupervisionGlobale(const Noeud tableauNoeuds[], int nb_noeuds, const float puissances_inst[], DonneesBilan bilan);

#endif // AFFICHAGE_H
