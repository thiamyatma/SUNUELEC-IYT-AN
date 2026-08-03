# SUNUELEC-IYT-AN

# COLLABORATION
Pour une bonne organisation de la collaboration, merci de bien lire  
 [le document](commands-collaborateur-github.md). Il regroupe les commandes Git  
 essentielles pour créer , mettre à jour et nettoyer votre branches.

 # Yatma : Premier Ajout-Code dans [le fichier header structures.h](Headers/structures.h)
*Le contrat d'opération qui permet la declaration de toutes les structures du projet. 
 On pourra ensuite appeller ces structures dans les fichiers .c pour les utiliser*/

#  Yatma : Creation DOSSIER  Sources et Headers et deplacement fichiers
Après la création des dossiers, j'ai deplacé les fichiers sources et headers dans leurs dossiers respectifs.

#  Yatma: Definitions des prototypes des sous programmes
j'ai créer le prototype des sous programmes (Contrat d'opération)  
Les fichiers concernés : [energie.h](Headers/energie.h)  
[supervision.h](Headers/supervision.h)  

# Yatma : Créations des commentaires de spécifications
Ces commentaires explique ce que fait la fonction.  
Les fichiers concernés: [energie.c](Sources/energie.c)  
[supervision.c](Sources/supervision.c)  

# Yatma : Premier ajout de code dans [le fichier main.c](main.c)
J'ai juste ajouté la fonction classique int main que l'on compilera plutard

# Yatma: Modification dans README.MD
Ajout d'un [fichier de commande git](commands-collaborateur-github.md)   
pour collaboration

# Assatou: Ajout fonctionnalité Menu par :
Elle a développé les fonctionnalités menu :  
fichiers concernés:  
[menu-Source](Sources/menu.c)  
[menu-Header](Headers/menu.h)

# Yatma : Correction [ajout-menu](Sources/menu.c) Après vérifications:
j'ai supprimmé les accents non encondés et un point virgule omis  
à la ligne 45.

#  Yatma : Debut de Codage des fonctions
Tout d'abord , dans [supervision.c](Sources/supervision.c), j'ai codé la fonction calcul_puissance_totale(Noeud noeuds[], int n) qui a comme parametre Le tableau de structures  
Noeud noeuds[] , et un entier int n.
Comme je l'avais dit dans [le-commentaire](Sources/supervision.c) , Cette fonction somme et  
 retourne les puissances de tous les noeuds à l'état ON.

 juste après cela , j'ai crée deux fichiers : [initialisation.h](Headers/initialisation.h)  
 et [initialisation.c](Sources/initialisation.c) : dans ce dernier , j'ai créer la procedure  
 void initialiser_noeuds() , avec comme parametre l'ensemble des noeuds. J'ai choisi cela parceque les mettre dans [main.c](main.c) serait trop encombrant. 

 # Petite remarque
 Dans [initialiser.c](Sources/initialisation.c), j'avais mis noeuds[0].nom="Hopital" . Cela marche  
 pour une chaine de caractère mais j'avais remarqué que dans [structures.h](Headers/structures.h)  
 j'ai déclaré id et nom comme tableau de caractère, donc j'ai importé la librarie string.h et  
 appelé la fonction strcpy() qui sert à copier une chaine de carctère à l'endroit ou l'on veut   
 mettre le texte noeuds[0].id . Ici , le texte à copier est "N01" : strcpy(noeuds[0].id, "N01")  
 Meme chose pour nom.

 # Yatma: Test de l'affichage des noeuds
 après  avoir créer un petit programme pour voir si tous les noeuds se chargent bien dans main.c,  
 j'ai compilé le programme mais , il y'a une erreur :

 # Erreurs et Correction

A la ligne 22 de [structures.h], le mot clé de la structure est struct , aulieu de Struct.  
fatal error: Headers/fichiers.h: No such file or directory : y'a pas de s dans fichier.h :  
correction effectué depuis l'entete de [main.c](main.c)  
j'ai oublié aussi le #endif dans [fichier.h](Headers/fichier.h)

