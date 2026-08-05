#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/fichier.h"

/*
    Chargement d'une courbe depuis un fichier CSV

    Format attendu :

    heure,solaire,reseau

    Exemple :
    0,0,15
    1,0,14.8
*/

int charger_courbe_csv(
    const char *nom_fichier,
    PointCourbe courbe[],
    int n_courbe
)
{
    FILE *fichier;

    fichier = fopen(nom_fichier, "r");

    if(fichier == NULL)
    {
        return 0;
    }

    int compteur = 0;

    while(compteur < n_courbe)
    {
        int heure;
        float solaire;
        float reseau;

        if(fscanf(
                fichier,
                "%d,%f,%f",
                &heure,
                &solaire,
                &reseau
            ) != 3)
        {
            break;
        }

        courbe[compteur].heure = heure;

        courbe[compteur].p_solaire_kW = solaire;

        courbe[compteur].p_reseau_kW = reseau;

        courbe[compteur].p_charge_kW = 0;

        courbe[compteur].taux_charge = 0;

        compteur++;
    }

    fclose(fichier);

    return compteur;
}


/*
    Sauvegarde binaire des noeuds
*/

int sauvegarder_noeuds(
    const char *nom_fichier,
    Noeud tableau[],
    int n_noeud
)
{
    FILE *fichier;

    fichier = fopen(
        nom_fichier,
        "wb"
    );

    if(fichier == NULL)
    {
        return 0;
    }

    size_t ecrits =
        fwrite(
            tableau,
            sizeof(Noeud),
            n_noeud,
            fichier
        );

    fclose(fichier);

    if(ecrits == (size_t)n_noeud)
    {
        return 1;
    }

    return 0;
}


/*
    Chargement binaire des noeuds
*/

int charger_noeuds(
    const char *nom_fichier,
    Noeud tableau[],
    int n_noeud
)
{
    FILE *fichier;

    fichier = fopen(
        nom_fichier,
        "rb"
    );

    if(fichier == NULL)
    {
        return 0;
    }

    size_t lus =
        fread(
            tableau,
            sizeof(Noeud),
            n_noeud,
            fichier
        );

    fclose(fichier);

    if(lus != (size_t)n_noeud)
    {
        return 0;
    }

    /*
        On verifie ce qu'on relit.

        Un vieux fichier .dat ecrit avant qu'on modifie la
        structure Noeud peut avoir la bonne taille mais
        contenir n'importe quoi. Dans ce cas on refuse le
        chargement et l'appelant repart d'un reseau neuf.
    */

    for(int i = 0; i < n_noeud; i++)
    {
        tableau[i].id[sizeof(tableau[i].id) - 1]   = '\0';
        tableau[i].nom[sizeof(tableau[i].nom) - 1] = '\0';

        if(tableau[i].id[0] != 'N' ||
           tableau[i].puissance_kW <= 0.0f ||
           tableau[i].priorite < 1 ||
           tableau[i].priorite > 3 ||
           (tableau[i].etat != 0 && tableau[i].etat != 1))
        {
            return 0;
        }
    }

    return 1;
}


/*
    Ajout d'un événement dans un fichier log
*/

int ajouter_evenement_log(
    const char *nom_fichier,
    Evenement event
)
{
    FILE *fichier;

    fichier = fopen(
        nom_fichier,
        "a"
    );

    if(fichier == NULL)
    {
        return 0;
    }

    fprintf(
        fichier,
        "%s | %s | %s | %s | %.2f kw\n",
        event.horodatage,
        event.type,
        event.noeud_id,
        event.message,
        event.valeur
    );

    fclose(fichier);

    return 1;
}


/*
    Génération du rapport journalier
*/

int generer_bilan_journalier(
    const char *nom_fichier,
    const char *date,
    Noeud noeuds[],
    int n_noeud,
    DonneesBilan bilan
)
{
    FILE *fichier;

    fichier = fopen(
        nom_fichier,
        "w"
    );

    if(fichier == NULL)
    {
        return 0;
    }

    /*
        Mise en page reprise du modele du sujet.
    */

    fprintf(
        fichier,
        "========================================\n"
    );

    fprintf(
        fichier,
        "BILAN ENERGETIQUE - %s\n",
        date
    );

    fprintf(
        fichier,
        "========================================\n\n"
    );

    fprintf(
        fichier,
        "CONSOMMATION PAR NOEUD (kWh)\n"
    );

    for(int i = 0; i < n_noeud; i++)
    {
        fprintf(
            fichier,
            "%s %s : %.1f kWh\n",
            noeuds[i].id,
            noeuds[i].nom,
            noeuds[i].energie_kWh
        );
    }

    fprintf(
        fichier,
        "\nPRODUCTION TOTALE\n"
    );

    fprintf(
        fichier,
        "Solaire : %.1f kWh\n",
        bilan.prod_solaire
    );

    fprintf(
        fichier,
        "Reseau national : %.1f kWh\n",
        bilan.prod_reseau
    );

    fprintf(
        fichier,
        "Total disponible : %.1f kWh\n",
        bilan.prod_solaire +
        bilan.prod_reseau
    );

    fprintf(
        fichier,
        "\nSTATISTIQUES\n"
    );

    fprintf(
        fichier,
        "Consommation totale: %.1f kWh\n",
        bilan.consommation_totale
    );

    fprintf(
        fichier,
        "Taux couverture PV : %.1f %%\n",
        bilan.taux_couverture_pv
    );

    fprintf(
        fichier,
        "Nb delestages : %d\n",
        bilan.nb_delestages
    );

    fprintf(
        fichier,
        "Nb retablissements : %d\n",
        bilan.nb_retablissements
    );

    fprintf(
        fichier,
        "Sauvegarder bilan : OK\n"
    );

    fprintf(
        fichier,
        "========================================\n"
    );

    fclose(fichier);

    return 1;
}
