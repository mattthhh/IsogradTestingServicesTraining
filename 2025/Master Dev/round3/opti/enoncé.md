# Root du rhum 2.0

**Attention** : cet exercice est une variante plus difficile du problème précédent. Vous n'avez pas à trouver la solution optimale : les solutions seront classées en fonction de leur score obtenu, et vous pouvez effectuer plusieurs soumissions.

Peut-être qu'il y a plus optimal que de ne prendre que les rations les plus caloriques... Saurez vous trouver la liste de rations maximisant les calories que vous embarquerez pour votre tour du monde, toujours sans dépasser la capacité maximale du bateau ?

## Données

### Entrée

Le format de l'entrée est le même que pour l'exercice précédent.

**Ligne 1**, deux nombres séparés par un espace:
- Un entier `N` représentant le nombre de rations disponibles.
- Un flottant `C` représentant la capacité maximale de stockage du bateau.

**N lignes suivantes** :
- Deux nombres flottants `E` et `P` séparés par un espace, où :
- `E` représente la valeur énergétique de la ration.
- `P` représente le poids de la ration.

### Sortie

Une liste des indices des objets sélectionnés, un par ligne, permettant d’optimiser la valeur énergétique totale sans dépasser la capacité `C`. L'ordre de la liste n'est pas important.

### Score

Votre solution sera évaluée selon la formule suivante :

```plaintext
score = 1.000.000 * valeur_objets / valeur_totale
```

où :
- `valeur_objets` est la somme des valeurs énergétiques des objets sélectionnés,
- `valeur_totale` est la somme des valeurs énergétiques de tous les objets disponibles.

Plus votre score est élevé, meilleure est votre solution.

### Contraintes

- `N ≤ 10^3`
- `C ≤ 10^6`
- `0 ≤ E, P ≤ 10^6`
- Les nombres flottants sont donnés avec 1 à 6 chiffres après la virgule.

Les jeux de données sont les mêmes pour tous les participants. Si votre code ne renvoie pas de solution dans le temps imparti (15 secondes par jeu de données), une erreur s'affichera : le score sera de 0 pour ce dataset, et les datasets suivants ne seront pas évalués.

Attention : votre solution doit pouvoir résoudre tous les datasets, aucun codage en dur ("hardcoding") des solutions ne sera toléré.

## Exemple

### Entrée
```plaintext
5 20.0
720.493 7.058
525.682 4.938
950.654 9.42
163.767 1.237
592.88 4.352
```

### Sortie
```plaintext
0
1
3
4
```

Par rapport à la solution de l'exercice précédent, il est possible d'optimiser le stockage pour embarquer davantage : en effet, si l'on ignore la ration la plus lourde, il est possible d'embarquer toutes les autres rations. La valeur énergétique totale est alors de 2002.822, bien meilleure que les 1834.914 de la solution initiale.

Pour cette solution, `valeur_objets` est donc égale à 2002.822, et `valeur_objets` vaut 2953.476. Le score pour cette solution est donc :

1000000 * 2002.822 / 2953.476 ≈ 678123.7