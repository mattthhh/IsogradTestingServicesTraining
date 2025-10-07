# Benchmarking

Félicitations, vous venez d'être désigné au prestigieux poste de directeur de la stratégie IA !

Votre première mission est de choisir le modèle de Machine Learning qui alimentera le nouveau chatbot de l'entreprise. Ce n'est pas une mince affaire, il y a de très nombreux LLMs disponibles et vous souhaitez prendre une décision éclairée quant au choix de modèle.

Pour cela, vous décidez de comparer les modèles sur la base de benchmarks, ces tests à grande échelle qui évaluent la performance d'un modèle sur des tâches spécifiques. À partir des résultats, pouvez-vous désigner le LLM qui a le meilleur score moyen ?

## Données

### Entrée

**Ligne 1** : un entier **N**, le nombre de modèles que vous souhaitez comparer.

**N lignes suivantes** : le nom du LLM suivi de 3 scores de benchmark, séparés par des espaces.

### Sortie

Le nom du modèle avec le meilleur score moyen.

## Exemple

Pour l'entrée :
```plaintext
3
Alpaca3 72.84 93.47 95.0
Mistrax9B 77.48 91.5 98.93
TGV4o 81.39 26.92 99.95
```

Votre code devra donc afficher le modèle avec la meilleure moyenne :
```plaintext
Mistrax9B
```

En effet, Mistrax9B a un score moyen d'environ 89.30 alors que ses deux concurrents ont des moyennes à 87.10 et 69.42 respectivement.

## Contraintes

- **N** est compris entre 2 et 20. Les scores à chaque benchmark sont compris entre 0 et 100.
- Il n'y aura jamais d'ex-aequo pour le meilleur modèle.
- Les noms des modèles ne comprennent que des caractères alphanumériques.