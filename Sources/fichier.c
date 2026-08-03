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

        courbe[compteur].p_solaire_kw = solaire;

        courbe[compteur].p_reseau_kw = reseau;

        courbe[compteur].p_charge_kw = 0;

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
        Validation du contenu.

        Un fichier ecrit par une version anterieure du
        programme (structure Noeud differente) peut avoir
        la bonne taille mais un contenu incoherent.
        On refuse alors le chargement pour que l'appelant
        reinitialise proprement le reseau.
    */

    for(int i = 0; i < n_noeud; i++)
    {

        tableau[i].id[sizeof(tableau[i].id) - 1]   = '\0';
        tableau[i].nom[sizeof(tableau[i].nom) - 1] = '\0';


        if(tableau[i].id[0] != 'N' ||
           tableau[i].puissance_kw <= 0.0f ||
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




    fprintf(
        fichier,
        "========== RAPPORT JOURNALIER ==========\n"
    );


    fprintf(
        fichier,
        "Date : %s\n\n",
        date
    );



    fprintf(
        fichier,
        "Production solaire : %.2f kwh\n",
        bilan.prod_solaire
    );


    fprintf(
        fichier,
        "Production reseau : %.2f kwh\n",
        bilan.prod_reseau
    );


    fprintf(
        fichier,
        "Production totale : %.2f kwh\n",
        bilan.prod_solaire +
        bilan.prod_reseau
    );


    fprintf(
        fichier,
        "Consommation totale : %.2f kwh\n",
        bilan.consommation_totale
    );


    fprintf(
        fichier,
        "Part du solaire dans la production : %.2f %%\n\n",
        bilan.taux_couverture_pv
    );




    fprintf(
        fichier,
        "====== CONSOMMATION DES NOEUDS ======\n"
    );



    for(int i = 0; i < n_noeud; i++)
    {

        fprintf(
            fichier,
            "%s - %s : %.2f kwh\n",
            noeuds[i].id,
            noeuds[i].nom,
            noeuds[i].energie_kwh
        );

    }




    fprintf(
        fichier,
        "\n====== STATISTIQUES ======\n"
    );


    fprintf(
        fichier,
        "Nombre delestages : %d\n",
        bilan.nb_delestages
    );


    fprintf(
        fichier,
        "Nombre retablissements : %d\n",
        bilan.nb_retablissements
    );



    fclose(fichier);



    return 1;

}