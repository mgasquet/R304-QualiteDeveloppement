---
title: TP3 &ndash; Qualité du code - Les principes SOLID
subtitle: SOLID, Qualité, Interface, Abstraction, Héritage, Composition, Injection de dépendances, Design Patterns
layout: tutorial
lang: fr
---

Dans la première partie de cette ressource, nous avons parlé de **conception logicielle** et notamment comment modéliser cela à l'aide de **diagrammes de classes de conception** et de **diagrammes de séquences des interactions**.

Cependant, savoir modéliser la conception ne garantit en rien la qualité de celle-ci. Un plan de construction d'un bâtiment peut être tout à fait valide d'un point de vue technique, mais donnera potentiellement une bâtisse qui s'écroulera dans quelques années si elle a été mal pensée.

On a la même logique au niveau du développement logiciel. Un logiciel mal conçu peut répondre à un besoin et satisfaire le client et ses utilisateurs dans l'immédiat, mais il sera alors très difficile de le faire évoluer sur la durée.

De manière générale, les principes liés à la qualité du développement s'assurent que le logiciel que vous allez construire pourra évoluer facilement tout en satisfaisant les besoins actuels.

Tout cela est difficile à mettre en place au premier abord, car il peut parfois être bien plus rapide et facile de développer une solution peu qualitative, mais qui fonctionne. Néanmoins, le code produit ne tiendra pas au fur et à mesure que l'application va grossir ce qui conduira finalement à la réécriture d'une partie voir de la totalité du code ou pire, l'abandon du projet.

C'est un phénomène qui touche beaucoup d'entreprises du monde du développement. Face au besoin de délivrer une solution rapidement, l'aspect qualité est parfois négligé. Au bout de plusieurs années, il est très compliqué d'ajouter de nouvelles fonctionnalités et d'éviter les bugs. Une nouvelle personne rentrant dans le projet ne comprend rien au code. Le client n'est plus satisfait, car les nouvelles fonctionnalités sont délivrées moins fréquemment et de plus en plus de bugs apparaissent. C'est une barque qui prend l'eau sur laquelle on place du sparadrap pour boucher les trous. Mais à chaque fois qu'un trou est bouché, deux nouveaux apparaissent. Le client transfère le projet à une autre entreprise, qui ne comprend rien à ce qu'elle récupère... Plus formellement, on dit que la [**dette technique**](https://fr.wikipedia.org/wiki/Dette_technique) s'accumule.

Tout cela est aussi dur pour le développeur. Travailler dans un tel environnement est très désagréable et peut même dégoûter du développement. Jusqu'ici, vous avez travaillé sur des projets relativement petits (même pour vos SAEs) mais vous devriez être plus conscients de cette problématique après votre période de stage ou d'alternance.

L'ingénieur doit avoir une vision à long terme et prendre en compte les évolutions possibles de son programme. Pour l'aider dans cette tâche, il dispose de différents outils : les principes liés à la qualité du code, comme les principes **SOLID** et aussi les **design patterns**. La maîtrise de ces outils différencie un codeur (une IA ?) d'un ingénieur. Le codeur sait produire du code, l'ingénieur sait produire des logiciels durables.

Les **frameworks** sont des outils qui englobent différents **design patterns** et "forcent" le développeur (de par leur structure) à respecter un certain niveau de qualité dans la conception (parfois, sans qu'il s'en rende compte). Nous allons étudier plusieurs **frameworks** l'année prochaine.

Bref, dans ce cours, nous allons commencer par nous intéresser aux **principes SOLID** qui constituent la porte d'entrée vers un programme bien conçu. Nous allons également commencer à parler de **design patterns** (nous allons en introduire 2) mais nous les étudierons plus en détail dans les prochains TP.

## Les principes SOLID

Les **principes SOLID** représentent un acronyme lié aux 5 principes clés pour obtenir un logiciel qualitatif :

* Le principe de **responsabiltié unique** (`S`ingle responsability)

* Le principe **ouvert/fermé** (`O`pen/Close)

* Le principe de **substitution de Liskov** (`L`iskov substitution)

* Le principe de **ségrégation des interfaces** (`I`nterface segregation)

* Le principe **d'inversion des dépendances** (`D`ependency inversion)

Le respect de ces principes permet d'améliorer le principe de **faible couplage** et de **forte cohésion** des classes (que nous avons abordé précédemment), l'évolutivité du logiciel, la réduction du risque de bugs liés à l'architecture...

Les **design patterns** sont des solutions à des problèmes bien définis qui fournissent des modèles réutilisables et adaptables à de nombreux projets. Ces patterns contribuent notamment à mieux respecter les principes **SOLID**. En revanche, utiliser **design patterns** ne garantit pas toujours une qualité de code respectant **SOLID** et peut même être contre-productif — il faut donc savoir les utiliser au bon endroit et au bon moment.

Dans un logiciel développé d'une telle manière, généralement, l'ajout d'une nouvelle fonctionnalité se résume à l'ajout de nouvelles classes ou de méthodes **sans avoir besoin de modifier ou de récrire les classes existantes**. Le programme est ouvert à l'extension, mais fermé aux modifications (qui pourraient entraîner elles-mêmes d'autres modifications...).

Dans ce TP, nous allons étudier chaque principe et nous allons vous fournir du code qui est (la plupart du temps) fonctionnel, mais développé sans respecter **SOLID**. Vous allez alors constater que :

* Il est difficile d'ajouter de nouvelles choses.
* L'ajout de fonctionnalités ou d'éléments entraîne la modification de multiples classes.
* Des bugs parfois assez inattendus peuvent survenir.
* Les tests unitaires sont difficiles à gérer.

Ensuite, nous allons voir comme un des principes **SOLID** permet de régler cela, et vous allez donc devoir **refactorer** les différentes applications. **Refactorer** du code (ou réusiner du code en français) signifie retravailler le code source du programme sans pour autant ajouter de nouvelles fonctionnalités à l'application. Il s'agit d'améliorer la qualité du code.

**Attention** : Dans plusieurs exercices, il vous sera demandé de **générer un diagramme de classes** (avec `IntelliJ` ou autre IDE qui propose cette fonctionnalité). Bien que les diagrammes générés puissent être parfois erronés, et il vaut mieux faire le dessin soit-même, cela vous fera gagner du temps. Il est fortement conseillé de prendre des **captures d'écran** de chaque diagramme de classes et de les sauvegarder dans un sous-dossier de votre dépôt. Certains diagrammes permettent de comparer l'évolution de l'architecture et des dépendances avant/après **refactoring**.

<div class="exercise">

1. Pour commencer, clonez en local le **dépôt gitlab** forké dans votre espace privé dans le cours de qualité de développement : [https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/etu/votre_login/tp3](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/etu/votre_login/tp3) en remplaçant `votre_login` par le login que vous utilisez pour accéder au serveur gitlab du département.

2. Ouvrez le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur.

3. À la fin de chaque séance, n'oubliez pas de faire un **push** vers votre dépôt distant sur **Gitlab**.

</div>

Ce projet contient divers **paquetages** contenant le code de base pour chaque exercice que nous allons traiter.

### Principe de responsabilité unique (Single Responsability)

Pour mener à bien le déroulement d'une fonctionnalité, le programme va faire appel à diverses classes qui vont interagir entre elles (comme nous l'avons vu avec le DSI). Ces classes vont **traiter** la demande. Chaque classe possède la **responsabilité** d'effecteur une partie de ce traitement. 

Le principe de **responsabilité unique** indique qu'une classe ne doit pas posséder plus d'une responsabilité. Une responsabilité concerne des **opérations** (traitement, méthodes) de **même nature**. Nous avions déjà abordé cela plus tôt dans le cours sur les diagrammes de séquences en parlant d'architecture centralisée et distribuée. Nous avions vu qu'une **distribution** du traitement (et donc des responsabilités) était plus conseillée. C'est un peu le même principe ici.

**Robert C. Martin** dit : "_Si une classe a plus d’une responsabilité, alors ces responsabilités deviennent couplées. Des modifications apportées à l’une des responsabilités peuvent porter atteinte ou inhiber la capacité de la classe de remplir les autres. Ce genre de couplage amène à des architectures fragiles qui dysfonctionnent de façon inattendue lorsqu’elles sont modifiées._"

En bref, **une classe ne doit changer que pour une seule raison**. Si diverses raisons liées à des responsabilités différentes impliquent de modifier la classe, le principe de responsabilité unique n'est donc pas respecté.

Par exemple, considérons le code suivant :

```java
class Email {

   private String sujet;

   private String[] destinataires;

   private String contenu;

   public Email(String sujet, String[] destinataires, String contenu) {
      this.sujet = sujet;
      this.destinataires = destinataires;
      this.contenu = contenu;
   }

   public String getSujet() {
      return sujet;
   }

   public String[] getDestinataires() {
      return destinataires;
   }

   public void envoyer() {
      //Code complexe pour envoyer un mail...
   }

}

class Main {

   public static void main(String[]args) {
      Email m = new Email("Hello", new String[]{"test@example.com"}, "Hello world!");
      m.envoyer();
   }

}
```

Ici, la classe **Email** a deux responsabilités clairement identifiables : **stocker** les informations d'un mail et **l'envoyer**. Le principe de responsabilité unique n'est donc pas respecté. Pour régler cela, il faudrait donc mettre en place une nouvelle classe qui se charge de l'envoi d'un mail :

```java
class Email {

   private String sujet;

   private String[] destinataires;

   private String contenu;

   public Email(String sujet, String[]destinataires, String contenu) {
      this.sujet = sujet;
      this.destinataires = destinataires;
      this.contenu = contenu;
   }

   public String getSujet() {return sujet;}

   public String[] getDestinataires() {return destinataires;}

}

class ServeurMail {

  public void envoyerMail(Email mail) {
      //Code complexe pour envoyer un mail...
  }

}

class Main {

   public static void main(String[]args) {
      Email e = new Email("Hello", new String[]{"test@example.com"}, "Hello world!");
      ServeurMail serveur = new ServeurMail();
      serveur.envoyerMail(e);
   }

}
```

Ici, chaque classe à **une responsabilité unique** : si la logique pour envoyer un mail change, la classe **Email** n'est pas impactée.

Le principe de responsabilité unique s'applique également aux **paquetages** : chaque paquetage est lié à une responsabilité du programme. Dans un logiciel plus complet, on aurait différents paquetages avec différents rôles : IHM, contrôleurs, services, stockage... (et on pourrait (même *devrait*) aller plus en détail).

Ce principe semble assez facile à mettre en place, mais dans la réalité, on retrouve malheureusement des classes (et des paquetages) "fourre-tout" qui deviennent illisibles au fur et à mesure de l'évolution du programme. Si votre classe a trop de méthode, c'est peut-être qu'elle possède plus d'une responsabilité et que celles-ci pourraient être mieux réparties.

<div class="exercise">

