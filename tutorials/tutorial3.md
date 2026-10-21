---
title: TP3 &ndash; Qualité du code - Les principes SOLID
subtitle: SOLID, Qualité, Interface, Abstraction, Héritage, Composition, Injection de dépendances, Design Patterns
layout: tutorial
lang: fr
---

Dans la première partie de cette ressource, nous avons parlé de **conception logicielle** et notamment de la manière de la représenter à l'aide de **diagrammes de classes de conception**.

Cependant, savoir modéliser la conception ne garantit en rien la qualité de celle-ci. Un plan de construction d'un bâtiment peut être tout à fait valide d'un point de vue technique, mais donnera potentiellement une bâtisse qui s'écroulera dans quelques années si elle a été mal pensée.

On a la même logique au niveau du développement logiciel. Un logiciel mal conçu peut répondre à un besoin et satisfaire le client et ses utilisateurs dans l'immédiat, mais il sera alors très difficile de le faire évoluer sur la durée.

De manière générale, les principes de qualité du développement visent à faciliter l'évolution du logiciel tout en permettant de satisfaire les besoins actuels.

Tout cela est difficile à mettre en place au premier abord, car il peut parfois être bien plus rapide et facile de développer une solution peu qualitative, mais qui fonctionne. Néanmoins, le code produit ne tiendra pas au fur et à mesure que l'application va grossir ce qui conduira finalement à la réécriture d'une partie voire de la totalité du code ou pire, l'abandon du projet.

C'est un phénomène qui touche beaucoup d'entreprises du monde du développement. Face au besoin de délivrer une solution rapidement, l'aspect qualité est parfois négligé. Au bout de plusieurs années, il est très compliqué d'ajouter de nouvelles fonctionnalités et d'éviter les bugs. Une nouvelle personne rentrant dans le projet ne comprend rien au code. Le client n'est plus satisfait, car les nouvelles fonctionnalités sont délivrées moins fréquemment et de plus en plus de bugs apparaissent. C'est une barque qui prend l'eau sur laquelle on place du sparadrap pour boucher les trous. Mais à chaque fois qu'un trou est bouché, deux nouveaux apparaissent. Le client transfère le projet à une autre entreprise, qui ne comprend rien à ce qu'elle récupère... Plus formellement, on dit que la [**dette technique**](https://fr.wikipedia.org/wiki/Dette_technique) s'accumule.

Tout cela est aussi dur pour le développeur. Travailler dans un tel environnement est très désagréable et peut même dégoûter du développement. Jusqu'ici, vous avez travaillé sur des projets relativement petits (même pour vos SAEs) mais vous devriez être plus conscients de cette problématique après votre période de stage ou d'alternance.

L'ingénieur doit avoir une vision à long terme et prendre en compte les évolutions possibles de son programme. Pour l'aider dans cette tâche, il dispose de différents outils : les principes liés à la qualité du code, comme les principes **SOLID** et aussi les **design patterns**. La maîtrise de ces outils différencie un codeur (une IA ?) d'un ingénieur. Le codeur sait produire du code, l'ingénieur sait produire des logiciels durables.

Les **frameworks** proposent des structures et des mécanismes qui s’appuient souvent sur différents design patterns. Ils peuvent guider les choix de conception et faciliter l’application de bonnes pratiques, sans garantir à eux seuls la qualité du logiciel. Nous étudierons plusieurs **frameworks** l’année prochaine.

Bref, dans ce cours, nous allons commencer par nous intéresser aux **principes SOLID** qui constituent la porte d'entrée vers un programme bien conçu. Nous allons également commencer à parler de **design patterns** (nous allons en introduire 2) mais nous les étudierons plus en détail dans les prochains TP.

## Les principes SOLID

L'acronyme **SOLID** désigne cinq principes de conception logicielle :

* Le principe de **responsabilité unique** (`S`ingle responsibility)

* Le principe **ouvert/fermé** (`O`pen/Closed)

* Le principe de **substitution de Liskov** (`L`iskov substitution)

* Le principe de **ségrégation des interfaces** (`I`nterface segregation)

* Le principe **d'inversion des dépendances** (`D`ependency inversion)

Le respect de ces principes favorise le **faible couplage** et la **forte cohésion** des classes, facilite l'évolution du logiciel et réduit les risques de bugs liés à son architecture.

Les **design patterns** sont des solutions à des problèmes bien définis qui fournissent des modèles réutilisables et adaptables à de nombreux projets. Ces patterns contribuent notamment à mieux respecter les principes **SOLID**. En revanche, utiliser des **design patterns** ne garantit pas toujours une qualité de code respectant **SOLID** et peut même être contre-productif — il faut donc savoir les utiliser au bon endroit et au bon moment.

Une conception adaptée permet de prendre en charge certaines évolutions en ajoutant de nouvelles implémentations, **sans modifier les classes qui utilisent les abstractions existantes**. C’est, par exemple, l’objectif du principe ouvert/fermé : prévoir des possibilités d’extension tout en limitant les modifications du code déjà en place. Cela ne signifie pas que les classes existantes ne devront plus jamais être modifiées.

Dans ce TP, nous allons étudier chaque principe et nous allons vous fournir du code qui est (la plupart du temps) fonctionnel, mais développé sans respecter **SOLID**. Vous allez alors constater que :

* Il est difficile d'ajouter de nouvelles choses.
* L'ajout de fonctionnalités ou d'éléments entraîne la modification de multiples classes.
* Des bugs parfois assez inattendus peuvent survenir.
* Les tests unitaires sont difficiles à gérer.

Ensuite, nous allons voir comment les principes **SOLID** permettent de traiter ces problèmes, et vous allez donc devoir **refactorer** les différentes applications. **Refactorer** du code (ou réusiner du code en français) consiste à améliorer sa structure interne **sans changer son comportement observable**. Il s’agit de rendre le code plus facile à comprendre et à faire évoluer.

**Attention** : Dans plusieurs exercices, il vous sera demandé de **générer un diagramme de classes** (avec `IntelliJ` ou autre IDE qui propose cette fonctionnalité). Bien que les diagrammes générés puissent être parfois légèrement erronés, et qu'il vaut généralement mieux faire le dessin soi-même, cela vous fera gagner du temps. Il est fortement conseillé de prendre des **captures d'écran** de chaque diagramme de classes et de les sauvegarder dans un sous-dossier de votre dépôt. Certains diagrammes permettent de comparer l'évolution de l'architecture et des dépendances avant/après **refactoring**.

<div class="exercise">

1. Pour commencer, clonez en local le **dépôt gitlab** forké dans votre espace privé dans le cours de qualité de développement : [https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/etu/votre_login/tp3](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/etu/votre_login/tp3) en remplaçant `votre_login` par le login que vous utilisez pour accéder au serveur gitlab du département.

2. Ouvrez le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur.

3. À la fin de chaque séance, n'oubliez pas de faire un **push** vers votre dépôt distant sur **Gitlab**.

</div>

Ce projet contient divers **paquetages** contenant le code de base pour chaque exercice que nous allons traiter.

### Principe de responsabilité unique (Single Responsibility)

Pour mener à bien le déroulement d'une fonctionnalité, le programme va faire appel à diverses classes qui vont interagir entre elles (comme nous l'avons vu avec le DSI). Ces classes vont **traiter** la demande. Chaque classe possède la **responsabilité** d'effectuer une partie de ce traitement. 

Le principe de **responsabilité unique** indique qu'une classe ne doit pas posséder plus d'une responsabilité. Une responsabilité regroupe des éléments de code qui évoluent pour les mêmes raisons. Deux traitements peuvent utiliser les mêmes données tout en relevant de responsabilités différentes.

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

   public String getContenu() {return contenu;}

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

Ici, chaque classe a **une responsabilité unique** : si la logique pour envoyer un mail change, la classe **Email** n'est pas impactée.

Le principe de responsabilité unique s'applique également aux **paquetages** : chaque paquetage est lié à une responsabilité du programme. Dans un logiciel plus complet, on aurait différents paquetages avec différents rôles : IHM, contrôleurs, services, stockage... (et on pourrait (même *devrait*) aller plus en détail).

Ce principe semble assez facile à mettre en place, mais dans la réalité, on retrouve malheureusement des classes (et des paquetages) "fourre-tout" qui deviennent illisibles au fur et à mesure de l'évolution du programme. Si votre classe a trop de méthodes, c'est peut-être qu'elle possède plus d'une responsabilité et que celles-ci pourraient être mieux réparties.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.srp1`. Examinez le code. Il s'agit d'un programme qui permet de faire un simple calcul (pour le moment, une addition). Actuellement, la classe `Client` possède trois responsabilités (certaines sont très simples et tiennent sur une ligne). Identifiez-les.

2. Refactorez le code pour répartir les responsabilités de `Client` en trois nouvelles classes distinctes (sans compter `Client`). Veillez à ce qu'après votre refactoring, les futures modifications restent limitées aux classes concernées. La classe `Client` devra dorénavant utiliser ces nouveaux **services**.

3. Effectuez les changements suivants du code qui, **si vous avez bien traité la question précédente**, ne doivent pas toucher le code de votre classe `Client` :

     * remplacer l'opération d'addition par une autre opération (par exemple, une soustraction)
     * changer l’affichage final du résultat et l'écrire dans un fichier à la place (plutôt qu'à la console). Vous pouvez utiliser le code suivant :
        ```java
          try (BufferedWriter writer = new BufferedWriter(new FileWriter("resultat.txt"))) {
            writer.write(String.format("Résultat : %s%n", resultat));
          }
          catch (IOException e) {
            throw new RuntimeException("Erreur lors de l'écriture dans le fichier...", e);
          }
        ```
     * changer la saisie des nombres en utilisant un `Scanner` et la méthode `nextInt` au lieu d'un `BufferedReader`. Il faudra enlever le **catch** de `IOException` et `NumberFormatException` ainsi que les `parseInt`. À la place, on attrapera une exception `InputMismatchException`. Pour rappel, pour définir un `Scanner` :

         ```java
         Scanner scanner = new Scanner(System.in);
         int valeur = scanner.nextInt();
         ```
</div>

Bien sûr, ce premier exercice est très simpliste (et donc assez peu concret), mais il faut vous imaginer que les différentes responsabilités sont généralement des traitements plus longs et/ou plus complexes !

Voyons maintenant un autre exemple.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.srp2`. Il contient une classe `Rectangle` qui permet de créer des rectangles et de calculer leur aire.

