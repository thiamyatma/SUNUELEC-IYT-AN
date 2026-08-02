#ifndef BILAN_H
#define BILAN_H

#include "structures.h"

/* Cette procedure Affiche un récapitulatif formaté contenant :
a) Énergie totale consommée (kWh)
b) Énergie produite par solaire + réseau (kWh)
c) Taux de couverture solaire (%)
d) Nombre total de délestages et rétablissements
e) Nœud le plus consommateur
f) Nœud le moins consommateur*/

void bilan_journalier(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int n_courbe,
    Evenement events[],
    int n_events
);

#endif