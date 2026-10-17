
---
# Compilation — Notes Réorganisées

## 1. VUE GLOBALE

### Compilateurs et ses cousins

- **Compilateur** : traduit langage en des instructions exécutables.
    
- **Interpréteurs** : analyse instruction après l’autre et l’exécute immédiatement, plus petit qu’un compilateur mais son programme est plus lent, ainsi il ne cache pas le code.
    
- **Préprocesseurs**
    
- **Langages intermédiaires (Pseudo-code)** : comme Java, compilé pour générer du pseudo-code (.class) qui sera interprété par la JVM.  
    **Q : pourquoi les langages ne sont pas tous des p-code ?**
    
- **Éditeurs de liens** : vient après la compilation.
    

### Langages

- Assemblage
    
- Langage machine
    

---

## 2. Structure de compilateur

### Phase d’analyse

- **Analyseur lexical (scanner)** : connaître les types des mots (variable, nombre, condition…). Utilisation des REGEXP et automates à états finis.
    
- **Analyseur syntaxique (parser)** : vérifie que la syntaxe est correcte (exemple : présence de "(" après un "if"). Utilise grammaire et automate à pile.
    
- **Analyseur sémantique** : vérifie si ce que vous avez écrit a du sens (ex : additionner un entier à une chaîne).
    

### Phase de production

- Génération de code intermédiaire
    
- Optimisation de code : dépend ou non de la machine cible
    
- Génération de code cible : dépend du processeur. Les _machines abstraites (virtuelles)_ permettent d’abstraire l’architecture.
    

### Gestion en parallèle

- **Table de symboles** : contient les informations des identificateurs (type, place mémoire…).
    
- **Traitement des erreurs**
    

---

# 3. ANALYSE LEXICALE

- **Rôle** : prendre les caractères saisis, produire des unités lexicales pour l’analyseur syntaxique (élimine tabs, commentaires…).
    
- **Unité lexicale** : groupe/classification de chaînes lues (identificateur, opérande, mots-clés…).
    
- **Modèle** : règles permettant de dire qu’une chaîne appartient à une unité lexicale (décrit avec REGEXP).
    
- **Lexème** : chaînes du programme vérifiant les règles d’une unité lexicale (ex : _toto_, _adam_ → lexèmes de IDENT).
    

### Définitions

- **Alphabet** : ensemble non vide dont les éléments sont des lettres.
    
- **Longueur(mot)** = nombre de symboles qui le composent (|mot|).
    
- **Aⁿ** : mots de longueur n formés depuis l’alphabet A.
    
- **Fermeture itérative A*** : union de tous les mots de toute longueur.
    
- **Langage formel** : sous-ensemble de A*.
    
- Note : un langage utilise des mots formés d’alphabets.
    

---

# 4. LANGAGE RÉGULIER

Un langage régulier sur un alphabet A :

- {x} et {y} sont des langages réguliers (et {x}*, {y}*)
    
- {x}{y} (et ({x}{y})*) = {xy} et {xy}*
    
- {x} ∪ {y} (et ({x} ∪ {y})*) = {x, y} et {x, y}*
    

### Expression régulière (présentation des langages réguliers)

#### Transformations (delim*)

- a + b : {a} ∪ {b}
    
- ab : {a}{b}
    
- (a + b)* : ({a} ∪ {b})*
    

#### Désignation

Si `a` désigne A et `b` désigne B alors :

- `a + b` ou `a|b` désigne A ∪ B
    
- `ab` désigne A.B
    
- `a*` désigne A*  
    Les expressions régulières peuvent être regroupées dans _des définitions régulières_ (comme des variables).
    

#### Abréviations

- aa* : a+
    
- a | élément_neutre : a? (donc 'a' ou rien)
    

---

# 5. AUTOMATES

Le langage doit être régulier pour être présenté dans un automate.

## Automate à états finis

### Construction d’un AEF à partir d’une REGEXP

- **Concaténation (r.g)** : lier les états finaux du premier à l’état initial du second par une ε-transition.
    
- **Union (r + g)** :
    
    - créer un nouvel état initial avec deux ε-transitions vers les anciens initiaux
        
    - créer un nouvel état final et lier les anciens finaux à celui-ci par ε-transitions
        
- **Automate de r+** : relier tous les états finaux à l’état initial par ε.
    
- **Automate de r*** :
    
    - ajouter deux états (initial et final)
        
    - depuis le nouvel initial → ε → ancien initial **ou** nouvel final
        
    - depuis ancien final → ε → nouvel final **ou** ancien initial
        

---

## Automates finis déterministes (AFD)

Utilisés pour éviter le backtracking.  
Règles :

- aucune transition portant le même symbole depuis un même état
    
- supprimer les ε-transitions
    

### Déterminisation d’un AFN avec ε

1. Calculer la ε-closure de l’état initial
    
2. Pour chaque état de cette closure : quels états atteint-on par ‘a’ ? puis par ‘b’ ?
    

---

## Minimisation

1. S’assurer qu’il est déterministe
    
2. Éliminer états non accessibles
    
3. Éliminer états ne menant à aucun final
    
4. Compléter automate avec un état puits
    
5. Partitionner : {états finaux}, {autres}
    
