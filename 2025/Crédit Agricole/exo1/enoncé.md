# Sommelier
Le travail de sommelier est aussi passionnant que difficile : il faut s'adapter aux goûts des clients même si vous ne pouvez pas proposer la bouteille de vin parfaite !

Pour chaque client, proposez la bouteille de vin disponible dans votre cave la plus proche de ses préférences.

La préférence du client est une liste de 10 caractéristiques gustatives représentés par des nombres, trouvez la bouteille disponible en cave la plus proche.

## Données
### Entrée
**Ligne 1 :** 10 entiers séparés par des espaces, représentant la préférence du client.

**Ligne 2 :** un entier N représentant le nombre de bouteilles disponibles en cave

**N lignes suivantes :** 10 entiers représentants les caractéristiques de chaque bouteille de la cave.

### Sortie
Une ligne avec un entier représentant le numéro dans la liste de la bouteille la plus proche des préférences du client.

Pour proposer au client la première bouteille de la liste il faudra ainsi afficher 0, pour la seconde 1 et ainsi de suite.

La proximité entre les caractéristiques d'une bouteille et les préférences est calculée par la somme des écarts de chaque caractéristique au carré (voir la section Exemple plus bas).

### Contraintes
Pour chaque jeu de données, ces différents points sont garantis et n'ont pas besoin d'être vérifiés :

N est compris entre 1 et 1000.
Les caractéristiques sont comprises entre 0 et 1000.
La solution est unique, il ne peut pas y avoir 2 bouteilles ex-aequo.
## Exemple
### Exemple 1
Pour l'entrée :

```
3 5 10 0 0 0 0 0 0 0
3
3 5 25 0 0 0 0 0 0 0
1 4 12 0 0 0 0 0 0 0
0 5 11 0 0 0 0 0 0 0
```
Les écarts avec la préférence du client pour chaque bouteille sont :

- (3 - 3)² + (5 - 5)² + (10 - 25)² = 0² + 0² + 15² = 225
- (3 - 1)² + (5 - 4)² + (10 - 12)² = 9
- (3 - 0)² + (5 - 5)² + (10 - 11)² = 10

Ainsi c'est la deuxième bouteille (à l'index 1 dans la liste) qui est la plus proche des goûts du client. Votre programme devra donc afficher :

```
1
```
### Exemple 2
Pour l'entrée :

```
6 14 13 2 1 4 5 16 16 14
10
13 15 1 16 20 12 6 16 5 5
16 4 19 5 1 3 16 12 5 5
14 10 15 6 2 19 12 14 2 1
1 5 8 12 1 19 15 15 3 3
0 0 5 10 20 20 1 20 4 13
4 7 8 2 11 4 12 4 15 6
14 9 18 0 10 11 8 18 4 5
17 17 5 2 5 13 5 2 3 2
6 20 12 12 2 6 15 20 0 13
11 5 10 18 2 1 16 12 13 19
```
Cette fois, c'est la bouteille à l'index 5 qui est la plus proche avec une distance de 436. Votre programme devra donc afficher :

```
5
```