2. Une application graphique souhaite pouvoir afficher les **rectangles**. Une première idée est d'utiliser la classe `JFrame` (de la librairie _Java Swing_), ce qui permettra de les afficher :

    * Faites hériter `Rectangle` de `JFrame`.

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
          super.paint(g);
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

4. L'idée est d'avoir deux classes : une première, gérant la forme rectangle et l'autre permettant de l'afficher. Mais pour autant, il ne faut pas dupliquer de code ! Refactorez votre code en conséquence afin de mettre en place cette nouvelle conception. **Indication** : pour afficher le rectangle, utilisez un `JPanel` placé dans une `JFrame`. Réalisez le dessin dans la méthode `paintComponent(Graphics g)` du panneau, en commençant par appeler `super.paintComponent(g)`.

5. Assurez-vous que tout fonctionne (il faudra sans doute adapter le `main`) et qu'il est possible de créer des rectangles sans logique d'affichage et de les afficher à l'aide de la classe dédiée.

6. Arrivez-vous à identifier le type de relation utilisé entre le rectangle et l'objet chargé de l'afficher : association, agrégation ou composition forte ? Justifiez votre choix.

</div>

### Principe Ouvert/Fermé (Open/Closed)

Après cette mise en bouche, il est temps d'attaquer de sérieux problèmes de conception en développant le **principe ouvert/fermé**. Ce principe est défini comme suit :

"_Les entités d'un logiciel (classes, modules, fonctions) doivent être **ouvertes** aux extensions, mais **fermées** aux modifications._" (**Bertrand Meyer**).

En d'autres termes, il doit être possible d'étendre les fonctionnalités/le **comportement** d'une entité comme une classe **sans pour autant avoir besoin de modifier son code source**.

Ce principe est un pilier fondamental de la qualité du code. Avec ce principe, même une classe ou une librairie compilée (non modifiable) autorise le développeur à étendre les fonctionnalités proposées.

