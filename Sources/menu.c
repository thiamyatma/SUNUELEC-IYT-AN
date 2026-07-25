#define <stdio.h>
#define "menu.h"
 void afficher_menu(){
     printf("===SUPERVISION RESEAU ELECTRIQUE===\n");
     printf("1. Charger configuration réseau\n");
     printf("2. Afficher état actuel des noeuds\n");
     printf("3. Simuler une heure\n");
     printf("4. Déclencher délestage manuel\n");
     printf("5. Afficher bilan jornalier\n");
     printf("6. Exporter rapport journalier\n");
     printf("7. Quitter\n");
     printf("Faite un choix :\n")
 }
 void gestion_choix(){
     int choix = 0;
     do {
        afficher_menu();
        printf("Votre choix :");
        if (scanf("%d", &choix) !=1){
            printf("Erreur : Veuiller saisir un choix valide\n");
        }
        switch(choix){
        case 1:
            printf("Charger configuration reseau\n");
            break;
        case 2:
            printf("Affichage état actuel des noeuds\n");
            break;
        case 3:
            printf("Simulation d'une heure\n");
            break;
        case 4:
            printf("Déclenchement délestage manuel\n");
            break;
        case 5:
            printf("Affichage bilan journalier\n");
            break;
        case 6:
            printf("Exportation rapport journalier\n");
            break;
        case 7:
            printf("Quitter\n");
            break;
        default:
            printf("Choix invalide, veuiller réessayer\n");
            break;
        }
     }while (choix != 7);
 }
