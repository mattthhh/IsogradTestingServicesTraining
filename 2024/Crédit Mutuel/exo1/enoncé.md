# La cible

Vous avez été choisi pour participer à l'organisation des épreuves de pentathlon moderne aux prochains championnats du monde! Il y aura, comme son nom l'indique, cinq épreuves et chacune d'entre-elles propose son lot de problèmes à résoudre. Que le championnat commence!

Lors de cette édition, le pentathlon commencera par l'épreuve de tir. Pour cette épreuve, les athlètes doivent tirer sur une cible, ronde, imprimée sur une carte carrée cartonnée dont la longueur du côté est exactement égale au diamètre de la cible.

Vous remarquez, de par le talent des athlètes, que même quand ils manquent la cible, le tir atteint quand même toujours le carton carré sur lequel cette dernière est imprimée. Mathématicien à vos heures perdues, vous vous dites alors que vous pourriez profiter de cette épreuve pour entraîner votre fibre scientifique et notamment calculer une approximation du nombre pi.
En effet, vous estimez que le ratio entre l'aire de la cible et l'aire de la carte cartonnée doit être semblable au ratio entre le nombre de tirs atteignant la cible et le nombre de tir total.

En faisant les calculs, vous trouvez que `pi ~ 4 x I / N`, avec `I` le nombre de tirs ayant atteint la cible et `N` le nombre de tirs total.

## Données

### Entrée

**Ligne 1** : Un entier `N`, représentant le nombre de coups tirés.

**Ligne 2 à N+1** : Deux nombre flottants `X` et `Y`, représentant les coordonnées de chaque tir.

L'entier `N` est compris entre `1` et `60` inclus.
Les flottants `X` et `Y` sont compris entre `-1.000` et `1.000` est sont donnés avec une précision de 3 chiffres après la virgule.

### Sortie

Une approximation de pi, calculée de la manière expliquée, en fonction du ratio des tirs ayant touché la cible, arrondie à 3 chiffres après la virgule.

La cible est un disque centré en `(0,0)` avec un rayon de `1`.
Un tir `(x,y)` atteint donc la cible si `x*x+y*y<=1`.


## Exemple

Pour l'entrée :
```plaintext
5
0.467 0.566
-0.964 -0.909
-0.998 -0.612
-0.840 0.512
-0.422 -0.448
```

Votre programme devra renvoyer :
```plaintext
2.400
```

Ici, seuls `3` tirs sur `5` sont dans la cible, le premier, le quatrième et le cinquième. Le résultat doit donc être `4 x 3 / 5 = 2.400`.