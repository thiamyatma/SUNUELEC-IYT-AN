#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

// 1. Sauvegarde et chargement binaire (noeuds.dat)
int sauvegarder_noeuds(const char *nom_fichier, Noeud *tableau, int n_noeud){
    FILE *file = fopen(nom_fichier, "wb");
    if (file == NULL) return 0;
    size_t ecrits = fwrite(tableau, sizeof(Noeud), (size_t)n_noeud, file);
    fclose(file);
    return (ecrits == (size_t)n_noeud);
}
int charger_noeuds(const char *nom_fichier, Noeud *tableau, int n_noeud){
    FILE *file = fopen(nom_fichier, "rb");
    if (file == NULL) return 0;
    size_t lus = fread(tableau, sizeof(Noeud), (size_t)n_noeud, file);
    fclose(file);
    return (lus == (size_t)n_noeud);
}

// 2. Écriture dans le CSV à partir de la structure CourbeCharge
int enregistrer_courbe_charge(const char *nom_fichier, CourbeCharge donnees) {
    FILE *file = fopen(nom_fichier, "w");
    if (file == NULL) return 0;
    fprintf(file, "heure,p_solaire,p_reseau\n");
    fprintf(file, "%d,%.1f,%.1f\n", donnees.heure, donnees.p_solaire, donnees.p_reseau);
    fclose(file);
    return 1;
}

// 3. Journalisation (evenements.log)
int ajouter_evenement(const char *nom_fichier, const char *evenement) {
    FILE *file = fopen(nom_fichier, "a");
    if (file == NULL) return 0;

    fprintf(file, "%s\n", evenement);
    fclose(file);
    return 1;
}

// 4. Génération du rapport TXT formaté à partir des structures Noeud et DonneesBilan
int generer_bilan_journalier(const char *nom_fichier, const char *date, Noeud *noeuds, int n_noeud, DonneesBilan bilan) {
    FILE *file = fopen(nom_fichier, "w");
    if (file == NULL) return 0;

    double conso_totale = 0.0;
    fprintf(file, "========================================\n");
    fprintf(file, "BILAN ÉNERGÉTIQUE - %s\n", date);
    fprintf(file, "========================================\n\n");
    fprintf(file, "CONSOMMATION PAR NŒUD (kWh)\n");
    for (int i = 0; i < n_noeud; i++){
        fprintf(file, "%-3s %-16s : %5.1f kWh\n", noeuds[i].id, noeuds[i].nom, noeuds[i].consommation);
        conso_totale += noeuds[i].consommation;
    }
    fprintf(file, "...\n\n");

    double total_dispo = bilan.prod_solaire + bilan.prod_reseau;
    fprintf(file, "PRODUCTION TOTALE\n");
    fprintf(file, "%-19s : %5.1f kWh\n", "Solaire", bilan.prod_solaire);
    fprintf(file, "%-19s : %5.1f kWh\n", "Réseau national", bilan.prod_reseau);
    fprintf(file, "%-19s : %5.1f kWh\n\n", "Total disponible", total_dispo);

    double taux_pv = (total_dispo > 0) ? (bilan.prod_solaire / total_dispo) * 100.0 : 0.0;
    fprintf(file, "STATISTIQUES\n");
    fprintf(file, "%-19s : %5.1f kWh\n", "Consommation totale", conso_totale);
    fprintf(file, "%-19s : %5.1f %%\n", "Taux couverture PV", taux_pv);
    fprintf(file, "%-19s : %8d\n", "Nb délestages", bilan.nb_delestages);
    fprintf(file, "%-19s : %8d\n", "Nb rétablissements", bilan.nb_retablissements);
    fprintf(file, "Sauvegarder bilan : OK\n");
    fprintf(file, "========================================\n");

    fclose(file);
    return 1;
}
