# Au fil de l'épée

Pour l'épreuve d'escrime, vous avez réalisé en amont une petite étude sur les qualités de chacun des athlètes. Chacun est jugé sur trois critères distincts: l'agilité, la réactivité et l’endurance. En attribuant une note sur 100 pour chaque athlète et chaque critère, vous pouvez déterminer avec certitude l'issue d'une rencontre. Si un escrimeur `a` possède une meilleur note qu'un escrimeur `b` dans au moins deux des trois critères, alors vous pouvez être sûr que `a` va battre `b`.

Vous vous rendez alors assez vite compte que l'issue du tournoi n'est pas complètement écrite pour autant. En effet, en considérant les trois athlètes suivants: `a=(0,1,2)`, `b=(2,0,1)` et `c=(1,2,0)`, alors `a` bats `b`, `b` bats `c` mais `c` bats à son tour `a`.

Afin d'avoir de belles demi-finales, vous vous demandez, compte tenu de vos notes, s'il est possible d'avoir une telle boucle mais avec quatre escrimeurs. De plus, vous aimeriez bien que votre athlète fétiche, celui en haut de votre liste de notes, fasse partie d'une telle boucle.

## Données

### Entrée

**Ligne 1** : Un entier `N`, représentant le nombre de participants.

**Ligne 2 à N+1** : Trois entiers `A`, `R` et `E`, représentant respectivement, l'agilité, la réactivité et l’endurance des participants.

Le nombre de participants `N` est compris entre `1` et `2000`.

Les entiers `A`, `R` et `E` sont compris entre `0` et `100` inclus.

### Sortie

`Yes` s'il est possible, de trouver quatre participants `a`, `b`, `c` et `d`, tels que:
- `a` est le participant en haut de la liste,
- `a` bats `b`,
- `b` bats `c`,
- `c` bats `d`,
- `d` bats `a`,

`No` sinon.

## Exemple

Pour l'entrée :
```plaintext
4
2 3 0
1 2 5
5 1 3
3 3 2
```

Votre programme devra renvoyer :
```plaintext
Yes
```

Le participant en haut de la liste, `2 3 0`, bats le participant `1 2 5`, qui lui-même bats le participant `5 1 3`, qui bats le participant `3 3 2`, qui bats `2 3 0`.

---

Pour l'entrée :
```plaintext
4
2 3 0
0 0 1
5 1 3
1 2 5
```

Votre programme devra renvoyer :
```plaintext
No
```

Cette fois, la boucle n'est que de taille `3`. Le participant `0 0 1` est en effet battu par tout le monde.

---

Pour l'entrée :
```plaintext
5
7 6 10
7 0 6
8 10 10
10 0 2
1 6 10
```

Votre programme devra renvoyer :
```plaintext
No
```

Le participant en haut de la liste `7 6 10`, ne peut être battu que par le participant `8 10 10`. Or, ce dernier ne peut être battu par personne d'autre. Il n'existe donc pas de telle boucle.