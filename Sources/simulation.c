#include <stdio.h>

#include "../Headers/structures.h"
#include "../Headers/simulation.h"
#include "../Headers/supervision.h"
#include "../Headers/energie.h"

void simuler_heure(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int heure,
    Evenement events[],
    int *nb_events
)
{
    float production_disponible;
    float puissance_charge;
    float taux_charge;

    if(heure < 0 || heure >= NB_POINTS_COURBE)
    {
        printf("Heure invalide : %d\n", heure);
        return;
    }

    printf("\n====== SIMULATION %dh ======\n", heure);

    /*
        1) Calcul de la production disponible
    */

    production_disponible =
        calcul_production_disponible(
            courbe,
            NB_POINTS_COURBE,
            heure
        );

    /*
        2) Calcul de la consommation actuelle
           uniquement des noeuds ON
    */

    puissance_charge =
        calcul_puissance_totale(
            noeuds,
            n_noeud
        );

    /*
        3) Calcul taux de charge
    */

    taux_charge =
        calcul_taux_charge_pct(
            puissance_charge,
            production_disponible
        );

    printf(
        "Production disponible : %.2f kW\n",
        production_disponible
    );

    printf(
        "Charge totale         : %.2f kW\n",
        puissance_charge
    );

    printf(
        "Taux de charge        : %.2f %%\n",
        taux_charge
    );

    /*
        Toute alerte est affichee ET archivee : la section VI.3
        du cahier des charges demande que le journal contienne
        les alertes au meme titre que les delestages.
    */

    if(taux_charge > SEUIL_DELESTAGE_PCT)
    {
        printf(
            "ALERTE CRITIQUE : surcharge reseau %.2f %%\n",
            taux_charge
        );

        ajouter_evenement(
            events,
            nb_events,
            "ALERTE",
            "SYS",
            "Surcharge critique du reseau",
            taux_charge
        );
    }
    else if(taux_charge > SEUIL_ALERTE_PCT)
    {
        printf(
            "ALERTE : reseau charge a %.2f %%\n",
            taux_charge
        );

        ajouter_evenement(
            events,
            nb_events,
            "ALERTE",
            "SYS",
            "Seuil d'alerte franchi",
            taux_charge
        );
    }

    /*
        4) Cas surcharge
    */

    if(taux_charge > SEUIL_DELESTAGE_PCT)
    {
        float deficit;

        deficit =
            puissance_charge -
            production_disponible;

        printf(
            "\nALERTE : surcharge reseau\n"
        );

        printf(
            "Deficit : %.2f kW\n",
            deficit
        );

        delestage_automatique(
            noeuds,
            n_noeud,
            deficit,
            events,
            nb_events
        );
    }

    /*
        5) Recalcul apres delestage
    */

    puissance_charge =
        calcul_puissance_totale(
            noeuds,
            n_noeud
        );

    taux_charge =
        calcul_taux_charge_pct(
            puissance_charge,
            production_disponible
        );

    /*
        6) Retablissement automatique

        La marge utilisable n'est pas toute la production
        restante : on vise le seuil d'alerte (90 %) pour
        ne pas repasser en surcharge a l'heure suivante.
    */

    if(taux_charge < SEUIL_ALERTE_PCT)
    {
        float marge;

        marge =
            production_disponible *
            (SEUIL_ALERTE_PCT / 100.0f) -
            puissance_charge;

        if(marge > 0)
        {
            retablissement_progressif(
                noeuds,
                n_noeud,
                marge,
                events,
                nb_events
            );

            /*
                Recalcul apres retablissement
            */

            puissance_charge =
                calcul_puissance_totale(
                    noeuds,
                    n_noeud
                );

            taux_charge =
                calcul_taux_charge_pct(
                    puissance_charge,
                    production_disponible
                );
        }
    }

    /*
        7) Controle du facteur de puissance
    */

    verifier_facteur_puissance(
        noeuds,
        n_noeud,
        events,
        nb_events
    );

    /*
        8) Sauvegarde de l'etat final dans la courbe

        Enregistre apres delestage et retablissement,
        pour refleter la charge reellement alimentee.
    */

    courbe[heure].p_charge_kW =
        puissance_charge;

    courbe[heure].taux_charge =
        taux_charge;

    /*
        9) Enregistrement de la consommation de l'heure
           puis mise a jour de l'energie
    */

    enregistrer_consommation_horaire(
        noeuds,
        n_noeud,
        heure
    );

    calculer_energie_tous_noeuds(
        noeuds,
        n_noeud,
        NB_POINTS_COURBE
    );

    printf(
        "\nEtat final : %.2f kW alimentes (%.2f %%)\n",
        puissance_charge,
        taux_charge
    );

    printf(
        "Simulation terminee.\n"
    );
}
