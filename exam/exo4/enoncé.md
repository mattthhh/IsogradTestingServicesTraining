# Distribution des paniers

Maintenant que vos paniers sont prêts, il est temps de les distribuer aux étudiants. Les choses ayant pris de l'ampleur, vous avez la charge de tous les points de distribution disséminés partout dans la ville.

Voulant encore une fois faire les choses bien, vous voulez coder un algorithme permettant au plus grand nombre d'étudiants d'avoir accès à un type de panier qui leur plait. Pour ce faire, vous avez mis en évidence deux critères: les préférences de l'étudiant, bien sûr, mais également la distance qu'il ou elle a à parcourir pour rejoindre un point de distribution.

Chaque étudiant a renseigné les trois types de paniers qu'il préfère, ainsi que les coordonnées de là où il ou elle a l'habitude de partir avant d'aller récupérer un panier.

Affectez à chaque étudiant un point de collecte de manière à rendre le plus de monde satisfait.

## Données

### Entrée

- **Ligne 1** : Trois entiers `D`, `P` et `E`, représentant respectivement le nombre de points de distribution, le nombre de types de paniers alimentaires différents et le nombre d'étudiant.
- **Prochaines 3D lignes** : Chaque point de distribution sera caractérisé par trois lignes distinctes:
- **Première ligne** : Trois entiers `X`, `Y` et `S`, représentant respectivement les coordonnées x et y du centre de distribution et le nombre de panier en stock
- **Deuxième ligne** : `S` identifiants de paniers différents
- **Troisième ligne** : `S` quantités de paniers en stock
- **Prochaines 2E lignes** : Chaque étudiant sera caractérisé par deux lignes distinctes:
- **Première ligne** : Deux entiers `X` et `Y` renseignant les coordonnés depuis lesquelles l'étudiant par pour aller récupérer un panier
- **Seconde ligne** : Les identifiants des trois paniers préférés de l'étudiant ou de l'étudiante dans l'ordre

### Contraintes

- `D<500`
- `3<=P<100`
- `E<25000`
- `0<=X,Y<=1000`
- `1<=S<=10`
- Pour éviter le gaspillage alimentaire, il y a exactement autant de paniers en stock que d'étudiants

### Sortie

Une ligne avec `E` identifiants de centres de distribution séparés par des espaces définissant les affectations des étudiants.

Le premier centre du dataset a pour identifiant `0`.

### Définition du score

Une fois les affectations des étudiants faites la distribution des paniers se fait comme suit:
Tous les étudiants se rangent tous au sein d'un même file. Ceux dont la distance entre le point de départ et le point de collecte et le plus proches peuvent choisir leur panier en premier. Le calcul de la distance utilisé et la distance de Manhattan. Si il y a égalité entre deux étudiants, celui apparaissant en premier dans le jeu de données pourra choisir son panier en premier.

Lorsqu'un ou une étudiante arrive à son tour, il choisit un unique panier parmi ceux restant dans le centre de distribution. Ce dernier choisira s'il le peut le premier panier de sa liste de préférence. S'il n'est pas disponible, il choisira le deuxième, et si aucun des deux n'est disponible, le troisième. Si aucun des paniers de sa liste de préférence n'est disponible, il ou elle choisira la panier dont l'identifiant est le plus bas.

Pour chaque étudiant repartant avec un panier, le score comptabilisé est calculé de la manière suivante:
`score = dist * pref * pref` où `dist` est la distance entre son point de départ et son point de collecte et `pref` définit à quel point le panier choisi lui plaît. La valeur de `pref` est égale à `1` si le panier choisit est le premier panier de sa liste, `2` s'il s'agit du deuxième, `3` du troisième ou `4` s'il n’apparaît pas dans sa liste.

Le score total sera évalué par la formule suivante:
```
score = 1.000.000 * (score_base - score_etudiants) / score_base
```
Ici, `score_etudiants` est la somme des `score` de chaque étudiants et `score_base` est le score d'une solution factice où tous les premiers étudiants de la liste sont envoyé aux premiers centres de distributions et ainsi de suite.

Les jeux de données sont les mêmes pour tous les participants. Si votre code ne renvoie pas de solution dans le temps imparti (15 secondes par jeu de données), une erreur s'affichera : le score sera de 0 pour ce dataset, et les datasets suivants ne seront pas évalués.
Enfin, seule votre meilleure soumission sera prise en compte pour votre classement final. Votre score global ne peut ainsi pas diminuer.


## Exemple

Pour l'entrée :
```plaintext
2 5 3
0 0 2
4 3
1 1
4 4 1
2
1
1 2
2 0 4
2 1
1 0 3
3 3
3 4 2
```

Solution possible:
```plaintext
1 0 0
```

Le premier étudiant (aux coordonnées `(1,2)`) est affecté au centre `1` (aux coordonnées `(4,4)`). Étant le seul il y choisit la panier de type `2` qui se trouve être son préféré, induisant un score de `5*1*1=5`.
Le deuxième et troisième étudiant vont tous deux au centre `0`. Le deuxième est à une distance `3` tandis que le troisième est à une distance `6`. Ainsi, le deuxième passe en premier et choisit le panier `3` qui correspond à son troisième panier préféré, induisant un score de `3*3*3=27`. Le dernier étudiant bien qu'il eut préféré le panier de type `3`, doit prendre le panier restant de type`4` qui est sont deuxième préféré, induisant un score de `6*2*2=24`.
Ceci donne un score total de `5+27+24=56`.
Le score de base étant ici égal à `72`, le score final normalisé est donc égal à :
```
1000000 * (72-56) / 72 = 1000000 * 2 / 9 ≈ 222222.22
```