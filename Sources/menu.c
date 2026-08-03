#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../Headers/menu.h"
#include "../Headers/affichage.h"
#include "../Headers/bilan.h"
#include "../Headers/simulation.h"
#include "../Headers/fichier.h"
#include "../Headers/initialisation.h"
#include "../Headers/supervision.h"
#include "../Headers/tri.h"
#include "../Headers/recherche.h"



void vider_buffer(void)
{
    int c;

    while((c = getchar()) != '\n' &&
          c != EOF);
}






void afficher_menu(void)
{

    printf("\n========== SUPERVISION RESEAU ELECTRIQUE ==========\n");

    printf("1. Charger configuration reseau\n");
    printf("2. Afficher etat actuel des noeuds\n");
    printf("3. Simuler une heure\n");
    printf("4. Delestage manuel\n");
    printf("5. Afficher bilan journalier\n");
    printf("6. Exporter rapport journalier\n");
    printf("7. Rechercher un noeud\n");
    printf("8. Trier les noeuds par consommation\n");
    printf("9. Quitter\n");
    printf("10. Simuler une journee complete (24h)\n");
    printf("11. Reinitialiser le reseau\n");
    printf("12. Charger la courbe de production (CSV)\n");

    printf("Votre choix : ");

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


                printf(
                "Note : etats et energies proviennent de la "
                "sauvegarde precedente.\n"
                "Utiliser le choix 11 pour repartir d'un reseau neuf.\n"
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
                Initialisation courbe production
            */

            initialiser_courbe(courbe);



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


            printf(
                "\nSimulation heure %d\n",
                heure
            );


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



            /*
                Sauvegarde historique événements
            */

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

            char date[20];



            obtenir_horodatage(date);



            for(int i=0;i<NB_POINTS_COURBE;i++)
            {

                bilan.prod_solaire +=
                    courbe[i].p_solaire_kw;


                bilan.prod_reseau +=
                    courbe[i].p_reseau_kw;

            }



            bilan.consommation_totale =
                calcul_consommation_totale(
                    noeuds,
                    NB_NOEUDS
                );


            bilan.taux_couverture_pv =
                calcul_taux_couverture_pv(
                    courbe,
                    NB_POINTS_COURBE
                );




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
                "donnees/bilan_journalier.txt",
                date,
                noeuds,
                NB_NOEUDS,
                bilan))
            {

                printf(
                "Rapport genere.\n"
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


            char id[4];


            printf(
                "ID du noeud : "
            );


            scanf("%3s",id);



            Noeud *n =
            recherche_noeud_par_id(
                noeuds,
                NB_NOEUDS,
                id
            );



            if(n)
            {

                printf(
                "%s - %s : %.2f kw\n",
                n->id,
                n->nom,
                n->puissance_kw
                );

            }
            else
            {

                printf(
                "Noeud introuvable.\n"
                );

            }



            break;

        }







        case 8:
        {


            trier_noeuds_par_consommation(
                noeuds,
                NB_NOEUDS
            );


            afficherListeNoeuds(
                noeuds,
                NB_NOEUDS
            );


            break;

        }







        case 9:
        {

            printf(
            "Fermeture du programme.\n"
            );


            break;

        }




        case 10:
        {


            simuler_journee(
                noeuds,
                NB_NOEUDS,
                courbe,
                events,
                nb_events
            );


            heure = 0;


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




        case 11:
        {

            /*
                Repart d'un reseau neuf :
                tous les noeuds ON, energie a 0.
            */

            initialiser_noeuds(noeuds);

            initialiser_courbe(courbe);


            *nb_events = 0;

            events_journalises = 0;

            heure = 0;


            sauvegarder_noeuds(
                "donnees/noeuds.dat",
                noeuds,
                NB_NOEUDS
            );


            printf(
            "Reseau reinitialise : %d noeuds ON, energie a 0.\n",
            NB_NOEUDS
            );


            break;

        }




        case 12:
        {

            int points =
                charger_courbe_csv(
                    "donnees/courbe.csv",
                    courbe,
                    NB_POINTS_COURBE
                );


            if(points == NB_POINTS_COURBE)
            {

                printf(
                "Courbe chargee depuis donnees/courbe.csv "
                "(%d points).\n",
                points
                );

            }
            else
            {

                /*
                    Fichier absent ou incomplet :
                    on repart de la courbe du cahier
                    des charges pour ne pas simuler
                    avec des donnees partielles.
                */

                printf(
                "Lecture CSV incomplete (%d/%d points) : "
                "courbe par defaut rechargee.\n",
                points,
                NB_POINTS_COURBE
                );


                initialiser_courbe(courbe);

            }


            break;

        }







        default:
        {

            printf(
            "Choix invalide.\n"
            );

        }


        }



    }while(choix!=9);



}