Malheureusement, dans de nombreux projets, on rencontre fréquemment des classes violant ce principe, car mal conçues. Les symptômes sont généralement :
* Utilisation d'énormes blocs `if/else if/else` ou de blocs `switch case` qui grossissent au fur et à mesure qu'on ajoute de nouvelles choses. Avec l'utilisation de `classes` et de l'héritage, on va en plus certainement se retrouver à utiliser des instructions `instanceof` ou `getClass()` (pour vérifier le type de l'objet) et des conversions de type (`cast`) pour pouvoir utiliser des méthodes précises.
* Nécessité de dupliquer du code pour ajouter une nouvelle fonctionnalité (non-respect du principe [_DRY_](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself)).
* Une classe mère qui dépend de ses classes filles.

Pour vous mettre dans le bain et vous montrer la problématique derrière tout cela, vous allez ajouter de nouvelles fonctionnalités à des projets existants qui ne respectent pas le principe ouvert/fermé.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.ocp1`. Dans ce projet, une classe `Animal` permet de gérer différents types d'animaux et leur cri, selon l'attribut `type` de l'objet.

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

1. Ouvrez le paquetage `fr.umontpellier.iut.ocp2`. Explorez les classes. Étudiez notamment la classe `SimulateurCombat`.

2. Ajoutez un nouveau type de pokémon : le pokémon type **électricité** qui possède les caractéristiques suivantes :

    * En plus des attributs d'un `Pokemon` classique, un pokémon **électrique** possède un attribut entier `chargeMax` et un attribut booléen `superDecharge`.

    * Son attaque s'appelle **Éclair** et inflige **20 dégâts**, auxquels s'ajoute un **bonus de dégâts** entier tiré au hasard entre **0** et `chargeMax`, bornes incluses. On suppose que `chargeMax` est positif. Si l'attribut `superDecharge` du pokémon vaut `true`, un **bonus supplémentaire de 20 dégâts** est ajouté.
  
    * Faites en sorte de prendre en charge ce nouveau type, **sans refactorer le code existant**, en créant une nouvelle classe `PokemonElectrique` et en ajoutant le code nécessaire là où il faut.

3. Ajoutez un nouveau type de pokémon : le pokémon type **psy** qui possède les caractéristiques suivantes :

    * En plus des attributs d'un `Pokemon` classique, un pokémon **psy** possède un attribut entier `bonusPsy`.

    * Son attaque s'appelle **Choc mental** et inflige précisément `30 * bonusPsy` dégâts.

    * Faites en sorte de prendre en charge ce nouveau type, **sans refactorer le code existant**, en créant une nouvelle classe `PokemonPsy` et en ajoutant le code nécessaire là où il faut.

4. Modifiez le `Main` pour faire combattre un pokémon possédant le type **électrique** contre un pokémon possédant le type **psy**. **Attention**, il ne faut pas modifier les autres classes créées auparavant ! Vérifiez que le type de chacun des deux pokémons s'affiche bien au début du combat (sinon, c'est que vous avez manqué quelque chose !).

</div>

Si ce n'était peut-être pas encore assez évident avec les animaux, à ce stade, vous devez vous rendre compte qu'ajouter un nouveau type de pokémon est fastidieux :

* Créer une classe du type correspondant.

* Implémenter une méthode donnant les dégâts de ce type.

* Modifier la classe `SimulateurCombat` en ajoutant un nouveau `else if` pour prendre en charge le nouveau type, faire un `cast` pour récupérer ses dégâts...

* Modifier la classe `Pokemon` pour adapter le `toString` en ajoutant un nouveau `else if` pour prendre en charge le nouveau type.

De plus, ici, seules deux fonctions ont vraiment besoin de connaître les détails des pokémons. Mais que se passerait-il s'il y avait beaucoup plus de méthodes et de classes qui en dépendent ? À chaque ajout d'un nouveau type, il faudrait modifier l'ensemble de ces classes et de ces méthodes ! Dans un gros projet, cela deviendrait vite un calvaire. De plus, il est facile d'oublier de mettre à jour une classe, ce qui ne provoque pas d'erreur de compilation, mais un bug lors de l'exécution (comme avec les animaux inconnus). Donc, la [**dette technique**](https://fr.wikipedia.org/wiki/Dette_technique) va croître beaucoup trop vite.

Le respect du principe **ouvert/fermé** va permettre de se limiter aux deux premières étapes : création d'une classe et implémentation des méthodes nécessaires dans cette même classe.

<div class="exercise">

Dans la suite du TP, nous allons donner un exemple de "mauvais code" similaire à celui présenté dans cet exercice puis une solution de refactorisation. Avant de lire ces explications, essayez de trouver par vous-même une solution pour refactorer le code du paquetage `fr.umontpellier.iut.ocp1` afin de respecter le principe **ouvert/fermé** (vous devrez aussi probablement adapter le `Main` en conséquence). Une fois que vous avez terminé, lisez la suite des explications. Si vous bloquez et/ou que vous n'arrivez pas à obtenir une solution satisfaisante, passez aussi à la suite des explications.

</div>

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

L'ajout d'une nouvelle figure géométrique (par exemple, un carré) nécessite la modification de la classe `FigureGeometrique` et de la méthode `dessiner`. Le principe ouvert/fermé n'est pas respecté. De plus, si `typeFigure` contient une chaîne différente de `"rectangle"` et de `"triangle"`, la méthode ne dessine rien et ne signale pas cette valeur inconnue.

Pour régler ce problème, l'idée est de se reposer sur un système d'héritage et d'abstraction :
* `FigureGeometrique` est une classe abstraite, qui permet d'imposer un comportement uniforme aux figures (méthode abstraite `dessiner`)
* Chaque type de figure géométrique donnera donc lieu à une classe spécialisée et l'attribut `typeFigure` de `FigureGeometrique` perd son utilité :

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

L'ajout d'une nouvelle figure nécessite une nouvelle classe et l'implémentation de sa méthode `dessiner`. Les classes qui manipulent les figures à travers le type `FigureGeometrique` peuvent utiliser cette nouvelle figure sans être modifiées. Le code qui construit les objets, par exemple le `Main`, peut en revanche devoir être adapté pour instancier cette nouvelle classe. On ne peut plus sélectionner un type de figure inconnu à l'aide d'une simple chaîne de caractères.

Ici, `FigureGeometrique` ne contient aucun état et définit uniquement une méthode abstraite : une `interface` convient donc bien pour représenter ce contrat commun. Une classe abstraite devient notamment utile si l’on souhaite factoriser des attributs ou une implémentation commune à plusieurs sous-classes.

Si vous bloquiez, ceci devrait vous permettre de refactorer le code du paquetage `fr.umontpellier.iut.ocp1` (animaux). Nous allons également refactorer `ocp2` (pokémons). Cela peut sembler un peu plus compliqué (car il y a déjà un système d'héritage), mais cela ne devrait pas être trop dur à adapter.

<div class="exercise">

1. Si vous n'étiez pas arrivés à une solution satisfaisante (ou cohérente par rapport à la solution présentée pour les figures géométriques), refactorez le code du paquetage `fr.umontpellier.iut.ocp1` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne. Il ne doit plus être possible de gérer des animaux inconnus, et c'est bien normal !

2. À l'aide d'`IntelliJ`, générez le **diagramme de classes de conception** de l'application du paquetage `fr.umontpellier.iut.ocp2` (avant refactoring). Pour cela, effectuez un **clic droit** sur le paquetage `ocp2` puis sélectionnez `Diagrams` et enfin `Show Diagrams`. Activez bien l'affichage de tous les éléments et notamment les **dépendances non triviales**.

3. Refactorez le code du paquetage `fr.umontpellier.iut.ocp2` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne.

4. Générez maintenant le **diagramme de classes de conception** de l'application du paquetage `fr.umontpellier.iut.ocp2` (après refactoring). Activez bien l'affichage de tous les éléments et notamment les **dépendances non triviales**.

</div>

En comparant vos deux diagrammes de classes, on peut facilement voir ce qui différencie la "mauvaise" conception de la "bonne" : dans votre premier diagramme, les classes `SimulateurCombat` et `Pokemon` ont autant de dépendances qu'il y a de sous-classes de type de pokémon. S'il y a 30 types de pokémons, `SimulateurCombat` et `Pokemon` auront chacune 30 dépendances. Après refactoring, ces dépendances disparaissent. `SimulateurCombat` est seulement dépendant de `Pokemon`.

Dans un code de qualité **les abstractions ne dépendent pas des implémentations**. En d'autres termes, une superclasse ne devrait pas dépendre de ses sous-classes. Seules les sous-classes peuvent dépendre de leurs parents (et on verra que parfois, là aussi, il faut faire attention lorsqu'on utilise l'héritage.). Sur votre premier diagramme, il est clair que ce principe n'est pas respecté, car `Pokemon` dépendait de ses différentes sous-classes, ce qui n'est plus le cas sur le deuxième diagramme.

Nous allons maintenant tester votre compréhension des deux principes (`S` et `O`) avec un nouvel exercice un peu différent de ce que vous avez vu jusqu'ici, dans sa forme.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.ocp3`. Ce projet permet de gérer un paquet de 52 cartes, de le trier, de le mélanger... Exécutez le programme pour observer le rendu. Deux méthodes de tri sont possibles. On définit la méthode de tri utilisée quand on construit l'objet et on peut la changer à tout moment avec un `setter`.

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
    
    Pour vous aider, vous pourrez utiliser `carte1.compareTo(carte2)`. Cette méthode renvoie un nombre négatif si `carte1` doit précéder `carte2` dans l’ordre de tri, **0** si les deux cartes sont équivalentes pour cet ordre et un nombre positif si `carte1` doit suivre `carte2`.

3. Testez que votre algorithme fonctionne bien en changeant la méthode de tri du paquet dans le `Main`.

4. À votre avis, en quoi les principes de responsabilité unique et ouvert/fermé ne sont pas respectés ?

</div>

Comme vous l'avez sans doute déduit, dans un premier temps, le principe **ouvert/fermé** n'est pas respecté : ajouter un nouveau tri demande de modifier le code source de la classe `Paquet` et notamment la méthode `trier`.

Dans un second temps, on remarque aussi que la classe `Paquet` a trop de responsabilités : cela ne devrait pas être à elle de gérer les différents algorithmes de tri de cartes. On pourrait aussi dire la même chose pour le mélange, et peut-être même pour l'affichage ! La vérification peut se faire facilement :

* Si la méthode de tri change, la classe `Paquet` doit être modifiée.

* Si la méthode de mélange change, la classe `Paquet` doit être modifiée.

* Si le format d'affichage du paquet change, la classe `Paquet` doit être modifiée.

Le principe de responsabilité unique n'est pas respecté. Pour le `toString`, cela peut encore se discuter, mais cela est clair pour le **tri** et le **mélange**.

<div class="exercise">

1. Refactorez le code afin de respecter le **principe ouvert/fermé** au niveau des **tris**. On souhaite tout de même garder la possibilité de changer de tri avec un `setter` et aussi de définir le tri utilisé via le `constructeur`. Quelques indices :

    * Isolez le code de chaque méthode de tri dans des classes dédiées.

    * Généralisez le tout avec une interface.

2. Refactorez le code concernant le **mélange** afin de respecter le **principe de responsabilité unique**. Prévoyez aussi le cas où d'autres méthodes de mélange pourraient être ajoutées. Comme pour le tri, on souhaite pouvoir définir la méthode de mélange dans le constructeur et la modifier via un setter.

3. Testez que tout fonctionne, essayez plusieurs méthodes de tri sur le paquet, notamment. Normalement, vous ne devez jamais éditer la classe `Paquet` si vous changez le tri utilisé.

4. Générez le diagramme de classes de conception du paquetage `fr.umontpellier.iut.ocp3` (avec `IntelliJ`).

</div>

Les principes **SOLID** se combinent naturellement entre eux. D'ailleurs, si vous avez refactoré proprement le dernier exercice, vous avez même déjà utilisé le principe **d'inversion des dépendances** dont nous parlerons plus tard ! 

Encore mieux, vous venez d'utiliser un **design pattern** au niveau des tris (et des mélanges) : **Stratégie**. Ce pattern permet d'encapsuler un ensemble de comportements (algorithmes de tris) dans des classes et de rendre ces algorithmes interchangeables dans une classe cliente (`Paquet`). Ainsi, le comportement spécifique est **injecté** dans la classe cliente sans modifier le code source de celle-ci. Ce pattern s'appuie sur **ouvert/fermé**, **l'inversion des dépendances** et aide à respecter le principe de **responsabilité unique**. C'est exactement ce que vous venez de faire : la méthode de tri du paquet est modulable et on peut même en ajouter des nouvelles dans le futur ! Et tout cela, sans modifier `Paquet`.

À partir du diagramme de classes de conception que vous venez de générer, vous devriez pouvoir reconnaître les éléments du pattern **stratégie** et le réutiliser lorsqu'un objet doit pouvoir changer d'algorithme.

### Héritage, composition et principe ouvert-fermé

Maintenant, voyons une nouvelle situation, où les choses risquent d'être plus compliquées notamment vis-à-vis du respect du principe **ouvert/fermé** !

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.ocp4`. Dans ce projet, il y a une classe `Produit` permettant de gérer des produits, leurs prix et d'afficher leur description (leur nom). Ensuite, on a souhaité définir une classe `ProduitAvecReduction`, car certains produits proposent des réductions. Tout fonctionne pour le moment, comme vous pouvez le constater dans le `Main`.

2. On souhaite maintenant ajouter un nouveau type de produit : les produits avec une date de péremption proche. Sur un tel produit, le prix est calculé en faisant une réduction de 50 % sur le prix d'origine. De plus, lors de l'affichage de la description du produit (son nom), on affiche en plus le message "Réduction de 50% appliquée". Implémentez donc une classe `ProduitAvecDatePeremptionProche` héritant de `Produit` et réécrivez les méthodes `getPrix` et `afficherDescription`. Testez que votre nouveau type de produit a bien le comportement attendu en testant dans le `Main` (ou encore mieux : avec des tests unitaires pour le prix !) en appelant les méthodes `getPrix` et `afficherDescription`.

3. Maintenant, nous voulons qu'un produit puisse à la fois être un produit qui périme bientôt et un produit avec une réduction. C'est-à-dire que les deux **comportements** (réductions) soient appliqués lors du calcul du prix (lors d'un appel à `getPrix`) et que les messages correspondants aux deux types de produit soient affichés (lors d'un appel à `afficherDescription`). On accepte de modifier `Produit` lors du refactoring initial pour introduire une abstraction commune. Une fois cette architecture en place, l'ajout de nouveaux comportements ne devra plus nécessiter de modifier cette classe. Est-il possible de faire en sorte de pouvoir ajouter un tel comportement à un produit **sans inclure de redondance** dans le code et en continuant de respecter le principe **ouvert/fermé** ?
</div>

Si vous vous êtes contenté uniquement de faire hériter `ProduitAvecDatePeremptionProche` de `Produit`, vous remarquerez qu'il est compliqué d'avoir un même produit possédant ces deux fonctionnalités à la fois, notamment, car le multihéritage de classes n'est pas possible en Java.

Peut-être que vous avez été plus malin et que vous avez pensé à implémenter une classe héritant de `Produit` et implémentant les deux comportements. Mais dans ce cas, il y a de la **duplication de code**.

Ou alors, peut-être que vous avez été encore plus malin et que vous avez pensé à faire une classe **composée** de deux instances des types de produit concernés. C'est déjà beaucoup mieux ! Mais que se passe-t-il si d'autres types de produit sont ajoutés ? Par exemple, si on a cinq types de produits différents et qu'on veut mixer au choix certaines fonctionnalités de certains types ? La classe composée sera de plus en plus difficile à gérer et ne sera jamais fermée aux modifications.

Tout en respectant le **principe ouvert/fermé**, il existe une méthode générale pour construire un `Produit` possédant autant de comportements mixtes que nous souhaitons. Si de nouveaux comportements sont ajoutés dans le futur, il n'y aura pas de modification du code existant. On peut implémenter un tel système en [favorisant la **composition** au lieu d'un **héritage**](https://en.wikipedia.org/wiki/Composition_over_inheritance).

<div class="exercise">

Dans la suite du TP, nous allons donner un exemple et un contexte similaire à celui présenté dans cet exercice puis une solution. Avant de lire ces explications, essayez de trouver par vous-même une solution pour pouvoir créer des produits avec des comportements mixtes, tout en respectant le principe **ouvert/fermé**. Une fois que vous avez terminé, lisez la suite des explications. Si vous bloquez et/ou que vous n'arrivez pas à obtenir une solution satisfaisante, passez aussi à la suite des explications.

</div>

Pour résoudre le problème présenté dans cet exercice, l'idée est la suivante :

* Une **abstraction commune**, notée `I`, typiquement une interface, définit les opérations que les objets de base et les décorateurs doivent proposer.

* Une classe de base implémente cette abstraction. Chaque classe de **décorateur** implémente également `I` et possède un attribut référençant un autre objet de type `I`. Le décorateur délègue une partie des opérations à cet objet et y ajoute son propre comportement.

* Un décorateur peut envelopper un objet de base ou un autre décorateur. On peut donc imbriquer **plusieurs décorateurs** pour combiner leurs comportements.

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

Ici, nous retrouvons le même problème que pour les produits : cette hiérarchie ne permet pas de combiner simplement les responsabilités de chef de projet et de responsable de stagiaires sans ajouter des sous-classes pour les différentes combinaisons.

Cette hiérarchie représente séparément les différents rôles, mais ne permet pas de les combiner facilement. Nous pouvons utiliser la **composition** pour construire des objets qui enveloppent d'autres objets et cumulent ainsi leurs comportements.

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

Avec cette nouvelle architecture, nous pouvons ajouter à des instances de salariés des **responsabilités** de chef de projet et/ou de responsables de stagiaires :

```java
//Un salarié (qui existe déjà et qui est utilisé dans l'application...)
Salarie salarie = new Salarie(2000);

//Salarie qui est chef de projet gérant 3 projets
SalarieInterface salarieChef = new SalarieChefProjet(salarie, 3);
salarieChef.getSalaire(); //Renvoie 2300

//Salarie qui est responsable de stagiaires gérant 5 stagiaires
SalarieInterface salarieResponsableDeStagiaires = new SalarieResponsableDeStagiaires(salarie, 5);
salarieResponsableDeStagiaires.getSalaire(); //Renvoie 2250

//Salarié qui est chef de projet gérant 3 projets et aussi responsable de stagiaires gérant 5 stagiaires
SalarieInterface salarieAvecMultiResponsabilites = new SalarieResponsableDeStagiaires(new SalarieChefProjet(salarie, 3), 5);
salarieAvecMultiResponsabilites.getSalaire(); //Renvoie 2550
```

Le type de l’attribut qui référence l’objet enveloppé est `SalarieInterface`, et non `Salarie`. Ainsi, cet attribut peut référencer aussi bien un salarié de base qu’un autre décorateur, ce qui permet de combiner `SalarieChefProjet` et `SalarieResponsableDeStagiaires`.

L’objet enveloppé est fourni au constructeur du décorateur : la dépendance est **injectée**, comme dans l’exercice sur le paquet de cartes et les méthodes de tri. Cela permet de décorer un objet existant et de choisir les décorateurs à combiner. Cette injection ne détermine pas, à elle seule, la notation UML de la relation.

<div class="exercise">

1. Si vous n'étiez pas arrivés à une solution satisfaisante (ou cohérente avec la solution présentée dans l'exemple avec les salariés), refactorez votre code afin de pouvoir créer un produit qui possède une réduction et qui a aussi une date de péremption proche. Chaque décorateur applique sa réduction au prix renvoyé par l'objet qu'il enveloppe.

2. Créez un **Twix** avec pour prix de base **3€**, qui périme bientôt et qui a une réduction de 50 centimes. Testez que la valeur obtenue pour le prix est bien la bonne et que l'affichage de la description présente bien toutes les informations.

3. Inversez l'ordre de création du produit (le produit avec réduction est composé d'un produit avec une date de péremption proche ou l'inverse selon ce que vous avez fait à la question précédente). Est-ce que le prix obtenu est le même qu'à l'étape précédente ?

</div>

Attention, **dans cet exemple précis**, même si nous pouvons maintenant rajouter un nouveau type de produit et le combiner aux autres pour calculer le prix adéquat, quand on instancie l'objet, il faut faire attention à l'ordre de combinaison des objets, à cause de la méthode de calcul du prix du produit avec une réduction. Si la méthode de calcul avait été un pourcentage pour ce type de produit (-X% du prix) comme pour le produit avec une date de péremption proche, l'ordre n'aurait pas eu d'importance. Bref, cela est à prendre en compte quand vous concevez et que vous utilisez ce type de solution. 

Tout fonctionne, mais le code est encore un peu redondant : chaque décorateur possède un attribut référençant un objet du type de l'interface commune aux produits et un constructeur pour initialiser cet attribut.

<div class="exercise">

Avant de lire la suite, essayez de proposer une refactorisation pour éliminer la redondance et la répétition de code au niveau des sous-classes (`ProduitAvecReduction` et `ProduitAvecDatePeremptionProche`). Si vous bloquez et/ou que vous n'arrivez pas à obtenir une solution satisfaisante, passez aussi à la suite des explications.

</div>

Concernant l'exemple des salariés, nous pourrions factoriser le code ainsi :

```java
//Nous reviendrons sur le nom "décorateur" plus tard.
abstract class SalarieDecorateur implements SalarieInterface {
   private SalarieInterface salarie;

   public SalarieDecorateur(SalarieInterface salarie) {
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

class SalarieResponsableDeStagiaires extends SalarieDecorateur {

  private int nombreStagiairesGeres;

  public SalarieResponsableDeStagiaires(SalarieInterface salarie, int nombreStagiairesGeres) {
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
        SalarieInterface s3 = new SalarieResponsableDeStagiaires(s1, 2);
        SalarieInterface s4 = new SalarieChefProjet(new SalarieResponsableDeStagiaires(s1, 4), 3);

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

1. Si vous n'étiez pas arrivés à une solution satisfaisante (ou cohérente avec la solution présentée dans l'exemple ci-dessus), refactorez votre code pour introduire une classe abstraite et réduire la redondance et la répétition de code au niveau des sous-classes (`ProduitAvecReduction` et `ProduitAvecDatePeremptionProche`).

2. Testez que tout fonctionne comme auparavant.

3. Générez le **diagramme de classes de conception** (avec `IntelliJ`) du paquetage `fr.umontpellier.iut.ocp4`.

</div>

Si nous ajoutons un nouveau comportement à un produit, il suffira de créer une nouvelle classe de décorateur qui étend la classe abstraite. Cette architecture utilise la composition pour combiner les comportements et l'héritage pour factoriser le code commun aux décorateurs. L'ajout d'un décorateur ne nécessite pas de modifier les classes existantes.

En fait, ce modèle est réutilisable et adaptable à d'autres situations (nous l'avons vu avec les salariés). C'est en fait un autre **design pattern** nommé **décorateur** d'où le nom de la classe abstraite dans l'exemple.

**Attention** : le décorateur est un pattern différent de **builder** que vous avez vu l'an dernier. 

Un **builder** facilite la construction d’un objet complexe, notamment lorsque celui-ci possède de nombreux paramètres, dont certains sont optionnels.

Le pattern **décorateur** permet d’ajouter des comportements à un objet en l’enveloppant dans un autre objet qui respecte la même abstraction. Plusieurs décorateurs peuvent être imbriqués pour cumuler leurs effets.

Les nouvelles fonctionnalités sont accessibles **en passant par le décorateur**. Une partie du programme qui conserve une référence vers l’objet d’origine continue à utiliser son comportement initial. Pour bénéficier des nouveaux comportements, elle doit utiliser la référence vers l’objet décoré.

De nouveaux comportements peuvent ainsi être développés dans de nouvelles classes de décorateurs, sans modifier la classe de l’objet d’origine. Le décorateur est donc un **pattern structurel** qui permet de combiner des comportements autour d’un objet.

À partir du diagramme de classes que vous avez généré, vous devriez pouvoir identifier les éléments du pattern **décorateur** et le réutiliser pour combiner des comportements autour d'un objet.

### Principe de substitution de Liskov (Liskov substitution)

Certains développeurs abusent de l'**héritage** par facilité au lieu d'utiliser d'autres solutions comme la **composition** d'objets. Un "mauvais" héritage est un héritage pour lequel il n'existe pas vraiment de relation de spécialisation entre la superclasse et la sous-classe. La sous-classe ne représente alors pas le même concept que sa classe mère, ce n'est pas réellement une spécialisation.

Tout cela occasionne parfois des problèmes inattendus qui sont mis en lumière par le principe de **substitution de Liskov** qui est fortement lié à la notion de **programmation par contrat**.

Quand on parle de **programmation par contrat** cela signifie que chaque classe possède un ensemble de **règles** (implicites ou explicites) autour de ses **méthodes** : **pré-conditions**, **post-conditions**, **effets de bord**, etc. Globalement, quelqu'un qui utilise une instance d'une **classe** donnée sait à quoi s'attendre quand on appelle telle ou telle méthode. Par exemple, le contrat de `ArrayList` précise qu’un appel réussi à `add(element)` ajoute cet élément à la fin de la liste.

Le principe de **substitution de Liskov**, introduit par **Barbara Liskov**, énonce qu'un **objet** d'un sous-type doit pouvoir être utilisé partout où un objet du type de base est attendu, **sans rompre le contrat** de ce type de base. Une méthode redéfinie dans une sous-classe doit donc préserver les garanties promises par la superclasse.

Par exemple, si une classe `MonArrayList` étend `ArrayList` et redéfinit `add(element)`, elle doit conserver le contrat de cette opération : après un appel réussi, l’élément ajouté se trouve à la fin de la liste. L’implémentation peut être différente, mais un code qui utilise `ArrayList` doit continuer à fonctionner avec une instance de `MonArrayList`, conformément au contrat de `ArrayList`. Les tests portant sur ce contrat doivent donc continuer à passer lorsque l’on remplace une instance de `ArrayList` par une instance de `MonArrayList`.


L'utilisation inappropriée de l'héritage peut amener au non-respect de ce principe.

Voici un scénario illustrant plus en détail le problème de non-respect du principe de substitution de Liskov : on possède une classe `Rectangle` et on souhaite modéliser une classe `Carre`. D'ailleurs, en géométrie, un carré est un sous-type de rectangle, non ?

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.lsp1` et observez les classes mises à disposition. Dans cette application, nous avons considéré qu'un `Carre` est une spécialisation d'un `Rectangle`. Cependant, un carré possède une caractéristique particulière : **sa hauteur et sa largeur sont toujours identiques**. Pour conserver cette propriété, un carré ne doit pas permettre de modifier sa largeur indépendamment de sa hauteur, ni l’inverse.

2. Dans le paquetage `fr.umontpellier.iut.lsp1` dans `src/test/java` vous trouverez deux classes de tests unitaires pour tester le rectangle, le carré et la classe `Utils` qui permet de redimensionner un rectangle. Lancez-les. Essayez de comprendre pourquoi les tests ne passent pas.

3. Les tests écrits sont bien valides. Si on change la hauteur d'un carré, alors sa largeur doit aussi changer. Une première solution peut donc être de redéfinir les méthodes `setLargeur` et `setHauteur` dans la classe `Carre` afin que quand on modifie la largeur, la hauteur soit mise à la même valeur et inversement. Faites cette modification (les attributs `hauteur` et `largeur` sont accessibles dans `Carre` car en `protected` dans la classe `Rectangle`).

4. Relancez les tests unitaires. Un autre test (de la classe `Utils`) ne passe plus ! Essayez de comprendre pourquoi.

</div>

Avec cette modification, le principe de substitution de Liskov n'est plus respecté ! On a **cassé** le contrat de `Rectangle` dans `Carre`. `Carre` est un `Rectangle` et on devrait pouvoir modifier sa hauteur et sa largeur librement !

De plus, si on utilise `Carre` comme un `Rectangle`, des bugs étranges surviennent quand on utilise une méthode prévue pour un `Rectangle` (ici, la méthode **agrandirRectangle**). On ne peut pas substituer le rectangle par un carré sans produire de bugs logiques.

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

Dans cette modélisation, faire hériter `Carre` de `Rectangle` pose donc problème : le contrat de `Rectangle` permet de modifier ses deux dimensions indépendamment, ce qui est incompatible avec les propriétés d’un carré. Un carré reste bien un rectangle en géométrie, mais cette relation mathématique ne suffit pas à justifier un héritage entre nos classes : il faut aussi que leurs comportements soient compatibles.

Si on souhaite quand même utiliser un rectangle dans un carré (pour ne pas dupliquer le calcul de l'aire ou des autres méthodes, par exemple) on peut éventuellement utiliser une **composition** à la place, ce qui nous éviterait de gérer les méthodes indésirables de changement de hauteur ou largeur imposées par héritage.

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

    * La signature du **constructeur** ne change pas. Le constructeur crée un `Rectangle` propre au `Carre`. Cet objet reste privé, sans méthode permettant de récupérer sa référence depuis l'extérieur.

    * On n'a plus besoin des méthodes `setHauteur` et `setLargeur` (on ne modifie pas indépendamment la largeur et la hauteur d'un carré).

    * Les méthodes `getLargeur`, `getHauteur` et `aire` sont **déléguées** au `Rectangle`.

    * Une nouvelle méthode `setTailleCote` permet de changer la taille du côté du carré (en utilisant le rectangle).

3. Faites aussi implémenter l'interface `FigureRectangulaire` à `Rectangle`.

4. Adaptez les **tests unitaires** portant sur `Carre` : remplacez les appels à `setLargeur` et `setHauteur` par `setTailleCote`. Si des tests passent encore un `Carre` à `Utils.agrandirRectangle`, adaptez-les à la nouvelle conception : cette méthode attend désormais uniquement des `Rectangle`. Conservez les tests des comportements qui restent valides.

5. Lancez les tests, vérifiez que tout fonctionne.

</div>

Après **refactoring**, le diagramme de classes de votre application devrait donner quelque chose comme ça :

<div style="text-align:center">
![Liskov substitution 2]({{site.baseurl}}/assets/TP3/LSP2.svg){: width="50%" }
</div>

La **composition forte** entre `Carre` et `Rectangle` exprime ici que chaque `Carre` possède son propre `Rectangle`, utilisé comme détail interne de son fonctionnement. Ce rectangle n'est pas partagé et sa référence n'est pas exposée à l'extérieur (d'où la **composition forte**). Elle est en opposition avec la **composition faible**, qui indique aussi une composition, mais dans laquelle la dépendance est injectée (comme avec les **décorateurs** dans l'exercice des produits).

Bien sûr, nous aurions pu quand même conserver la logique d'agrandissement d'une `FigureRectangulaire`. À ce moment-là, il faudrait rajouter une méthode `agrandir(int facteur)` dans l'interface `FigureRectangulaire` et implémenter les méthodes dans `Rectangle` et `Carre`.

Mettons vos nouvelles connaissances en pratique avec un autre exercice.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.lsp2`. On souhaite implémenter le fonctionnement d'une `Pile`. Une `Pile` est une structure de données `LIFO` (last in, first out) qui fonctionne comme une pile d'assiettes. On peut globalement réaliser **quatre opérations** sur une pile :

    * Vérifier si elle est vide.

    * Obtenir la valeur au sommet de la pile.

    * Empiler un élément (l'ajouter au sommet de la pile)

    * Dépiler un élément (le retirer du sommet de la pile et le renvoyer).

    La classe `Pile` que nous allons implémenter possède un paramètre de type **générique**. Cela permet de créer des piles contenant un type de données paramétré, comme quand vous créez un objet de type `List<Double>` par exemple.

    Afin de ne pas avoir à définir la structure stockant les données nous-mêmes, nous allons étendre la classe `Vector` qui permet de gérer une structure de données ordonnée. Diverses méthodes de la super-classe vont vous être utiles :

    * `isEmpty` → permet de vérifier si la structure est vide.

    * `get(index)` → permet de récupérer la valeur située à la position ciblée par l'index.

    * `remove(index)` → permet de supprimer la valeur située à la position ciblée par l'index.

    * `add(index, valeur)` → permet d'insérer une valeur à la position ciblée par l'index.

2. Ouvrez la classe de tests unitaires `PileTest` placée dans le paquetage `fr.umontpellier.iut.lsp2` du dossier `src/test/java`. Exécutez les tests. Rien ne passe, c'est normal ! Vous n'avez pas encore implémenté le code de la classe `Pile` qui contient du code par défaut... Vous êtes donc en mode **TDD** (test driven development).

3. Implémentez les méthodes de la classe `Pile` afin que les tests passent (ne décommentez pas les quatre derniers tests pour le moment).

4. Décommentez et exécutez les quatre derniers tests de la classe `PileTest`. Ces tests semblent étranges, car ils ne testent pas seulement les méthodes de la pile. Essayez de comprendre pourquoi ils sont nécessaires puis lisez la suite.

</div>

Les derniers tests ne sont pas mal rédigés, car, comme `Pile` hérite de `Vector`, cette classe doit respecter le contrat imposé par sa classe mère. Ces tests vérifient qu'il est bien possible de substituer un `Vector` par une `Pile` dans des algorithmes qui acceptent un `Vector` en paramètre. De plus, comme `Vector` implémente (par héritage) l'interface `List` qui étend elle-même l'interface `Collection` : on doit pouvoir substituer un objet de type `List` ou `Collection` par un objet de type `Pile` dans les fonctions et méthodes de **Java** qui prennent des collections ou des listes en paramètre, tout en conservant un comportement cohérent (donc, sans casser le contrat de `Vector`, des classes héritées et des interfaces implémentées).

Comme ces tests passent, on peut donc à priori en conclure que `Pile` respecte bien le contrat de `Vector`... Logique : nous n'avons redéfini aucune méthode de `Vector`, il y a donc peu de chances de casser quoi que ce soit !

Nous souhaitons cependant que l'interface publique de `Pile` se limite aux opérations `estVide`, `empiler`, `depiler` et `sommetPile`. Or, comme `Pile` hérite de `Vector`, toutes les opérations publiques d'une liste restent accessibles : on peut notamment insérer ou supprimer un élément ailleurs qu'au sommet. Cette classe respecte encore le contrat de `Vector`, mais elle n'impose pas l'usage LIFO attendu dans cet exercice.

Pour résoudre ce problème, on pourrait alors redéfinir toutes les méthodes de `Vector` (qui nous gênent) pour qu'elles ne fassent rien, afin de respecter le contrat de `Pile`. Par exemple, celles-ci :

```java
public class Pile<T> extends Vector<T> {

    @Override
    public synchronized Iterator<T> iterator() {
        return null;
    }

    @Override
    public synchronized T get(int index) {
        return null;
    }

    @Override
    public boolean remove(Object o) {
        return false;
    }

    @Override
    public synchronized T remove(int index) {
        return null;
    }

    @Override
    public void add(int index, T element) {}

    //Etc...
}
```

Mais le principe de substitution de Liskov ne serait alors plus respecté, car on casserait le **contrat** de `Vector` ! On ne pourrait pas substituer un `Vector` par une `Pile` et les quatre derniers tests (dans la classe `PileTest` du paquetage `fr.umontpellier.iut.lsp2` dans `src/test/java`) ne fonctionneraient plus...

Bref, conceptuellement, une `Pile` n'est pas un `Vector` spécial, mais bien une structure indépendante... Néanmoins, il est possible d'utiliser une **composition** pour utiliser un `Vector` comme attribut, dans notre classe `Pile` et ainsi éviter un certain degré de duplication de code.

<div class="exercise">

1. Refactorez le code de la classe `Pile` en enlevant l'héritage et en utilisant une **composition** avec un `Vector` à la place.

2. Les quatre derniers tests ne compilent plus : `Pile` n'est plus un sous-type de `Vector`, de `List` ou de `Collection`. Ses instances ne proposent plus les opérations héritées comme `add`, `remove` ou `clear`, et ne peuvent plus être passées aux méthodes `List.copyOf` ou `Collections.replaceAll`. Supprimez les quatre tests qui vérifiaient cette ancienne relation de sous-typage.

3. Relancez les tests et vérifiez que tout passe.

4. Quelque part dans votre code, définissez une variable de type `Stack` qui est une classe de `Java` permettant de gérer une pile. Allez observer le code source de cette classe (`CTRL+B` sur **IntelliJ** en cliquant sur le nom de la classe). Que remarquez-vous au niveau de sa déclaration ? Cette classe est aujourd'hui [déconseillée](https://docs.oracle.com/en/java/javase/26/docs/api/java.base/java/util/Stack.html). À votre avis, pourquoi ?

</div>

L'héritage de `Stack` vers `Vector` expose des opérations qui permettent de contourner le fonctionnement attendu d'une pile (voir [documentation](https://docs.oracle.com/en/java/javase/26/docs/api/java.base/java/util/Stack.html)). Cette classe est conservée notamment pour assurer la compatibilité avec les programmes existants. D'où l'importance de bien penser sa conception !

### Principe de ségrégation des interfaces (Interface segregation)

Le quatrième principe **SOLID** est le **principe de ségrégation des interfaces**.

Les clients d'une interface ne devraient pas dépendre de méthodes qu'ils n'utilisent pas. On préfère donc plusieurs interfaces ciblées, correspondant à des besoins ou à des capacités précis, à une interface qui regroupe des opérations sans rapport pour ses différents clients.

Une interface définit un **contrat**. Une classe concrète doit fournir ou hériter d'une implémentation de ses méthodes abstraites. Si certaines de ces opérations n'ont aucun sens pour cette classe, cela peut révéler que l'interface regroupe trop de responsabilités.

Voyons comment ne pas respecter ce principe peut devenir très fastidieux au fur et à mesure que le projet grossit.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.isp`. Ce projet modélise un système de jeu où certaines créatures sont des **montures**. Toutes les montures du même type ont les mêmes caractéristiques type (vitesse, endurance...). Au début, le développeur a modélisé une créature `Cheval`. Pour cette monture, on veut connaître :

    * Le nom de la monture.

    * La vitesse.

    * L'endurance.

    Pour prévoir le futur dans le cas où il y aurait besoin d'ajouter d'autres montures, le développeur a ajouté une interface `Monture`.

    Il a ensuite ajouté un autre type de monture, le **Tigre**.

2. Ajoutez une classe `Griffon` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 300. Cependant, contrairement aux autres montures, cette monture est une **monture volante**. Elle ne possède pas d'endurance. Par contre, on veut connaître son **temps maximum de vol** qui est de 40. Adaptez votre classe en conséquence.

    Concernant l'endurance, que faut-il renvoyer ? On ne peut pas renvoyer **0** ou un nombre négatif, cela n'aurait pas beaucoup de sens. À la place, on peut lever une exception :

    ```java
    public double getEnduranceMonture() {
        throw new UnsupportedOperationException("Une monture volante n'a pas d'endurance!");
    }
    ```

3. Dans le cas où il y aurait besoin d'ajouter d'autres montures volantes dans le futur, ajoutez la méthode permettant d'obtenir le temps de vol dans l'interface `Monture`.

4. Les classes `Cheval` et `Tigre` ne compilent plus ! C'est parce qu'il faut implémenter la méthode permettant d'obtenir **le temps maximum de vol**... Or, ces montures n'ont pas de temps maximum de vol ! On va donc procéder comme pour `Griffon` en levant une exception :

    ```java
    public double getTempsMaximumDeVol() {
        throw new UnsupportedOperationException("Cette monture ne peut pas voler!");
    }
    ```

5. Ajoutez une classe `Dragon` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 400. Elle possède aussi un temps de vol maximum de 120 (car c'est une monture volante). Elle ne possède pas d'endurance. Par contre, on veut connaître sa **puissance de feu** qui est de 200. Adaptez votre classe en conséquence.

6. Mettez à jour l'interface `Monture` avec la méthode pour la puissance de feu au cas où il y ait d'autres types de dragons ajoutés dans le futur et corrigez les erreurs de compilation.

7. Enfin, ajoutez une classe `LicorneAilee` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 75. Elle possède aussi un temps de vol maximum de 20 (car c'est une monture volante) et une endurance de 50 (car c'est aussi une monture terrestre !). Par contre, elle n'a pas de puissance de feu.

</div>

C'était pénible, n'est-ce pas ? C'est normal, cette solution est très mauvaise et fastidieuse. À chaque nouvel ajout de type de monture avec ses spécificités, on doit modifier tous les autres types et les forcer à implémenter des méthodes qui ne les concernent pas... Le fait de lever tant d'exceptions pour des opérations sans signification indique une très mauvaise conception.

Le problème vient du regroupement, dans une seule interface, des opérations communes à toutes les montures et de celles qui correspondent à des capacités particulières. `Monture` peut conserver les opérations communes, comme l'accès au nom et à la vitesse. Les capacités supplémentaires, comme l'endurance, le vol ou la puissance de feu, peuvent être décrites dans des interfaces distinctes. Chaque classe implémente alors les interfaces correspondant à ses capacités. Une nouvelle classe peut réutiliser les interfaces existantes.

<div class="exercise">

Avant de lire la suite des explications, tentez de refactorer votre code pour respecter le **principe de ségrégation des interfaces**. On veut garder les spécificités de chaque type de monture, mais éliminer les exceptions signalant des opérations non prises en charge. Soyez vigilants pour le dragon et la licorne ailée. Si vous bloquez et/ou que vous n'arrivez pas à obtenir une solution satisfaisante, passez aussi à la suite des explications.

</div>

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
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
  }

  public void operationC() {
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
  }
}

class B implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
  }

  public void operationB() {
    //Code
  }

  public void operationC() {
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
  }
}

class C implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
  }

  public void operationB() {
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
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
    throw new UnsupportedOperationException("Impossible d'implémenter cette méthode.");
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

Comme vous le constatez, plus aucune classe n'est forcée à implémenter des méthodes qu'elle ne peut pas définir, tout en conservant ses spécificités. Plus aucune exception signalant une opération non prise en charge n'a besoin d'être levée.

Bref, cela est en partie un mix entre le **principe de responsabilité unique** et une visualisation **hiérarchique** du problème. On note quand même le cas intéressant de la classe `D` qui permet à la fois d'avoir le type `I_Exemple`, `I_B` et `I_C` !

<div class="exercise">

Si vous n'étiez pas arrivés à une solution satisfaisante, refactorez votre code de nouveau afin de respecter le **principe de ségrégation des interfaces**.

</div>

### Principe d'inversion des dépendances (Dependency inversion)

Enfin, il reste le **principe d'inversion des dépendances**.

Ce principe dit que :

* Les modules de **haut niveau**, qui portent les règles métier, ne doivent pas dépendre directement des modules de **bas niveau**, qui réalisent les détails techniques. Les deux doivent dépendre d'**abstractions**.

* Les abstractions doivent décrire les opérations attendues sans dépendre des détails de leur réalisation. Les implémentations concrètes doivent se conformer à ces abstractions.

Cela ne signifie pas qu'il faut créer une interface pour chaque classe utilisée. On cherche surtout à isoler le code métier des détails techniques que l'on souhaite pouvoir remplacer ou faire évoluer indépendamment.

L'**injection de dépendances** permet de fournir aux objets les implémentations qu'ils utilisent. Le choix et l'assemblage de ces implémentations peuvent être regroupés dans un point d'entrée, dans des **fabriques** ou dans un **conteneur de dépendances**s. On peut ainsi remplacer une implémentation sans modifier les modules qui l'utilisent. On obtient ainsi des logiciels dont on peut moduler le fonctionnement sans toucher au code source, simplement en ajoutant de nouvelles classes et/ou en éditant des fichiers de configuration. Les différents **frameworks** mettent en place une architecture favorisant l'inversion des dépendances.

Ce principe complète les autres principes SOLID. Dépendre d'abstractions facilite l'ajout de nouvelles implémentations sans modifier leurs clients, conformément au principe **ouvert/fermé**. Ces implémentations doivent respecter le contrat de l'abstraction, conformément au **principe de substitution de Liskov**.

Nous verrons aussi qu'il est essentiel de bien respecter ce principe quand on réalise des tests unitaires.

Tout d'abord, illustrons ce principe avec un exemple. 

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.dip`. Dans ce projet, il y a une classe `Etudiant` et une classe `CompteUniversitaire`. Un compte universitaire est détenu par un étudiant. On utilise son nom et son prénom pour générer un login.

2. Ajoutez une classe **Enseignant** qui possède un nom, un prénom et définit des **getters** pour ces deux attributs.

3. La logique pour créer un compte universitaire pour un enseignant est la même que pour un étudiant. On souhaite donc logiquement réutiliser la classe `CompteUniversitaire`. Mais ce n'est pas possible, car un enseignant n'est pas un étudiant !

</div>

<div class="exercise">

Dans la suite du TP, nous allons donner un exemple et un contexte similaire à celui présenté dans cet exercice puis une solution de refactorisation. Avant de lire ces explications, essayez de trouver par vous-même une solution pour refactorer le code du paquetage `fr.umontpellier.iut.dip` afin de pouvoir utiliser la classe `CompteUniversitaire` pour les étudiants et les enseignants. Une fois que vous avez terminé, lisez la suite des explications. Si vous bloquez et/ou que vous n'arrivez pas à obtenir une solution satisfaisante, passez aussi à la suite des explications.

</div>

Le problème souligné dans cet exercice est qu'on a utilisé (à la base) une classe concrète (`Etudiant`) dans `CompteUniversitaire` à la place d'une classe abstraite ou d'une interface, ce qui empêche l'utilisation avec d'autres types de classes (ici, `Enseignant`).

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
    dependance.methodeA();
  }
}
```

Ici, nous avons un problème similaire : la classe `Service` dépend directement d'une implémentation concrète `A`, ce qui la rend peu modulable. Si je veux utiliser `B` à la place de `A`, je dois récrire le code source de `Service`.

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

Pour pallier ce problème, on utilise ici **l'injection de dépendances par constructeur**. Une instance concrète de la dépendance est fournie au constructeur de `Service` depuis l'extérieur. La classe `Service` manipule cette instance à travers le type abstrait `I_Exemple` et peut ainsi utiliser différentes implémentations de cette interface. C'est ce que nous avons fait avec le paquet de cartes et les tris, avec le pattern **stratégie**, mais également avec le **décorateur** dans l'exercice des produits.

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
    // L'appel à action() utilise methodeA().
    Service s1 = new Service(new A());
    s1.action();

    // L'appel à action() utilise methodeB().
    Service s2 = new Service(new B());
    s2.action();
  }

}
```

<div style="text-align:center">
![Dependency inversion 1]({{site.baseurl}}/assets/TP3/DIP1.svg){: width="50%" }
</div>

De cette manière, **l'inversion des dépendances** est respectée. La classe `Service` ne dépend plus d'aucun service concret, mais d'**abstractions**.

<div class="exercise">

1. Si vous n'aviez pas obtenu une solution totalement satisfaisante (ou cohérente par rapport au principe **d'inversion des dépendances** que nous venons de développer), refactorez votre code de nouveau pour pouvoir utiliser `CompteUniversitaire` aussi bien avec un objet de type `Etudiant` qu'un objet de type `Enseignant`. Il faudra normalement adapter le code dans le `Main`.

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

4. En utilisant votre connaissance du pattern **stratégie** et de **l'injection de dépendances**, faites en sorte qu'on puisse choisir si `CompteUniversitaire` utilise la génération de login "simple" (nom + première lettre du prénom) ou par mélange.

5. Le compte de "_Tarembois Guy_" doit être généré en utilisant le générateur de login simple et celui de "_Bricot Judas_" avec le générateur par mélange. Testez.
</div>

## Exercices bilan

Dans cette section, vous allez travailler sur un ensemble d'exercices "bilan" qui reprennent les notions abordées dans ce TP. L'idée est que vous identifiez le problème et mettiez en place une solution adéquate et respectueuse des **principes SOLID**.

### Villes et bâtiments

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.bilan1`. Ce projet modélise le fonctionnement d'un jeu dans lequel on peut construire sa propre **ville** (qui peut être éventuellement attaquée par d'autres joueurs) :

    * Une ville possède différents types de **bâtiments**. 
    
    * Un **bâtiment** est caractérisé par : un **nombre de points de vie maximum** (`pvMax`) et un **nombre de points de vie actuels** (`pv` qui est égal au maximum au début et qui peut diminuer si le bâtiment est attaqué). Vous pouvez voir tout cela dans la classe `Batiment`.

    * Chaque **bâtiment** possède (éventuellement) ses propres caractéristiques.

    * Une ville peut posséder plusieurs fois le même type de bâtiment (par exemple, trois théâtres).

    * On doit pouvoir calculer le **score culturel d'une ville**. Le score culturel est calculé en fonction de tous les bâtiments que possède la ville, selon les règles suivantes :

      * Pour chaque **musée** que comporte la ville, on ajoute au score le **nombre d'œuvres** que possède le musée ainsi que le **bonus** associé au thème du musée.

      * Pour chaque **théâtre** que comporte la ville, on ajoute au score le **nombre d'entrées** du théâtre.

      * Pour chaque **statue** que comporte la ville, on ajoute le **prix de construction** de la statue ainsi que son **nombre de points de vie** actuel.

    * On doit pouvoir savoir si une ville est **majeure**. Une ville est **majeure** si elle possède au moins **10 bâtiments majeurs**. Les bâtiments majeurs sont les **palais** et les **banques**.

2. Implémentez les méthodes `calculerScoreCulturel`, `compterBatimentsMajeurs` et `estMajeure` de la classe `Ville` en respectant les contraintes définies au point précédent. **Attention** dans le futur, on souhaitera éventuellement ajouter de nouveaux types de bâtiments qui pourraient influer sur le score culturel d'une ville, ou qui pourraient être majeurs. Dans ce cas, il faudra que votre conception permette cet ajout facilement sans avoir à modifier la classe `Ville`.

3. Une classe de test unitaire est présente dans le paquetage `fr.umontpellier.iut.bilan1` du dossier `src/test/java`. Lisez les tests et exécutez-les afin de vérifier que votre solution fonctionne.

</div>

### Comptes bancaires

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.bilan2`. Il s'agit d'une application de gestion de comptes bancaires. Le **contrat** de `CompteBancaire` permet de consulter son solde, d'effectuer des dépôts sans plafond et d'effectuer autant de retraits que souhaité, à condition de disposer d'un solde suffisant.

  En plus de ce compte bancaire, nous disposons de diverses classes :

  * Des comptes bancaires spécialisés, qui héritent de `CompteBancaire` (pas encore complets).
  * Des classes pour gérer les **exceptions**.
  * Une classe `Banque` qui permet d'ouvrir, d'accéder, de mettre à jour et de supprimer des comptes bancaires de tout type.
  * Une classe `Employe` qui possède les informations d'un salarié et son salaire.
  * Une classe `Entreprise` qui permet d'embaucher des employés et qui utilise un compte bancaire afin de recevoir de l'argent et verser le salaire des employés.

2. Complétez la classe `CompteBancaireAvecPlafond` : cette classe doit lever une exception `PlafondDepotAtteintException` si on essaye d'ajouter de l'argent qui ferait dépasser au solde le plafond du compte. On souhaite garder l'héritage avec `CompteBancaire`.

3. Complétez la classe `CompteBancaireAvecNombreRetraitMaximum` : cette classe doit compter le nombre de retraits effectués et lever une exception `LimiteRetraitAtteinteException` si on essaye de retirer trop de fois (si le nombre de retraits effectués est supérieur ou égal au nombre de retraits maximum lors de la tentative de retrait). On souhaite garder l'héritage avec `CompteBancaire`.

</div>

Les classes `Entreprise` et `Banque` manipulent des objets de type `CompteBancaire`. Elles doivent donc pouvoir compter sur son contrat : des dépôts sans plafond et un nombre illimité de retraits, sous réserve d'un solde suffisant. Les opérations d'ajout de bénéfices et de paiement des salariés de `Entreprise` doivent fonctionner avec tout objet respectant ce contrat. `Banque`, quant à elle, se contente de gérer les références vers les comptes : elle n'a pas besoin des garanties particulières de `CompteBancaire`.

<div class="exercise">

1. Pour valider, exécutez les tests unitaires consacrés à `Entreprise` du paquetage `fr.umontpellier.iut.bilan2` dans le dossier `src/test/java`. Pourquoi certains tests ne passent pas ? Analysez ces tests et comprenez pourquoi ils sont nécessaires, au vu du contrat imposé par `CompteBancaire`. À votre avis, quel est le principe **SOLID** violé par votre code ?

2. Refactorez les comptes avec restrictions afin qu'ils n'héritent plus de `CompteBancaire`. Les tests qui vérifiaient leur substituabilité avec `CompteBancaire` n'ont plus lieu d'être et peuvent être supprimés. Adaptez les tests des opérations de chaque type de compte à la nouvelle conception et conservez les tests de `Entreprise` avec des comptes respectant le contrat qu'elle attend.

3. Est-ce que votre `Main` fonctionne ? Si nécessaire, adaptez `Banque` pour qu'elle puisse gérer tous les types de comptes. Introduisez une interface commune `Compte`, permettant de consulter l'identifiant et le solde d'un compte, de déposer et de retirer de l'argent. Son contrat autorise le refus d'une opération lorsque les règles du compte ne sont pas respectées : solde insuffisant, plafond de dépôt ou limite du nombre de retraits. Un refus laisse le solde inchangé.

   Les différents types de comptes implémentent cette interface. `CompteBancaire` conserve ses garanties supplémentaires : aucun plafond de dépôt et aucun quota de retraits, sous réserve d'un solde suffisant. `Entreprise` continue à utiliser `CompteBancaire`, tandis que `Banque` utilise désormais `Compte`.

4. **Bonus** : comment pourrait-on ajouter dynamiquement aux comptes manipulés par la banque les fonctionnalités de plafond et/ou de nombre de retraits maximum, ainsi que d'autres fonctionnalités à l'avenir ?

   Les décorateurs doivent implémenter `Compte` et envelopper un autre objet de ce type. Ils conservent l'identifiant du compte enveloppé et lui délèguent la gestion du solde. Ils ne doivent pas hériter de `CompteBancaire`, dont ils ne respecteraient pas les garanties supplémentaires. `Entreprise` continue donc à utiliser des objets de type `CompteBancaire`.

   **Si et seulement si le temps le permet**, refactorez votre code pour rendre cela possible. Pour tester, ajoutez dans la banque un compte bancaire simple, sans stocker son instance dans le `Main`. Récupérez-le ensuite via son identifiant, ajoutez-lui une limite de 10 retraits et mettez à jour sa référence dans la banque. Enfin, répétez l'opération pour lui ajouter un plafond de 100 000 €.

   Pour cet exercice, le compteur de retraits démarre à zéro lors de l'ajout de cette fonctionnalité et ne compte que les retraits réussis. Le plafond ajouté doit être au moins égal au solde actuel du compte.

</div>

### Serveurs à louer

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.bilan3`. Il s'agit d'une application de gestion d'une entreprise qui loue des **serveurs** dédiés. Chaque serveur possède notamment un certain montant de **mémoire vive** (en Go), un **processeur** et un **prix mensuel** (à payer par le client qui loue le serveur). L'entreprise propose trois **offres** de serveurs configurés différemment et avec des coûts mensuels plus ou moins élevés : un serveur **basique**, un serveur **intermédiaire** et un serveur **pro**. Sur chaque **serveur**, on peut réaliser certaines actions :

    * Calculer le montant mensuel à payer pour louer le serveur (`calculerPrixMensuel`).

    * Récupérer le montant de mémoire vive (`getMemoireVive`)

    * Récupérer le processeur utilisé (`getCategorieProcesseur`)

    * Allumer le serveur (`allumer`).

    * Éteindre le serveur (`eteindre`).

    * Ouvrir un ticket, s'il y a un problème, pour être aidé par un technicien (`ouvrirTicket`).

    * Fermer un ticket (`fermerTicket`).

2. On aimerait pouvoir ajouter dynamiquement divers **services optionnels** à un **serveur**. On connait déjà un certain nombre de ces services, d'autres pourraient être ajoutés dans le futur. On vous demande d'implémenter une solution permettant d'ajouter à des serveurs certains de ces services optionnels :

    * Serveur avec plus de mémoire vive : 
      
      * Le serveur dispose d'une extension de sa mémoire vive, exprimée par un nombre entier de Go ajoutés. La méthode `getMemoireVive()` renvoie la quantité totale de mémoire : celle du serveur enveloppé augmentée de cette extension.
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
      * Le compteur représente le nombre de tickets actuellement ouverts. Il est initialisé à zéro, incrémenté à chaque ouverture et décrémenté à chaque fermeture. Pour simplifier, on suppose qu'on ne ferme jamais un ticket lorsqu'aucun n'est ouvert.
      * À chaque ouverture, **après incrémentation**, si le compteur est strictement supérieur à trois, on affiche un message annonçant un remboursement de 10 € sur la prochaine facture. Le message apparaît donc à l'ouverture du quatrième ticket, puis à chaque ouverture supplémentaire tant que le compteur reste supérieur à trois.
      * Pour cet exercice, on se limite à afficher ce message : aucun remboursement ni cumul de remboursements n'est effectivement calculé.

    * Serveur avec logs :

      * Le serveur dispose d'un système qui permet de garder une trace des événements qui se produisent sur le serveur : allumage, arrêt, ouverture et fermeture de tickets. Pour cela, on doit fournir un **nom de fichier** (chaîne de caractères) où les informations seront sauvegardées.
      * Quand le serveur est allumé, en plus des informations habituelles, on signale que le système de log est activé, en indiquant le nom du fichier où sont sauvegardés les logs.
      * Le prix mensuel de location du serveur n'augmente pas (option gratuite).
      * Dès qu'un événement se produit (allumage, arrêt, ouverture et fermeture de tickets) l'information est reportée dans le fichier en indiquant la date de l'événement. Par exemple `[2024-10-29T17:44:22] : Serveur allumé`, etc.

      Pour réaliser la dernière fonctionnalité, vous pouvez vous servir de la méthode `Utils.ecrireDansFichier`, qui permet d'écrire une ligne dans un fichier, en la combinant avec `LocalDateTime.now()` pour obtenir la date et l'heure courantes :

      ```java
      LocalDateTime time = LocalDateTime.now();
      Utils.ecrireDansFichier(nomFichier, String.format("[%s] : %s\n", time, "Mon message"));
      ```
      
      Normalement, le fichier sera sauvegardé à la racine de votre projet.

      Il est conseillé de se créer une méthode (privée) afin de ne pas dupliquer le code.

      Pour les logs, on se contentera de messages simples : Serveur allumé, Serveur éteint, Ticket ouvert, Ticket fermé.

3. Testez de créer divers serveurs puis de leur ajouter des services (et vérifiez leur comportement : prix, allumage, tickets, etc) :

    * Un serveur **basique** avec **4Go** de **mémoire vive supplémentaire** et un **fichier de log**.

    * Un serveur **intermédiaire** avec la **sauvegarde des données** et une **assurance**.

    * Un serveur **pro** avec **8Go** de **mémoire vive supplémentaire**, la **sauvegarde des données**, une **assurance** et un **fichier de log**.

4. **Bonus** : comment pourrait-on faire pour que les services **assurance** et **sauvegarde des données** soient seulement réservés aux configurations intermédiaires et pros ? **Si et seulement si le temps le permet**, refactorez votre code pour rendre cela possible.

</div>

### Une application modulable

Pour finir, nous allons travailler sur un exercice un poil plus conséquent divisé en différentes **couches** (cf. partie architecture logicielle du cours sur les DSI).

Vous allez voir qu'isoler les règles métier des détails techniques et injecter les dépendances facilite les **tests unitaires**. On peut ainsi contrôler les collaborateurs utilisés par le code testé et éviter de déclencher des écritures persistantes ou des envois de mails pendant ces tests.

<div class="exercise">

1. Ouvrez le paquetage `fr.umontpellier.iut.bilan4`. Cette application permet de créer des utilisateurs, de hacher leur mot de passe, de se connecter... Il y a aussi un système de gestion de diverses erreurs. Prenez le temps d'examiner l'architecture, la répartition des classes. Exécutez le programme avec le `Main`.

2. Générez un **diagramme de classes de conception** du paquetage `fr.umontpellier.iut.bilan4` (avec `IntelliJ`). Cela nous permettra de faire une comparaison après **refactoring**.

3. Une classe contenant des **tests unitaires** est présente dans le paquetage `fr.umontpellier.iut.bilan4.service.utilisateur` du dossier `src/test/java`. Lancez les tests deux fois, tout devrait bien se passer.

4. On aimerait effectuer quelques changements dans le programme, notamment au niveau de `ServiceUtilisateur` :

    * Hacher le mot de passe avec `SHA256` au lieu de `MD5`.

      **Simplification pédagogique :** les classes utilisant MD5 et SHA-256 servent ici à illustrer le remplacement d'une implémentation par une autre. Ces algorithmes utilisés seuls ne conviennent pas au stockage de mots de passe dans une application réelle. On utiliserait une fonction dédiée, comme **Argon2id**, avec un sel propre à chaque mot de passe. L'architecture proposée doit permettre d'intégrer une telle implémentation sans modifier `ServiceUtilisateur`.

    * Utiliser la classe `StockageUtilisateurFichier` pour gérer le stockage des utilisateurs. Contrairement à `StockageUtilisateurMemoire` qui stocke les données de manière volatile, ici, les utilisateurs seront stockés dans un fichier de manière persistante (qui sera généré à la racine du projet).

    Effectuez ces changements, relancez le programme (`Main`) pour vérifier que tout fonctionne.

5. Lancez maintenant les tests unitaires **2 fois de suite**. Il y a une erreur ! Trouvez la raison de cette erreur.
</div>

La classe `ServiceUtilisateur` dépend directement de détails techniques concrets et choisit elle-même leurs implémentations. Ces dépendances ne sont pas injectées, ce qui empêche de les remplacer facilement pour les tests.

Un **test unitaire** vérifie le comportement d'une unité de code, qui peut correspondre à une classe ou à un petit ensemble de classes. Ici, nous souhaitons tester `ServiceUtilisateur` sans dépendre d'un stockage persistant ni envoyer réellement des mails.

Avec le stockage dans un fichier, l'utilisateur créé lors d'une première exécution reste présent lors de la suivante. Le résultat du test dépend donc des exécutions précédentes. Nous souhaitons au contraire des tests **isolés et reproductibles**, qui retrouvent les mêmes conditions de départ à chaque exécution.

Pour cela, nous pouvons remplacer certaines dépendances par des **doublures de test**, c'est-à-dire des objets adaptés aux besoins des tests.

`StockageUtilisateurMemoire` constitue ici un **fake** : une implémentation fonctionnelle mais simplifiée du stockage. Elle modifie bien son état en mémoire ; nous utiliserons donc une nouvelle instance, initialement vide, pour chaque test.

Un **stub** fournit des réponses prédéfinies pour les besoins d'un scénario. Plus tard dans l'année, vous découvrirez aussi les **mocks**, qui permettent notamment de vérifier les appels effectués sur une dépendance.

Nous remplacerons ensuite l'envoi de mails par une doublure qui n'envoie aucun message réel.

Cependant, comment faire pour garder le stockage avec fichier pour l'exécution "normale" du programme, et le stockage en mémoire pour les tests ? Devons-nous éditer le code source de la classe `ServiceUtilisateur` avant les tests, puis la remettre en ordre ensuite ? Bien sûr que non ! Il suffit de mettre en pratique le **principe d'inversion de dépendance** que vous connaissez.

<div class="exercise">

1. Refactorez les classes du paquetage **storage** puis le code de `ServiceUtilisateur` afin de respecter le principe d'inversion des dépendances en utilisant des **abstractions** et surtout **l'injection de dépendances**.

2. Mettez à jour le code de `ControllerUtilisateur` afin que celui-ci utilise `ServiceUtilisateur` avec `StockageUtilisateurFichier`.

3. Mettez à jour vos tests unitaires pour injecter dans `ServiceUtilisateur` une nouvelle instance de `StockageUtilisateurMemoire`, initialement vide, pour chaque test.

4. Vérifiez que votre programme fonctionne toujours correctement et vérifiez que vos tests unitaires passent plusieurs fois sans problème.

</div>

Il reste maintenant le problème des "mails envoyés" quand on exécute les tests. On aimerait également que plusieurs autres dépendances soient modulables dans le programme :

* L'envoi des mails. On veut pouvoir utiliser une autre classe et surtout une classe n'envoyant rien (un "Fake mailer") pour les tests.

* Le système de hachage du mot de passe. On veut pouvoir changer entre MD5 et SHA-256. Pour tester la logique de `ServiceUtilisateur` indépendamment du calcul de hachage, on utilisera un `FakeHasher` qui renvoie simplement la chaîne reçue.

* La classe `ServiceUtilisateur` elle-même, qui doit pouvoir être remplacée par autre chose dans le `ControllerUtilisateur`. Cela pourrait notamment être utile si on veut tester le controller indépendamment du code de `ServiceUtilisateur`.

<div class="exercise">

1. Refactorez votre code pour appliquer **l'inversion de dépendances** par rapport aux modules cités (mails, hasher, service utilisateur...). Il faudra créer de nouvelles interfaces et modifier des classes existantes (les hashers, le mailer...) et aussi créer deux **doublures de test** : `FakeMailer` et `FakeHasher`.

2. Adaptez l'instanciation de `ServiceUtilisateur` dans vos tests unitaires et vérifiez qu'ils passent toujours. Vous ne devez plus constater aucun message "mail envoyé".

3. Vérifiez que le programme fonctionne toujours comme attendu.

4. Générez le **diagramme de classes de conception** de l'application (après refactoring donc) et comparez-le avec le premier diagramme que vous aviez réalisé.

</div>

## Conclusion

Voilà, maintenant, vous savez tout des principes **SOLID** ! Vous êtes donc plus proche d'un ingénieur logiciel qu'un codeur. Il existe un acronyme opposé : les principes **STUPID** qui sont six pratiques qui rendent le code très peu qualitatif, intestable, non évolutif et qu'il faut donc absolument éviter ! Bref, des **mauvaises pratiques** qui sont souvent observées. Vous pouvez consulter de la documentation à ce propos [sur cette page](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming).

Pour vos futurs projets, ou ceux déjà en cours comme la SAE, prenez le temps de réfléchir à la conception de votre programme et aux évolutions envisageables. Une bonne conception facilite les changements, mais n'élimine pas le besoin de **refactoring** : celui-ci permet de faire évoluer la structure du code à mesure que les besoins et votre compréhension du problème se précisent.

Dans les prochains TP, nous allons donc nous concentrer sur les **design patterns** (nous en avons déjà vu deux dans ce TP), qui vous fourniront des outils pour résoudre des problèmes de conception connus tout en facilitant l’application des principes **SOLID**.
