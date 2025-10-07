# Root du rhum

Partir pour un tour du monde en solitaire à la voile est une aventure exaltante, mais la gestion des ressources est cruciale pour assurer votre survie et votre performance. L’un des aspects les plus importants est l’optimisation des vivres que vous emmenez à bord : vous devez maximiser l’apport énergétique tout en respectant la capacité de transport de votre bateau.

Vous avez le choix entre plusieurs rations, donc chacune a un certain apport énergétique et un certain poids. Vous voulez prendre les rations totalisant un grand apport énergétique : quelle est la liste de rations que vous pouvez prendre sans dépasser la capacité du bateau ?

Pour gagner du temps, vous décidez d'aller au plus simple : vous rangez toutes les rations par apport énergétique décroissant, et vous les chargez dans cet ordre dans votre bateau. Pour chaque ration qui entraînerait une surcharge du navire, ignorez-la et passez à la suivante.

## Données

### Entrée

**Ligne 1**, deux nombres séparés par un espace:
- Un entier `N` représentant le nombre de rations disponibles.
- Un flottant (nombre à virgules) `C` représentant la capacité maximale de stockage du bateau.

**N lignes suivantes** :
- Deux nombres flottants `E` et `P` séparés par un espace, où :
- `E` représente la valeur énergétique de la ration.
- `P` représente le poids de la ration.

### Sortie

Une liste des indices (indexés à 0) des rations sélectionnées, un par ligne, comprenant les rations les plus énergétiques sans dépasser la capacité `C`.

### Contraintes

- `N ≤ 10^4`
- `C ≤ 10^6`
- `0 ≤ E, P ≤ 10^6`
- Les nombres flottants sont donnés avec 1 à 6 chiffres après la virgule.
- Toutes les valeurs énergétiques sont uniques.

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
2
0
3
```

En effet, la ration 2 a la plus haute valeur énergétique (950.654), c'est donc la première sélectionnée, suivie de la ration 0. La ration suivante dans l'ordre serait la ration 4, mais cela ferait dépasser la masse limite (9.42 + 7.058 + 4.352 > 20.0), elle est donc ignorée, tout comme la ration 1 qui est dans le même cas. La dernière ration se trouve à l'index 3, et elle est suffisamment légère pour être ajoutée au bateau avec les deux autres.