# À bout de souffle

En regardant les épreuves de 200m nage libre, vous remarquez que chaque nageur et nageuse possède ses habitudes quant à sa façon de respirer. Afin d'aller le plus vite possible, les nageurs ne respirent évidemment pas à chacun de leurs mouvements de bras. Ils ont donc tous un nombre de mouvements de bras minimum entre deux respirations. De plus, ayant une capacité pulmonaire limitée, ils ont également un nombre de mouvements de bras maximum.

En assumant qu'il respirent avant de plonger, et donc juste avant leur séquence de mouvements de bras, vous voulez compter combien de séquences de mouvements avec et sans respiration sont possibles pour une longueur donnée.

## Données

### Entrée

**Ligne 1** : Un entier `A`, représentant le nombre minimum de mouvements de bras entre deux respirations.

**Ligne 2** : Un entier `B`, représentant le nombre maximum de mouvements de bras entre deux respirations.

**Ligne 3** : Un entier `L`, représentant le nombre de mouvements réalisés par le nageur.

Les entiers `A` et `B` sont compris entre `0` et `20` inclus et tels que `A <= B`.

L'entier `L` est compris entre `0` et `100`.

### Sortie

Le nombre de façons possibles de réaliser `L` mouvements, telles qu'il n'existe pas moins de `A` mouvements et pas plus de `B` mouvements entre chaque respiration. Chaque respiration compte également comme un mouvement.

De plus, nous assumons que le nageur ou la nageuse vient de respirer juste avant de commencer la séquence de mouvement.

## Exemple


Pour l'entrée :
```plaintext
0
1
3
```

Votre programme devra renvoyer :
```plaintext
5
```

Avec ces contraintes, et en notant `-` un mouvement sans respirer et `x` un mouvement avec respiration, seules 5 possibilités existent:
1. `(x)-x-`
2. `(x)-xx`
3. `(x)x-x`
4. `(x)xx-`
5. `(x)xxx`

Le `(x)` signifie que le ou la nageuse vient de respirer avant de commencer sa séquence de mouvements.

---

Pour l'entrée :
```plaintext
1
3
5
```

Votre programme devra renvoyer :
```plaintext
6
```

Avec ces contraintes, seules 6 possibilités existent:
1. `(x)---x-`
2. `(x)--x--`
3. `(x)--x-x`
4. `(x)-x---`
5. `(x)-x--x`
6. `(x)-x-x-`