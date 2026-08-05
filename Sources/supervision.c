#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../Headers/structures.h"
#include "../Headers/supervision.h"
#include "../Headers/recherche.h"

/* Création d'un horodatage dynamique */
void obtenir_horodatage(char date[])
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    strftime(date, 20, "%d/%m/%Y %H:%M", tm_info);
}


/* Date seule au format JJ-MM-AAAA, pour nommer le rapport */
void obtenir_date_fichier(char date[])
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    strftime(date, 11, "%d-%m-%Y", tm_info);
}


/*
    Ajout sécurisé d'un événement

    strncpy ne termine pas la chaîne lorsque la source
    remplit exactement le tampon : on force le '\0'.
*/
void ajouter_evenement(
    Evenement events[],
    int *nb_events,
    const char type[],
    const char id[],
    const char message[],
    float valeur
)
{
    if(*nb_events >= MAX_EVENTS)
    {
        printf("Limite maximale d'evenements atteinte.\n");
        return;
    }

    Evenement *e = &events[*nb_events];

    obtenir_horodatage(e->horodatage);

    strncpy(e->type, type, sizeof(e->type) - 1);
    e->type[sizeof(e->type) - 1] = '\0';

    strncpy(e->noeud_id, id, sizeof(e->noeud_id) - 1);
    e->noeud_id[sizeof(e->noeud_id) - 1] = '\0';

    strncpy(e->message, message, sizeof(e->message) - 1);
    e->message[sizeof(e->message) - 1] = '\0';

    e->valeur = valeur;

    (*nb_events)++;
}


/*
    Calcule la puissance totale active
    uniquement des noeuds ON

    Fonction de calcul pur : les alertes cos_phi
    sont traitées par verifier_facteur_puissance().
*/
float calcul_puissance_totale(Noeud noeuds[], int n)
{
    float somme = 0;

    for(int i = 0; i < n; i++)
    {
        if(noeuds[i].etat == 1)
        {
            somme += noeuds[i].puissance_kW;
        }
    }

    return somme;
}


/*
    Contrôle du facteur de puissance.

    Génère une alerte et un événement pour chaque
    noeud actif dont le cos_phi est inférieur au
    minimum admis (0.85).
*/
void verifier_facteur_puissance(
    Noeud noeuds[],
    int n,
    Evenement events[],
    int *nb_events
)
{
    for(int i = 0; i < n; i++)
    {
        if(noeuds[i].etat == 1 &&
           noeuds[i].cos_phi < COS_PHI_MIN)
        {
            printf(
                "Attention : facteur de puissance faible pour %s (%.2f)\n",
                noeuds[i].id,
                noeuds[i].cos_phi
            );

            ajouter_evenement(
                events,
                nb_events,
                "COS_PHI",
                noeuds[i].id,
                "Facteur de puissance insuffisant",
                noeuds[i].cos_phi
            );
        }
    }
}


/*
    Recherche du noeud à couper dans une priorité donnée.

    Stratégie :
    1) le plus petit noeud qui couvre à lui seul le déficit
       (évite de couper plus que nécessaire) ;
    2) sinon le plus gros noeud disponible, pour réduire le
       déficit au plus vite et limiter le nombre de coupures.

    Retour : index du noeud, -1 si aucun candidat.
*/
int trouver_noeud_a_couper(
    Noeud noeuds[],
    int n,
    int priorite,
    float deficit
)
{
    int index = -1;
    float puissance_min = 0;

    /* 1) plus petit noeud couvrant le déficit */
    for(int i = 0; i < n; i++)
    {
        if(noeuds[i].priorite == priorite &&
           noeuds[i].etat == 1 &&
           noeuds[i].puissance_kW >= deficit)
        {
            if(index == -1 ||
               noeuds[i].puissance_kW < puissance_min)
            {
                puissance_min = noeuds[i].puissance_kW;
                index = i;
            }
        }
    }

    if(index != -1)
    {
        return index;
    }

    /* 2) sinon, le plus gros noeud disponible */
    float puissance_max = 0;

    for(int i = 0; i < n; i++)
    {
        if(noeuds[i].priorite == priorite &&
           noeuds[i].etat == 1)
        {
            if(index == -1 ||
               noeuds[i].puissance_kW > puissance_max)
            {
                puissance_max = noeuds[i].puissance_kW;
                index = i;
            }
        }
    }

    return index;
}


