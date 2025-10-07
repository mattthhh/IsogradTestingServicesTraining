# Réseau futuriste

Votre équipe de R&D est en train de travailler sur une nouvelle génération de réseaux de neurones, dont la structure est inspirée du comportement de micro-organismes vivants.

L'architecture du réseau prend la forme d'une grille rectangulaire constituée de cellules, chacune d'entre elles étant à l'un des 5 niveaux possibles d'excitation.

À chaque étape du calcul, toutes les cellules mesurent l'état de leurs voisins puis changent d'état simultanément en fonction de certaines règles :
- Une cellule à l'état 5 passe à l'état 4
- Une cellule à l'état 4 passe à l'état 3
- Une cellule à l'état 3 passe à l'état 2
- Une cellule à l'état 2 passe à l'état 1
- Une cellule à l'état 1 passe à l'état 5 si elle a au moins un voisin à l'état 5. Si ce n'est pas le cas et qu'elle a au moins 2 voisins à l'état 1, elle reste à l'état 1. Dans tous les autres cas, elle passe à l'état 3.

Chaque cellule a 4 voisins (haut, bas, gauche, droite) sauf celles qui se trouvent dans les coins ou sur les bords de la grille (2 et 3 voisins respectivement).

Votre objectif est de trouver une périodicité dans les états du réseau de neurones. En effet, l'état global du réseau finira systématiquement par converger vers un cycle d'états qui se répète dans le temps. Votre objectif est d'identifier l'étape à laquelle vous entrez dans ce cycle, ainsi que la durée de celui-ci.

## Données

### Entrée

**Ligne 1** : deux entiers **W** et **H** compris chacun entre 3 et 50, représentant la largeur et la hauteur de la grille de cellules.

**H lignes suivantes** : l'état initial de la grille, composé de **H** lignes de **W** chiffres chacune, chaque chiffre représentant l'état initial de la cellule correspondante.


### Sortie

Affichez deux lignes :
- Sur la première ligne, un entier représentant le numéro de la première étape faisant partie du cycle.
- Sur la deuxième ligne, un entier représentant la durée du cycle.

Il est garanti qu'au moins un cycle complet sera présent dans les 1000 premières itérations.

## Exemple

Pour l'entrée :
```plaintext
4 3
1411
2321
3351
```

Les états successifs de la grille sont les suivants :
```plaintext
Etat 0 (initial) :
1411
2321
3351

Etat 1 :
3331
1211
2245

Etat 2 :
2223
3135
1134

Etat 3 :
1112
2324
3123

Etat 4 :
3131
1213
2312

Etat 5 :
2323
3132
1231

Etat 6 :
1212
2321
3123

Etat 7 :
3131
1213
2312

Etat 8 :
2323
3132
1231
```

À partir de l'état 4, on peut remarquer que le réseau entre dans un cycle d'états se répétant toutes les 3 itérations. Votre code devra donc afficher :

```plaintext
4
3
```