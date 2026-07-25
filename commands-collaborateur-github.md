# Guide Git pour le Collaborateur sur GitHub

Ce guide regroupe les commandes Git essentielles pour un collaborateur travaillant avec le flux de branches de fonctionnalités (*feature branches*).

## 1. Commencer la journée (Synchronisation)
Avant de coder, récupérez toujours la version la plus récente du projet depuis la branche principale (`main`).
```bash
# Basculer sur la branche principale
git checkout main

# Récupérer et fusionner les dernières modifications du serveur
git pull origin main
```

## 2. Créer une branche de fonctionnalité
Isolez votre travail dans une branche dédiée à votre tâche. Donnez-lui un nom clair.
```bash
# Créer et basculer sur la nouvelle branche
git checkout -b feature/nom-de-la-fonctionnalite
```

## 3. Enregistrer son travail localement
Ajoutez et validez vos modifications au fur et à mesure de votre avancement.
```bash
# Voir les fichiers modifiés
git status

# Indexer toutes les modifications
git add .

# Enregistrer les modifications avec un message clair
git commit -m "feat: ajout de la fonctionnalité X"
```

## 4. Publier la branche et ouvrir une Pull Request
Envoyez votre branche locale sur GitHub pour que l'équipe puisse relire votre code.
```bash
# Publier la branche sur GitHub (à ne faire que la première fois)
git push -u origin feature/nom-de-la-fonctionnalite
```
*Note : Après cette commande, cliquez sur le lien affiché dans votre terminal ou allez sur GitHub pour ouvrir la **Pull Request (PR)**.*

## 5. Mettre à jour sa branche (Éviter les conflits)
Si vos collègues ont fusionné d'autres fonctionnalités sur `main` pendant que vous codiez, mettez votre branche à jour.
```bash
# Récupérer l'historique du serveur sans modifier votre code
git fetch origin

# Fusionner les nouveautés de main dans votre branche actuelle
git merge origin/main
```

## 6. Nettoyer son espace local après fusion
Une fois votre Pull Request acceptée et fusionnée par le chef sur GitHub, supprimez votre branche locale devenue inutile.
```bash
# Retourner sur main
git checkout main

# Mettre à jour main avec votre fonctionnalité intégrée
git pull origin main

# Supprimer la branche locale
git branch -d feature/nom-de-la-fonctionnalite
```