/*
    Délestage automatique

    Ordre :
    priorité 3 puis priorité 2.

    La priorité 1 (services critiques) n'est jamais
    coupée automatiquement.
*/
int delestage_automatique(
    Noeud noeuds[],
    int n,
    float deficit_kW,
    Evenement events[],
    int *nb_events
)
{
    int compteur = 0;

    /* marge de 0.001 kW : évite une boucle sur un résidu flottant */
    while(deficit_kW > 0.001f)
    {
        int index = trouver_noeud_a_couper(
            noeuds,
            n,
            3,
            deficit_kW
        );

        if(index == -1)
        {
            index = trouver_noeud_a_couper(
                noeuds,
                n,
                2,
                deficit_kW
            );
        }

        /*
            Plus aucune charge délestable :
            seules les charges critiques restent.
        */
        if(index == -1)
        {
            printf(
                "Surcharge persistante : %.2f kW non couverts "
                "(charges critiques conservees).\n",
                deficit_kW
            );

            ajouter_evenement(
                events,
                nb_events,
                "SURCHARGE",
                "SYS",
                "Deficit residuel apres delestage",
                deficit_kW
            );

            break;
        }

        noeuds[index].etat = 0;

        deficit_kW -= noeuds[index].puissance_kW;

        printf(
            "DELESTAGE : %s - %s (%.2f kW)\n",
            noeuds[index].id,
            noeuds[index].nom,
            noeuds[index].puissance_kW
        );

        ajouter_evenement(
            events,
            nb_events,
            "DELESTAGE",
            noeuds[index].id,
            "Coupure automatique",
            noeuds[index].puissance_kW
        );

        compteur++;
    }

    return compteur;
}

 /*
    Rétablissement progressif

    Objectif :
    rester sous le seuil d'alerte (90 %)
    afin d'éviter les oscillations ON/OFF.
    La marge reçue est déjà plafonnée par l'appelant.

    Ordre :
    priorité 1 (critique) puis 2 puis 3.
*/
void retablissement_progressif(
    Noeud noeuds[],
    int n_noeud,
    float marge_kW,
    Evenement events[],
    int *nb_events
)
{
    int retablis = 0;

    for(int priorite = 1; priorite <= 3; priorite++)
    {
        for(int i = 0; i < n_noeud; i++)
        {
            /*
                On cherche uniquement
                les noeuds coupés
            */

            if(noeuds[i].etat == 0 &&
               noeuds[i].priorite == priorite)
            {
                /*
                    Vérification de la marge disponible
                */

                if(marge_kW >= noeuds[i].puissance_kW)
                {
                    if(retablis == 0)
                    {
                        printf(
                        "\n====== RETABLISSEMENT PROGRESSIF ======\n"
                        );
                    }

                    noeuds[i].etat = 1;

                    marge_kW -= noeuds[i].puissance_kW;

                    retablis++;

                    printf(
                    "RETABLISSEMENT : %s - %s (%.2f kW)\n",
                    noeuds[i].id,
                    noeuds[i].nom,
                    noeuds[i].puissance_kW
                    );

                    /*
                        Enregistrement événement

                        On passe par ajouter_evenement() pour
                        obtenir l'horodatage et des chaînes
                        correctement terminées.
                    */

                    ajouter_evenement(
                        events,
                        nb_events,
                        "RETABLISSEMENT",
                        noeuds[i].id,
                        "Retablissement automatique",
                        noeuds[i].puissance_kW
                    );
                }
            }
        }
    }
}


/*
    Calcul du taux de charge du réseau

    Formule :
    taux = (charge / production disponible) * 100

    >90%  : avertissement
    >100% : surcharge
*/
float calcul_taux_charge_pct(
    float p_charge,
    float p_dispo
)
{
    if(p_dispo <= 0)
    {
        return 0;
    }

    float taux = (p_charge / p_dispo) * 100;

    return taux;
}


/*
    Calcul de la production disponible

    Retour :
    solaire + réseau

    Gestion :
    - heure exacte
    - interpolation linéaire
*/
float calcul_production_disponible(
    PointCourbe courbe[],
    int n,
    int heure
)
{
    /* Recherche exacte */
    for(int i = 0; i < n; i++)
    {
        if(courbe[i].heure == heure)
        {
            return courbe[i].p_solaire_kW +
                   courbe[i].p_reseau_kW;
        }
    }

    /* Interpolation */
    for(int i = 0; i < n - 1; i++)
    {
        if(heure > courbe[i].heure &&
           heure < courbe[i+1].heure)
        {
            float p1 =
                courbe[i].p_solaire_kW +
                courbe[i].p_reseau_kW;

            float p2 =
                courbe[i+1].p_solaire_kW +
                courbe[i+1].p_reseau_kW;

            float h1 = courbe[i].heure;
            float h2 = courbe[i+1].heure;

            return p1 +
            ((p2 - p1) / (h2 - h1))
            * (heure - h1);
        }
    }

    return 0;
}


/*
    Délestage manuel

    Coupe un noeud choisi par l'utilisateur.
*/
void delestage_manuel(
    Noeud noeuds[],
    int n,
    Evenement events[],
    int *nb_events
)
{
    char id[4];

    printf("\n===== DELESTAGE MANUEL =====\n");
    printf("Entrer l'identifiant du noeud (ex N05) : ");

    /*
       Protection contre dépassement mémoire
    */
    if(scanf("%3s", id) != 1)
    {
        printf("Saisie invalide.\n");
        return;
    }

    /*
       La recherche est deleguee au module recherche,
       pour ne pas dupliquer le parcours du tableau.
    */
    Noeud *noeud = recherche_noeud_par_id(noeuds, n, id);

    if(noeud == NULL)
    {
        printf("Noeud introuvable.\n");
        return;
    }

    if(noeud->etat == 0)
    {
        printf("Noeud deja coupe.\n");
        return;
    }

    noeud->etat = 0;

    ajouter_evenement(
        events,
        nb_events,
        "DELESTAGE",
        noeud->id,
        "Coupure manuelle",
        noeud->puissance_kW
    );

    printf(
        "Noeud %s coupe manuellement avec succes.\n",
        noeud->id
    );
}
