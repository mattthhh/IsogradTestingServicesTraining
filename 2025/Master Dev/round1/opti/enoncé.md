# Vous êtes ici 2.0

**Attention** : cet exercice est une variante plus difficile du problème que vous venez de résoudre. Votre code du problème précédent a été reporté sur cette question pour vous aider à démarrer. Vous n'avez pas à trouver la solution optimale pour chaque test : les solutions seront classées en fonction de leur score obtenu, et vous pouvez effectuer plusieurs soumissions.

La première cartographie de la vielle est fascinante ! Mais vous vous rendez vite compte que vos drones pourraient explorer bien plus de rues si vous amélioriez leur algorithme de recherche. En particulier, plusieurs drones peuvent évidemment passer par une même rue !

Combien de rues arriverez vous à photographier avec vos drones ?

## Données

### Entrée

Le format d'entrée est le même que pour le premier exercice.

**Lignes 1 et 2** :

```plaintext
nbDrones battery
nbStreets nbInter
```

**nbStreets lignes suivantes** : Chaque ligne décrit une rue sous la forme :

```plaintext
idInter1 idInter2 streetLength
```

### Sortie

`X` lignes, où chaque ligne représente le trajet emprunté par un drone, sous la forme d’une liste d’intersections séparées par des espaces.

**Note** : Une rue peut être parcourue dans un sens ou dans l'autre. Une visite dans un sens compte pour les deux sens.

### Contraintes

- `2 ≤ nbDrones ≤ 10`
- `nbStreets, nbInter ≤ 5 000`
- `battery ≤ 1 000 000`
- Toutes les routes sont uniques : il n'y aura jamais deux routes qui relient la même paire d'intersections.
- Une route ne reliera jamais une intersection à elle-même.
- Les intersections sont numérotées de 0 à nbInter-1.

Les jeux de données sont les mêmes pour tous les participants. Si votre code ne renvoie pas de solution dans le temps imparti (15 secondes par jeu de données), une erreur s'affichera : le score sera de 0 pour ce dataset, et les datasets suivants ne seront pas évalués.

Attention : votre solution doit pouvoir résoudre tous les datasets, aucun codage en dur ("hardcoding") des solutions ne sera toléré.

### Score

Votre solution sera évaluée selon les longueurs des rues parcourues par vos drones. Le score est calculé comme suit :

```plaintext
score = 1.000.000 * distance_cartographiée / distance_totale
```

`distance_totale` est la somme des distances de toutes les rues.

`distance_cartographiée` est la somme des distances des rues **uniques** visitées par un drone. Même si 2 drones peuvent passer par une même rue (ou un drone passer plusieurs fois par la meme rue), la rue ne comptera qu'une seule fois dans le score.

**Important** : seule votre meilleure soumission sera prise en compte pour votre classement final. Votre score global ne peut ainsi pas diminuer.

## Exemple

### Entrée :

```plaintext
3 50
8 7
0 1 20
0 2 10
0 5 20
2 3 10
3 4 30
2 6 35
3 6 10
4 6 10
```

### Solution possible :

```plaintext
0 1 0 5
0 2 3 4
0 2 6 3
```

### Explication

![Illustration de l'exemple](https://preprod.isograd.com/visualaids/codecontest/fr/codecontest_fr_ot_ctstfr0463.png)

Avec cette sortie, toutes les rues sont cartographiées sauf la rue de 4 à 6. La rue de 0 à 1 est cartographiée 2 fois par le premier drone mais elle ne compte qu'une seule fois. De même, la rue de 0 à 2 est cartographiée par 2 drones différents mais ne compte qu'une seule fois.

Avec cette solution, le score est de : 1.000.000 * 135 / 145 ≈ 931034.5