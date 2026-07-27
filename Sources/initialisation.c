#include <string.h>
#include "../Headers/initialisation.h"
/* Cette fonction sert uniquement à créer la configuration de départ de notre réseau.
Elle va recevoir le tableau Noeud noeuds[], remplir les 12 cases et mettre les valeurs initiale*/
void initialiser_noeuds(Noeud noeuds[]){
    
    strcpy(noeuds[0].id, "N01");
    strcpy(noeuds[0].nom, "Hopital");
    noeuds[0].puissance_KW=8.5;
    noeuds[0].priorite=1;
    noeuds[0].etat=1;
    noeuds[0].energie_KWh=0;
    noeuds[0].cos_phi=0.86;

    strcpy(noeuds[1].id, "N02");
    strcpy(noeuds[1].nom, "Ecole");
    noeuds[1].puissance_KW=4.2;
    noeuds[1].priorite=1;
    noeuds[1].etat=1;
    noeuds[1].energie_KWh=0;
    noeuds[1].cos_phi=0.86;

    strcpy(noeuds[2].id, "N03");
    strcpy(noeuds[2].nom, "Pompe Eau");
    noeuds[2].puissance_KW=3.0;
    noeuds[2].priorite=1;
    noeuds[2].etat=1;
    noeuds[2].energie_KWh=0;
    noeuds[2].cos_phi=0.86;

    strcpy(noeuds[3].id, "N04");
    strcpy(noeuds[3].nom, "Marché");
    noeuds[3].puissance_KW=5.8;
    noeuds[3].priorite=2;
    noeuds[3].etat=1;
    noeuds[3].energie_KWh=0;
    noeuds[3].cos_phi=0.86;

    strcpy(noeuds[4].id, "N05");
    strcpy(noeuds[4].nom, "Résid. A");
    noeuds[4].puissance_KW=6.1;
    noeuds[4].priorite=2;
    noeuds[4].etat=1;
    noeuds[4].energie_KWh=0;
    noeuds[4].cos_phi=0.86;

    strcpy(noeuds[5].id, "N06");
    strcpy(noeuds[5].nom, "Résid. B");
    noeuds[5].puissance_KW=5.3;
    noeuds[5].priorite=2;
    noeuds[5].etat=1;
    noeuds[5].energie_KWh=0;
    noeuds[5].cos_phi=0.86;

    strcpy(noeuds[6].id, "N07");
    strcpy(noeuds[6].nom, "Résid. C");
    noeuds[6].puissance_KW=4.7;
    noeuds[6].priorite=3;
    noeuds[6].etat=1;
    noeuds[6].energie_KWh=0;
    noeuds[6].cos_phi=0.86;

    strcpy(noeuds[7].id, "N08");
    strcpy(noeuds[7].nom, "Résid. D");
    noeuds[7].puissance_KW=4.4;
    noeuds[7].priorite=3;
    noeuds[7].etat=1;
    noeuds[7].energie_KWh=0;
    noeuds[7].cos_phi=0.86;

    strcpy(noeuds[8].id, "N09");
    strcpy(noeuds[8].nom, "Commerce 1");
    noeuds[8].puissance_KW=3.9;
    noeuds[8].priorite=3;
    noeuds[8].etat=1;
    noeuds[8].energie_KWh=0;
    noeuds[8].cos_phi=0.86;

    strcpy(noeuds[9].id, "N10");
    strcpy(noeuds[9].nom, "Commerce 2");
    noeuds[9].puissance_KW=3.2;
    noeuds[9].priorite=3;
    noeuds[9].etat=1;
    noeuds[9].energie_KWh=0;
    noeuds[9].cos_phi=0.86;

    strcpy(noeuds[10].id, "N11");
    strcpy(noeuds[10].nom, "Eclairage");
    noeuds[10].puissance_KW=2.1;
    noeuds[10].priorite=2;
    noeuds[10].etat=1;
    noeuds[10].energie_KWh=0;
    noeuds[10].cos_phi=0.86;

    strcpy(noeuds[11].id, "N12");
    strcpy(noeuds[11].nom, "Divers");
    noeuds[11].puissance_KW=1.8;
    noeuds[11].priorite=3;
    noeuds[11].etat=1;
    noeuds[11].energie_KWh=0;
    noeuds[11].cos_phi=0.86;



   


}