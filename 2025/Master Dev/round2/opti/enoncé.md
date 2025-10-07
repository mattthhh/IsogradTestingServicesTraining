# Coder Coaster Tycoon 2.0

**Attention** : cet exercice est une variante plus difficile du problème que vous venez de résoudre. Votre code du problème précédent a été reporté sur cette question pour vous aider à démarrer. Vous n'avez pas à trouver la solution optimale pour chaque test : les solutions seront classées en fonction de leur score obtenu, et vous pouvez effectuer plusieurs soumissions.

Après réflexion, vous voulez optimiser le plan de votre parc. Et si vous déplaciez les attractions pour que les visiteurs doivent se déplacer le moins possible entre deux attractions ?

On considère que le parc est construit sur un long chemin sur lequel les attractions sont placées à intervalles réguliers : deux attractions voisines sont à une distance de 1.

À partir de la même liste des visites, proposez un ordre de répartition des attractions, pour minimiser la distance totale parcourue par les visiteurs du parc sur la journée.

## Données

### Entrée

Le format d'entrée est le même que pour le premier exercice.

**Ligne 1** : Deux entiers `nbGroupes` et `nbAttractions` représentant respectivement le nombre de groupes et le nombre total d'attractions disponibles dans le parc.

**nbGroupes lignes suivantes** : Pour chaque groupe, un entier `tailleGroupe` représentant le nombre de personnes dans le groupe, suivi d'un entier `nbVisites` représentant le nombre d'attractions que le groupe souhaite faire. Ensuite, la liste des `nbVisites` attractions choisies par le groupe. Les attractions sont données dans l'ordre dans lequel le groupe va faire les attractions.

### Sortie

Une liste des noms des `nbAttractions` attractions séparée par des espaces.

### Score

Le score est calculé avec la distance parcourue par chaque visiteur pour faire toutes les attractions voulues, en fonction de l'ordre proposé.

Chaque groupe part de la première attraction de sa liste. Pour aller a la suivante, la distance est l'écart de position dans la liste que vous avez fournie. Vous devez donc minimiser la somme des distances parcourues par chaque groupe, pondérées par la taille du groupe (voir exemple plus bas).

Le score final est normalisé entre 0 et 1 000 000. Une solution très optimisée se rapprochera de 1 000 000, le détail de cette normalisation est donné à la fin de l'énoncé.

### Contraintes

Pour chaque jeu de données, ces différents points sont garantis et n'ont pas besoin d'être vérifiés :

- Les noms des attractions font au maximum 100 caractères, uniquement lettres majuscules et minuscules.
- Il y a au maximum 1 000 groupes.
- Il y a au maximum 1 000 attractions différentes.
- Chaque groupe comporte 1 à 1000 membres, et a visité entre 1 et 100 attractions.
- Une attraction peut être visitée plusieurs fois par un même groupe, mais jamais consécutivement.
- Chaque attraction est visitée par au moins un groupe.

Les jeux de données sont les mêmes pour tous les participants. Si votre code ne renvoie pas de solution dans le temps imparti (15 secondes par jeu de données), une erreur s'affichera : le score sera de 0 pour ce dataset, et les datasets suivants ne seront pas évalués.

Attention : votre solution doit pouvoir résoudre tous les datasets, aucun codage en dur ("hardcoding") des solutions ne sera toléré.

## Exemple

### Entrée

```plaintext
3 4
3 3 RollerCoaster WaterSlide RollerCoaster
5 3 WaterSlide FerrisWheel PirateShip
2 1 FerrisWheel
```

### Sortie

Parmi toutes les configurations possibles du parc, on pourrait par exemple choisir l'ordre suivant :

```plaintext
WaterSlide FerrisWheel RollerCoaster PirateShip
```

Le premier groupe commence à RollerCoaster, puis se déplace de 2 pour aller à WaterSlide (en effet dans la liste proposée ces 2 attractions sont à deux positions d'écart), puis se déplace à nouveau d'une distance 2 pour retourner à RollerCoaster. Déplacement total : 4

Le second groupe se déplace de 1 entre WaterSlide et FerrisWheel, puis de 2 entre FerrisWheel et PirateShip. Déplacement total : 3

Le 3e groupe n'a pas à se déplacer.

Total de la distance pondérée : `4 * 3 + 3 * 5 + 0 = 27`. C'est cette valeur qu'il faut minimiser.

## Détails du score

On calcule pour chaque groupe la distance parcourue comme décrit plus haut. Cette distance est pondérée par la taille du groupe. La somme de ces `distances x taille de groupe` est appelée `sommeDistances`

On calcule ensuite la valeur `worstCase`, qui est la somme pour tous les groupes de `tailleGroupe x nbAttractions x nbVisites`. À noter que cette valeur ne dépend pas de la solution proposée.

Le score final de chaque jeu de données est calculé ainsi : `1 000 000 * (worstCase - sommeDistances) / worstCase`

Dans l'exemple ci-dessus, `worstCase` vaut 104. Le score obtenu par la solution proposée est donc `1 000 000 * (104 - 27) / 104` ≈ 740384.6