# Sorties des tests

Ce dossier regroupe les sorties console enregistrées le 5 août 2026 sur la version finale du programme. Chaque fichier correspond à une section du rapport.

Pour rejouer un test, il suffit de lancer `.\supervision.exe` et de taper la séquence indiquée dans le tableau.

| Fichier | Séquence au menu | Ce qu'on vérifie |
|---|---|---|
| `01_menu.txt` | `7` | Les 7 entrées du menu |
| `02_etat_initial.txt` | `2` puis `7` | 12 nœuds ON, énergie à 0 |
| `03_simulation_h0_delestage.txt` | `3` `2` `7` | Surcharge à 00h, délestage par priorité, N01 à N03 conservés |
| `04_energie_3h.txt` | `3` `3` `3` `5` `7` | 47.10 kWh après 3 heures |
| `05_energie_6h.txt` | `3` × 6 puis `5` `7` | 94.20 kWh après 6 heures |
| `06_delestage_manuel.txt` | `4` `N01` `4` `N01` `4` `N99` `7` | Coupure, nœud déjà coupé, identifiant inconnu |
| `07_sauvegarde_chargement.txt` | `1` `2` `7` après coupure de N07 | État relu depuis `noeuds.dat`, courbe lue depuis le CSV |
| `08_saisies_invalides.txt` | `abc` `99` `7` | Le menu ne bloque pas |
| `09_journee_24h_bilan.txt` | `3` × 24 puis `5` `6` `7` | Journée complète, bilan, génération du rapport |
| `10_evenements.log.txt` | — | Journal produit par la journée complète, 45 événements |
| `11_rapport_journalier.txt` | — | Rapport `bilan_JJ-MM-AAAA.txt` produit par le choix 6 |
| `12_test_interpolation.txt` | — | Interpolation linéaire, programme séparé |
| `13_test_tri.txt` | — | Tri décroissant, programme séparé |

## Les deux programmes de test séparés

L'interpolation et le tri ne sont accessibles par aucune entrée du menu. On les a donc validés à part, avec les deux petits programmes fournis ici :

```powershell
gcc -Wall -std=c11 Tests\sorties\programme_test_interpolation.c Sources\supervision.c Sources\recherche.c -I Headers -o test_interp.exe
.\test_interp.exe

gcc -Wall -std=c11 Tests\sorties\programme_test_tri.c Sources\tri.c Sources\initialisation.c -I Headers -o test_tri.exe
.\test_tri.exe
```

Pour le test d'interpolation, on utilise volontairement une courbe réduite à 5 points : avec la courbe complète, l'heure demandée tombe toujours sur un point déjà défini et l'interpolation n'a jamais l'occasion de servir. Le test du tri, lui, attribue des énergies dans le désordre puis vérifie qu'après tri aucun élément n'est supérieur à celui qui le précède.

## À propos des captures PNG du dossier parent

Les images du dossier `Tests/` datent des 1er et 2 août, c'est-à-dire d'avant la correction du calcul d'énergie. Les valeurs qu'elles affichent (195.50 kWh, 1219.00 kWh) ne correspondent donc plus au programme actuel. On les garde comme trace du développement.