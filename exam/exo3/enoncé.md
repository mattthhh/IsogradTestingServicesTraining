# Préparation de paniers alimentaires

Pour cette troisième initiative, vous avez décidé de mettre en place la préparation et la distribution de paniers alimentaires. Bénéficiant d’ingrédients variés, vous voulez dans la mesure du possible proposer des paniers qui plaisent à chaque étudiant venant en récupérer un. Pour ce faire vous avez fait passer un questionnaire aux étudiants dans le besoin, leur demandant ce qu'ils aimeraient, ou n'aimeraient pas trouver dans un panier.
Pour garder un minimum de laxité, vous avez laissé à chaque étudiant la possibilité de faire deux demandes:
- La première est nécessairement un aliment qu'ils aimeraient avoir dans un panier solidaire.
- La seconde peut être un choix un second aliment qu'ils aimeraient trouver ou, au contraire, un aliment qu'ils préféreraient éviter, soit par goût soit par allergie.

En fonction de toutes les demandes qui vous sont arrivées et des ingrédients à votre disposition, vous devez déterminer s'il est possible de répartir les ingrédients dans différents types de paniers de manière à ce que chaque étudiant puisse trouver un panier à sa convenance.

Dans cet exercice, vos ressources vous permettent de préparer autant de paniers d'un même type que vous le souhaitez. Cependant pour éviter une logistique trop importante, un type d'ingrédient ne peut être utilisé que dans un type de panier.

## Données

### Entrée

**Ligne 1** : Deux entiers `I` et `E`, représentant respectivement le nombre d'ingrédients différents et le nombre d'étudiants.
**Prochaines I lignes** : Un chaîne de caractères, représentant le nom d'un ingrédient, constitué de lettres ascii en minuscule et potentiellement d'espaces.
**Prochaines E lignes** : Les goûts d'un étudiants, constitué de deux ingrédients séparés par un `and`. Le second peut être précédé d'un `no`.

- `1<=I<=2000`
- `1<=E<=10000`

### Sortie

Le mot `yes` s'il est possible de constitué des paniers convenant à tous les étudiants avec les ingrédients à disposition, `no` sinon.


## Exemple

Pour l'entrée :
```plaintext
4 5
rice
cucumber
cheese
ham
ham and cucumber
cucumber and no rice
rice and cheese
rice and no ham
rice and no cucumber
```

Votre programme devra renvoyer :
```plaintext
yes
```

En faisant un panier avec `rice` et `cheese` et un autre avec `cucumber` et `ham`, la totalité des contraintes suivantes sont satisfaites.

Pour l'entrée :
```plaintext
4 4
carrot
leek
bell pepper
eggplant
leek and carrot
eggplant and no carrot
bell pepper and carrot
leek and no bell pepper
```

Votre programme devra renvoyer :
```plaintext
no
```

La première et troisième contraintes impliquent de créer un panier avec `leek`, `carrot` et `bell pepper`. Or, un tel panier enfreint la dernière contrainte.