# Faussaire de vins
**Attention :** cet exercice est une variante plus difficile du problème que vous venez de résoudre. Votre code du problème précédent a été reporté sur cette question pour vous aider à démarrer. Vous n'avez pas à trouver la solution optimale pour chaque test : les solutions seront classées en fonction de leur score obtenu, et vous pouvez effectuer plusieurs soumissions.

Votre métier de sommelier vous frustre : vous savez qu'avec votre nez d'exception, vous pourriez mélanger vos vins en cave pour proposer des vins encore plus proches des goûts de vos clients !

Désormais, vous pouvez afficher plusieurs vins de la liste : ceux-ci seront mélangés avant d'être proposés au client. Saurez vous trouver le vin ultime ?

Note pour les curieux : cet énoncé est inspiré du faussaire bien réel Rudy Kurniawan !

## Données
### Entrée
Le format d'entrée est le même que pour le premier exercice.

**Ligne 1 :** 10 entiers séparés par des espaces, représentant la préférence du client.

**Ligne 2 :** un entier N représentant le nombre de bouteilles disponibles en cave

**N lignes suivantes :** 10 entiers représentants les caractéristiques de chaque bouteille de la cave.

### Sortie
Une ligne d'entiers séparés par des espaces représentant les vins que vous voulez mélanger.

Vous pouvez mélanger jusqu'à 50 vins. Un même vin peut être ajouté plusieurs fois au mélange, une "dose" sera ajoutée au mélange à chaque fois (voir la section Exemple plus bas).

Les caractéristiques du mélange est la moyenne des caractéristiques des vins mélangés.

**Note :** votre solution à l'exercice précédent a été transférée, et est déjà une solution valide ! Exécutez la directement pour marquer vos premiers points.

### Score
Pour chacun des tests, votre solution obtiendra un score entre 0.0 et 1 000 000. Votre classement sera établi sur la somme des scores sur chaque test.

La formule de calcul est la suivante : score = (1.0 - (écart / norme_goût)) * 1 000 000.

- `écart` : est l'écart entre le mélange et le vin attendu tel que calculé au premier exercice (somme des écarts au carré)
- `norme_goût` : la somme des caractéristiques du vin attendu au carré
A noter que ce score peut théoriquement être négatif. S'il l'est, il sera mis a 0.

**Important :** seule votre meilleure soumission sera prise en compte pour votre classement final. Votre score global ne peut ainsi pas baisser.

### Contraintes
- **N** est compris entre 1 et 1000.
- Les caractéristiques sont comprises entre 0 et 1000.
- La sortie doit être composée de 1 à 50 entiers maximum.
Exemple
Pour l'entrée :

```
3 5 10 0 0 0 0 0 0 0
3
3 5 25 0 0 0 0 0 0 0
1 4 12 0 0 0 0 0 0 0
0 5 11 0 0 0 0 0 0 0
```
Une solution possible est :

```
1 1 1 2
```
Le mélange résultant aura les caractéristiques suivantes :

```
0.75 4.25 11.75 0 0 0 0 0 0 0
```
L'écart sera donc de (3 - 0.75)² + (5 - 4.25)² + (10 - 11.25)² = 8.6875

`norme_goût` sera quant à elle égale à 3² + 5² + 10² = 134. Notez que cette valeur ne dépend pas de la solution proposée.

Ainsi, le score de cette solution est de :

(1 - 8.6875 / 134) * 1 000 000 = 935 167.9