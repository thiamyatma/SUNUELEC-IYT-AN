#ifndef STRUCTURES_H
#define STRUCTURES_H

#define NB_NOEUDS 12
#define NB_POINTS_COURBE 24
#define MAX_EVENTS 200
/*Le contrat d'opération qui permet la declaration de toutes les structures du projet. 
 On pourra ensuite appeller ces structures dans les fichiers .c pour les utiliser*/

/* DEFINITION DE LA STRUCTURE NOEUD*/
typedef struct {
    char id[4];
    char nom[30];
    float puissance_KW;
    int priorite;
    int etat;
    float energie_KWh;
    float cos_phi;
} Noeud;

/*DEFINITION DE LA STRUCTURE POINT COURBE*/
typedef struct {
    int heure;
    float p_solaire_KW;
    float p_reseau_KW;
    float p_charge_KW;
    float taux_charge;
} PointCourbe;

/*DEFINITION DE LA STRUCTURE EVENEMENT*/
typedef struct{
    char horodotage[20];
    char type[20];
    char noeud_id[4];
    char message[100];
    float valeur;
} Evenement;



#endif // STRUCTURES_H
