#include <stdio.h>
#include <string.h>

#include "../Headers/menu.h"
#include "../Headers/affichage.h"
#include "../Headers/bilan.h"
#include "../Headers/simulation.h"
#include "../Headers/fichier.h"
#include "../Headers/initialisation.h"
#include "../Headers/supervision.h"

void vider_buffer(void)
{
    int c;

    while((c = getchar()) != '\n' &&
          c != EOF);
}


void afficher_menu(void)
{
    printf("\n===== SUPERVISION RESEAU ELECTRIQUE =====\n");

    printf("1. Charger configuration reseau\n");
    printf("2. Afficher etat actuel des noeuds\n");
    printf("3. Simuler une heure (avancer de 1h dans la courbe)\n");
    printf("4. Declencher delestage manuel (choix du noeud)\n");
    printf("5. Afficher bilan journalier\n");
    printf("6. Exporter rapport journalier\n");
    printf("7. Quitter\n");

    printf("Choix : ");
}


/*
    Ecrit dans le journal uniquement les evenements
    qui n'y ont pas encore ete ecrits.

    Sans ce compteur, l'historique complet etait
    reecrit a chaque simulation et le fichier se
    remplissait de doublons.
*/
static void journaliser_nouveaux_evenements(
    Evenement events[],
    int nb_events,
    int *deja_ecrits
)
{
    for(int i = *deja_ecrits; i < nb_events; i++)
    {
        ajouter_evenement_log(
            "donnees/evenements.log",
            events[i]
        );
    }

    *deja_ecrits = nb_events;
}


void gestion_choix(
    Noeud noeuds[],
    PointCourbe courbe[],
    Evenement events[],
    int *nb_events
)
{
    int choix;

    int heure = 0;

    int events_journalises = 0;

    do
    {
        afficher_menu();

        if(scanf("%d",&choix)!=1)
        {
            vider_buffer();

            printf("Choix invalide.\n");

            continue;
        }

        vider_buffer();

        switch(choix)
        {
        case 1:
        {
            /*
                Etat des noeuds : fichier binaire,
                ou configuration initiale si le
                fichier est absent ou incoherent.
            */

            if(charger_noeuds(
                "donnees/noeuds.dat",
                noeuds,
                NB_NOEUDS))
            {
                int actifs = 0;

                for(int i = 0; i < NB_NOEUDS; i++)
                {
                    if(noeuds[i].etat == 1)
                    {
                        actifs++;
                    }
                }

                printf(
                "Configuration chargee (%d/%d noeuds ON).\n",
                actifs,
                NB_NOEUDS
                );
            }

            else
            {
                printf(
                "Sauvegarde absente ou incoherente : "
                "creation configuration initiale.\n"
                );

                initialiser_noeuds(noeuds);

                sauvegarder_noeuds(
                    "donnees/noeuds.dat",
                    noeuds,
                    NB_NOEUDS
                );
            }

            /*
                Courbe de production : fichier CSV,
                ou courbe du cahier des charges si
                la lecture est incomplete.
            */

            int points =
                charger_courbe_csv(
                    "donnees/courbe_charge.csv",
                    courbe,
                    NB_POINTS_COURBE
                );

            if(points == NB_POINTS_COURBE)
            {
                printf(
                "Courbe de production chargee (%d points).\n",
                points
                );
            }
            else
            {
                printf(
                "Lecture CSV incomplete (%d/%d points) : "
                "courbe par defaut utilisee.\n",
                points,
                NB_POINTS_COURBE
                );

                initialiser_courbe(courbe);
            }

            break;
        }

        case 2:
        {
            afficherListeNoeuds(
                noeuds,
                NB_NOEUDS
            );

            break;
        }

        case 3:
        {
            simuler_heure(
                noeuds,
                NB_NOEUDS,
                courbe,
                heure,
                events,
                nb_events
            );

            sauvegarder_noeuds(
                "donnees/noeuds.dat",
                noeuds,
                NB_NOEUDS
            );

            journaliser_nouveaux_evenements(
                events,
                *nb_events,
                &events_journalises
            );

            heure++;

            if(heure >= NB_POINTS_COURBE)
                heure = 0;

            break;
        }

        case 4:
        {
            delestage_manuel(
                noeuds,
                NB_NOEUDS,
                events,
                nb_events
            );

            journaliser_nouveaux_evenements(
                events,
                *nb_events,
                &events_journalises
            );

            sauvegarder_noeuds(
                "donnees/noeuds.dat",
                noeuds,
                NB_NOEUDS
            );

            break;
        }

        case 5:
        {
            bilan_journalier(
                noeuds,
                NB_NOEUDS,
                courbe,
                NB_POINTS_COURBE,
                events,
                *nb_events
            );

            break;
        }

        case 6:
        {
            DonneesBilan bilan = {0};

            char date[11];

            char chemin[64];

            /*
                Le sujet impose un rapport nomme
                bilan_JJ-MM-AAAA.txt
            */

            obtenir_date_fichier(date);

            snprintf(
                chemin,
                sizeof(chemin),
                "donnees/bilan_%s.txt",
                date
            );

            for(int i=0;i<NB_POINTS_COURBE;i++)
            {
                bilan.prod_solaire +=
                    courbe[i].p_solaire_kW;

                bilan.prod_reseau +=
                    courbe[i].p_reseau_kW;
            }

            bilan.consommation_totale =
                calcul_consommation_totale(
                    noeuds,
                    NB_NOEUDS
                );

            /*
                Taux de couverture solaire au sens du sujet :
                part de la consommation reelle couverte par
                la production photovoltaique.
            */

            if(bilan.consommation_totale > 0)
            {
                bilan.taux_couverture_pv =
                    (bilan.prod_solaire /
                     bilan.consommation_totale) * 100.0f;
            }

            for(int i=0;i<*nb_events;i++)
            {
                if(strcmp(events[i].type,
                    "DELESTAGE")==0)
                {
                    bilan.nb_delestages++;
                }

                if(strcmp(events[i].type,
                    "RETABLISSEMENT")==0)
                {
                    bilan.nb_retablissements++;
                }
            }

            if(generer_bilan_journalier(
                chemin,
                date,
                noeuds,
                NB_NOEUDS,
                bilan))
            {
                printf(
                "Rapport genere : %s\n",
                chemin
                );
            }
            else
            {
                printf(
                "Erreur generation rapport.\n"
                );
            }

            break;
        }

        case 7:
        {
            printf(
            "Fermeture du programme.\n"
            );

            break;
        }

        default:
        {
            printf(
            "Choix invalide.\n"
            );
        }
        }

    }while(choix!=7);
}
