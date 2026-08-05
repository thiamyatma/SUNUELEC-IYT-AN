#include <stdio.h>
#include "structures.h"
#include "supervision.h"

int main(void){
    /* Courbe partielle : 5 points seulement (00h, 06h, 12h, 18h, 23h) */
    PointCourbe c[5] = {
        {0,  0.0f, 15.0f, 0, 0},
        {6,  0.8f, 14.2f, 0, 0},
        {12, 14.8f, 2.0f, 0, 0},
        {18, 2.1f, 14.0f, 0, 0},
        {23, 0.0f, 14.2f, 0, 0}
    };
    printf("Points fournis :\n");
    for(int i=0;i<5;i++)
        printf("  %02dh -> %.2f kW\n", c[i].heure, c[i].p_solaire_kW + c[i].p_reseau_kW);

    printf("\nHeures presentes dans la courbe (recherche exacte) :\n");
    printf("  06h -> %.2f kW\n", calcul_production_disponible(c,5,6));
    printf("  12h -> %.2f kW\n", calcul_production_disponible(c,5,12));

    printf("\nHeures absentes (interpolation lineaire) :\n");
    printf("  09h -> %.2f kW  (attendu 15.90)\n", calcul_production_disponible(c,5,9));
    printf("  15h -> %.2f kW  (attendu 16.45)\n", calcul_production_disponible(c,5,15));
    printf("  20h -> %.2f kW  (attendu 15.34)\n", calcul_production_disponible(c,5,20));

    printf("\nHors bornes :\n");
    printf("  25h -> %.2f kW  (attendu 0.00)\n", calcul_production_disponible(c,5,25));
    return 0;
}
