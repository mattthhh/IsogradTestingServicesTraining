# Livreur de Pizzas

La pizzeria "Chez Luigi" a un défi logistique : livrer les commandes en optimisant les tournées du livreur ! Vous devez concevoir un algorithme permettant au livreur de livrer un maximum de commandes avant de devoir retourner à la pizzeria.

## Règles de livraison

Le livreur suit les règles suivantes :

1. Il charge les commandes **dans leur ordre d'apparition** dans la liste de commandes.
2. Il ne peut pas transporter plus de `C` pizzas à la fois.
3. Dès qu'il essaie de charger une commande qui dépasserait la capacité de son scooter, il part livrer sa cargaison dans l'ordre, puis revient à la pizzeria.

## Données

### Entrée

**Ligne 1** : Deux entiers `N` et `C` séparés par un espace
- `N` représente le nombre total de commandes
- `C` est la capacité maximale du scooter en nombre de pizzas

**Les `N` lignes suivantes** : Trois entiers `x y nbPizzas`, représentant :
- `x` et `y` : coordonnées de livraison de la commande
- `nbPizzas` : nombre de pizzas à livrer à cette adresse

### Sortie

Vous devez afficher une ligne par tournée de livraison. Chaque ligne contient une liste d'indices de commandes (indexées à 0) séparés par un espace.

Dans cet exercice, vous pouvez ignorer les coordonnées `[x, y]` de chaque client.

### Contraintes

- `1 ≤ N ≤ 10 000`
- `1 ≤ C ≤ 1 000`
- `1 ≤ nbPizzas ≤ C`
- `-100 000 ≤ x, y ≤ 100 000`

## Exemple

#### Entrée :
```plaintext
5 10
1 2 3
-3 4 4
5 6 9
7 -8 2
-9 -10 3
```

#### Sortie attendue :
```plaintext
0 1
2
3 4
```

Dans cet exemple, le scooter a une capacité de 10 pizzas maximum :
- Le livreur prend les commandes **0 et 1** (3+4=7 pizzas), puis revient à la pizzeria. Il ne peut pas prendre en plus la commande suivante (9 pizzas)
- Il prend ensuite la commande **2** (9 pizzas), puis retourne à la pizzeria.
- Enfin, il prend les commandes **3 et 4** (2+3=5 pizzas), et revient à la pizzeria.

Votre objectif est donc d'implémenter cet algorithme pour optimiser les tournées du livreur tout en respectant la capacité de son scooter !