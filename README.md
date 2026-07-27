# SUNUELEC-IYT-AN

# COLLABORATION
Pour une bonne organisation de la collaboration, merci de bien lire  
 [le document](commands-collaborateur-github.md). Il regroupe les commandes Git  
 essentielles pour créer , mettre à jour et nettoyer votre branches.

 # Premier Ajout-Code dans [le fichier header structures.h](Headers/structures.h)
*Le contrat d'opération qui permet la declaration de toutes les structures du projet. 
 On pourra ensuite appeller ces structures dans les fichiers .c pour les utiliser*/

# Creation DOSSIER  Sources et Headers et deplacement fichiers
Après la création des dossiers, j'ai deplacé les fichiers sources et headers dans leurs dossiers respectifs.

# Definitions des prototypes des sous programmes
j'ai créer le prototype des sous programmes (Contrat d'opération)  
Les fichiers concernés : [energie.h](Headers/energie.h)  
[supervision.h](Headers/supervision.h)  

# Créations des commentaires de spécifications
Ces commentaires explique ce que fait la fonction.  
Les fichiers concernés: [energie.c](Sources/energie.c)  
[supervision.c](Sources/supervision.c)  

# Premier ajout de code dans [le fichier main.c](main.c)
J'ai juste ajouté la fonction classique int main que l'on compilera plutard

# Modification dans README.MD
Ajout d'un [fichier de commande git](commands-collaborateur-github.md)   
pour collaboration

# Ajout fonctionnalité Menu par Assatou:
Elle a développé les fonctionnalités menu :  
fichiers concernés:  
[menu-Source](Sources/menu.c)  
[menu-Header](Headers/menu.h)

# Correction [ajout-menu](Sources/menu.c) Après vérifications:
j'ai supprimmé les accents non encondés et un point virgule omis  
à la ligne 45.

# Debut de Codage des fonctions
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

 # Test de l'affichage des noeuds
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

# Création du dossier [Tests](Test)

# commande à utiliser pour la compilation :  
gcc main.c Sources/initialisation.c -I Headers -o SUNUELEC

après cela , nous pouvons exécuté le fichier avec la commande : .\SUNUELEC.exe

# créattion de la gestion des fichiers
J'ai créé dans le fichier headers les structures de la gestion des fichiers en appelant structures.h pour les structures noeud et courbe charge et je l'ai développé dans le fichier sources; ce qui m'a donné du vrai fil à retordre pour l'insertion dans le GitHub.
