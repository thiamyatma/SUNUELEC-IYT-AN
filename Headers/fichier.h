#ifndef FICHIER_H
#define FICHIER_H
#include "structures.h"

// Structure pour le rapport bilan_JJ-MM-AAAA.txt
typedef struct {
    float prod_solaire;
    float prod_reseau;
    int nb_delestages;
    int nb_retablissements;
} DonneesBilan;

int sauvegarder_noeuds(const char *nom_fichier, Noeud *tableau, int n_noeud );
int charger_noeuds(const char *nom_fichier, Noeud *tableau, int n_noeud);

int enregistrer_courbe_charge(const char *nom_fichier, PointCourbe donnees);

int ajouter_evenement(const char *nom_fichier, const char *evenement);

int generer_bilan_journalier(const char *nom_fichier, const char *date, Noeud *noeuds, int n_noeud, DonneesBilan bilan);

#endif // FICHIER_H
