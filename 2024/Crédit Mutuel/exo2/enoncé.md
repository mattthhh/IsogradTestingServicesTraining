# Anatomie d'une chute

L'épreuve de saut d'obstacle consiste en une succession de murs placés les uns après les autres le long du parcours. Ces murs, opaques, sont peints soit en blanc, soit en noir.

Vous tenez à ce que les cavaliers et cavalières puissent visualiser au mieux leur course et les obstacles à venir lorsqu'ils sont positionnés en début de piste. Or, étant donné que les murs sont tous placés les uns à la suite des autres, il est possible qu'un mur soit complètement caché, s'il est positionné derrière un mur au moins aussi haut que lui. De plus, il est également possible que plusieurs murs paraissent, aux yeux du cavalier ou de la cavalière en début de piste, comme un seul et même mur.

Prenons l'exemple des trois murs suivants:
- le mur `A`, situé devant, a une hauteur de `2` et est de couleur `White`,
- le mur `B`, situé au milieu, a une hauteur de `2` et est de couleur `Black`,
- le mur `C`, situé derrière, a une hauteur de `4` et est de couleur `White`.

Le mur `B` étant placé derrière un mur aussi haut que lui, il est de fait complètement caché. Seuls restent visibles les murs `A` et `C`, qui ont la même couleur, et paraissent ainsi comme un seul et unique mur.

Les murs ont déjà été placés. En vue de réarranger les obstacles pour éviter toute confusion, vous voulez compter le nombre de murs pouvant se confondre avec d'autres, toujours du point de vue des cavaliers et cavalières situés en début de piste.


## Données

### Entrée

**Ligne 1** : Un entier `N`, représentant le nombre de murs.

**Ligne 2 à N+1** : Un entier `H`, représentant la hauteur du mur, suivi de la chaîne de caractères `Black` ou `White`.

L'entier `N` est compris entre `1` et `10000` inclus.
Chaque entier `H` est compris entre `1` et `100` inclus.


### Sortie

Le nombre de murs pouvant porter à confusion.

## Exemple


Pour l'entrée :
```plaintext
5
1 Black
2 Black
3 White
4 Black
5 Black
```

Votre programme devra renvoyer :
```plaintext
4
```

Chaque mur est plus grand que tous ceux placés avant. Ainsi, aucun n'est caché. Puisque le premier mur à la même couleur que le deuxième, ces deux peuvent se confondre. Il en va de même pour le quatrième et cinquième, ce qui fait un total de 4 murs pouvant porter à confusion.

---

Pour l'entrée :
```plaintext
6
3 White
2 White
4 White
1 White
4 White
5 White
```

Votre programme devra renvoyer :
```plaintext
3
```

Ici, le deuxième, quatrième et cinquième mur sont obstrués par des murs placé avant. Il reste alors 3 murs visibles depuis le départ. Puisqu'ils partagent tous les même couleur, ils peuvent tous porter à confusion.


---

Pour l'entrée :
```plaintext
4
1 White
3 Black
5 White
7 Black
```

Votre programme devra renvoyer :
```plaintext
0
```

Dans cet exemple, aucun mur n'est caché. Puisque les couleurs alternent, aucun mur ne peux porter à confusion avec un autre le suivant ou le précédant.