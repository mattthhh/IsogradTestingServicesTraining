# Vous êtes ici

La légende raconte qu’une cité cachée, oubliée de tous, se trouve quelque part au cœur d’une jungle inexplorée. Vous, un explorateur chevronné, avez retrouvé un ancien manuscrit décrivant précisément le réseau de ruelles. Equipé de vos drones autonomes, vous êtes bien décidé à prendre en photo chaque centimètre des rues de cette ville !

Votre objectif est de guider ces drones à travers la ville en respectant une stratégie simple : chaque drone prend la première rue non visitée disponible, dans l’ordre d’apparition dans les données d’entrée. Il s'arrêtera si toutes les rues reliées à son intersection actuelle ont déjà été parcourues, ou lorsque sa batterie atteint une charge inférieure ou égale à 0 après avoir atteint une intersection.

Les drones sont envoyés chacun leur tour : dès que le premier drone stoppe son exploration, vous faites décoller le deuxième. Quand celui-ci a terminé son parcours, vous enverrez le troisième, et ainsi de suite. Le point de décollage de tous les drones est l'intersection qui porte l'identifiant `0`.

## Données

### Entrée

**Lignes 1 et 2** :
```
nbDrones battery
nbStreets nbInter
```

- `nbDrones` le nombre de drones à disposition
- `battery` la distance maximale qu'un drone peut parcourir.
- `nbStreets` le nombre de rues de la ville
- `nbInter` le nombre d'intersections : une rue commence et termine par une intersection

**nbStreets lignes suivantes** : Chaque ligne décrit une rue sous la forme :
```
idInter1 idInter2 streetLength
```

- `idInter1 idInter2` les 2 intersections de début et de fin de la rue
- `streetLength` la longueur de la rue

### Sortie

`nbDrones` lignes, où chaque ligne représente le trajet emprunté par un drone, sous la forme d’une liste d’intersections séparées par des espaces.

Chaque drone commence son itinéraire à la base `0` et suit les rues selon l’ordre d’entrée jusqu’à atteindre sa limite de distance `battery`, ou à atteindre une intersection connectée uniquement à des rues déjà visitées auparavant.

**Note** : Une rue peut être parcourue dans un sens ou dans l'autre. Une visite dans un sens compte pour les deux sens.

### Contraintes

- `2 ≤ nbDrones ≤ 10`
- `nbStreets, nbInter ≤ 2 000`
- `battery ≤ 1 000 000`
- Toutes les routes sont uniques : il n'y aura jamais deux routes qui relient la même paire d'intersections.
- Une route ne reliera jamais une intersection à elle-même.
- Les intersections sont numérotées de 0 à `nbInter`-1.

**Important** : un drone peut toujours visiter intégralement une rue si sa batterie n'est pas à 0 ou négative. Par exemple, un drone peut visiter une rue de longueur 15 s'il lui reste 10 de batterie, mais ne pourra pas en revisiter une autre.

## Exemple

### Entrée :
```plaintext
3 50
5 5
3 1 30
0 2 20
3 4 40
1 2 30
0 1 40
```

### Sortie attendue :
```plaintext
0 2 1
0 1 3
0
```

### Explication

![Illustration de l'exemple](https://visualaids.isograd.com/codecontest/fr/codecontest_fr_ot_ctstfr0462.png)

Le premier drone décolle de l'intersection 0, puis :
- Depuis 0, il peut se rendre en 1 ou en 2. La route vers 2 (`0 2 20`) est la première des deux dans la liste, il va donc vers 2.
- Depuis 2, il peut se rendre en 0 ou en 1. La route pour aller à 0 est déjà visitée, il doit donc se rendre en 1.
- En arrivant à l'intersection 1, le drone atteint une charge de 0 (soit 50 - 20 - 30), il arrête donc son parcours. Les intersections visitées sont `0 2 1`.

Le second drone décolle de l'intersection 0, puis :
- Depuis 0, il peut se rendre en 1 ou en 2. La route entre 0 et 2 a déjà été visitée par le premier drone, il doit donc se rendre en 1.
- Depuis 1, il peut se rendre en 0, 2 ou 3. Les routes vers 0 et vers 2 sont déjà visitées, il navigue donc vers l'intersection 3.
- En arrivant à l'intersection 3, le drone a une charge de -20 (soit 50 - 40 - 30), il s'arrête donc à cet endroit. Son parcours est `0 1 3`.

Le dernier drone décolle de l'intersection 0, mais ne peut visiter aucune rue qui n'a pas déjà été parcourue. Il stoppe son parcours immédiatement, le trajet correspondant ne contient donc que l'intersection `0`.