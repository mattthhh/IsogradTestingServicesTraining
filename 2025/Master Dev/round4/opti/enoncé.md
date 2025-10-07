# Livreur de Pizzas 2.0

**Attention** : cet exercice est une variante plus difficile du problème que vous venez de résoudre. Votre code du problème précédent a été reporté sur cette question pour vous aider à démarrer. Vous n'avez pas à trouver la solution optimale pour chaque test : les solutions seront classées en fonction de leur score obtenu, et vous pouvez effectuer plusieurs soumissions.

Aidez le livreur à distribuer encore plus vite vos délicieuses pizzas : trouvez l'ordre de livraison qui nécessite de parcourir le moins de distance !

Vous n'êtes plus obligés de livrer les commandes dans l'ordre, et comme vous vous trouvez dans une ville organisée en grille, la distance à optimiser et la distance de Manhattan. Mais attention, le livreur devra retourner à la pizzeria située en (0,0) pour chercher les pizzas de la prochaine livraison.

## Données

### Entrée

Le format d'entrée est le même que pour le premier exercice.

**Ligne 1** : Deux entiers `N` et `C` séparés par un espace
- `N` représente le nombre total de commandes
- `C` est la capacité maximale du scooter en nombre de pizzas

**Les `N` lignes suivantes** : Trois entiers `x y nbPizzas`, représentant :
- `x` et `y` : coordonnées de livraison de la commande
- `nbPizzas` : nombre de pizzas à livrer à cette adresse

### Sortie

Vous devez afficher `M` lignes, chaque ligne représentant une tournée de livraison. Chaque ligne contient une liste d'indices de commandes (indexées à 0) séparés par un espace.

### Score

Votre solution sera évaluée sur la réduction de la distance totale parcourue par le livreur.

Le score est calculé comme suit :
```plaintext
score = 1 000 000 * (distance_baseline - distance_optimisee) / distance_baseline
```
- `distance_baseline` est la distance totale parcourue si chaque commande était livrée individuellement en partant et revenant de la pizzeria.
- `distance_optimisee` est la distance totale parcourue avec votre solution optimisée.

Un score proche de **1 000 000** signifie un chemin très court par rapport à la livraison individuelle.

Il est à noter que le score de 1 000 000 est impossible à atteindre (cela signifierait une distance optimisée de 0).

### Contraintes

- `1 ≤ N ≤ 10 000`
- `1 ≤ C ≤ 1 000`
- `1 ≤ nbPizzas ≤ C`
- `-100 000 ≤ x, y ≤ 100 000`
- Le livreur doit retourner à la pizzeria en (0, 0) entre chaque commande
- Chaque commande doit être livrée en une seule fois
- les distances sont calculées en distance de Manhattan : la distance entre les points (x1, y1) et (x2, y2) est de `|x1 - x2| + |y1 - y2|`

Les jeux de données sont les mêmes pour tous les participants. Si votre code ne renvoie pas de solution dans le temps imparti (15 secondes par jeu de données), une erreur s'affichera : le score sera de 0 pour ce dataset, et les datasets suivants ne seront pas évalués.

Attention : votre solution doit pouvoir résoudre tous les datasets, aucun codage en dur ("hardcoding") des solutions ne sera toléré.

## Exemple

#### Entrée :
```plaintext
5 10
1 2 3
-3 4 4
5 6 5
7 -8 2
-9 -10 3
```

#### Sortie possible :

```plaintext
0 2
4 3 1
```

Pour cette solution, la première tournée a une distance de :
- Trajet pizzeria vers `0` : `|1| + |2| = 3`
- Trajet `0` vers `2` : `|1 - 5| + |2 - 6| = 8`
- Trajet `2` vers pizzeria: `|5| + |6| = 11`

La distance de cette tournée est donc de 3 + 8 + 11 = 22. De même, la distance parcourue lors de la deuxième tournée est de 66. On a donc : `distance_optimisee = 22 + 66 = 88`


`distance_baseline` est toujours égale à 110 pour cette entrée, quelque soit la solution proposée.

Le score de cette solution est donc de :

`(110 - 88) / 110 * 1 000 000 = 200 000`