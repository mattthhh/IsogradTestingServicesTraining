# Dernier Kilomètre
Bravo pour votre qualification en finale ! Vous aurez ici à résoudre un unique problème d'optimisation, comme le deuxième exercice de votre session de qualification. Vous n'avez pas à trouver la solution optimale : les solutions seront classées en fonction de leur score obtenu, et vous pouvez effectuer plusieurs soumissions.

Dans un monde où la logistique urbaine est en pleine mutation, la livraison de colis doit allier efficacité et responsabilité écologique. Votre mission est simple en apparence : livrer tous les colis en minimisant l’empreinte carbone de votre flotte de véhicules.

Deux options s’offrent à vous :

- Les vélos, propres mais à la capacité limitée et de courte portée
- Les camionnettes, plus puissantes mais aussi plus polluantes

A vous de concevoir la flotte idéale pour assurer la livraison complète des colis. Choisissez les véhicules de votre flotte ainsi que l'emplacement du dépôt dont partiront tous les véhicules.

Saurez-vous trouver l’équilibre parfait entre efficacité logistique et impact environnemental ? À vous de coder la solution la plus ingénieuse et écologique !

## Données
### Entrée
Le format d'entrée est le suivant :

**Ligne 1**, les caractéristiques des vélos : `productionCost maxDistance maxStops maxWeight consoKm` (tous des nombres flottants sauf `maxStops` qui est entier)

- `productionCost` le coût carbone de la production d'un véhicule
- `maxDistance maxStops maxWeight` sont les limites du véhicule en termes de distance, d'arrêts maximum et de poids transportable par trajet
- `consoKm` le coût carbone d'un kilomètre parcouru par ce véhicule

**Ligne 2**, les caractéristiques des camionnettes, au même format

**Ligne 3**, un entier **N**, le nombre de commandes

**N lignes suivantes**, 3 nombres flottants représentant une commande au format `x y packageWeight`, donnant les coordonnées en kilomètres de livraison et le poids du colis.

### Sortie
La première ligne doit contenir deux nombres flottants séparés par un espace, les coordonnées du dépôt `x y`.

Ensuite, chaque ligne décrit un véhicule et sa tournée, au format `vehicleType idStop1 idStop2 ...`

- Les identifiants de livraison (`idStopX`) correspondent au numéro de commande dans l'ordre fourni en entrée, numéroté de 0 à `N`-1
- Le type de véhicule est `V` pour un vélo, `C` pour une camionnette

Chaque véhicule effectue une seule tournée, et se déplace entre les points de livraison en ligne droite. Le coût du retour au dépôt n'est pas comptabilisé.

Les distances sont calculées en distance euclidienne : `sqrt((x1 - x2)² + (y1 - y2)²)`

Contraintes
- `N ≤ 10 000`
- `0 ≤ x, y ≤ 1 000 000`
- `productionCost, maxDistance, maxStops, maxWeight, packageWeight ≤ 10^12`
- `maxStops ≤ N`
- Les nombres flottants sont donnés avec une précision allant de 1 à 4 décimales. Une tolérance de 10^-6 sera appliquée sur les limites des véhicules pour éviter les problèmes d'arrondis
- Toutes les adresses à livrer se trouvent sur des coordonnées distinctes
- Il existe au moins une solution qui parviendra à livrer toutes les commandes
- Toutes les caractéristiques des vélos (`productionCost maxDistance maxStops maxWeight consoKm`) sont inférieure ou égales à celles des camionettes

Les jeux de données sont les mêmes pour tous les participants. Si votre code ne renvoie pas de solution dans le temps imparti (15 secondes par jeu de données), une erreur s'affichera : le score sera de 0 pour ce dataset, et les datasets suivants ne seront pas évalués.

Attention : votre solution doit pouvoir résoudre tous les datasets, aucun codage en dur ("hardcoding") des solutions ne sera toléré.

### Score
Le score est calculé pour chaque jeu de données comme suit :

```
score = 1.000.000 * (cout_base - cout_solution) / cout_base
```
Ici, `cout_base` est un coût spécifique à chaque jeu de données, calculé avec une heuristique volontairement inefficace. Il est garanti que chaque jeu de données admet au moins une solution avec un score supérieur à 500 000.

`cout_solution` est le coût carbone de votre solution. Ce score est la somme pour chaque véhicule de :

- Son coût de production `productionCost`
- Sa distance parcourue multipliée par `consoKm`

**Important :** seule votre meilleure soumission sera prise en compte pour votre classement final. Votre score global ne peut ainsi pas diminuer.

## Exemple
### Entrée :
```
50.0 5.0 6 20.0 1.0
80.0 20.0 3 100.0 10.0
6
1.1268 7.0616 0.7234
2.9560 7.1608 4.9361
7.6233 3.8512 2.7024
5.4489 5.6413 6.2798
5.4932 4.2839 6.9587
8.2525 5.2595 10.1155
```
### Solution possible :
Pour ce jeu de données, on peut par exemple afficher la sortie suivante :
```
5.5 5.0
C 3 1 0
V 4 2 5
```
### Explication
L'exemple et sa solution sont illustrés ci-dessous :

Illustration de l'exemple

Ici, on place le dépôt en x=5.5, y=5.0 et on utilise deux véhicules pour effectuer les livraisons :

- Une camionnette (en rouge) qui dessert les adresses 3, 1 puis 0
- Un vélo (en vert) qui fait les livraisons en 4, 2 puis 5

Le coût de cette solution est approximativement égal à 188.38:

- Pour la camionnette : 80 à l'achat puis 53.95 pour avoir parcouru 5.394 km
- Pour le vélo : 50 à l'achat puis 4.43 pour avoir parcouru 4.43 km.

Pour le premier jeu de données, cout_base vaut environ 323.88. Le score de la solution ci-dessus vaut donc environ 1000000 * (323.88 - 188.38) / 323.88 ≈ 418364.

### Illustration des jeux de données
Afin de vous aider à visualiser les données d'évaluation, voici la cartographie des commandes pour tous les jeux de données (à l'exception du premier qui correspond à l'exemple ci-dessus). La couleur d'un point correspond au poids de la commande, bleu étant le plus léger et rouge étant le plus lourd.

Illustration des jeux de données

L'image en haute définition est disponible sur ce lien.