Aussi dans [menu-c](Sources/menu.c) : #define "menu.h" -------> #include "../Headers/menu.h"

j'ai mis en commentaire  quelques inclusions dans [main.c](main.c) inutiles pour le teste.

Après de nombreuses compilation echoué , j'ai finalement reussit à le compiler et à affichers les   
12 noeuds , ainsi que leurs données !!!

# Yatma: Création du dossier [Tests](Tests)

# commande à utiliser pour la compilation :  
gcc main.c Sources/initialisation.c -I Headers -o SUNUELEC

après cela , nous pouvons exécuté le fichier avec la commande : .\SUNUELEC.exe

# Assatou : créattion de la gestion des fichiers
J'ai créé dans le fichier headers les structures de la gestion des fichiers en appelant structures.h pour les structures noeud et courbe charge et je l'ai développé dans le fichier sources; ce qui m'a donné du vrai fil à retordre pour l'insertion dans le GitHub.

# Yatma : Test Calcul puissance Neuds

J'ai tester la fonction calcul_puissance_totale qui retourne la somme de tous les noeuds à l'etat ON  
Puisqu'on avait intialisé tous les neouds à ON , On se retrouve avec comme puissance totale : 53.00 kw   voir[resultat](Tests/puissance-totale-tous_noeuds.png)
## Cas où un noeud est off .
Si on suppose que Resid. C est off , on se trouve avec une puissance totale de 48.30kw   
voir [resultats](Tests/puissanceTot_avec_1noeuds_OFF.png)

# Yatma : Codage de la fonction : float calcul_taux_charge_pct(float p_charge, float p_dispo);

Cette fonction retourne le taux de charge en %. actifs  . Cette fonction génère une ALERTE CONSOLE si le taux est > 90%  . ou une ALERTE CRITIQUE si le taux est > 100
p_charge est la puissance consommé par les noeuds 
p_dispo est la production disponible ( solaire + reseau)
[clique ici pour voir le code du test](Tests/code_test_taux_charge.png)  
[clique ici pour voir le resultat du test](Tests/resultat_taux_charge_test.png) 

