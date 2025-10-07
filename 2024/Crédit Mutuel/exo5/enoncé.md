# La solitude du coureur de fond

Pour l'épreuve de Cross-Country, le comité d'organisation a installé tout le long de la course une série de portiques à radiofréquence. Ces derniers permettent de détecter les coureurs et coureuses passant à travers et de maintenir à jour le classement en direct. En revanche, tous les portiques n'ont pas la même portée d'émission et certains on été placés bien trop proches les uns des autres, tant et si bien que leurs zones d'émission se chevauchent. Ce chevauchement peut entraîner des interférences entre portiques et fausser les résultats donnés.

Une manière de solutionner le problème est d'affecter à deux portiques trop proches l'un de l'autre des fréquences radio différentes. Toutefois, les marqueurs disposés sur les athlètes ne peuvent réagir qu'à un nombre limité de fréquences et des marqueurs plus perfectionnés coûtent chers. Afin, de minimiser les coûts d'organisation de la course, déterminez le nombre minimal de fréquences, tel qu'aucun portique n'ait la même fréquence que ceux proches de lui.

## Données

### Entrée

**Ligne 1** : Deux entiers `P` et `I`, représentant respectivement le nombre de portiques et le nombre de paire de portiques suffisamment proches pour pouvoir causer des interférences.

**Ligne 2 à I+1** : Deux entiers `A` et `B`, représentant les identifiants de deux portiques pouvant engendrer des interférences s'ils émettent sur la même fréquence.

L'entier `P` est compris entre `0` et `1000`.

L'entier `I` est compris entre `P-1` et `(P*P-P)/2`.

Les entiers `A` et `B` sont compris entre `0` et `P-1` inclus et tels que `A < B`.

Si `A` interfèrent avec `B`, alors `B` interfère avec `A`.

L'intégralité de la course est couverte par les portiques.

Chaque portique couvre un unique tronçon continu de la course.

Nous considérerons que la trajectoire de la course est parfaitement droite et que les zones d'influence des portiques sont circulaires. De fait aucune interférence ne peut être engendrée par les sinuosités de la course.

### Sortie

Le nombre minimum de fréquences que l'on peut attribuer aux portiques de manière à n'avoir aucune interférence.

## Exemple


Pour l'entrée :
```plaintext
4 3
0 1
1 2
2 3
```

Votre programme devra renvoyer :
```plaintext
2
```

![](https://i.imgur.com/U5rC6sL.jpeg)

Il est possible d'affecter une fréquence `f1` aux portiques `0` et `2` et une fréquence `f2` aux portiques `1` et `3`. La figure ci-dessus montre une configuration possible des portiques et l'affectation des fréquences.

---

Pour l'entrée :
```plaintext
5 6
0 3
0 2
1 4
2 3
2 4
3 4
```

Votre programme devra renvoyer :
```plaintext
3
```

![](https://i.imgur.com/0mP55cQ.jpeg)

Il est possible d'affecter une fréquence `f1` aux portiques `0` et `4`, une fréquence `f2` aux portiques `1` et `3` et enfin une fréquence `f3` au portique `2`.
Il n'est pas possible de résoudre cette instance avec moins de `3` fréquences.