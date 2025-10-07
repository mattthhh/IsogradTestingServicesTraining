# Dressing solidaire

Comme deuxième initiative, vous décidez de créer un lieu permettant aux étudiants, soit de donner des vêtements dont ils ne se servent plus, soit de venir en récupérer gratuitement.

Par souci de simplicité, vous construisez simplement un bac dans lequel il est possible de déposer n'importe quel type de vêtement. Au fur et à mesure des personne venant y déposer leurs vêtements, ces derniers s'empilent ainsi les uns sur les autres. Le bac étant assez étroit, il n'est cependant pas très aisé de regarder les vêtements du dessous. Ainsi, pour regarder ce qu'il se trouve en dessous il est obligatoire de sortir au préalable ce qui se trouve au dessus du bac, quitte à l'y remettre par la suite.

De plus, pour garder trace du stock à l'intérieur, et l'afficher en ligne, vous avez installé une caméra à l'intérieur qui, à l'aide d'un petit programme de votre création, reconnaît les types de vêtements et envoie un message avec le type en question précédé de `+` s'il s'agit d'un don ou de `-` si une personne l'a pris.

Votre rôle est de vérifier que votre petit programme fonctionne bien et qu'il n'y a pas d'incohérence dans les données qu'il donne.

## Données

### Entrée

**Ligne 1** : Un entier `N`, représentant le nombre de messages envoyés par votre programme.
**Prochaines N lignes** : Une chaîne de caractère pouvant comporter un espace ou un tiret et précédé du symbole `+` ou `-`.

L'entier `N` est compris entre `1` et `100` inclus.

### Sortie

`yes` si toutes les notes concordent entre-elles, `no` sinon.
Nous considérons le bac vide au début des notes.


## Exemple

Pour l'entrée :
```plaintext
6
+ Scarf
+ Boots
- Boots
+ Dress
- Dress
- Scarf
```

Votre programme devra renvoyer :
```plaintext
yes
```

Ici, lorsque l'item `Boots` est récupérer c'était bien le dernier item a avoir été mis. Il en va de même pour l'item `Dress`. Enfin, lorsque quelqu'un récupère l'item `Scarf`, les deux autres items ont déjà été récupérés.

Pour l'entrée :
```plaintext
6
+ Scarf
+ Boots
- T-shirt
+ Dress
- Dress
- Dress
```

Votre programme devra renvoyer :
```plaintext
no
```

Ici, il est possible de noter deux incohérences. La première est qu'un `T-shirt` a été récupéré sans que personne n'en ai donné un au préalable. La seconde est que deux `Dress` ont été récupérées alors qu'une seule n'a été donnée.

Pour l'entrée :
```plaintext
4
+ Scarf
+ Boots
- Boots
+ Dress
```

Votre programme devra renvoyer :
```plaintext
yes
```

Il n'est pas nécessaire que le bac finisse vide. Cette entrée est donc valide.

Pour l'entrée :
```plaintext
4
+ Scarf
+ Boots
- Scarf
- Boots
```

Votre programme devra renvoyer :
```plaintext
no
```

L'item `Scarf` a été récupéré alors qu'il se trouvait en dessous des `Boots`, ce qui n'est donc pas possible.