# Yatma : codage de la fonction calcul_production_disponible(PointCourbe courbe[], int n, int heure)  
/*Cette fonction retourne la production totale disponible (solaire + réseau).
à une heure donnée. [voir le code](Sources/supervision.c)
## Remaque
Pour l'instant , on a pas encore implémenter l'interpolation linéaire dans le cas ou l'heure ne correspond pas exactement . Faison le test avec 5 données de la courbe.

### Resultat du test :
 [Voir le code pour le test ](Tests/code_test_production_dispo2_heure.png)
 [Voir le code pour le test_Suite](Tests/code_test_production_dispo1_heure.png)  
 
 [voir le resultat du test](Tests/resultat_production_dispo_12heure.png)

 # Yatma:  Début de l'implémentation de l'algorithme de délestage automatique.
 L'algorithme coupe les charges en cas de surcharge du reseau selon l'ordre de priorité.  
 d'abord l'algorithme deleste les neouds de priorit3.  
 ensuite si le déficit est toujours la , les noeuds de priorite 2 sont coupés.  
 Par contre , les neouds de priorité 1 sont jamais coupés . [voir-resultat-priorite2](Tests/Resultat_delestage_priorite2.png) et [voir-resutat-priorite 3](Tests/resultat_delestage_priorite3.png)

# Ajout de l'enregistrement des événements de delestage.

Ici , chaque coupure est enregistré dans le tableau eventd[] avec   
le type d'evenemnt, l'id du noeud, un message, la puissance coupés.  
[voir-resultat_test](Tests/resultat_events_delestage.png)

# Retablissement Progressif
Ici , les charges délestés sont restaurés selon l'ordre des priorités  
priorité 2 en premier , puis priorité 3  
Le retablissement est effectué uniquement si la marge disponible  
est suffisante . Et Chaque retablissement est enregistré dans le tableau des événements.

[voir-resultat-test](Tests/resultat_retablissement.png)

# Implémentation de la fonction calcul_energie_noeud


Cette fonction calcule l'énergie consommée par un nœud sur la journée
en intégrant son historique de consommation heure par heure.

> **Note :** les chiffres de cette section datent de la première version,
> qui intégrait un profil constant sur 24 h au lieu de l'historique réel.
> Les valeurs corrigées sont dans la section « Correction du calcul
> d'énergie » en bas de ce fichier.

 Test réalisé :
- Nœud testé : N01 Hôpital
- Puissance : 8.5 kw
- Énergie calculée : 195.50 kwh

## Calcul énergie de tous les noeuds

fonction calculer_energie_tous_noeuds().

elle parcourt l'ensemble des charges du réseau et met à jour
le champ energie_kwh de chaque noeud.

Test réalisé sur les 12 noeuds :
- N01 Hôpital : 195.50 kwh
- N02 École : 96.60 kwh
- ...
- N12 Divers : 41.40 kwh

[voir le reste des resultats](Tests/resultat-energie-tous-noeuds.png)  

## Recherche d'un noeud par ID

Ajout de la fonction recherche_noeud_par_id().

Cette fonction réalise une recherche séquentielle dans le tableau
des noeuds et retourne un pointeur vers la structure trouvée.

Test réalisé :
Recherche : N05 [capture ici](Tests/resultat_rechercher_noeud_id.png)

Résultat :
N05 - Résid. A trouvé

## Tri des noeuds par consommation

Ajout de la fonction trier_noeuds_par_consommation().

Cette fonction utilise un tri par sélection afin de classer les noeuds
selon leur énergie consommée (energie_kwh) dans un ordre décroissant.

Résultat du test :

1. N01 Hôpital : 195.50 kwh
2. N05 Résid. A : 140.30 kwh
3. N04 Marché : 133.40 kwh
...
12. N12 Divers : 41.40 kwh

[voir la capture](Tests/resultat_tri_noeud_consommation.png)

# Bilan énergétique journalier

## Fonctionnalité ajoutée

Ajout de la fonction :

```c
void bilan_journalier(
    Noeud noeuds[],
    int n_noeud,
    PointCourbe courbe[],
    int n_courbe,
    Evenement events[],
    int n_events
);
```

### Modules ajoutés et validés

- Implémentation du **bilan énergétique journalier** (`bilan.c`)
  - Calcul de la consommation totale.
  - Calcul de la production solaire et réseau.
  - Calcul du taux de couverture PV.
  - Recherche du plus gros et plus faible consommateur.
  - Comptage des délestages et rétablissements.
  - Affichage de l'historique des événements.

J'avais oublié de fermer le bloc de code juste au-dessus, du coup tout le
bas du README s'affichait comme du code sur GitHub. C'est réparé.

### Initialisation de la courbe de production

- Intégration des 24 points horaires fournis dans le cahier des charges :
  - Production solaire variable.
  - Production réseau national disponible.

Les mêmes 24 points sont aussi disponibles dans [donnees/courbe.csv](donnees/courbe.csv),
chargeable depuis le menu (choix 12).

# Module simulation

Ajout de [simulation.c](Sources/simulation.c) et [simulation.h](Headers/simulation.h).

`simuler_heure()` enchaîne : production disponible → consommation totale →
taux de charge → délestage si surcharge → rétablissement si marge →
enregistrement de la consommation de l'heure → mise à jour de l'énergie.

`simuler_journee()` répète l'opération sur les 24 heures.

# Correction du calcul d'énergie

C'est le gros bug de cette version. `consommation_horaire[24]` était rempli
une fois pour toutes à l'initialisation avec la puissance nominale du nœud,
et la simulation ne le mettait jamais à jour. Résultat :

- l'énergie affichée était la même après 1 heure ou après 10 heures de simulation ;
- dès qu'un nœud était délesté, `if(etat == 0)` remettait **toute** sa journée
  à zéro, alors qu'il avait bien consommé avant d'être coupé.

Ce qui a changé :

- `consommation_horaire[]` est maintenant un **historique**, initialisé à 0 et
  rempli heure par heure par `enregistrer_consommation_horaire()`, appelée
  après le délestage et le rétablissement.
- `calcul_energie_noeud()` intègre cet historique (`E = Σ P(h) × 1 h`).
  La puissance étant constante pendant l'heure simulée, le trapèze se réduit
  à un rectangle par heure.

Les valeurs plus haut dans ce README viennent de l'ancien calcul et ne sont
plus valables. Résultats actuels après une journée complète (choix 11 puis 10) :

```
========== BILAN JOURNALIER ==========

Consommation totale : 376.80 kwh
Production solaire : 112.20 kwh
Production reseau : 262.50 kwh
Production totale disponible : 374.70 kwh
Part du solaire dans la production : 29.94 %
Couverture PV de la consommation : 29.78 %

Plus gros consommateur : N01 - Hopital : 204.00 kwh
Plus faible consommateur : N04 - Marche : 0.00 kwh
```

204.00 = 8.5 kw × 24 h pour l'Hôpital, ce qui est cohérent. Les 9 nœuds à 0.00
sont ceux qui ont été délestés à l'heure 0 et jamais rétablis (voir la remarque
sur les données, plus bas).

# Autres corrections

- `ajouter_evenement()` : `strncpy` ne terminait pas les chaînes quand la source
  remplissait exactement le tampon (cas de `noeud_id[4]` avec "N01"). Le `\0`
  est maintenant forcé.
- Le rétablissement écrivait ses événements à la main avec `strcpy` au lieu
  d'appeler `ajouter_evenement()`, donc l'horodatage n'était jamais rempli.
- Délestage : quand aucun nœud ne couvre à lui seul le déficit, on prend
  maintenant le plus gros disponible et non le plus petit, ce qui limite le
  nombre de coupures.
- Le rétablissement vise 90 % de la production et non 100 %, sinon le réseau
  repassait en surcharge à l'heure suivante (oscillation ON/OFF).
- `evenements.log` : le menu réécrivait tout l'historique à chaque simulation,
  le fichier se remplissait de doublons. Seuls les nouveaux événements sont
  désormais écrits.
- Les 8 fonctions déclarées dans les `.h` sans définition sont implémentées
  (`bilan.h` en avait 6, plus `simuler_journee` et `verifier_facteur_puissance`).
- `MAX_EVENTS` passé de 200 à 500, sinon une journée complète sature le tableau.
- `charger_noeuds()` valide le contenu relu : une vieille sauvegarde
  incohérente est refusée et le réseau est réinitialisé proprement.

# Menu

Trois options ajoutées :

- **10** : simulation d'une journée complète (24 h)
- **11** : réinitialisation du réseau (12 nœuds ON, énergie à 0)
- **12** : chargement de la courbe de production depuis le CSV

# Remarque sur les données

La charge nominale totale des 12 nœuds est de **53.0 kw**, alors que la
production disponible varie entre **13.8 et 17.8 kw** sur la journée. Le réseau
est donc structurellement déficitaire : les priorités 2 et 3 sont coupées dès
l'heure 0 et la marge ne suffit jamais à les rétablir.

Le délestage fonctionne comme prévu (les priorités 1 ne sont jamais coupées),
mais le bilan reste peu parlant tant que les données du cahier des charges ne
sont pas rééquilibrées.

# Compilation

```powershell
gcc -Wall -Wextra -std=c11 main.c (Get-ChildItem Sources\*.c) -I Headers -o supervision.exe
```

Compile sans aucun warning. Exécution : `.\supervision.exe`

