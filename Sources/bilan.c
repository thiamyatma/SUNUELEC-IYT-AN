#include <stdio.h>
#include <string.h>

#include "../Headers/bilan.h"

/*
    Consommation totale journalière.

    On utilise energie_kWh, déjà calculée par la
    simulation à partir de l'historique horaire.

    On ne regarde PAS l'état actuel : un noeud coupé
    après délestage a quand même consommé avant.
*/
float calcul_consommation_totale(
    Noeud noeuds[],
    int n_noeud
)
{
    float total = 0;

    for(int i = 0; i < n_noeud; i++)
    {
        total += noeuds[i].energie_kWh;
    }

    return total;
}


/*
    Production totale disponible sur la journée.

    Chaque point représente une heure :
    kw x 1 heure = kwh
*/
float calcul_production_totale(
    PointCourbe courbe[],
    int n_courbe
)
{
    float total = 0;

    for(int i = 0; i < n_courbe; i++)
    {
        total += courbe[i].p_solaire_kW +
                 courbe[i].p_reseau_kW;
    }

    return total;
}


/*
    Part du solaire dans la production disponible.

    (energie_solaire / energie_totale) * 100
*/
float calcul_taux_couverture_pv(
    PointCourbe courbe[],
    int n_courbe
)
{
    float solaire = 0;
    float totale  = 0;

    for(int i = 0; i < n_courbe; i++)
    {
        solaire += courbe[i].p_solaire_kW;

        totale  += courbe[i].p_solaire_kW +
                   courbe[i].p_reseau_kW;
    }

    if(totale <= 0)
    {
        return 0;
    }

    return (solaire / totale) * 100.0f;
}


/*
    Compte les événements d'un type donné.
*/
int compter_evenements(
    Evenement events[],
    int n_events,
    char type[]
)
{
    int compteur = 0;

    for(int i = 0; i < n_events; i++)
    {
        if(strcmp(events[i].type, type) == 0)
        {
            compteur++;
        }
    }

    return compteur;
}


/*
    Noeud ayant la plus grande consommation.

    Retour : NULL si le tableau est vide.
*/
Noeud* noeud_plus_consommateur(
    Noeud noeuds[],
    int n_noeud
)
{
    if(n_noeud <= 0)
    {
        return NULL;
    }

    int max = 0;

    for(int i = 1; i < n_noeud; i++)
    {
        if(noeuds[i].energie_kWh >
           noeuds[max].energie_kWh)
        {
            max = i;
        }
    }

    return &noeuds[max];
}


/*
    Noeud ayant la plus faible consommation.

    Retour : NULL si le tableau est vide.
*/
Noeud* noeud_moins_consommateur(
    Noeud noeuds[],
    int n_noeud
)
{
    if(n_noeud <= 0)
    {
        return NULL;
    }

    int min = 0;

    for(int i = 1; i < n_noeud; i++)
    {
        if(noeuds[i].energie_kWh <
           noeuds[min].energie_kWh)
        {
            min = i;
        }
    }

    return &noeuds[min];
}


void bilan_journalier(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int n_courbe,
    Evenement events[],
    int n_events
)
{
    int i;

    float consommation_totale =
        calcul_consommation_totale(noeuds, n_noeud);

    float production_totale =
        calcul_production_totale(courbe, n_courbe);

    float part_solaire_production =
        calcul_taux_couverture_pv(courbe, n_courbe);

    float production_solaire = 0;
    float production_reseau  = 0;

    for(i = 0; i < n_courbe; i++)
    {
        production_solaire += courbe[i].p_solaire_kW;

        production_reseau  += courbe[i].p_reseau_kW;
    }

    /*
        Part de la consommation réelle couverte
        par le solaire.
    */

    float couverture_conso_pv = 0;

    if(consommation_totale > 0)
    {
        couverture_conso_pv =
            (production_solaire / consommation_totale)
            * 100.0f;
    }

    printf("\n========== BILAN JOURNALIER ==========\n\n");

    printf(
        "Consommation totale : %.2f kwh\n",
        consommation_totale
    );

    printf(
        "Production solaire : %.2f kwh\n",
        production_solaire
    );

    printf(
        "Production reseau : %.2f kwh\n",
        production_reseau
    );

    printf(
        "Production totale disponible : %.2f kwh\n",
        production_totale
    );

    printf(
        "Part du solaire dans la production : %.2f %%\n",
        part_solaire_production
    );

    printf(
        "Couverture PV de la consommation : %.2f %%\n",
        couverture_conso_pv
    );

    /*
        Détail par noeud
    */

    printf(
        "\n====== CONSOMMATION PAR NOEUD ======\n"
    );

    for(i = 0; i < n_noeud; i++)
    {
        printf(
            "%s - %-12s : %8.2f kwh  [%s]\n",
            noeuds[i].id,
            noeuds[i].nom,
            noeuds[i].energie_kWh,
            noeuds[i].etat == 1 ? "ON " : "OFF"
        );
    }

    /*
        Extrêmes de consommation
    */

    Noeud *plus_gros =
        noeud_plus_consommateur(noeuds, n_noeud);

    Noeud *plus_faible =
        noeud_moins_consommateur(noeuds, n_noeud);

    if(plus_gros != NULL)
    {
        printf(
            "\nPlus gros consommateur : %s - %s : %.2f kwh\n",
            plus_gros->id,
            plus_gros->nom,
            plus_gros->energie_kWh
        );
    }

    if(plus_faible != NULL)
    {
        printf(
            "Plus faible consommateur : %s - %s : %.2f kwh\n",
            plus_faible->id,
            plus_faible->nom,
            plus_faible->energie_kWh
        );
    }

    /*
        Comptage événements
    */

    int nb_delestages =
        compter_evenements(events, n_events, "DELESTAGE");

    int nb_retablissements =
        compter_evenements(events, n_events, "RETABLISSEMENT");

    printf(
        "\nNombre de delestages : %d\n",
        nb_delestages
    );

    printf(
        "Nombre de retablissements : %d\n",
        nb_retablissements
    );

    /*
        Historique événements
    */

    printf(
        "\n========== HISTORIQUE EVENEMENTS ==========\n"
    );

    if(n_events == 0)
    {
        printf("\nAucun evenement enregistre.\n");
    }

    for(i = 0; i < n_events; i++)
    {
        printf(
            "\n[%s] %s - %s\n",
            events[i].horodatage,
            events[i].type,
            events[i].noeud_id
        );

        printf(
            "%s : %.2f kw\n",
            events[i].message,
            events[i].valeur
        );
    }
}
