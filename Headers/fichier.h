#ifndef FICHIER_H
#define FICHIER_H

// 1. Structure pour noeuds.dat
typedef struct {
    char id[4];
    char nom[30];
    float consommation;
} Noeud;

// 2. Structure pour courbe_charge.csv
typedef struct {
    int heure;
    double p_solaire;
    double p_reseau;
} CourbeCharge;

// 3. Structure pour le rapport bilan_JJ-MM-AAAA.txt
typedef struct {
    double prod_solaire;
    double prod_reseau;
    int nb_delestages;
    int nb_retablissements;
} DonneesBilan;

int sauvegarder_noeuds(const char *nom_fichier, Noeud *tableau, int n_noeud );
int charger_noeuds(const char *nom_fichier, Noeud *tableau, int n_noeud);

int enregistrer_courbe_charge(const char *nom_fichier, CourbeCharge donnees);

int ajouter_evenement(const char *nom_fichier, const char *evenement);

int generer_bilan_journalier(const char *nom_fichier, const char *date, Noeud *noeuds, int n_noeud, DonneesBilan bilan);

#endif // FICHIER_H
