# Coder Coaster Tycoon

Après des mois de préparation, vous ouvrez enfin les portes de votre nouveau parc d'attractions !

Vous voulez faire un premier bilan après ce premier jour : quelles sont les attractions les plus populaires de votre parc ?

## Données

### Entrée

**Ligne 1** : Deux entiers `nbGroupes` et `nbAttractions` représentant respectivement le nombre de groupes de visiteurs et le nombre total d'attractions disponibles dans le parc.

**nbGroupes lignes suivantes** : Pour chaque groupe de visiteurs, un entier `tailleGroupe` représentant le nombre de personnes dans le groupe, suivi d'un entier `nbVisites` représentant le nombre d'attractions que le groupe a visité. Ensuite, la liste des `nbVisites` attractions choisies par le groupe.

### Sortie

Une liste des `nbAttractions` noms des attractions, triés par ordre décroissant de popularité et séparés par des espaces.

La popularité est calculée par nombre total de visiteurs ayant fait l'attraction. Un visiteur faisant plusieurs fois une attraction compte pour autant de fois qu'il fait cette attraction.

### Contraintes

Pour chaque jeu de données, ces différents points sont garantis et n'ont pas besoin d'être vérifiés :

- Les noms des attractions font au maximum 100 caractères, uniquement lettres majuscules et minuscules.
- Il y a au maximum 1 000 groupes.
- Il y a au maximum 1 000 attractions différentes.
- Chaque groupe comporte 1 à 1000 membres, et a visité entre 1 et 100 attractions.
- Il n'y a pas d'ex-aequo de popularité entre les attractions.
- Une attraction peut être visitée plusieurs fois par un même groupe.
- Chaque attraction est visitée par au moins un groupe.

## Exemple

### Entrée

```plaintext
3 4
3 3 RollerCoaster WaterSlide RollerCoaster
5 3 WaterSlide FerrisWheel PirateShip
2 1 FerrisWheel
```

### Sortie

```plaintext
WaterSlide FerrisWheel RollerCoaster PirateShip
```

En effet :

- `WaterSlide` est visité par le premier groupe (3 personnes) et le deuxième (5 personnes) = 8 personnes.
- `FerrisWheel` accueille 5 + 2 = 7 personnes sur la journée.
- `RollerCoaster` est visité deux fois par le premier groupe, soit 2x3 = 6 personnes.
- `PirateShip` accueille uniquement les 5 personnes du dernier groupe.