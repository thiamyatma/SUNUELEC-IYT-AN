#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "fichier.h"

void afficherEnteteEcran(const char* titre);
void afficherUnNoeudEcran(const Noeud* noeud, float puissance_inst);
void afficherSupervisionGlobale(const Noeud tableauNoeuds[], int nb_noeuds, const float puissances_inst[], DonneesBilan bilan);
void afficherListeNoeuds(Noeud noeuds[], int n);

#endif // AFFICHAGE_H