1. Ouvrez le paquetage `srp1`. Examinez le code. Il s'agit d'un programme qui permet de faire un simple calcul (pour le moment, une addition). Actuellement, la classe `Client` possède trois responsabilités (certaines sont très simples et tiennent sur une ligne). Identifiez-les.

2. Refactorez le code pour répartir les responsabilités de `Client` en trois nouvelles classes distinctes (sans compter `Client`). Pensez notamment qu'après votre refactoring, les diverses demandes de modifications futures soient mieux cloisonnées. Ainsi les demandes de changements suivants du code ne devraient pas toucher le code de votre nouvelle classe `Client` :

     * remplacer l'opération d'addition par une autre opération (avec 2 opérandes pour simplifier)
     * changer l’affichage final du résultat et le faire par exemple dans un fichier (plutôt qu'à la console)
     * changer la saisie des nombres en utilisant un `Scanner` et la méthode `nextInt` au lieu d'un `BufferedReader`. Il faudra enlever le **catch** de `IOException` et `NumberFormatException` ainsi que les `parseInt`. À la place, on attrapera une exception `InputMismatchException`. Pour rappel, pour définir un `Scanner` :

         ```java
         Scanner scanner = new Scanner(System.in);
         int valeur = scanner.nextInt();
         ```

   Ainsi, la classe `Client` devra simplement utiliser ces nouveaux **services**.


</div>

Bien sûr, ce premier exercice est très simpliste (et donc assez peu concret), mais il faut vous imaginer que les différentes responsabilités sont généralement des traitements plus longs et/ou plus complexes !

Voyons maintenant un autre exemple.

<div class="exercise">

1. Ouvrez le paquetage `srp2`. Il contient une classe `Rectangle` qui permet de créer des rectangles et de calculer leur aire.

2. Une application graphique souhaite pouvoir afficher les **rectangles**. Une première idée est d'utiliser la classe `JFrame` (de la librairie _Java Swing_), ce qui permettra de l'afficher :

    * Faites étendre la classe `JFrame` à `Rectangle`.

    * Dans le constructeur, ajoutez le code suivant qui permettra de configurer la fenêtre affichant le rectangle :

      ```java
      setSize(largeur * 2, hauteur * 2);
      setTitle("Rectangle");
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      ```

    * Redéfinissez la méthode `paint(Graphics g)` de la classe `JFrame` de la façon suivante :

      ```java
      @Override
      public void paint(Graphics g) {
          g.drawRect(largeur/2, hauteur/2, largeur, hauteur);
      }
      ```

    * Pour afficher votre rectangle dans le `main`, utilisez simplement la méthode suivante :

      ```java
      //Affiche une fenêtre contenant le rectangle.
      rectangle.setVisible(true);
      ```

    * Testez.

3. Certaines applications aimeraient aussi utiliser simplement la classe `Rectangle` pour faire des calculs géométriques sans pour autant avoir besoin de l'afficher. À ce stade, vous avez sans doute clairement identifié que la classe `Rectangle` possède trop de responsabilités : la gestion de la forme géométrique et de ses propriétés (aire, peut-être plus tard périmètre, etc.) et l'affichage graphique. La classe peut changer si on ajoute de nouvelles opérations ou si l'affichage graphique change. Le principe de responsabilité unique n'est pas respecté.

4. L'idée est d'avoir deux classes : une première, gérant la forme rectangle et l'autre permettant de l'afficher. Mais pour autant, il ne faut pas dupliquer de code ! Refactorez votre code en conséquence afin de mettre en place cette nouvelle conception.

5. Assurez-vous que tout fonctionne (il faudra sans doute adapter le `main`) et qu'il est bien possible d'avoir de créer des rectangles ne contenant aucune logique d'affichage et des rectangles qu'il est possible d'afficher.

</div>

### Principe Ouvert/Fermé (Open/Close)

Après cette mise en bouche, il est temps d'attaquer de sérieux problèmes de conception en développant le **principe ouvert/fermé**. Ce principe est défini comme suit :

"_Les entités d'un logiciel (classes, modules, fonctions) doivent être **ouverts** aux extensions, mais **fermés** aux modifications._" (**Bertand Meyer**).

En d'autres termes, il doit être possible d'étendre les fonctionnalités/le **comportement** d'une entité comme une classe **sans pour autant avoir besoin de modifier son code source**.

Ce principe est un pilier fondamental de qualité de code. Avec ce principe, même une classe ou une librairie compilée (non modifiable) autorise le développeur à étendre les fonctionnalités proposées.

Malheureusement, dans de nombreux projets, on rencontre fréquemment des classes violant ce principe, car mal conçues. Les symptômes sont généralement :
* Utilisation d'énormes blocs `if/else if/else` ou de blocs `switch case` qui grossissent au fur et à mesure qu'on ajoute de nouvelles choses. Avec l'utilisation de `classes` et de l'héritage, on va en plus certainement se retrouver à utiliser des instructions `instanceof` ou `getClass()` (pour vérifier le type de l'objet) et de `cast` pour pouvoir utiliser des méthodes précises.
* Nécessité de dupliquer du code pour ajouter une nouvelle fonctionnalité (non-respect du principe [_DRY_](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself)).
* Une classe mère qui dépend de ses classes filles.

Pour vous mettre dans le bain et vous montrer la problématique derrière tout cela, vous allez ajouter de nouvelles fonctionnalités à des projets existants qui ne respectent pas le principe ouvert/fermé.

<div class="exercise">

1. Ouvrez le paquetage `ocp1`. Dans ce projet, une classe `Animal` permet de gérer différents types d'animaux et leur cri, selon l'attribut `type` de l'objet.

2. On aimerait prendre en charge les **chiens** et les **poules**. Modifiez la classe `Animal` en conséquence et testez dans le `Main`.

3. Que se passe-t-il si vous essayez de créer un animal qui n'existe pas et d'afficher son cri ? Pour régler cela, ajoutez une clause `default` dans le `switch` affichant simplement "Animal inconnu".

</div>

Votre programme fonctionne ? C'est super ! Mais votre code serait-il encore lisible s'il y avait une centaine d'animaux ? Aussi, la classe `Animal` ne sera jamais finie, car il faudra en permanence modifier la méthode `cri` pour ajouter de nouveaux animaux. Elle n'est donc pas fermée aux modifications lorsqu'on veut étendre l'application à d'autres animaux.

Continuons maintenant avec de petits monstres bien populaires : les **pokémons**.

Le programme sur lequel nous allons travailler fait combattre des pokémons dans un simulateur. Il y a différents types de pokémons (feu, eau, plante...) et chaque type de pokémon possède une attaque (le type feu attaque toujours avec lance-flamme). Bien sûr, cette analyse est un peu bizarre et ne correspond pas à la réalité du jeu (où chaque pokémon possède plusieurs attaques, et pas une attaque précise selon le type) mais nous allons l'utiliser ainsi pour ne pas plus compliquer l'exercice.

En plus de l'attaque, le type de pokémon est aussi lié à un nombre de dégâts. Par exemple, le type **feu** fait toujours 60 dégâts et le type plante entre 40 et 80 dégâts.

Pour modéliser tout cela, le développeur a choisi de mettre en place un héritage pour gérer les différents types. Pour savoir quelle attaque annoncer dans le simulateur et quels dégâts infliger, il a besoin de vérifier quel est le pokémon qui attaque.

De même, dans la classe `Pokemon`, pour que le pokémon puisse se présenter avec son `type` (dans la méthode `toString`), la classe vérifie son type concret.

<div class="exercise">

1. Ouvrez le paquetage `ocp2`. Explorez les classes. Étudiez notamment la classe `SimulateurCombat`.

2. Ajoutez un nouveau type de pokémon : le pokémon type **électricité** qui possède les caractéristiques suivantes :

    * En plus des attributs d'un `Pokemon` classique, un pokémon **électrique** possède un attribut entier `chargeMax` et un attribut booléen `superDecharge`.

    * Son nom d'attaque est **Eclair** et il fait **20 dégâts** plus un **bonus de dégâts** entre **0** et la valeur de `chargeMax` (tiré au hasard). Si l'attribut `superDecharge` du pokémon vaut `true`, alors **bonus de dégâts** supplémentaire de 20 est ajouté.
  
    * Faites en sorte de prendre en charge ce nouveau type, **sans refactorer le code existant**, en créant une nouvelle classe `PokemonElectrique` et en ajoutant le code nécessaire là où il faut.

3. Ajoutez un nouveau type de pokémon : le pokémon type **psy** qui possède les caractéristiques suivantes :

    * En plus des attributs d'un `Pokemon` classique, un pokémon **psy** possède un attribut entier `bonusPsy`.

    * Son nom d'attaque est **Choc mental** et elle fait précisément 30 * `bonusPsy` dégâts.

    * Faites en sorte de prendre en charge ce nouveau type, **sans refactorer le code existant**, en créant une nouvelle classe `PokemonPsy` et en ajoutant le code nécessaire là où il faut.

4. Modifiez le `Main` pour faire combattre un pokémon possédant le type **électrique** contre un pokémon possédant le type **psy**. **Attention**, il ne faut pas modifier les autres classes créées auparavant ! Vérifiez que le type des deux pokémons s'affichent bien au début du combat (sinon, c'est que vous avez manqué quelque-chose !). 

</div>

Si ce n'était peut-être pas encore assez évident avec les animaux, à ce stade, vous devez vous rendre compte qu'ajouter un nouveau type de pokémon est fastidieux :

* Créez une classe du type correspondant.

* Implémenter une méthode donnant les dégâts de ce type.

* Modifier la classe `SimulateurCombat` en ajoutant un nouveau `else if` pour prendre en charge le nouveau type, faire un `cast` pour récupérer ses dégâts...

* Modifier la classe `Pokemon` pour adapter le `toString` en ajoutant un nouveau `else if` pour prendre en charge le nouveau type.

De plus, ici, seules deux fonctions ont vraiment besoin de connaître les détails des pokémons. Mais que se passerait-il s'il y avait beaucoup plus de méthodes et de classes qui en dépendent ? À chaque ajout d'un nouveau type, il faudrait modifier l'ensemble de ces classes et de ces méthodes ! Dans un gros projet, cela deviendrait vite un calvaire. De plus, il est facile d'oublier de mettre à jour une classe, ce qui ne provoque pas d'erreur de compilation, mais un bug lors de l'exécution (comme avec les animaux inconnus). Donc, la [**dette technique**](https://fr.wikipedia.org/wiki/Dette_technique) va croître beaucoup trop vite.

Le respect du principe **ouvert/fermé** va permettre de se limiter aux deux premières étapes : création d'une classe et implémentation des méthodes nécessaires dans cette même classe.

Considérons l'exemple suivant, similaire à ce que vous venez de faire :

```java

class FigureGeometrique {

   private String typeFigure;

   public FigureGeometrique(String typeFigure) {
      this.typeFigure = typeFigure;
   }

   public void dessiner() {
      if(typeFigure.equals("rectangle")) {
         dessinerRectangle();
      }
      else if(typeFigure.equals("triangle")) {
         dessinerTriangle();
      }
   }

   private void dessinerRectangle() {
      //Code pour dessiner un rectangle...
   }

   private void dessinerTriangle() {
      //Code pour dessiner un triangle...
   }

}
```

L'ajout d'une nouvelle figure géométrique (par exemple, un carré) nécessite la modification de la classe `FigureGeometrique` et de la méthode `dessiner`. Le principe ouvert/fermé n'est pas respecté. De plus, un bug (à l'exécution) se produira si on essaie de traiter une figure géométrique qui n'existe pas !

Pour régler ce problème, l'idée est de se reposer sur un système d'héritage et d'abstraction :
* `FigureGeometrique` est une classe abstraite, qui permet d'imposer un comportement uniforme aux figures (méthode abstraite `dessiner`)
* Chaque type de figure géométrique donnera donc lieu à une classe spécialisée et l'attribut `type` de `FigureGeometrique` perd son utilité :

```java

abstract class FigureGeometrique {

  public abstract void dessiner();

}

class Rectangle extends FigureGeometrique {

  public void dessiner() {
    //Code pour dessiner un rectangle...
  }
}

class Triangle extends FigureGeometrique {

  public void dessiner() {
    //Code pour dessiner un triangle...
  }
}
```
<div style="text-align:center">
![Open-close 1]({{site.baseurl}}/assets/TP3/OCP1.svg){: width="25%" }
</div>

L'ajout d'une nouvelle figure nécessite donc simplement l'ajout d'une nouvelle classe correspondant à la figure et l'implémentation des méthodes requises (ici, dessiner la figure). Aucune autre classe n'est modifiée. L'extension est possible (ajout de nouvelles figures) sans modification du code source déjà présent. Par ailleurs, il est maintenant impossible de créer des figures géométriques qui n'existent pas au préalable dans notre programme (c'est une bonne chose !).

Comme `FigureGeometrique` ne contient aucun attribut (qui pourraient être communs à toutes les figures) et définit simplement des méthodes `abstraites`, il serait plus judicieux d'utiliser une `interface` ! Par contre, si la classe abstraite possède des attributs et/ou définit un bout de comportement commun à toutes les sous-classes, on utilisera bien une classe abstraite.

Ceci devrait vous permettre de refactorer le code du paquetage `ocp1` (animaux). Pour `ocp2` (pokémons) cela peut sembler un peu plus dur (car il y a déjà un système d'héritage), mais cela ne devrait pas être trop dur à adapter.

<div class="exercise">

1. Refactorez le code du paquetage `ocp1` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne. Il ne doit plus être possible de gérer des animaux inconnus, et c'est bien normal !

2. À l'aide d'`IntelliJ`, générez le **diagramme de classes de conception** de l'application du paquetage `ocp2` (avant refactoring). Pour cela, effectuez un **clic droit** sur le paquetage `ocp2` puis sélectionnez `Diagrams` et enfin `Show Diagrams`. Activez bien l'affichage de tous les éléments et notamment les **dépendances non triviales**.

3. Refactorez le code du paquetage `ocp2` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne.

4. Générez maintenant le **diagramme de classes de conception** de l'application du paquetage `ocp2` (après refactoring). Activez bien l'affichage de tous les éléments et notamment les **dépendances non triviales**.

</div>

En comparant vos deux diagrammes de classes, on peut facilement voir ce qui différencie la "mauvaise" conception de la "bonne" : dans votre premier diagramme, les classes `SimulateurCombat` et `Pokemon` ont autant de dépendances qu'il y a de sous-classes de type de pokémon. S'il y a 30 types de pokémons, `SimulateurCombat` et `Pokemon` auront chacune 30 dépendances. Après refactoring, ces dépendances disparaissent. `SimulateurCombat` est seulement dépendant de `Pokemon`.

Dans un code de qualité **les abstractions ne dépendent pas des implémentations**. En d'autres termes, une superclasse ne devrait pas dépendre de ses sous-classes. Seules les sous-classes peuvent dépendre de leurs parents (et on verra que parfois, là aussi, il faut faire attention lorsqu'on utilise l'héritage.). Sur votre premier diagramme, il est clair que ce principe n'est pas respecté, car `Pokemon` dépendait de ses différentes sous-classes, ce qui n'est plus les cas sur le deuxième diagramme.

Nous allons maintenant tester votre compréhension des deux principes (`S` et `O`) avec un nouvel exercice un peu différent de ce que vous avez vu jusqu'ici, dans sa forme.

<div class="exercise">

1. Ouvrez le paquetage `ocp3`. Ce projet permet de gérer un paquet de 52 cartes, de le trier, de le mélanger... Exécutez le programme pour observer le rendu. Deux méthodes de tri sont possibles. On définit la méthode de tri utilisée quand on construit l'objet et on peut la changer à tout moment avec un `setter`.

2. On aimerait ajouter une nouvelle méthode de tri par **bulles**. Voici cet algorithme illustré sur un simple tableau d'entiers :

    ```java
    //Soit t, un tableau contenant des entiers
    for(int i=t.length-1;i>=0;i--) {
      for(int j=0; j < i; j++) {
        if(t[j] > t[j+1]) {
          int temp = t[j];
          t[j] = t[j+1];
          t[j+1] = temp;
        }
      }
    }
    ```

    Faites en sorte que la classe `Paquet` puisse effectuer un tri à bulles. 
    
    Pour vous aider, vous pourrez utiliser la méthode `compareTo` qui permet de comparer deux cartes. Cette méthode renvoie un nombre négatif si la première carte est strictement inférieure à la seconde, **0** si elles sont égales et un nombre positif si la première carte est strictement supérieure à la seconde.

3. Testez que votre algorithme fonctionne bien en changeant la méthode de tri du paquet dans le `Main`.

4. À votre avis, en quoi les principes de responsabilité unique et ouvert/fermé ne sont pas respectés ?

</div>

Comme vous l'avez sans doute déduit, dans un premier temps, le principe **ouvert/fermé** n'est pas respecté : ajouter un nouveau tri demande de modifier le code source de la classe `Paquet` et notamment la méthode `trier`.

Dans un second temps, on remarque aussi que la classe `Paquet` a trop de responsabilités : cela ne devrait pas être à elle de gérer les différents algorithmes de tri de cartes. On pourrait aussi dire la même chose pour le mélange, et peut-être même pour l'affichage ! La vérification peut se faire facilement :

* Si la méthode de tri change, la classe `Paquet` doit être modifiée.

* Si la méthode de mélange change, la classe `Paquet` doit être modifiée.

* Si le format d'affichage du paquet change, la classe `Paquet` doit être modifiée.

Le principe de responsabilités unique n'est pas respecté. Pour le `toString`, cela peut encore se discuter, mais cela est clair pour le **tri** et le **mélange**.

<div class="exercise">

1. Refactorez le code afin de respecter le **principe ouvert/fermé** au niveau des **tris**. On souhaite tout de même garder la possibilité de changer de tri avec un `setter` et aussi de définir le tri utilisé via le `constructeur`. Quelques indices :

    * Isolez le code de chaque méthode de tri dans des classes dédiées.

    * Généralisez le tout avec une interface.

2. Refactorez le code concernant le **mélange** afin de respecter le **principe de responsabilité unique**. Prévoyez aussi le cas où d'autres méthodes de mélanges pourraient être ajoutées. Comme pour le tri, on souhaite pouvoir définir la méthode de mélange dans le constructeur et la modifier via un setter.

3. Testez que tout fonctionne, essayez plusieurs méthodes de tri sur le paquet, notamment. Normalement, vous ne devez jamais éditer la classe `Paquet` si vous changez le tri utilisé.

4. Générez le diagramme de classes de conception du paquetage `ocp3` (avec `IntelliJ`).

</div>

Les principes **SOLID** se combinent naturellement entre eux. D'ailleurs, si vous avez refactoré proprement le dernier exercice, vous avez même déjà utilisé le principe **d'inversion des dépendances** dont nous parlerons plus tard ! 

Encore mieux, vous venez d'utiliser un **design pattern** au niveau des tris (et des mélanges) : **Stratégie**. Ce pattern permet d'encapsuler un ensemble de comportements (algorithmes de tris) dans des classes et rendre ces algorithmes interchangeables dans une classe cliente (`Paquet`). Ainsi, le comportement spécifique est **injecté** dans la classe cliente sans modifier le code source de celle-ci. Ce pattern s'appuie sur **ouvert/fermé**, **l'inversion des dépendances** et aide à renforcer **responsabilité unique**. C'est exactement ce que vous venez de faire : la méthode de tri du paquet est modulable et on peut même en ajouter des nouvelles dans le futur ! Et tout cela, sans modifier `Paquet`.

À partir du diagramme de classes de conception que vous venez de générer, vous devriez être en mesure de généraliser le pattern **stratégie** à tout type de problème.

### Héritage, composition et principe ouvert-fermé

Maintenant, voyons une nouvelle situation, où les choses risquent d'être plus compliquées notamment vis-à-vis du respect du principe **ouvert/fermé** !

<div class="exercise">

1. Ouvrez le paquetage `ocp4`. Dans ce projet, il y a une classe `Produit` permettant de gérer des produits, leurs prix et afficher leur description (leur nom). Ensuite, on a souhaité définir une classe `ProduitAvecReduction`, car certains produits proposent des réductions. Tout fonctionne pour le moment, comme vous pouvez le constater dans le `Main`.

2. On souhaite maintenant ajouter un nouveau type de produit : les produits avec une date de péremption proche. Sur un tel produit, le prix est calculé en faisant une réduction de 50% sur le prix d'origine. De plus, lors de l'affichage de la description du produit (son nom), on affiche en plus le message "Réduction de 50% appliquée". Implémentez donc une classe `ProduitAvecDatePeremptionProche` héritant de `Produit` et réécrivez les méthodes `getPrix` et `afficherDescription`. Testez que votre nouveau type de produit a bien le comportement attendu en testant dans le `Main` (ou encore mieux : avec des tests unitaires pour le prix !) en appelant les méthodes `getPrix` et `afficherDescription`.

3. Maintenant, nous voulons qu'un produit puisse à la fois être un produit qui périme bientôt et un produit avec une réduction. C'est-à-dire que les deux **comportements** (réductions) soient appliqués lors du calcul du prix (lors d'un appel à `getPrix`) et que les messages correspondants aux deux types de produit soient affichés (lors d'un appel à `afficherDescription`). Est-il possible de créer une telle classe ou un tel comportement ?
</div>

Si vous vous êtes contenté uniquement de faire hériter `ProduitAvecDatePeremptionProche` de `Produit`, vous remarquerez qu'il est compliqué d'avoir un même produit possédant ces deux fonctionnalités à la fois, notamment, car le multihéritage de classes n'est pas possible en Java.

Peut-être que vous avez été plus malin et que vous avez pensé à implémenter une classe héritant de `Produit` et implémentant les deux comportements. Mais dans ce cas, il y a de la **duplication de code**.

Ou alors, peut-être que vous avez été encore plus malin et que vous avez pensé à faire une classe **composée** de deux instances des types de produit concernés. C'est déjà beaucoup mieux ! Mais que se passe-t-il si d'autres types de produit sont ajoutés ? Par exemple, si on a cinq types de produits différents et qu'on veut mixer au choix certaines fonctionnalités de certains types ? La classe composée sera de plus en difficile à gérer et ne sera jamais fermée aux modifications.

Tout en respectant le **principe ouvert/fermé**, il existe une méthode générale pour construire un `Produit` possédant autant de comportements mixtes que nous souhaitons. Si de nouveaux comportements sont ajoutés dans le futur, il n'y aura pas de modification du code existant. On peut implémenter un tel système en [favorisant la **composition** au lieu d'un **héritage**](https://en.wikipedia.org/wiki/Composition_over_inheritance). L'idée est la suivante :

* La classe "mère", disons `I`, définie une abstraction (typiquement une interface) : elle définit son contrat, à savoir ce que tous les objets du même type qu'elle, doivent pouvoir faire.

* La classe "fille" implémente cette interface et redéfinit les fonctions afin de respecter le contrat. En plus, la classe fille possède **un attribut stockant une réference vers une instance de `I`**. Ainsi, la classe fille **délègue** une partie de l’exécution des **opérations** à l'instance qu'elle agrège et ajoute son propre **comportement**.

* On peut ainsi développer plusieurs classes "filles" sous le même format et les concaténer lors de la création de l'objet, ajoutant ainsi plusieurs comportements de manière dynamique.

Illustrons cela à travers un exemple :

```java
class Salarie {

   private double salaire;

   public Salarie(double salaire) {
      this.salaire = salaire;
   }

   public double getSalaire() {
      return salaire;
   }

}

class SalarieChefDeProjet extends Salarie {

   private int nombreProjetsGeres;

   public SalarieChefDeProjet(double salaire, int nombreProjetsGeres) {
      super(salaire);
      this.nombreProjetsGeres = nombreProjetsGeres;
   }

   @Override
   public double getSalaire() {
      return super.getSalaire() + 100 * (nombreProjetsGeres);
   }

}

class SalarieResponsableDeStagiaires extends Salarie {

   private int nombreStagiairesGeres;

   public SalarieResponsableDeStagiaires(double salaire, int nombreStagiairesGeres) {
      super(salaire);
      this.nombreStagiairesGeres = nombreStagiairesGeres;
   }

   @Override
   public double getSalaire() {
      return super.getSalaire() + 50 * nombreStagiairesGeres;
   }
}
```

Ici, même problème que pour les produits, si je veux un salarié qui a à la fois les responsabilités de chef de projet et de responsable de stagiaire, cela est impossible !

Comme souvent, l'héritage est le problème ici. Au lieu de faire un simple héritage entre les classes, nous pourrions plutôt utiliser des **compositions** sur les sous-types et créer ainsi des salariés incluant des salariés, incluant des salariés... ce qui permet de combiner la logique de chaque type ! 

```java
interface SalarieInterface {
  double getSalaire();
}


class Salarie implements SalarieInterface {

  private double salaire;

  public Salarie(double salaire) {
    this.salaire = salaire;
  }

  public double getSalaire() {
    return salaire;
  }

}

class SalarieChefProjet implements SalarieInterface {

  private SalarieInterface salarie;

  private int nombreProjetsGeres;

  public SalarieChefProjet(SalarieInterface salarie, int nombreProjetsGeres) {
    this.salarie = salarie;
    this.nombreProjetsGeres = nombreProjetsGeres;
  }

  @Override
  public double getSalaire() {
    return salarie.getSalaire() + 100 * (nombreProjetsGeres);
  }

}

class SalarieResponsableDeStagiaires implements SalarieInterface {

  private SalarieInterface salarie;

  private int nombreStagiairesGeres;

  public SalarieResponsableDeStagiaires(SalarieInterface salarie, int nombreStagiairesGeres) {
    this.salarie = salarie;
    this.nombreStagiairesGeres = nombreStagiairesGeres;
  }

  @Override
  public double getSalaire() {
    return salarie.getSalaire() + 50 * nombreStagiairesGeres;
  }
}
```

<div style="text-align:center">
![Open close 2]({{site.baseurl}}/assets/TP3/OCP2.svg){: width="80%" }
</div>

Avec cette nouvelle architecture, nous pouvons créer des salariés qui sont chefs de projet et responsables de stagiaires :

```java
//Salarié qui est chef de projet gérant 3 projets et aussi responsable de stagiaires gérant 5 stagiaires
SalarieInterface salarie = new SalarieResponsableStagiaires(new SalarieChefProjet(new Salarie(2000), 3), 5);
salarie.getSalaire(); //Renvoie 2550
```

Il est important de noter que la classe composée est `SalarieInterface` et non pas `Salarie`! Sinon, on ne pourrait pas combiner `SalarieChefProjet` avec `SalarieResponsableStagiaires`.

Aussi, le salarie n'est pas instancié dans la classe, il est **injecté** (autrement, cela ne fonctionnerait pas), comme ce que vous avez fait, par exemple, avec l'exercice sur le paquet de carte et les différentes méthodes de tri. Sur un diagramme de classes de conception, cela pourrait être représenté par une **agrégation blanche**.

<div class="exercise">

1. Refactorez votre code afin de pouvoir créer un produit qui possède une réduction et qui a aussi une date de péremption proche.

2. Créez un **Twix** avec pour prix de base **3€**, qui périme bientôt et qui a une réduction de 50 centimes. Testez que la valeur obtenue pour le prix est bien la bonne et que l'affiche de la description du produit affiche bien toutes les informations.

3. Inversez l'ordre de création du produit (le produit avec réduction est composé d'un produit avec une date de péremption proche ou l'inverse selon ce que vous avez fait à la question précédente). Est-ce que le prix obtenu est le même qu'à l'étape précédente ?

</div>

Attention, **dans cet exemple précis**, même si nous pouvons maintenant rajouter un nouveau type de produit et le combiner aux autres pour calculer le prix adéquat, quand on instancie l'objet, il faut faire attention à l'ordre de combinaison des objets, à cause de la méthode de calcul du prix du produit avec une réduction. Si la méthode de calcul avait été un pourcentage pour ce type de produit (-X% du prix) comme pour le produit avec une date de péremption proche, l'ordre n'aurait pas eu d'importance. Bref, cela est à prendre en compte quand vous concevez et que vous utilisez des décorateurs. 

Bon, tout fonctionne bien, mais le code est encore un peu redondant : A priori, tous nos produits "dérivés" vont posséder un objet `I_Produit`. Il est alors possible de factoriser cela avec une **classe abstraite** dont vont hériter tous les sous-produits.

Par exemple, pour l'exemple des salariés :

```java
//Nous reviendrons sur le nom "décorateur" plus tard.
abstract class SalarieDecorateur implements SalarieInterface {
   private SalarieInterface salarie;

   public SalarieDecorator(SalarieInterface salarie) {
      this.salarie = salarie;
   }

   public double getSalaire() {
      return salarie.getSalaire();
   }
}

class SalarieChefProjet extends SalarieDecorateur {

  private int nombreProjetsGeres;

  public SalarieChefProjet(SalarieInterface salarie, int nombreProjetsGeres) {
    super(salarie);
    this.nombreProjetsGeres = nombreProjetsGeres;
  }

  @Override
  public double getSalaire() {
    return super.getSalaire() + 100 * (nombreProjetsGeres);
  }

}

class SalarieResponsableStagiaires extends SalarieDecorateur {

  private int nombreStagiairesGeres;

  public ResponsableDeStagiaires(SalarieInterface salarie, int nombreStagiairesGeres) {
    super(salarie);
    this.nombreStagiairesGeres = nombreStagiairesGeres;
  }

  @Override
  public double getSalaire() {
    return super.getSalaire() + 50 * nombreStagiairesGeres;
  }

}

class Main {
    public static void main(String[]args) {
        SalarieInterface s1 = new Salarie(2000);
        SalarieInterface s2 = new SalarieChefProjet(s1, 3);
        SalarieInterface s3 = new SalarieResponsableStagiaires(s1, 2);
        SalarieInterface s4 = new SalarieChefProjet(new SalarieResponsableStagiaires(s1, 4), 3);

        //Affiche 2000
        System.out.println(s1.getSalaire());

        //Affiche 2300
        System.out.println(s2.getSalaire());

        //Affiche 2100
        System.out.println(s3.getSalaire());

        //Affiche 2500
        System.out.println(s4.getSalaire());
    }
}
```

<div style="text-align:center">
![Open close 3]({{site.baseurl}}/assets/TP3/OCP3.svg){: width="80%" }
</div>

<div class="exercise">

1. Réfactorez votre code pour introduire une classe abstraite et réduire la redondance et la répétition de code au niveau des sous-classes (`ProduitAvecReduction` et `ProduitAvecDatePeremptionProche`).

2. Testez que tout fonctionne comme auparavant.

3. Générez le **diagramme de classes de conception** (avec `IntelliJ`) du paquetage `ocp4`.

</div>

Dans le futur, si nous ajoutons un nouveau type de **produit**, il suffira alors de rajouter une nouvelle classe et lui faire étendre votre classe abstraite. Avec une telle architecture, le principe ouvert/fermé est respecté et nous avons tiré profit de manière avantageuse du mécanisme de composition au lieu de se reposer sur l'héritage qui ne nous permettait pas d'arriver à nos fins.

En fait, ce modèle est réutilisable et adaptable à d'autres situations (nous l'avons vu avec les salariés). C'est en fait un autre **design pattern** nommé **décorateur** d'où le nom de la classe abstraite dans l'exemple. 

À partir du diagramme de classes que vous avez généré, vous devriez être capable de produire un modèle général fonctionnant pour tous les cas de figures.

### Principe de substitution de Liskov (Liskov substitution)

Certains développeurs abusent de l'**héritage** par facilité au lieu d'utiliser d'autres solutions comme la **composition** d'objets. Un "mauvais" héritage est un héritage pour lequel il n'existe pas vraiment de relation de spécialisation entre la superclasse et la sous-classe. La sous-classe ne représente alors pas le même concept que sa classe mère, ce n'est pas réellement une spécialisation.

Tout cela occasionne parfois des problèmes inattendus qui sont mis en lumière par le principe de **substitution de Liskov** qui est fortement liée à la notion de **programmation par contrat**.

Quand on parle de **programmation par contrat** cela signifie que chaque classe possède un ensemble de **règles** (implicites ou explicites) autour de ses **méthodes** : **pré-conditions**, **post-conditions**, **effet de bords**, etc. Globalement, quelqu'un qui utilise une instance d'une **classe** donnée sait à quoi s'attendre quand on appelle telle ou telle méthode. Par exemple, on sait qu'un appel à la méthode `add` sur une instance de `ArrayList` va ajouter l'élément à la fin de la collection.

Le principe de **substitution de Liskov** a été introduit par **Barbara Liskov** et énonce qu'un **objet** d'une superclasse donnée doit pouvoir être remplacée par une de ses **sous-classes** sans "casser" le fonctionnement du programme. Une méthode provenant à l'origine d'une superclasse et appelée sur la sous-classe devrait **respecter le contrat** défini dans la superclasse.

Par exemple, si on étend `ArrayList` pour faire un sous-type de collection spécialisé `MonArrayList` : si on redéfinit la méthode `add` dans `MonArrayList`, à la fin d'un appel à cette méthode, l'élément ajouté doit se trouver à la fin de la collection, comme spécifié dans le contrat de `ArrayList`. Peut-être que le chemin et la manière de faire aura été différente de la classe mère, mais le résultat est le même : un code qui utiliserait une instance de `ArrayList` pourrait être remplacé par `MonArrayList` sans perturbation du programme : les tests unitaires passeraient toujours, par exemple.

L'utilisation inappropriée de l'héritage peut amener au non-respect de ce principe.

Voici un scénario illustrant plus en détail le problème de non-respect du principe de substitution de Liskov : on possède une classe `Rectangle` et on souhaite modéliser une classe `Carre`. D'ailleurs, en géométrie, un carré est un sous-type de rectangle, non ?

<div class="exercise">

1. Ouvrez le paquetage `lsp1` et observez les classes mises à disposition. Dans cette application, nous avons considéré qu'un `Carre` est une spécialisation d'un `Rectangle`. Cependant, un carré possède une caractéristique particulière : **sa hauteur et sa largeur sont toujours identiques**. Bref, si on change la hauteur d'un carré, sa largeur change aussi. Ou plutôt, on ne devrait pas pouvoir changer la largeur d'un rectangle indépendamment de sa hauteur et vice-versa.

2. Dans le paquetage `lsp1` dans `src/test/java` vous trouverez deux classes de tests unitaires pour tester le rectangle et le carré. Lancez-les. Essayez de comprendre pourquoi les tests ne passent pas.

3. Les tests écrits sont bien valides. Si on change la hauteur d'un carré, alors sa largeur doit aussi changer. Une première solution peut donc être de récrire les méthodes `setLargeur` et `setHauteur` dans la classe `Carre` afin que quand on modifie la largeur, la hauteur soit mise à la même valeur et inversement. Faites cette modification (les attributs `hauteur` et `largeur` sont accessibles dans `Carre` car en `protected` dans la classe `Rectangle`).

4. Relancez les tests unitaires. Un autre test ne passe plus ! Essayez de comprendre pourquoi.

</div>

Avec cette modification, le principe de substitution de Liskov n'est plus respecté ! On a **cassé** le contrat de `Rectangle` dans `Carre`. `Carre` est un `Rectangle` et on devrait pouvoir modifier sa hauteur et sa largeur librement !

De plus, si on utilise `Carre` comme un `Rectangle`, des bugs étranges surviennent quand on utilise une méthode prévue pour un `Rectangle`(ici, la méthode **agrandirRectangle**). On ne peut pas substituer le rectangle par un carré sans produire de bugs logiques. Ajouter des nouvelles méthodes dans la classe `Rectangle` force à ajouter du code dans `Carre` pour éviter les bugs et essayer de continuer à respecter le contrat de `Rectangle`.

Une autre mauvaise solution possible serait d'ajouter une fonction `setTailleCote` dans `Carre` et de redéfinir les fonctions `setHauteur` et `setLargeur` dans `Carre` de façon à ce qu'elles ne fassent rien :

```java
class Carre extends Rectangle {

  public Carre(int tailleCote) {
    super(tailleCote, tailleCote);
  }

  public void setTailleCote(int tailleCote) {
    this.hauteur = tailleCote;
    this.largeur = tailleCote;
  }

  @Override
  public void setHauteur(int hauteur) {}

  @Override
  public void setLargeur(int largeur) {}
  
}
```

Mais dans ce cas, on ne peut toujours pas utiliser `Carre` comme un `Rectangle` (on ne respecte toujours pas `LSP`) et en plus :
* On crée des méthodes qui ne font rien et qui polluent le code.
* On duplique le code de `setHauteur` et `setLargeur` dans `Carre` dans `setTailleCote` !

Bref, cet héritage est une très mauvaise idée ! En fait, conceptuellement, en programmation, un carré n'est pas un rectangle spécialisé, car les règles pour la hauteur et la largeur sont différentes... Cela peut être un peu dur à accepter.

Si on souhaite quand même utiliser un rectangle dans un carré (pour ne pas dupliquer le calcul de l'aire ou des autres méthodes, par exemple) on peut éventuellement utiliser une **composition** à la place, ce qui nous éviterait à gérer les méthodes indésirables de changement de hauteur ou largeur imposées par héritage.

<div class="exercise">

1. Créez l'interface `FigureRectangulaire` suivante :

    ```java
    public interface FigureRectangulaire {
      int getHauteur();
      int getLargeur();
      int aire();
    }
    ```

2. Modifiez la classe `Carre` afin qu'elle n'étende plus la classe `Rectangle`, mais implémente l'interface `FigureRectangulaire` et utilise plutôt une **composition** avec un objet de type `Rectangle` (en attribut de la classe) :

    * On utilise une composition avec un rectangle, donc il n'y a pas besoin d'attribut `tailleCote` dans la classe. Cela est stocké au niveau du rectangle.

    * La signature du **constructeur** ne change pas. L'attribut de type `Rectangle` est directement initialisé dans le constructeur (agrégation noire sur un diagramme de classes).

    * On n'a plus besoin des méthodes `setHauteur` et `setLargeur` (on ne modifie pas indépendamment la largeur et la hauteur d'un carré).

    * Les méthodes `getLargeur` et `getHauteur`et `aire` sont **déléguées** au `Rectangle`.

    * Une nouvelle méthode `setTailleCote` permet de changer la taille du côté du carré (en utilisant le rectangle).

3. Faites aussi implémenter l'interface `FigureRectangulaire` à `Rectangle`.

4. Modifiez les **tests unitaires** portants sur `Carre` :

    * Les méthodes `setLargeur` et `setHauteur` n'existent plus. On utilise à la place `setTailleCote`.

    * Le test `testAireAgrandirCarre` n'a plus lieu d'être, car la méthode `agrandirRectangle` porte sur un `Rectangle` et dorénavant, un `Carre` n'est plus un `Rectangle`. Supprimez donc ce test.

5. Lancez les tests, vérifiez que tout fonctionne.

</div>

Après **refactoring**, le diagramme de classes de votre application devrait donner quelque-chose comme ça :

<div style="text-align:center">
![Liskov substitution 2]({{site.baseurl}}/assets/TP3/LSP2.svg){: width="50%" }
</div>

La **composition forte** entre `Carre` et `Rectangle` (initialisé dans `Carre` et n'en sort pas) est en opposition avec la **composition faible**, qui indique aussi une composition, mais dans laquelle la dépendance est injectée (comme avec les **décorateurs** dans l'exercice des produits).

Bien sûr, nous aurions pu quand même conserver la logique d'agrandissement d'une `FigureRectangulaire`. À ce moment-là, il faudrait rajouter une méthode `agrandir(int facteur)` dans l'interface `FigureRectangulaire` et implémenter les méthodes dans `Rectangle` et `Carre`.

Mettons vos nouvelles connaissances en pratique avec un autre exercice.

<div class="exercise">

1. Ouvrez le paquetage `lsp2`. On souhaite implémenter le fonctionnement d'une `Pile`. Une `Pile` est une structure de données `LIFO` (last in, first out) qui fonctionne comme une pile d'assiette. On peut globalement réaliser **quatre opérations** sur une pile :

    * Vérifier si elle est vide.

    * Obtenir la valeur au sommet de la pile.

    * Empiler un élément (l'ajouter au sommet de la pile)

    * Dépiler un élément (le retirer du sommet de la pile et le renvoyer).

    La classe `Pile` que nous allons implémenter possède un paramètre de type **générique**. Cela permet de créer des piles contenant un type de données paramétré, comme quand vous créez un objet de type `List<Double>` par exemple.

    Afin de ne pas avoir à définir la structure stockant les données nous même, nous allons étendre la classe `Vector` qui permet de gérer une structure de données ordonnée. Diverses méthodes de la super-classe vont vous être utiles :

    * `isEmpty` → permet de vérifier si la structure est vide.

    * `get(index)` → permet de récupérer la valeur située à la position ciblée par l'index.

    * `remove(index)` → permet de supprimer la valeur située à la position ciblée par l'index.

    * `add(index, valeur)` → permet d'insérer une valeur à la position ciblée par l'index.

2. Ouvrez la classe de tests unitaires placée dans `test/java/lsp2/PileTest`. Exécutez les tests. Rien ne passe, c'est normal ! Vous n'avez pas encore implémenté le code de la classe `Pile` qui contient du code par défaut... Vous êtes donc en mode **TDD** (test driven development).

3. Implémentez les méthodes de la classe `Pile` afin que les tests passent (ne décommentez pas le dernier test pour le moment).

4. Lisez et exécutez le test contenu dans `test/java/lsp2/VectorTest`. Comprenez-vous pourquoi ce test est valide et nécessaire ?

5. Décommentez le test `testSupprimerIndex` de `test/java/lsp2/PileTest` et exécutez-le. Pourquoi ne passe-t-il pas ?

</div>

Le dernier test n'est pas mal rédigé, car, selon le **contrat** de `Pile`, seules les opérations `estVide`, `empiler`, `depiler` et `sommetPile` doivent produire un effet. Or, comme `Pile` hérite de `Vector`, on a accès à toutes les opérations réalisables sur une liste classique... Donc, dans la logique, même s'il est possible d'appeler `remove` sur notre `Pile`, cela ne doit produire aucun effet ! Or, ce n'est pas le cas ici. Bref, **le contrat de la Pile** n'est pas respecté : on peut ajouter et supprimer des éléments autres part qu'au sommet.

On pourrait redéfinir la méthode `remove` (et toutes les méthodes de `Vector` !) pour qu'elles ne fassent rien, mais le principe de substitution de Liskov ne serait alors plus respecté, car on casserait le **contrat** de `Vector` ! On ne pourrait pas substituer un `Vector` par une `Pile` et le test `testSubstitutionVectorParPile` (dans `test/java/lsp2/VectorTest`) ne fonctionnerait plus...

Bref, conceptuellement, une `Pile` n'est pas un `Vector` spécial, mais bien une structure indépendante... Néanmoins, il est possible d'utiliser une **composition** pour utiliser un `Vector` comme attribut, dans notre classe `Pile` et ainsi éviter un certain degré de duplication de code.

<div class="exercise">

1. Refactorez le code de la classe `Pile` en enlevant l'héritage et en utilisant une **composition** avec un `Vector` à la place.

2. Les tests `testSupprimerIndex` et `testSubstitutionVectorParPile` ne compilent plus, c'est normal ! La pile n'est pas un `Vector`, on ne peut pas appeler `remove` dessus (et c'est tant mieux). Supprimez donc le test `testSupprimerIndex` ainsi que la classe `VectorTest`.

3. Relancez les tests et vérifiez que tout passe.

4. Quelque part dans votre code, définissez une variable de type `Stack` qui est une classe de `Java` permettant de gérer une pile. Allez observer le code source de cette classe (`CTRL+B` sur **IntelliJ** en cliquant sur le nom de la classe). Que remarquez-vous au niveau de sa déclaration ? Cette classe est aujourd'hui dépréciée. À votre avis, pourquoi ?

</div>

Eh oui, même les concepteurs de `Java` ont fait quelques bêtises lors du développement du langage. Et il n'est plus possible de supprimer cette classe après coup pour ne pas causer de problèmes de compatibilité. La seule chose à faire est de déprécier cette classe et de conseiller une nouvelle solution mieux conçue (la classe `Deque`). D'où l'importance de bien penser sa conception !

### Principe de ségrégation des interfaces (Interface segregation)

Le quatrième principe **SOLID** est le **principe de ségrégation des interfaces**.

Un objet ne doit pas être forcé de dépendre de méthodes qu'il n'utilise pas. Globalement, il ne faut pas qu'une **interface** définisse dans son contrat des méthodes qui ne seront voir ne pourront pas être implémentées par la classe implémentant l'interface.

Nous en avons déjà parlé, mais une interface est un **contrat**. Une classe qui implémente une interface est forcé d'implémenter toutes les méthodes de l'interface. Mais une classe ne devrait pas être forcée à implémenter un bout de contrat qu'elle ne peut pas remplir.

Voyons comment ne pas respecter ce principe peut devenir très fastidieux au fur et à mesure que le projet grossit.

<div class="exercise">

1. Ouvrez le paquetage `isp`. Ce projet modélise un système de jeu où certaines créatures sont des **montures** toutes les montures du même type ont les mêmes caractéristiques type (vitesse, endurance...). Au début, le développeur a modélisé une créature `Cheval`. Pour cette monture, on veut connaître :

    * Le nom de la monture.

    * La vitesse.

    * L'endurance.

    Pour prévoir le futur dans le cas où il y aurait besoin d'ajouter d'autres montures, le développeur a ajouté une interface `Monture`.

    Il a ensuite ajouté un autre type de monture, le **Tigre**.

2. Ajoutez une classe `Griffon` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 300. Cependant, contrairement aux autres montures, cette monture est une **monture volante**. Elle ne possède pas d'endurance. Par contre, on veut connaître son **temps maximum de vol** qui est de 40. Adaptez votre classe en conséquence.

    Concernant l'endurance, que faut-il renvoyer ? On ne peut pas renvoyer **0** ou un nombre négatif, cela n'aurait pas beaucoup de sens. À la place, on peut lever une erreur :

    ```java
    public double getEnduranceMonture() {
        throw new Error("Une monture volante n'a pas d'endurance!");
    }
    ```

3. Dans le cas où il y aurait besoin d'ajouter d'autres montures volantes dans le futur, ajoutez la méthode permettant d'obtenir le temps de vol dans l'interface `Monture`.

4. Les classes `Cheval` et `Tigre` ne compilent plus ! C'est parce qu'il faut implémenter la méthode permettant d'obtenir **le temps maximum de vol**... Or, ces montures n'ont pas de temps maximum de vol ! On va donc procéder comme pour `Griffon` en soulevant une erreur :

    ```java
    throw new Error("Cette monture ne peut pas voler!");
    ```

5. Ajoutez une classe `Dragon` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 400. Elle possède aussi un temps de vol maximum de 120 (car c'est une monture volante). Elle ne possède pas d'endurance. Par contre, on veut connaître sa **puissance de feu** qui est de 200. Adaptez votre classe en conséquence.

6. Mettez à jour l'interface `Monture` avec la méthode pour la puissance de feu au cas où il y ait d'autres types de dragons ajoutés dans le futur et corrigez les erreurs de compilation.

7. Enfin, ajoutez une classe `LicorneAilee` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 75. Elle possède aussi un temps de vol maximum de 20 (car c'est une monture volante) et une endurance de 50 (car c'est aussi une monture terrestre !). Par contre, elle n'a pas de puissance de feu.

</div>

C'était pénible, n'est-ce pas ? C'est normal, cette solution est très mauvaise et fastidieuse. À chaque nouvel ajout de type de monture avec ses spécificités, on doit modifier tous les autres types et les forcer à implémenter des méthodes qui ne les concernent pas... Le fait de lever tant d'erreurs indique une très mauvaise conception.

Si le développeur avait bien raison de vouloir faire une interface lors de la création de la première monture, il a voulu regrouper trop de chose dans une seule et même interface : les méthodes communes à toutes les montures (nom, vitesse) et la méthode concernant l'endurance, spécifique aux montures terrestres. Par la suite, on a continué dans cette mauvaise logique. Il aurait dû dès le départ diviser cela en **deux interfaces** et on aurait dû créer plus d'interfaces à chaque nouveau type de monture ayant ses spécificités. 

On rappelle qu'une **interface** peut hériter d'une autre interface ! Et qu'une classe peut implémenter autant d'interfaces qu'elle le désire.

Imaginons l'exemple suivant :

```java
interface I_Exemple {
  void operationGlobale();
  void operationA();
  void operationB();
  void operationC();
}

class A implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    //Code...
  }

  public void operationB() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }

  public void operationC() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }
}

class B implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }

  public void operationB() {
    //Code
  }

  public void operationC() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }
}

class C implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }

  public void operationB() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }

  public void operationC() {
    //Code
  }
}

class D implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    throw new Error("Impossible d'implémenter cette méthode.");
  }

  public void operationB() {
    //Code
  }

  public void operationC() {
    //Code
  }
}
```

<div style="text-align:center">
![Interface segregation 1]({{site.baseurl}}/assets/TP3/ISP1.svg){: width="50%" }
</div>

Tout cela peut être refactoré bien plus élégamment ainsi :

```java
interface I_Exemple {
  void operationGlobale();
}

interface I_A extends I_Exemple {
  void operationA();
}

interface I_B extends I_Exemple {
  void operationB();
}

interface I_C extends I_Exemple {
  void operationC();
}

class A implements I_A {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    //Code...
  }
}

class B implements I_B {
  public void operationGlobale() {
    //Code...
  }

  public void operationB() {
    //Code...
  }
}

class C implements I_C {
  public void operationGlobale() {
    //Code...
  }

  public void operationC() {
    //Code...
  }
}

class D implements I_B, I_C {
  public void operationGlobale() {
    //Code...
  }

  public void operationB() {
    //Code
  }

  public void operationC() {
    //Code
  }  
}
```

<div style="text-align:center">
![Interface segregation 2]({{site.baseurl}}/assets/TP3/ISP2.svg){: width="50%" }
</div>

Comme vous le constatez, plus aucune classe n'est forcée à implémenter des méthodes qu'elle ne peut pas définir, tout en conservant ses spécificités. Plus aucune erreur n'a besoin d'être levée.

Bref, cela est en partie un mix entre le **principe de responsabilité unique** et une visualisation **hiérarchique** du problème. On note quand même le cas intéressant de la classe `D` qui permet à la fois d'avoir le type `I_Exemple`, `I_B` et `I_C` !

<div class="exercise">

Refactorez votre code pour respecter le **principe de ségrégation des interfaces**. On veut garder les spécificités de chaque type de monture, mais éliminer toutes les levées d'erreurs. Soyez vigilant pour le dragon et la licorne ailée.

</div>

### Principe d'inversion des dépendances (Dependency inversion)

Enfin, il reste le **principe d'inversion des dépendances**.

Ce principe dit que :

* Les différentes classes ne doivent pas dépendre d'implémentations concrètes, mais d'abstractions (classes abstraites/interfaces).

* Les abstractions ne doivent pas dépendre des détails (les implémentations, les classes filles) mais les détails (les classes concrètes) doivent dépendre des abstractions. Nous l'avons bien vu avec l'exercice sur les **pokémons** lorsque nous étudions le principe **ouvert/fermé**.

Ce principe permet d'obtenir une très forte **modularité** du programme. Si on couple cela avec la technique **d'injection des dépendances** et des **design patterns créateurs**, tels que des **fabriques abstraites**, ou bien des **conteneurs de dépendances**, on obtient un logiciel dont on peut moduler le fonctionnement sans toucher au code source, simplement en ajoutant de nouvelles classes et/ou en éditant des fichiers de configuration. Les différents **frameworks** mettent en place une architecture favorisant l'inversion des dépendances.

En fait, ce principe découle de la bonne application des autres principes et notamment du principe **ouvert/fermé** et de la **substitution de Liskov**.

Nous verrons aussi qu'il est essentiel de bien respecter ce principe quand on réalise des tests unitaires.

Tout d'abord, illustrons ce principe avec un exemple. 

<div class="exercise">

1. Ouvrez le paquetage `dip`. Dans ce projet, il y a une classe `Etudiant` et une classe `CompteUniversitaire`. Un compte universitaire est détenu par un étudiant. On utilise son nom et son prénom pour générer un login.

2. Ajoutez une classe **Enseignant** qui possède un nom, un prénom et définit des **getters** pour ces deux attributs.

3. La logique pour créer un compte universitaire pour un enseignant est la même que pour un étudiant. On souhaite donc logiquement réutiliser la classe `CompteUniversitaire`. Mais ce n'est pas possible, car un enseignant n'est pas un étudiant !

</div>

Le problème souligné ici est qu'on a utilisé une classe concrète (`Etudiant`) dans `CompteUniversitaire` à la place d'une classe abstraite ou d'une interface, ce qui empêche l'utilisation avec d'autres types de classes (ici, `Enseignant`).

Illustrons ce problème avec un exemple :

```java
class A {

  public void methodeA() {
    //Code...
  }

}

class B {

  public void methodeB() {
    //Code
  }

}

class Service {

  private A dependance;

  public Service() {
    dependance = new A();
  }

  public void action() {
    a.methodeA();
  }
}
```

Ici, nous avons un problème similaire : la classe `Service` dépend directement d'une implémentation concrète `A` ce qui le rend peu modulable. Si je veux utiliser `B` à la place de `A`, je dois récrire le code source de `Service`.

Pour régler cela, nous allons tout d'abord commencer par définir et utiliser une **interface** :

```java
interface I_Exemple {
  void methodeExemple();
}

class A implements I_Exemple {

  public void methodeA() {
    //Code...
  }

  @Override
  public void methodeExemple() {
    methodeA();
  }

}

class B implements I_Exemple {

  public void methodeB() {
    //Code
  }

  @Override
  public void methodeExemple() {
    methodeB();
  }
}
```

Bien, je peux maintenant utiliser un `I_Exemple` dans `Service` au lieu de `A` ou `B`... Mais il reste un problème ! Dans l'exemple d'origine, `A` était instancié dans le constructeur. Or, on ne peut pas instancier une interface ou une classe abstraite (seulement une classe concrète). Et on ne peut pas spécifier directement quelle classe concrète est utilisée, car notre classe `Service` ne sera alors plus modulable :

```java
class Service {

  private I_Exemple dependance;

  public Service() {
    dependance = new ???;
  }

  public void action() {
    dependance.methodeExemple();
  }
}
```

Pour palier à ce problème, on utilise **l'injection de dépendance**. La classe concrète est injectée via le constructeur, au moment de l'instanciation de l'objet, mais la classe ne connaît que le type abstrait. Cela permet une modularité de la classe qui peut alors être utilisée avec n'importe quel service concret dérivé du type abstrait. Et on peut en ajouter dans le futur. C'est exactement ce que nous avions fait avec le paquet de cartes et les tris avec le pattern **stratégie**, mais également avec le **décorateur** dans l'exercice avec les produits. L'injection de dépendance est partout !

```java
class Service {

  private I_Exemple dependance;

  public Service(I_Exemple dependance) {
    this.dependance = dependance;
  }

  public void action() {
    dependance.methodeExemple();
  }
}

class Main {

  public static void main(String[] args) {
    //Utilise "methodeA" dans "action"
    Service s1 = new Service(new A());

    //Utilise "methodeB" dans "action"
    Service s2 = new Service(new B());
  }

}
```

<div style="text-align:center">
![Dependency inversion 1]({{site.baseurl}}/assets/TP3/DIP1.svg){: width="50%" }
</div>

De cette manière, **l'inversion des dépendances** est respectée. La classe `Service` ne dépend plus d'aucun service concret, mais d'**abstractions**.

<div class="exercise">

1. Réfactorez votre code pour pouvoir utiliser `CompteUniversitaire` aussi bien avec un objet de type `Etudiant` qu'un objet de type `Enseignant`. Il faudra normalement adapter le code dans le `Main`.

2. Testez de créer un compte universitaire pour l'enseignante "_Bricot Judas_".

3. On souhaite pouvoir utiliser différentes méthodes pour générer le login dans `CompteUniversitaire`. La première méthode est celle déjà présente qui combine le nom + la première lettre du prénom. On souhaite aussi pouvoir disposer d'une méthode qui mélange les caractères du nom avec cet algorithme :

    ```java
    List<String> nomList = Arrays.asList(nom.split(""));
    Collections.shuffle(nomList);
    StringBuilder builder = new StringBuilder();
    for(String letter : nomList) {
      builder.append(letter);
    }
    String login = builder.toString();
    ```

4. En utilisant votre connaissance du pattern **stratégie** et de **l'injection de dépendances** faites en sorte qu'on puisse choisir si `CompteUniversitaire` utilise la génération de login "simple" (nom + première lettre prénom) ou par mélange.

5. Le compte de "_Tarembois Guy_" doit être généré en utilisant le générateur de login simple et celui de "_Bricot Judas_" avec le générateur par mélange. Testez.
</div>

## Exercices bilan

Dans cette section, vous allez travailler sur un ensemble d'exercices "bilan" qui reprennent les notions abordées dans ce TP. L'idée est que vous identifiez le problème et mettiez en place une solution adéquate et respectueuse des **principes SOLID**.

### Villes et bâtiments

<div class="exercise">

1. Ouvrez le paquetage `bilan1`. Ce projet modélise le fonctionnement d'un jeu dans lequel on peut construire sa propre **ville** (qui peut être éventuellement attaquée par d'autres joueurs) :

    * Une ville possède différents types de **bâtiments**. 
    
    * Un **bâtiment** est caractérisé par : un **nombre de points de vie maximum** (`pvMax`) et un **nombre de points de vie actuels** (`pv` qui est égal au maximum au début et qui peut diminuer si le bâtiment est attaqué). Vous pouvez voir tout cela dans la classe `Batiment`.

    * Chaque **bâtiment** possède (éventuellement) ses propres caractéristiques.

    * Une ville peut posséder plusieurs fois le même type de bâtiment (par exemple, trois théâtres).

    * On doit pouvoir calculer le **score culturel d'une ville**. Le score culturel est calculé en fonction de tous les bâtiments que possède la ville, selon les règles suivantes :

      * Pour chaque **musée** que comporte la ville, on ajoute au score le **nombre d'œuvres** que possède le musée ainsi que le **bonus** associé au thème du musée.

      * Pour chaque **théâtre** que comporte la ville, on ajoute au score le **nombre d'entrées** du théâtre.

      * Pour chaque **statue**, que comporte la ville, on ajoute le **prix de construction** de la statue ainsi que son **nombre de points de vie** actuel.

    * On doit pouvoir savoir si une ville est **majeure**. Une ville est **majeure** si elle possède au moins **10 bâtiments majeurs**. Les bâtiments majeurs sont les **palais** et les **banques**.

2. Implémentez les méthodes `calculerScoreCulturel`, `compterBatimentsMajeurs` et `estMajeure` de la classe `Ville` en respectant les contraintes définies au point précédent. **Attention** dans le futur, on souhaitera éventuellement ajouter de nouveaux types de bâtiments qui pourraient influer sur le score culturel d'une ville, ou qui pourraient être majeurs. Dans ce cas, il faudra que votre conception permette cet ajout facilement sans avoir à modifier la classe `Ville`.

3. Une classe de test unitaire est présente dans `test/java/bilan1`. Lisez les tests et exécutez-les afin de vérifier que votre solution fonctionne.

</div>

### Comptes bancaires

<div class="exercise">

1. Ouvrez le paquetage `bilan2`. Il s'agit d'une application de gestion de comptes bancaires. Le **contrat** de la classe `CompteBancaire` est qu'on puisse consulter son solde, retirer de l'argent d'un compte (sans passer son solde en négatif) et en déposer autant d'argent qu'on souhaite.

2. Complétez la classe `CompteBancaireAvecPlafond` : cette classe doit lever une exception `throw new RuntimeException("On ne peut pas déposer plus que le plafond du compte.")` si on essaye d'ajouter de l'argent qui ferait dépasser au solde le plafond du compte. On souhaite garder l'héritage avec `CompteBancaire`.

3. Complétez la classe `CompteBancaireAvecNombreRetraitMaximum` : cette classe doit compter le nombre de retraits effectués et lever une exception `throw new RuntimeException("Nombre maximal de retraits atteint!")` si on essaye de retirer trop de fois (si le nombre de retraits effectués est supérieur au nombre de retraits maximum). On souhaite garder l'héritage avec `CompteBancaire`.

4. Pour valider, exécutez les tests unitaires contenus dans les trois classes de tests dans `test/java/bilan2`. 

5. Décommentez les tests `testDeposerCompteBancaireAvecPlafond` et `testRetirerCompteBancaireAvecNombreRetraitMaximum` puis exécutez-les. Pourquoi ne passent-ils pas ? Quel est le principe **SOLID** est violé par votre code ?

6. Réfactorez votre code afin de supprimer l'héritage vers `CompteBancaire` et ainsi ne plus violer un *certain* principe SOLID. Les deux tests unitaires `testDeposerCompteBancaireAvecPlafond` et `testRetirerCompteBancaireAvecNombreRetraitMaximum` ne devraient plus compiler, vous pouvez les supprimer (car ils n'ont plus lieu d'être).

7. **Bonus** : comment pourrait-on faire pour avoir des comptes bancaires qui combinent les fonctionnalités de plafond et de nombre de retraits maximum, et peut-être d'autres fonctionnalités à l'avenir ? **Si et seulement si le temps le permet**, réfactorez votre code pour rendre cela possible (et adaptez vos tests unitaires en conséquence).

</div>

### Serveurs à louer

<div class="exercise">

1. Ouvrez le paquetage `bilan3`. Il s'agit d'une application de gestion d'une entreprise qui loue des **serveurs** dédiés. Chaque serveur possède notamment un certain montant de **mémoire vive** (en Go), un **processeur** et un **prix mensuel** (à payer par le client qui loue le serveur). L'entreprise propose trois **offres** de serveurs configurés différemment et avec des coûts mensuels plus ou moins élevés : un serveur **basique**, un serveur **intermédiaire** et un serveur **pro**. Sur chaque **serveur**, on peut réaliser certaines actions :

    * Calculer le montant mensuel à payer pour louer le serveur (`calculerPrixMensuel`).

    * Récupérer le montant de mémoire vive (`getMemoireVive`)

    * Récupérer le processeur utilisé (`getCategorieProcesseur`)

    * Allumer le serveur (`allumer`).

    * Éteindre le serveur (`eteindre`).

    * Ouvrir un ticket, s'il y a un problème, pour être aidé par un technicien (`ouvrirTicket`).

    * Fermer un ticket (`fermerTicket`).

2. On aimerait pouvoir ajouter divers **services optionnels** à un **serveur**. On vous demande d'implémenter une solution permettant de créer des serveurs disposant de certains de ces services optionnels :

    * Serveur avec plus de mémoire vive : 
      
      * Le serveur dispose d'une extension de sa mémoire vive (nombre entier représentant des Go ajoutés).
      * Quand le serveur est allumé, en plus des informations habituelles, on affiche la quantité de mémoire vive ajoutée.
      * Le prix mensuel de location du serveur augmente de 5€ par Go de mémoire ajoutée. 

    * Serveur avec sauvegarde des données :

      * Le serveur dispose d'un système de sauvegarde des données (que nous allons modéliser simplement par des messages).
      * Quand le serveur est allumé, en plus des informations habituelles, on signale que la sauvegarde des données est disponible.
      * Le prix mensuel de location du serveur augmente de 5€.
      * Lorsque le serveur est éteint, on demande à l'utilisateur s'il souhaite créer un fichier de sauvegarde des données du serveur. S'il confirme, un message "Création et export d'un fichier de sauvegarde..." est affiché.

      Pour réaliser la dernière fonctionnalité, vous pouvez vous servir de la fonction : `Utils.demander` qui permet de poser une question à un utilisateur et renvoie vrai ou faux (s'il répond oui ou non) :

      ```java
      if(Utils.demander("Voulez-vous réaliser cette action ?")) {
        System.out.println("Action...");
      }
      ```

    * Serveur avec assurance :

      * Le serveur dispose d'un système d'assurance qui permet au client d'être dédommagé s'il rencontre trop de problèmes.
      * Quand le serveur est allumé, en plus des informations habituelles, on signale que le serveur est couvert par une assurance.
      * Le prix mensuel de location du serveur augmente de 10€.
      * Lorsqu'un ticket est ouvert, un compteur comptant le nombre de tickets ouverts est incrémenté.
      * Lorsqu'un ticket est fermé, ce compteur est décrémenté (pour simplifier, on dira qu'on ne ferme jamais un ticket s'il n'y a pas de tickets ouverts).
      * Lors de l'ouverture d'un nouveau ticket, s'il y a déjà trois tickets d'ouverts, on affiche un message informant l'utilisateur qu'il sera remboursé de 10€ sur sa prochaine facture.

    * Serveur avec logs :

      * Le serveur dispose d'un système qui permet d'avoir de garder une trace des événements qui se produisent sur le serveur : allumage, arrêt, ouverture et fermeture de tickets. Pour cela, on doit fournir un **nom de fichier** (chaîne de caractères) où les informations seront sauvegardées.
      * Quand le serveur est allumé, en plus des informations habituelles, on signale que le système de log est activé, en indiquant le nom du fichier où sont sauvegardés les logs.
      * Le prix mensuel de location du serveur n'augmente pas (option gratuite).
      * Dès qu'un événement se produit (allumage, arrêt, ouverture et fermeture de tickets) l'information est reportée dans le fichier en indiquant la date de l'événement. Par exemple `[2024-10-29T17:44:22] : Serveur allumé`, etc.

      Pour réaliser la dernière fonctionnalité, vous pouvez vous servir de la fonction : `Utils.ecrireDansFichier` qui permet d'écrire une ligne dans un fichier, combiné à l'utilisation d'un objet `LocalDateTime` :

      ```java
      LocalDateTime time = LocalDateTime.now();
      Utils.ecrireDansFichier(nomFichier, String.format("[%s] : %s\n", time, "Mon message"));
      ```
      
      Normalement, le fichier sera sauvegardé à la racine de votre projet.

      Il est conseillé de se créer une méthode (privée) afin de ne pas dupliquer le code.

      Pour les logs, on se contentera de messages simples : Serveur allumé, Serveur éteint, Ticket ouvert, Ticket Fermé.

3. Testez de créer divers serveurs avec des services (et vérifiez leur comportement : prix, allumage, tickets, etc) :

    * Un serveur **basique** avec **4Go** de **mémoire vive supplémentaire** et un **fichier de log**.

    * Un serveur **intermédiaire** avec la **sauvegarde des données** et une **assurance**.

    * Un serveur **pro** avec **8Go** de **mémoire vive supplémentaire**, la **sauvegarde des données**, une **assurance** et un **fichier de log**.

4. **Bonus** : comment pourrait-on faire pour que les services **assurance** et **sauvegarde des données** soient seulement réservés aux configurations intermédiaires et pros ? **Si et seulement si le temps le permet**, réfactorez votre code pour rendre cela possible.

</div>

### Une application modulable

Pour finir, nous allons travailler sur un exercice un poil plus conséquent divisé en différentes **couches** (cf. partie architecture logicielle du cours sur les DSI).

Vous allez voir qu'en plus de rendre notre projet modulable, utiliser **l'inversion de dépendances** et globalement **ne pas dépendre d'implémentations concrètes** est plus qu'important, car une architecture ne respectant pas ce principe peut occasionner des effets de bords indésirables lors des **tests unitaires**.

<div class="exercise">

1. Ouvrez le paquetage `bilan4`. Cette application permet de créer des utilisateurs, de hacher leur mot de passe, de se connecter... Il y a aussi un système de gestion de diverses erreurs. Prenez le temps d'examiner l'architecture, la répartition des classes. Exécutez le programme avec le `Main`.

2. Générez un **diagramme de classes de conception** du paquetage `bilan4` (avec `IntelliJ`). Cela nous permettra de faire une comparaison après **refactoring**.

3. Une classe contenant des **tests unitaires** est présente dans `src/test/java/bilan4/service/utilisateur`. Lancez les tests deux fois, tout devrait bien se passer.

4. On aimerait effectuer quelques changements dans le programme, notamment au niveau de `ServiceUtilisateur` :

    * Hasher le mot de passe avec `SHA256` au lieu de `MD5`.

    * Utiliser la classe `StockageUtilisateurFichier` pour gérer le stockage des utilisateurs. Contrairement à `StockageUtilisateurMemoire` qui stocke les données de manière volatile, ici, les utilisateurs seront stockés dans un fichier de manière persistante (que sera généré à la racine du projet).

    Effectuez ces changements, relancez le programme (`Main`) pour vérifier que tout fonctionne.

5. Lancez maintenant les tests unitaires **2 fois de suite**. Il y a une erreur ! Trouvez la raison de cette erreur.
</div>

L'architecture proposée ne respecte pas le principe d'inversion des dépendances, car la classe `ServiceUtilisateur` possède des dépendances vers des classes **concrètes** qui, de plus, ne sont pas injectées.

On se rend compte que cela pose un véritable problème au niveau des **tests unitaire**. Un test **unitaire**, comme son nom l'indique, teste le fonctionnement d'**une classe**, une **unité**. Or, quand on exécute les tests sur `ServiceUtilisateur`, les méthodes des dépendances concrètes utilisées sont aussi appelées ! Ce qui déclenche donc réellement l'enregistrement de l'utilisateur créé pour les tests dans la base de donnée, alors qu'on souhaitait simplement vérifier la méthode `creerUtilisateur`. Quand les tests sont exécutés une seconde fois, une erreur est détectée, car l'utilisateur existe déjà.

Imaginez-vous dans un contexte plus concret, par exemple, dans un projet web : avec une telle conception, vos tests unitaires déclencheraient l'enregistrement d'utilisateurs de test sur votre base de données réelle ! Ce n'est pas envisageable.

Les tests unitaires **ne doivent pas dépendre de l'environnement de production**. Ils doivent pouvoir être lancé seulement à partir du code de la classe testée, sans dépendre de rien d'autre.

Vous avez sans doute constaté des messages **mail envoyé** lors de l'exécution des tests unitaires. Bien sûr, cela n'est pas vraiment le cas, mais de même, dans un cas concret, avec la conception actuelle, des mails seraient véritablement envoyés lors du test du programme (après création d'un utilisateur). C'est problématique.

Pour palier à cela, les testeurs mettent en place des **stubs**. Il s'agit de classes **bouchons** qui ne réalisent pas réellement l'action demandée, ou alors pas de manière persistante. Aucun effet de bord est produit.

Plus tard, dans l'année, vous découvrirez les **mocks** qui permettent de créer de "fausses" classes destinées aux tests dont on peut facilement éditer les méthodes.

Ici, la classe `StockageUtilisateurMemoire` agit comme un **stub** qu'on peut utiliser pour les tests sans risque. Dans un environnement réel, on utiliserait un stockage avec une base de données dédiée aux tests, comme `SQLite`, qu'on viderait ensuite.

Cependant, comment faire pour garder le stockage avec fichier pur l'exécution "normale" du programme, et le stockage en mémoire pour les tests ? Devons-nous éditer le code source de la classe `ServiceUtilisateur` avant les tests, puis la remettre en ordre ensuite ? Bien sûr que non ! Il suffit de mettre en pratique le **principe d'inversion de dépendance** que vous connaissez.

<div class="exercise">

1. Refactorez les classes du paquetage **storage** puis le code de `ServiceUtilisateur` afin de respecter le principe d'inversion des dépendances en utilisant des **abstractions** et surtout **l'injection de dépendances**.

2. Mettez à jour le code de `ControllerUtilisateur` afin que celui-ci utilise `ServiceUtilisateur` avec `StockageUtilisateurFichier`.

3. Mettez à jour le code de vos tests unitaires pour utiliser que l'objet de type `ServiceUtilisateur` utilisé dans les tests utilise `StockageUtilisateurMemoire`.

4. Vérifiez que votre programme fonctionne toujours correctement et vérifiez que vos tests unitaires passent plusieurs fois sans problème.

</div>

Il reste maintenant le problème des "mails envoyés" quand on exécute les tests. On aimerait également que plusieurs autres dépendances soient modulables dans le programme :

* L'envoi des mails. On veut pouvoir utiliser une autre classe et surtout une classe n'envoyant rien (un "Fake mailer") pour les tests.

* Le système de hachage du mot de passe. On veut pouvoir changer entre MD5 et SHA256. Et pour économiser du temps de calcul pour les tests, on voudrait un "Fake Hasher" qui ne hache rien et renvoie le mot de passe en clair.

* La classe `ServiceUtilisateur` elle-même, qui doit pouvoir être remplacée par autre chose dans le `ControllerUtilisateur`. Cela pourrait notamment être utile si on veut tester le controller indépendamment du code de `ServiceUtilisateur`.

<div class="exercise">

1. Refactorez votre code pour appliquer **l'inversion de dépendances** par rapport aux modules cités (mails, hasher, service utilisateur...). Il faudra créer de nouvelles interfaces et modifier des classes existantes (les hashers, le mailer...) et aussi créer deux classes de **stub** pour les tests : `FakeMailer` et `FakeHasher`.

2. Adaptez l'instanciation de `ServiceUtilisateur` dans vos tests unitaires et vérifiez qu'ils passent toujours. Vous ne devez plus constater aucun message "mail envoyé".

3. Vérifiez que le programme fonctionne toujours comme attendu.

4. Générez le **diagramme de classes de conception** de l'application (après refactoring donc) et comparez-le avec le premier diagramme que vous aviez réalisé.

</div>

## Conclusion

Voilà, maintenant, vous savez tout des principes **SOLID** ! Vous êtes donc plus proche d'un ingénieur logiciel qu'un codeur. Il existe un acronyme opposé : les principes **STUPID** qui sont six pratiques qui rendent le code très peu qualitatif, intestable, non évolutif et qu'il faut donc absolument éviter ! Bref, des **mauvaises pratiques** qui sont souvent observées. Vous pouvez consulter de la documentation à ce propos [sur cette page](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming).

Dorénavant, pour vos futurs projets (ou ceux actuels, comme la SAE) il faut systématiquement vous poser et réfléchir à la conception de votre programme **à long terme**. Il n'est jamais trop tard pour faire du **refactoring**, mais ne pas avoir besoin d'en faire en respectant une certaine qualité logicielle d'entrée de jeu est encore mieux.

Dans les prochains TPs, nous allons donc nous concentrer sur les **design patterns** (nous en avons déjà vu deux dans ce TP) qui permettront de vous donner des outils pour résoudre des problèmes de conception connus tout en mettant en facilitant le respect et la mise en ouvre les principes SOLID.