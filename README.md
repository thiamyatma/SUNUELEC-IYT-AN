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

# Yatma: Création du dossier [Tests](Test)

# commande à utiliser pour la compilation :  
gcc main.c Sources/initialisation.c -I Headers -o SUNUELEC

après cela , nous pouvons exécuté le fichier avec la commande : .\SUNUELEC.exe

# Assatou : créattion de la gestion des fichiers
J'ai créé dans le fichier headers les structures de la gestion des fichiers en appelant structures.h pour les structures noeud et courbe charge et je l'ai développé dans le fichier sources; ce qui m'a donné du vrai fil à retordre pour l'insertion dans le GitHub.

# Yatma : Test Calcul puissance Neuds

J'ai tester la fonction calcul_puissance_totale qui retourne la somme de tous les noeuds à l'etat ON  
Puisqu'on avait intialisé tous les neouds à ON , On se retrouve avec comme puissance totale : 53.00 KW   voir[resultat](Tests/puissance-totale-tous_noeuds.png)
## Cas où un noeud est off .
Si on suppose que Resid. C est off , on se trouve avec une puissance totale de 48.30KW   
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


Cette fonction calcule l'énergie consommée par un nœud pendant une journée
avec la méthode numérique des trapèzes.  
 Test réalisé :
- Nœud testé : N01 Hôpital
- Puissance : 8.5 kW
- Énergie calculée : 195.50 kWh

## Calcul énergie de tous les noeuds

fonction calculer_energie_tous_noeuds().

elle parcourt l'ensemble des charges du réseau et met à jour
le champ energie_KWh de chaque noeud.

Test réalisé sur les 12 noeuds :
- N01 Hôpital : 195.50 kWh
- N02 École : 96.60 kWh
- ...
- N12 Divers : 41.40 kWh

[voir le reste des resultats](Tests/resultat-energie-tous-noeuds.png)