6. Affiner les classes (états équivalents)
    
7. Répéter jusqu’à stabilité
    

---

## Flex

Créer son propre analyseur lexical (fichier de spécifications).

---

## Relations importantes

```
(a+b)* = (a*+b*)* = (a*b*)* = (a*b)*a* = a*(ba*)*
a(ba)* = (ab)*a
```

---

## From automata to regexp — Lemme d’Arden

### À gauche (version du cours)

`L = aL + b ⇔ L = a* b`  
Équations : si L₁ sort par ‘a’ vers L₂ et par ‘b’ vers L₃ alors :  
`L₁ = aL₂ + bL₃`  
(Si L₁ est final → ajouter ε)

### À droite

`L = La + b ⇔ L = b a*`  
Si L₁ reçoit ‘a’ depuis L₂ et ‘b’ depuis L₃ :  
`L₁ = L₂ a + L₃ b`

---

# 6. Analyse Syntaxique

Un mot = suite d’unités lexicales.  
Input : lexèmes. Output : arbre syntaxique.  
Vérifie que les lexèmes respectent la grammaire.

### Types de parsers

- **Bottom-up**
    
- **Top-down**
    
    - Avec backtracking
        
    - Sans backtracking
        
        - Recursive Descent
            
        - Predictive (LL)
            

### Grammaire

Ensemble : terminaux, non-terminaux, axiome, règles de dérivation.

---

## Top-Down (sans backtracking)

Les grammaires ne doivent pas avoir :

- Récursivité gauche
    
- Non-déterminisme
    
- Ambiguïté
    

### Left Recursion

A → Aα | β  
Cause des boucles infinies.  
Transformation :

```
A  → βA'
A' → αA' | ε
```

### Ambiguïté

#### Ambiguïté de précédence

Ex : a + b * c → plusieurs arbres.  
Solution : introduire E, T, F selon niveaux.

#### Ambiguïté d’associativité

Ex : i+i+i  
Solution : imposer un sens (gauche ou droite).

---

## Recursive Descent

Chaque non-terminal → une procédure récursive.

---

## Predictive Parsers

### Premier & Suivant (First & Follow)

_(Tu avais déjà les détails, inchangés pour respecter la consigne.)_

---

## LL(1)

### Table d’analyse

- E → TE' placé dans les premiers de (TE’)
    
- T → *F' | ε :
    
    - T → *F' dans case (T, *)
        
    - T → ε dans les Suivants(T)
        

### Vérification d’un mot

Utilisation d’une pile + table d’analyse.

---

## Récursivité à gauche non-immédiate

A → ... Aα (indirect).  
On la rend immédiate puis on applique la transformation habituelle.

---

## Grammaire propre

Pas de règle A → ε.  
On remplace A par ε dans les règles où A apparaît.

---

## Factorisation à gauche

Avant LL(1) :

1. enlever ambiguïté
    
2. rendre la grammaire propre
    
3. éliminer récursivité gauche
    
4. factoriser
    

---

# 7. SLR

## Canonical LR(0) Collection

- Augmented Grammar
    
- Closure
    
- Goto
    

### Items

On déplace le point, génère les états I₀, I₁ = goto(I₀, X), etc.

---

## LR(0) — Remplissage de table

|Cas|Action|
|---|---|
|`A → α • a β` dans Iᵢ et `Goto(Iᵢ, a) = Iⱼ`|`ACTION[i, a] = shift j`|
|`A → α •` et `A ≠ S'`|`ACTION[i, a] = reduce A → α`|
|`S' → S •`|`ACTION[i, $] = accept`|
|`Goto(Iᵢ, A) = Iⱼ`|`GOTO[i, A] = j`|

---
## Analyser un mot:
initialiser la pile par: empiler $ puis empiler l'état 0 (0 tout court, çad: pile= [$, 0]), entrée = [mots, $] 
si M[sommet, a] = acc alors succes()
si M[sommet, a] = dj alors empiler a, puis j, avencer pointeur de lecture de mot
si M[sommet, a] = rj alors dépiler 2*|longeur_production_regle_j|, puis empiler le pere de production j, puis empiler M[new_sommet, ce qui le précede]

# Exam prep

| LL                             | LR                        |
| ------------------------------ | ------------------------- |
| Ambiguité(faire la regle #sur) | Ambiguité                 |
| *[Grammaire propre]*           | Premiers & Suivants       |
| ==Récursivité à gauche==       | ==Collections des items== |
| Factoriser à gauche            | *[Automate]*              |
| ==Premiers & Suivants==        | ==Table d'analyse==       |
| Table d'analyse                | ==Analyser mot==          |
| Analyser mot                   | Arbre derivation          |
| Arbre dérivation               |                           |
Pour montrer qu'une grammaire n'est pas LL(1) on peut vérifier si:
- il est  ambigue
 - il est  récursive à gauche
 - il est non factoriser à gauche 
ou bien pour être #sûr et montrer quelle l'est :
 - Pour chaque non terminal A: Les Premier(chaque production de A) ne doivent pas s'intersecter.
 - si on a A->ε alors Suivant(A) ne doivent pas s'intersecter avec Premier(chaque production de A)
 - il doit etre factoriser à gauche 