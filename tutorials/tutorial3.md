---
title: TP3 &ndash; Qualité du code - Les principes SOLID
subtitle: SOLID, Qualité, Interface, Abstraction, Héritage, Composition, Injection de dépendances, Design Patterns
layout: tutorial
lang: fr
---

Dans la première partie de cette ressource, nous avons parlé de **conception logicielle** et notamment comment modéliser cela à l'aide de **diagrammes de classes de conception** et de **diagrammes de séquences des interactions**.

Cependant, savoir modéliser la conception ne garantit en rien la qualité de celle-ci. Un plan de construction d'un bâtiment peut être tout à fait valide d'un point de vue technique, mais donnera potentiellement une bâtisse qui s'écoulera dans quelques années si elle a été mal pensée.

On a la même logique au niveau du développement logiciel. Un logiciel mal conçu peut répondre à un besoin et satisfaire le client et ses utilisateurs dans l'immédiat, mais il sera alors très difficile de le faire évoluer sur la durée.

De manière générale, les principes liés à la qualité du développement s'assurent que le logiciel que vous allez construire pourra évoluer facilement tout en satisfaisant les besoins actuels.

Tout cela est difficile à mettre en place au premier abord, car il peut parfois être bien plus rapide et facile de développer une solution peu qualitative, mais qui fonctionne. Néanmoins, le code produit ne tiendra pas au fur et à mesure que l'application va grossir ce qui conduira finalement à la réécriture d'une partie voir de la totalité du code ou pire, l'abandon du projet.

C'est un phénomène qui touche beaucoup d'entreprises du monde du développement. Face au besoin de délivrer une solution rapidement, l'aspect qualité est parfois négligé. Au bout de plusieurs années, il est très compliqué d'ajouter de nouvelles fonctionnalités et d'éviter les bugs. Une nouvelle personne rentrant dans le projet ne comprend rien au code. Le client n'est plus satisfait, car les nouvelles fonctionnalités sont délivrées moins fréquemment et de plus en plus de bugs apparaissent. C'est une barque qui prend l'eau sur lequel on place du sparadrad pour boucher les trous. Mais à chaque fois qu'un trou est bouché, deux nouveaux apparaissent. Le client transfère le projet à une autre entreprise, qui ne comprend rien à ce qu'elle récupère...

Tout cela est aussi dur pour le développeur. Travailler dans un tel environnement est très désagréable et peut même dégoûter du développement. Jusqu'ici, vous avez travaillé sur des projets relativement petits (même pour vos SAEs) mais vous devriez être plus conscients de cette problématique après votre période de stage (ou d'alternance pour certains !).

L'ingénieur doit avoir une vision à long terme et prendre en compte que son programme peut évoluer. Pour l'aider dans cette tâche, il dispose de différents outils : les principes liés à la qualité du code, comme les principes **SOLID** et aussi les **design patterns**. La maîtrise de ces outils différencie un programmeur (une IA?) d'un ingénieur. Le développeur sait produire du code, l'ingénieur sait produire des logiciels durables.

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

Les **design patterns** sont des solutions à des problèmes bien définis qui fournissent des modèles réutilisables et adaptables sur n'importe quel projet. Ces patterns permettent notamment de respecter les principes **SOLID**.

Dans un logiciel développé d'une telle manière, généralement, l'ajout d'une nouvelle fonctionnalité se résume à l'ajout de nouvelle classes ou de méthodes **sans avoir besoin de modifier ou de récrire les classes existantes**. Le programme est ouvert à l'extension, mais fermé aux modifications (qui pourraient entraîner elles-mêmes d'autres modifications...).

Dans ce TP, nous allons étudier chaque principe et nous allons vous fournir du code qui est (la plupart du temps) fonctionnel, mais développé sans respecter **SOLID**. Vous allez alors constater que :

* Il est difficile d'ajouter de nouvelles choses.
* L'ajout de fonctionnalités ou d'éléments entraînent la modification de multiples classes.
* Des bugs parfois assez inattendus peuvent survenir.
* Les tests unitaires sont difficiles à gérer.

Ensuite, nous allons voir comme un des principes **SOLID** permet de régler cela, et vous allez donc devoir **refactorer** les différentes applications. **Refactorer** du code (ou réusiner du code en français) signfit retravailler le code source du programme sans pour autant ajouter de nouvelles fonctionnalités à l'application. Il s'agit d'améliorer la qualité du code.

<div class="exercise">

1. Pour commencer, forkez [le dépôt gitlab suivant](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/tp3-etudiants) en le plaçant dans le namespace `qualite-de-developpement-semestre-3/etu/votrelogin`.

2. Clonez votre nouveau dépôt en local. Ouvre le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur.

3. Pendant ce TP, on vous demandera de créer des **diagrammes UML** de conception (classes, séquences). Vous déposerez vos diagrammes dans un dossier `uml` (en image ou bien avec le fichier du projet **.mdj** si vous utilisez **StarUML**) que vous devrez créer à la racine du dépôt.

4. À la fin de chaque séance, n'oubliez pas de faire un **push** vers votre dépôt distant sur **Gitlab**.

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

Ici, la classe **Mail** a deux responsabilités clairement identifiables : **stocker** les informations d'un mail et **l'envoyer**. Le principe de responsabilité unique n'est donc pas respecté. Pour régler cela, il faudrait donc mettre en place une nouvelle classe qui se charge de l'envoi d'un mail :

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

Le principe de responsabilité unique s'applique également aux **paquetages** : chaque paquetage est lié à une responsabilité du programme. Par exemple, sur le TP JDBC que vous faites en bases de données, chaque paquetage à un rôle (et donc une responsabilité) précis : IHM, controllers, services, stockage... (et on pourrait (même *devrait*) aller plus en détail).

Ce principe semble assez facile à mettre en place, mais dans la réalité, on retrouve malheureusement des classes (et des paquetages) "fourre-tout" qui sont deviennent illisibles au fur et à mesure de l'évolution du programme. Si votre classe a trop de méthode, c'est peut-être qu'elle possède plus d'une responsabilité et que celles-ci pourraient donc être mieux réparties.

<div class="exercise">

1. Ouvrez le paquetage `srp1`. Examinez le code. Il s'agit d'un programme qui permet de faire un simple calcul (pour le moment, une addition). Actuellement, la classe `Client` possède trois responsabilités (certaines sont très simples et tiennent sur une ligne). Identifiez-les.

2. Refactorez le code pour répartir les responsabilités de `Client` en **trois classes**.

3. Assurez-vous qu'en effectuant les changements suivants, vous ne modifiez jamais la même classe deux fois :

    * On veut que le calcul effectué soit une soustraction.

    * On veut que l'affichage final soit "Résultat : valeur".

    * Pour la saisie, on veut plutôt utiliser un `Scanner` et la méthode `nextInt` au lieu d'un `BufferedReader` (il faudra enlever le **catch** de `IOException` et les `parseInt`). Pour rappel, pour définir un `Scanner` :

    ```java
    Scanner scanner = new Scanner(System.in);
    ```

</div>

Bien sûr, ce premier exercice est très simpliste, mais il faut vous imaginer que les différentes responsabilités sont généralement des traitements plus longs et/ou plus complexes !

Voyons maintenant un autre exemple.

<div class="exercise">

1. Ouvrez le paquetage `srp2`. Il contient une classe `Rectangle` qui permet de créer des rectangles et de calculer leur aire.

2. Une application graphique souhaite pouvoir afficher les **rectangles**. Une première idée est d'utiliser la classe `JFrame`, ce qui permettra de l'afficher :

    * Faites étendre la classe `JFrame` à `Rectangle`.

    * Dans le constructeur, ajoutez le code suivant qui permettra de configurer la fenêtre affichant le rectangle :

      ```java
      setSize(largeur * 2, hauteur * 2);
      setTitle("Rectangle");
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      ```

    * Réécrivez la méthode suivante :

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

5. Assurez-vous que tout fonctionne (il faudra sans doute adapter la `main`) et qu'il est bien possible d'avoir de créer des rectangles ne contenant aucune logique d'affichage et des rectangles qu'il est possible d'afficher.

</div>

### Principe Ouvert/Fermé (Open/Close)

Après cette mise en bouche, il est temps d'attaquer de sérieux problèmes de conception en développant le **principe ouvert/fermé**. Ce principe est défini comme suit :

"Les entités d'un logiciel (classes, modules, fonctions) doivent être **ouverts** aux extensions, mais **fermés** aux modifications." (Bertand Meyer).

En d'autres termes, il doit être possible d'étendre les fonctionnalités/le comportement d'une entité comme une classe sans pour autant avoir besoin de modifier son code source.

Ce principe est un pilier fondamental de qualité de code. Avec ce principe, même une classe ou une librairie compilée (non modifiable) autorise le développeur à étendre les fonctionnalités proposées.

Malheureusement, dans de nombreux projets, on rencontre fréquemment des classes violant ce principe, car mal conçues. Les symptômes sont généralement l'utilisation d'un énorme bloc `if/else/else if` ou d'un `switch case` qui grossit au fur et à mesure qu'on ajoute de nouvelles choses. Avec l'utilisation de `classes` et de l'héritage, on va en plus généralement retrouver l'utilisation de multiples instructions `instanceof` (pour vérifier le type de l'objet) et de `cast` pour pouvoir utiliser des méthodes précises.

Pour vous mettre dans le bain et vous montrer la problématique derrière tout cela, vous allez ajouter de nouvelles fonctionnalités à des projets existants qui ne respectent pas le principe ouvert/fermé.

<div class="exercise">

1. Ouvrez le paquetage `ocp1`. Dans ce projet, une classe `Animal` permet de gérer différents types d'animaux et leur cri, selon l'attribut `type` de l'objet.

2. On aimerait prendre en charge les **chiens** et les **poules**. Modifiez la classe `Animal` en conséquence et testez dans le `Main`.

3. Que se passe-t-il si vous essayez de créer un animal qui n'existe pas et d'afficher son cri ? Pour régler cela, ajoutez une clause `default` dans le `switch` affichant simplement "Animal inconnu".

</div>

Votre programme fonctionne ? C'est super ! Mais votre code serait-il encore lisible s'il y avait une centaine d'animaux...?

Continuons maintenant avec de petits monstres bien populaires : les **pokémons**.

Le programme sur lequel nous allons travailler fait combattre des pokémons dans un simulateur. Il y a différents types de pokémons (feu, eau, plante...) et chaque type de pokémon possède une attaque (le type feu attaque toujours avec lance-flamme). Bien sûr, cette analyse est un peu bizarre et ne correspond pas à la réalité du jeu (où chaque pokémon possède plusieurs attaques, et pas une attaque précise selon le type) mais nous allons l'utiliser ainsi pour ne pas plus compliquer l'exercice.

En plus de l'attaque, le type de pokémon est aussi lié à un nombre de dégâts. Par exemple, le type **feu** fait toujours 60 dégâts et le type plante entre 40 et 80 dégâts.

Pour modéliser tout cela, le développeur a choisi de mettre en place un héritage pour gérer les différents types. Pour savoir quelle attaque annoncer dans le simulateur et quels dégâts infliger, il a besoin de vérifier quel est le pokémon qui attaque.

De même, dans la classe `Pokemon`, pour que le pokémon puisse se présenter avec son `type` (dans la méthode `toString`), la classe vérifie de quel type concret elle est.

<div class="exercise">

1. Ouvrez le paquetage `ocp2`. Explorez les classes. Étudiez notamment la classe `SimulateurCombat`.

2. On souhaite ajouter un nouveau type de pokémon : le pokémon type **électricité**. Son attaque est **Eclair** et il fait entre 20 et 100 dégâts. Faites en sorte de prendre en charge ce nouveau type.

3. On souhaite ajouter un nouveau type de pokémon : le pokémon type **psy**. Son attaque est **Choc mental** et il fait précisément 60 dégâts. Faites en sorte de prendre en charge ce nouveau type.

4. Modifiez le `Main` pour faire combattre un pokémon possédant le type **électrique** contre un pokémon possédant le type **psy**.

5. Ajoutez encore un nouveau pokémon (avec le type, l'attaque et les dégâts de votre choix...)

</div>

Si ce n'était peut-être pas encore assez évident avec les animaux, à ce stade, vous devez vous rendre compte qu'ajouter un nouveau type de pokémon est fastidieux :

* Créez une classe du type correspondant.

* Implémenter une méthode donnant les dégâts de ce type.

* Modifier la classe `SimulateurCombat` en ajoutant un nouveau `else if` pour prendre en charge le nouveau type, faire un `cast` pour récupérer ses dégâts...

* Modifier la classe `Pokemon` pour adapter le `toString` en ajoutant un nouveau `else if` pour prendre en charge le nouveau type.

De plus, ici, seules deux fonctions ont vraiment besoin de connaître les détails des pokémons. Mais que se passerait-il s'il y avait beaucoup plus de méthodes et de classes qui en dépendent ? À chaque ajout d'un nouveau type, il faudrait modifier l'ensemble de ces classes et de ces méthodes ! Dans un gros projet, cela deviendrait vite un calvaire. De pus qu'on a vite fait d'oublier de mettre à jour une classe, ce qui ne provoque pas d'erreur de compilation, mais un bug lors de l'exécution (comme avec les animaux inconnus).

Le respect du principe **ouvert/fermé** va permettre de se limiter aux deux premières étapes : création d'une classe et implémentation des méthodes nécessaires dans cette même classe.

Considérons l'exemple suivant, similaire à ce que vous venez de faire :

```java

class FigureGeometrique {

   private String typeFigure;

   public FigureGeometrique(String typeFigure) {
      this.typeFigure = typeFigure;
   }

   public void dessiner() {
      if(typeFigure == "rectangle") {
         dessinerRectangle();
      }
      else if(typeFigure == "triangle") {
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

Pour régler ce problème, l'idée est de se reposer sur un système d'héritage et d'abstraction : `FigureGeometirque` est une classe abstraite, car on a besoin de savoir dans quel type de figure géométrique on se trouve pour pouvoir effectuer le dessin. Chaque type figure géométrique donnera donc lieu à une classe spécialisée et on laisse tomber l'attribut `type` dans `FigureGeometrique` :

```java

abstract class FigureGeometrique {

  public abstract void dessiner();

}

class Rectangle extends FigureGeometrique {

  public Rectangle() {
    super();
  }

  public void dessiner() {
    //Code pour dessiner un rectangle...
  }
}

class Triangle extends FigureGeometrique {

  public Rectangle() {
    super();
  }

  public void dessiner() {
    //Code pour dessiner un triangle...
  }
}
```
<div style="text-align:center">
![Open-close 1]({{site.baseurl}}/assets/TP3/OCP1.svg){: width="25%" }
</div>

L'ajout d'une nouvelle figure nécessite donc simplement l'ajout d'une nouvelle classe correspondant à la figure et l'implémentation des méthodes requises (ici, dessiner la figure). Aucune autre classe est modifiée. L'extension est possible (ajout de nouvelles figures) sans modification du code source déjà présent. Par ailleurs, il est maintenant impossible de créer des figures géométriques qui n'existent pas au préalable dans notre programme (c'est une bonne chose !).

Comme `FigureGeometrique` ne contient aucun attribut (qui pourraient être communs à toutes les figures) et définit simplement des méthodes `abstraites`, il serait plus judicieux d'utiliser une `interface` ! Par contre, si la classe abstraite possède des attributs et/ou définit un bout de comportement commun à toutes les sous-classes, on utilisera bien une classe abstraite.

Ceci devrait vous permettre de refactorer le code du paquetage `ocp1` (animaux). Pour `ocp2` (pokémons) cela peut sembler un peu plus dur (car il y a déjà un système d'héritage), mais cela ne devrait pas être trop dur à adapter.

<div class="exercise">

1. Refactorez le code du paquetage `ocp1` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne. Il ne doit plus être possible de gérer des animaux inconnus, et c'est bien normal !

2. Réaliser un **diagramme de classes de conception** (hors Main) de l'application du paquetage `ocp2` (avant refactoring). Indiquez bien les **dépendances**.

3. Refactorez le code du paquetage `ocp2` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne.

4. Réaliser un **diagramme de classes de conception** (hors Main) de l'application du paquetage `ocp2` (après refactoring). Indiquez bien les **dépendances**.

</div>

En comparant vos deux diagrammes de classes, on peut facilement voir ce qui différencie la "mauvaise" conception de la "bonne" : dans votre premier diagramme, les classes `SimulateurCombat` et `Pokemon` ont autant de dépendances qu'il y a de sous-classes de type de pokémon. S'il y a 30 types de pokémons, `SimulateurCombat` et `Pokemon` auront chacune 30 dépendances. Après refactoring, ces dépendances disparaissent. `SimulateurCombat` est seulement dépendant de `Pokemon`.

Dans un code de qualité **les abstractions ne dépendent pas des implémentations**. En d'autres termes, une superclasse ne devrait pas dépendre de ses sous-classes. Seules les sous-classes peuvent dépendre de leurs parents (et on verra que parfois, là aussi il faut faire attention qu'on utilise l'héritage.). Sur votre premier diagramme, il est clair que ce principe n'est pas respecté, car `Pokemon` dépendait de ses différentes sous-classes, ce qui n'est plus les cas sur le deuxième diagramme.

Nous allons mettre à l'épreuve votre compréhension des deux principes (`S` et `O`) avec un nouvel exercice un peu différent de ce que vous venez de voir, dans sa forme.

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
    
    Pour vous aider, vous pourrez utiliser la méthode `compareTo` qui permet de comparer deux cartes. Cette méthode renvoie un nombre négatif si la première carte est strictement inférieure à la seconde, 0 si elles sont égales et un nombre positif si la première carte est strictement supérieure à la seconde.

3. Testez que votre algorithme fonctionne bien en changeant la méthode de tri du paquet dans le `Main`.

4. À votre avis, en quoi les principes de responsabilité unique et ouvert/fermé ne sont pas respectés ?

</div>

Comme vous l'avez sans doute déduit, dans un premier temps, le principe **ouvert/fermé** n'est pas respecté : ajouter un nouveau tri demande de modifier le code source de la classe `Paquet` et notamment la méthode `trier`.

Dans un second temps, on remarque aussi que la classe `Paquet` a peut-être un peu trop de responsabilités : cela ne devrait pas être à elle de trier les cartes ! On pourrait aussi dire la même chose pour le mélange, et peut-être même pour l'affichage ! La vérification peut se faire facilement :

* Si la méthode de tri change, la classe `Paquet` doit être modifiée.

* Si la méthode de mélange change, la classe `Paquet` doit être modifiée.

* Si le format d'affichage du paquet change, la classe `Paquet` doit être modifiée.

Le principe de responsabilités unique n'est pas respecté. Pour le `toString`, cela peut encore se discuter, mais cela est clair pour le **tri** et le **mélange**.

<div class="exercise">

1. Refactorez le code afin de respecter le **principe ouvert/fermé** au niveau des **tris**. On souhaite tout de même garder la possibilité de changer de tri avec un `setter` et aussi de définir le tri utilisé via le `constructeur`. Quelques indices :

    * Isolez le code de chaque méthode de tri dans des classes dédiées.

    * Généralisez le tout avec une interface.

    * Utilisez cette interface dans la classe `Paquet`, à la place de `typeTri`.

2. Refactorez le code concernant le **mélange** afin de respecter le **principe de responsabilité unique**. Prévoyez aussi le cas où d'autres méthodes de mélanges pourraient être ajoutées. Comme pour le tri, on souhaite pouvoir définir la méthode de mélange dans le constructeur et la modifier via un setter.

3. Testez que tout fonctionne, essayez plusieurs méthodes de tri sur le paquet, notamment. Normalement, vous ne devez jamais éditer la classe `Paquet` si vous changez le tri utilisé.

4. Réalisez un diagramme de classes de conception votre application (sans la classe Main).

</div>

Les principes **SOLID** se combinent naturellement entre eux. D'ailleurs, si vous avez refactoré proprement le dernier exercice, vous avez même déjà utilisé le principe **d'inversion des dépendances** dont nous parlerons plus tard ! 

Encore mieux, vous venez d'utiliser votre premier **design pattern** au niveau des tris : **Stratégie**. Ce pattern permet **d'injecter** un comportement spécifique dans une classe sans en modifier le code source (et éventuellement, le modifier plus tard). Ce pattern s'appuie sur **ouvert/fermé**, **l'inversion des dépendances** et aide à renforcer **responsabilité unique**. C'est exactement ce que vous venez de faire : la méthode de tri du paquet est modulable et on peut même en ajouter des nouvelles dans le futur ! Et tout cela, sans modifier `Paquet`.

À partir du diagramme de classes de conception que vous venez de réaliser, vous devriez être en mesure de généraliser le pattern **stratégie** à tout type de problème.

### Principe de substitution de Liskov (Liskov substitution)

Le principe de **substitution de Liskov** a été introduit par **Barbara Liskov** et énonce qu'un **objet** d'une superclasse donnée doit pouvoir être remplacée par une de ses **sous-classes** sans casser le fonctionnement du programme. Une méthode provenant à l'origine d'une superclasse et appelée sur la sous-classe devrait produire le même résultat que si elle avait été appelée sur la superclasse.

Certains développeurs abusent de l'**héritage** par facilité au lieu d'utiliser d'autres solutions comme la **composition** d'objets. Un "mauvais" héritage est un héritage où il n'existe pas vraiment de relation de spécialisation entre la superclasse et la sous-classe. La sous-classe ne représente alors pas le même concept que sa classe mère, ce n'est pas vraiment une spécialisation.

Tout cela occasionne des bugs parfois inattendus.

<div class="exercise">

1. Ouvrez le paquetage `lsp1`. Dans ce programme, on gère des **comptes bancaires**. La première classe `CompteBancaire` permet d'effectuer des opérations et de gérer un **solde**. La deuxième classe `CompteBancaireAvecHistorique` permet de gérer l'**historique** de toutes les opérations réalisées. Il semble s'agir d'un compte bancaire spécialisé, on lui fait donc étendre la classe `CompteBancaire`.

2. Une classe de test unitaire est présente dans `test/java/lsp1`. Lisez les tests et exécutez-les. Tout devrait bien se passer.

3. Le développeur à l'origine de la classe `CompteBancaire` souhaite revoir sa classe et légèrement la réfactorer afin d'éviter la duplication de code. Dans la méthode `effectuerTransactions`, il souhaite donc plutôt appeler la méthode `effectuerTransaction` au lieu de dupliquer la ligne de code ajoutant le montant au solde. Faites cette modification.

4. Relancez les tests unitaires... Le second ne passe plus. Pourquoi ?

</div>

Ici, le principe de substitution de Liskov n'est pas respecté, car, selon l'implémentation interne de `CompteBancaire`, l'appel de `ajoutOperations` sur une classe fille provoque un bug (historique des opérations enregistrées en double).

Tout cela peut être réglé en utilisant de la **composition** au lieu d'un **héritage**. L'idée est que la classe "fille" n'hérite pas de la classe mère, mais possède à la place un attribut stockant une instance de cette classe et l'utilise. Si on a besoin que les deux classes soient du même type, on utilise une **interface**.

Considérons l'exemple suivant :

```java

class A {

  public void operation() {
    //Code de l'opération...
  }

  //Execute operation n fois
  public void operations(int n) {
    for(int i = 0 ; i < n; i++) {
      operation();
    }
  }

}

class B extends A {

  @Override
  public void operation() {
      super.operation();
      System.out.println("Execution d'une opération");
  }

  @Override
  public void operations(int n) {
    super.operations(n);
    for(int i = 0 ; i < n; i++) {
      System.out.println("Execution d'une opération");
    }
  }

}
```

Ici, selon le code de la méthode `operations` de la classe `A`, on aura des résultats étranges. Ici, si on exécute `operations(n)` sur une classe de type `B`, on aura `n*2` affichage de `Execution d'une opération`. Si on change le code de `A`, on aura peut-être plus ce bug...(si le code est dupliqué).

Bref, cela n'est pas bon. Pour éviter cela, on peut à la place définir une `interface` pour les méthodes utilisées dans `A` et `B` et mettre en place de la **composition** :

```java

public interface Operateur {
   void operation();

   void operations(int n);
}

class A implements Operateur {

   @Override
   public void operation() {
      //Code de l'opération...
   }

   //Execute operation n fois
   @Override
   public void operations(int n) {
      for(int i = 0 ; i < n; i++) {
         operation();
      }
   }

}

class B implements Operateur {

   private Operateur operateurParent;

   public B(Operateur operateurParent) {
      this.operateurParent = operateurParent;
   }

   //Ou bien, si on veut faire une véritable composition (et qu'on connait la classe mère précise)
   public B() {
      this.operateurParent = new A();
   }

   @Override
   public void operation() {
      operateurParent.operation();
   }

   @Override
   public void operations(int n) {
      operateurParent.operations(n);
      for(int i = 0 ; i < n; i++) {
         System.out.println("Execution d'une opération");
      }
   }

}
```

<div style="text-align:center">
![Liskov substitution 1]({{site.baseurl}}/assets/TP3/LSP1.svg){: width="25%" }
</div>

Maintenant, peu importe l'implémentation de `A`, il n'y aura plus jamais aucun bug de duplication des affichages.

<div class="exercise">

1. Définissez une interface `I_CompteBancaire` regroupant les signatures des méthodes `ajouterTransaction` et `ajouterTransactions`.

2. Refactorez votre code en utilisant votre nouvelle interface et en remplaçant l'héritage par une **composition**.

3. Adaptez les tests unitaires et vérifiez qu'ils passent.

4. Remplacez l'appel à `ajouterTransaction` par une incrémentation du solde dans `ajouterTransactions` de la classe `CompteBancaire` (comme c'était le cas à l'origine). Vérifiez que les tests passent toujours.

</div>

Le fait d'utiliser de la composition au lieu de l'héritage est une bonne pratique et n'est pas nécessairement lié à la substitution de Liskov. Attention cependant, l'héritage peut parfois avoir un véritable intérêt quand il existe un lien fort entre la classe mère et les classes filles, comme c'était le cas avec les pokémons, par exemple.

Une autre illustration plus précise de principe de substitution de Liskov est le suivant : on possède une classe `Rectangle`. On veut modéliser une classe `Carre`. En géométrie, un carré est un sous-type de rectangle. On implémente donc le code suivant :

```java
class Rectangle {

  private int hauteur;

  private int largeur;

  public Rectangle(int hauteur, int largeur) {
    this.hauteur = hauteur;
    this.largeur = largeur;
  }

  public int getHauteur() {
    return hauteur;
  }

  public int getLargeur() {
    return largeur:
  }

  public void setHauteur(int hauteur) {
    this.hauteur = hauteur;
  }

  public void setLargeur(int largeur) {
    this.largeur = largeur;
  }

  public int aire() {
    return hauteur*largeur;
  }

}

class Carre extends Rectangle {

  public Carre(int tailleCote) {
    super(tailleCote, tailleCote);
  }

}
```

Si à première vue l'implémentation semble correcte, le fait que le carré soit un rectangle pose problème : on peut changer sa largeur et sa hauteur indépendamment. Or, un carré a la même largeur et la même hauteur !

```java
Carre c = new Carre(5);
c.aire() //Renvoie 25, OK
c.setHauteur(10);
c.aire() // Renvoie 50, Pas OK!
```

Pour régler cela, on pourrait réécrire les méthodes `setHauteur` et `setLargeur` dans `Carre` :

```java
class Carre extends Rectangle {

  public Carre(int tailleCote) {
    super(tailleCote, tailleCote);
  }

  @Override
  public void setHauteur(int hauteur) {
    this.hauteur = hauteur;
    this.largeur = hauteur;
  }

  @Override
  public void setLargeur(int largeur) {
    this.largeur = largeur;
    this.hauteur = largeur;
  }

}
```

Cependant, le principe de substitution de Liskov n'est plus respecté ! En effet, si on utilise `Carre` comme un `Rectangle`, des bugs étranges vont survenir !

Imaginons la méthode suivante :

```java
public static void agrandirRectangle(Rectangle r, int facteur) {
  r.setHauteur(r.getHauteur() * facteur);
  r.setLargeur(r.getLatgeur() * facteur);
}
```

Tout va bien se passer si j'exécute cette méthode sur un rectangle, mais pas sur un rectangle spécialisé carré !

```java
Rectangle r = new Rectangle(5,5);
r.aire() //Renvoie 25
Rectangle c = new Carre(5);
c.aire() //Renvoie 25
agrandirRectangle(r, 2);
r.aire() //Renvoie 100
agrandirRectangle(c, 2);
c.aire() //Renvoie 400! Pourquoi ???
```

Bref, cet héritage est une très mauvaise idée ! En fait, conceptuellement, en programmation, un carré n'est pas un rectangle spécialisé, car les règles pour la hauteur et la largeur sont différentes...cela peut être un peu dur à accepter.

Si on souhaite quand même utiliser un rectangle dans un carré (pour ne pas dupliquer le calcul de l'aire ou des autres méthodes, par exemple) on peut éventuellement utiliser une **composition** comme nous l'avons vu dans l'exercice précédent, en interdisant à un `Carre` de redéfinir sa hauteur et sa largeur.

```java
interface FigureRectangulaire {
  int aire();
  int getHauteur();
  int getLargeur();
}

class Rectangle implements FigureRectangulaire {

  private int hauteur;

  private int largeur;

  public Rectangle(int hauteur, int largeur) {
    this.hauteur = hauteur;
    this.largeur = largeur;
  }

  @Override
  public int getHauteur() {
    return hauteur;
  }

  @Override
  public int getLargeur() {
    return largeur;
  }

  public void setHauteur(int hauteur) {
    this.hauteur = hauteur;
  }

  public void setLargeur(int largeur) {
    this.largeur = largeur;
  }

  @Override
  public int aire() {
    return hauteur*largeur;
  }

}

class Carre implements FigureRectangulaire {

  private Rectangle rectangle;

  public Carre(int tailleCote) {
    rectangle = new Rectangle(tailleCote, tailleCote);
  }

  public void setTailleCote(int tailleCote) {
    rectangle.setHauteur(tailleCote);
    rectangle.setLargeur(tailleCote);
  }

  @Override
  public int getHauteur() {
    return rectangle.getHauteur();
  }

  @Override
  public int getLargeur() {
    return rectangle.getLargeur();:
  }

  @Override
  public int aire() {
    return rectangle.aire();
  }

}
```

<div style="text-align:center">
![Liskov substitution 2]({{site.baseurl}}/assets/TP3/LSP2.svg){: width="50%" }
</div>

Mettons vos nouvelles connaissances en pratique avec un nouvel exercice.

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

2. Ouvrez la classe de tests unitaires placée dans `test/java/lsp2`. Exécutez les tests. Rien ne passe, c'est normal ! Vous n'avez pas encore implémenté le code de la classe `Pile` qui contient du code par défaut... Vous êtes donc en mode **TDD** (test driven development).

3. Implémentez les méthodes de la classe `Pile` afin que les tests passent.

4. Ajoutez le test unitaire suivant et exécutez-le :

    ```java
    @Test
    public void testSupprimerIndex() {
        Pile<Integer> pile = new Pile<>();
        pile.empiler(5);
        pile.empiler(9);
        pile.empiler(10);
        pile.remove(1);
        pile.depiler();
        assertEquals(9, pile.sommetPile());
    }
    ```

</div>

Le dernier test n'est pas mal rédigé, car, selon le **contrat** de `Pile`, seules les opérations `estVide`, `empiler`, `depiler` et `sommetPile` doivent produire un effet. Or, comme `Pile` hérite de `Vector`, on a accès à toutes les opérations réalisables sur une liste classique... Donc, dans la logique, même s'il est possible d'appeler `remove` sur notre `Pile`, cela ne doit produire aucun effet ! Or, ce n'est pas le cas ici.

On pourrait redéfinir la méthode `remove` (et toutes les méthodes de `Vector` !) pour qu'elles ne fassent rien, mais le principe de substitution de Liskov ne serait alors plus respecté ! On ne pourrait pas substituer un `Vector` par une `Pile`.

Bref, conceptuellement, une `Pile` n'est pas un `Vector` spécial, mais bien une structure indépendante... Néanmoins, il est possible d'utiliser une **composition** pour utiliser un `Vector` comme attribut, dans notre classe `Pile`.

<div class="exercise">

1. Refactorez le code de la classe `Pile` en enlevant l'héritage et en utilisant une **composition** avec un `Vector` à la place.

2. Le dernier test ajouté ne compile plus, c'est normal ! La pile n'est pas un `Vector`, on ne peut pas appeler `remove` dessus (et c'est tant mieux). Supprimez donc ce test.

3. Relancez les tests et vérifiez que tout passe.

4. Quelque part dans votre code, définissez une variable de type `Stack` qui est une classe de `Java` permettant de gérer une pile. Allez observer le code source de cette classe (`CTRL+B` sur **IntelliJ** en cliquant sur le nom de la classe). Que remarquez-vous au niveau de sa déclaration ? Cette classe est aujourd'hui dépréciée, pourquoi ?

</div>

Eh oui, même les concepteurs de `Java` ont fait quelques bêtises lors du développement du langage. Et il n'est plus possible de supprimer cette classe après coup pour ne pas causer de problèmes de compatibilité. La seule chose à faire est de déprécier cette classe et de conseiller une nouvelle solution mieux conçue. D'où l'importance de bien penser sa conception !

### Héritage, composition et principe ouvert-fermé

Maintenant, voyons un nouveau problème que vous devriez pouvoir résoudre en utilisant judicieusement la **composition** à la place de l'héritage, comme nous l'avons vu en étudiant le principe de substitution de Liskov. Cette fois-ci, il s'agit d'un problème plutôt lié au principe **ouvert/fermé**.

<div class="exercise">

1. Ouvrez le paquetage `ocp4`. Dans ce projet, il y a une classe `Produit` permettant de gérer des produits et leurs prix. Ensuite, on a souhaité définir une classe `ProduitAvecReduction`, car certains produits proposent des réductions. Tout fonctionne pour le moment, comme vous pouvez le constater dans le `Main`.

2. On souhaite maintenant ajouter un nouveau type de produit : les produits avec une date de péremption proche. Sur un tel produit, le prix est calculé en faisant une réduction de 50% sur le prix d'origine. Implémentez donc une classe `ProduitAvecDatePeremptionProche` héritant de `Produit` et réécrivez la méthode `getPrix`. Testez que votre nouveau type de produit a bien le comportement attendu en testant dans le `Main` (ou encore mieux, avec des tests unitaires !)

3. Maintenant, nous voulons qu'un produit puisse à la fois être un produit qui périme bientôt et un produit avec une réduction. Est-il possible de créer une telle classe ou un tel comportement ?
</div>

Avec l'architecture actuelle, il est impossible d'avoir un même produit possédant ces deux fonctionnalités à la fois. Avec un héritage multiple, il y aurait pu y avoir une solution, mais nous avons vu qu'il est déconseillé de faire cela et de toute façon, dans la plupart des langages et en Java, ce n'est pas possible.

Heureusement, la composition nous permet de faire cela assez facilement ! Tout en respectant le **principe ouvert/fermé**. Il existe une méthode pour construire un `Produit` possédant autant de comportement mixte que nous souhaitons.

Illustrons le problème et sa solution :

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

class ChefProjet extends Salarie {

   private int nombreProjetsGeres;

   public ChefProjet(double salaire, int nombreProjetsGeres) {
      super(salaire);
      this.nombreProjetsGeres = nombreProjetsGeres;
   }

   @Override
   public double getSalaire() {
      return super.getSalaire() + 100 * (nombreProjetsGeres);
   }

}

class ResponsableDeStagiaires extends Salarie {

   private int nombreStagiairesGeres;

   public ResponsableDeStagiaires(double salaire, int nombreStagiairesGeres) {
      super(salaire);
      this.nombreStagiairesGeres = nombreStagiairesGeres;
   }

   @Override
   public double getSalaire() {
      return super.getSalaire() + 50 * (nombreStagiairesGeres);
   }
}
```

Ici, même problème que pour les produits, si je veux un salarié qui est à la fois chef de projet et responsable de stagiaire, cela est impossible !

Comme souvent, l'héritage est le problème ici. Au lieu de faire hériter nos classes, nous pourrions utiliser des **compositions** sur les sous-types et créer ainsi des salariés incluant des salariés, incluant des salariés...ce qui permet de combiner la logique de chaque type ! 

```java
interface I_Salarie {
  double getSalaire();
}


class Salarie implements I_Salarie {

  private double salaire;

  public Salarie(double salaire) {
    this.salaire = salaire;
  }

  public double getSalaire() {
    return salaire;
  }

}

class ChefProjet implements I_Salarie {

  private I_Salarie salarie;

  private int nombreProjetsGeres;

  public ChefProjet(I_Salarie salarie, int nombreProjetsGeres) {
    this.salarie = salarie;
    this.nombreProjetsGeres = nombreProjetsGeres;
  }

  @Override
  public double getSalaire() {
    return salarie.getSalaire() + 100 * (nombreProjetsGeres);
  }

}

class ResponsableDeStagiaires implements I_Salarie {

  private I_Salarie salarie;

  private int nombreStagiairesGeres;

  public ResponsableDeStagiaires(I_Salarie salarie, int nombreStagiairesGeres) {
    this.salarie = salarie;
    this.nombreStagiairesGeres = nombreStagiairesGeres;
  }

  @Override
  public double getSalaire() {
    return salarie.getSalaire() + 50 * (nombreStagiairesGeres);
  }
}
```

<div style="text-align:center">
![Open close 2]({{site.baseurl}}/assets/TP3/OCP2.svg){: width="80%" }
</div>

Avec cette nouvelle architecture, nous pouvons créer des salariés qui sont chefs de projet et responsables de stagiaires :

```java
//Salarié qui est chef de projet gérant 3 projets et aussi responsable de stagiaires gérant 5 stagiaires
I_Salarie salarie = new ResponsableStagiaires(new ChefProjet(new Salarie(2000), 3), 5);
salarie.getSalaire(); //Renvoie 2550
```

Il est important de noter que la classe composée est `I_Salarie` et non pas `Salarie`! Sinon, on ne pourrait pas combiner `ChefProjet` avec `ResponsableStagiaires`.

Aussi, le salarie n'est pas instancié dans la classe, il est **injecté** (autrement, cela ne fonctionnerait pas), comme ce que vous avez fait, par exemple, avec l'exercice sur le paquet de carte et les différentes méthodes de tri. Sur un diagramme de classes de conception, cela pourrait être représenté par une **agrégation blanche**.

<div class="exercise">

1. Refactorez votre code afin de pouvoir créer un produit qui possède une réduction et qui a aussi une date de péremption proche.

2. Créez un **Twix** avec pour prix de base 3€, qui périme bientôt et qui a une réduction de 50 centimes. Testez que la valeur obtenue pour le prix est bien la bonne.

3. Inversez l'ordre de création du produit (le produit avec réduction est composé d'un produit avec une date de péremption proche ou l'inverse selon ce que vous avez fait à la question précédente). Est-ce que le prix obtenu est le même qu'à l'étape précédente ?

</div>

Attention, même si nous pouvons maintenant rajouter un nouveau type de produit et le combiner aux autres pour calculer le prix adéquat, quand on instancie l'objet, il faut faire attention à l'ordre de combinaison des objets.

Bon, tout fonctionne bien, mais le code est encore un peu redondant : A priori, tous nos produits "dérivés" vont posséder un objet `I_Produit`. Il est alors possible de factoriser cela avec une **classe abstraite** dont vont hériter tous les sous-produits.

Par exemple, pour l'exemple des salariés :

```java
//Nous reviendrons sur le nom "decorator" plus tard.
abstract class SalarieDecorator implements I_Salarie {
   protected I_Salarie salarie;

   public SalarieDecorator(I_Salarie salarie) {
      this.salarie = salarie;
   }
}

class ResponsableDeStagiaires extends SalarieDecorator implements I_Salarie {

   private int nombreStagiairesGeres;

   public ResponsableDeStagiaires(I_Salarie salarie, int nombreStagiairesGeres) {
      super(salarie);
      this.nombreStagiairesGeres = nombreStagiairesGeres;
   }

   //Reste du code

}
```

<div style="text-align:center">
![Open close 3]({{site.baseurl}}/assets/TP3/OCP3.svg){: width="80%" }
</div>

<div class="exercise">

1. Réfactorez votre code pour introduire une classe abstraite et réduire la redondance et la répétition de code au niveau des sous-classes (`ProduitAvecReduction` et `ProduitAvecDatePeremptionProche`).

2. Testez que tout fonctionne comme auparavant.

3. Dessinez le **diagramme de classes de conception** (hors `Main`) de cette application.

</div>

Dans le futur, si nous ajoutons un nouveau type de **produit**, il suffira alors de rajouter une nouvelle classe et lui faire étendre votre classe abstraite. Avec une telle architecture, le principe ouvert/fermé est respecté et nous avons tiré profit de manière avantageuse du mécanisme de composition au lieu de se reposer sur l'héritage qui ne nous permettait pas d'arriver à nos fins.

En fait, ce modèle est réutilisable et adaptable à d'autres situations (nous l'avons vu avec les salariés). C'est en fait un autre **design pattern** nommé **décorateur** d'où le nom de la classe abstraite dans l'exemple. 

À partir du diagramme de classes que vous avez réalisé, vous devriez être capable de produire un modèle général fonctionnant pour vous.

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

2. Ajoutez une classe `Rhinoceros` implémentant la classe `Monture`. Pour un `Rhinoceros` on a une vitesse de 30 et une endurance de 100.

3. Ajoutez une classe `Dauphin` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 45. Cependant, contrairement aux autres montures, cette monture est une monture aquatique. Elle ne possède pas d'endurance et on veut connaître son **temps de respiration sous l'eau** qui est de 15.

    Concernant l'endurance, que faut-il renvoyer ? On ne peut pas renvoyer 0 ou un nombre négatif, cela n'aurait pas beaucoup de sens. A la place, on peut lever une erreur :

    ```java
    public double getEnduranceMonture() {
        throw new Error("Une monture aquatique n'a pas d'endurance!");
    }
    ```

4. Dans le cas où il y aurait besoin d'ajouter d'autres montures aquatiques dans le futur, ajoutez la méthode permettant d'obtenir le temps de respiration dans l'interface `Monture`.

5. Les classes `Cheval` et `Tigre` ne compilent plus ! C'est parce qu'il faut implémenter la méthode permettant d'obtenir le temps de respiration sous l'eau...Or ces montures n'ont pas de temps de respiration ! On va donc procéder comme pour `Dauphin` en soulevant une erreur :

    ```java
    throw new Error("Cette monture ne peut pas respirer sous l'eau!");
    ```

6. Ajoutez une classe `Griffon` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 300. Cependant, contrairement aux autres montures, cette monture est une monture volante. Elle ne possède pas d'endurance et ne respire pas sous l'eau non plus. Par contre, on veut connaître son **temps maximum de vol** qui est de 40. Adaptez votre classe en conséquence.

7. Mettez à jour l'interface `Monture` avec la méthode pour le temps de vol au cas où il y ait d'autres types de montures volantes ajoutées et corrigez les erreurs de compilation.

8. Ajoutez une classe `Dragon` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 400. Elle possède aussi un temps de vol maximum de 120 (car c'est une monture volante). Elle ne possède pas d'endurance et ne respire pas sous l'eau non plus. Par contre, on veut connaître sa **puissance de feu** qui est de 200. Adaptez votre classe en conséquence.

9. Mettez à jour l'interface `Monture` avec la méthode pour la puissance de feu au cas où il y ait d'autres types de dragons ajoutés dans le futur et corrigez les erreurs de compilation.

10. Enfin, ajoutez une classe `LicorneAilee` étendant `Creature` et implémentant l'interface `Monture`. Cette monture a une vitesse de 75. Elle possède aussi un temps de vol maximum de 20 (car c'est une monture volante) et une endurance de 50 (car c'est aussi une monture terrestre !). Par contre, elle ne respire pas sous l'eau et n'a pas de puissance de feu non plus.

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

Enfin, il reste le **principe d'inversion des dépendances**. Ce principe dit que :

* Les différentes classes ne doivent pas dépendre d'implémentations concrètes, mais d'abstractions (classes abstraites/interfaces).

* Les abstractions ne doivent pas dépendre des détails (les implémentations, les classes filles) mais les détails (les classes concrètes) doivent dépendre des abstractions. Nous l'avons bien vu avec l'exercice sur les **pokémons** lorsque nous étudions le principe **ouvert/fermé**.

Ce principe permet d'obtenir une très forte **modularité** du programme. Si on couple cela avec la technique **d'injection des dépendances** et des **design patterns créateurs** tels que des **fabriques abstraites** ou bien des **conteneurs de dépendances** on obtient un logiciel dont on peut moduler le fonctionnement sans toucher au code source, simplement en ajoutant de nouvelles classes et/ou en éditant des fichiers de configuration. Les différents **frameworks** mettent en place une architecture favorisant l'inversion des dépendances.

En fait, ce principe découle de la bonne application des autres principes et notamment du principe **ouvert/fermé** et de la **substitution de Liskov**.

Nous verrons aussi qu'il est essentiel de bien respecter ce principe quand on réalise des tests unitaires.

Tout d'abord, illustrons ce principe avec un exemple. 

<div class="exercise">

1. Ouvrez le paquetage `dip1`. Dans ce projet, il y a une classe `Etudiant` et une classe `CompteUniversitaire`. Un compte universitaire est détenu par un étudiant. On utilise son nom et son prénom pour générer un login.

2. Ajoutez une classe **Enseignant** qui possède un nom, un prénom et définit des **getters** pour ces deux attributs.

3. La logique pour créer un compte universitaire pour un enseignant est la même que pour un étudiant. On souhaite donc logiquement réutiliser la classe `CompteUniversitaire`. Mais ce n'est pas possible, car un enseignant n'est pas un étudiant !

</div>

Le problème souligné ici est qu'on a utilisé une classe concrète (`Etudiant`) à la place d'une classe abstraite ou d'une interface, ce qui empêche son utilisation pour d'autres types de classes (ici, Enseignant).

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

Ici, nous avons un problème similaire : la classe `Service` dépend directement d'une implémentation concrète `A` ce qui le rend peut modulable. Si je veux utiliser `B` à la place de `A`, je dois récrire le code source de `Service`.

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

Bien, je peux maintenant utiliser un `I_Exemple` dans `Service` au lieu de `A` ou `B`... Mais il reste un problème ! Dans l'exemple d'origine, `A` était instancié dans le constructeur. Hors, on ne peut pas instancier une interface ou une classe abstraite (seulement une classe concrète) :

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

Pour palier à ce problème, on utilise **l'injection de dépendance**. La classe concrète est injectée via le constructeur, au moment de l'instanciation de l'objet, mais la classe ne connait que le type abstrait. Cela permet une modularité de la classe qui peut alors être utilisée avec n'importe quel service concret dérivé du type abstrait. Et on peut en ajouter dans le futur. C'est exactement ce que nous avions fait avec le paquet de cartes et les tris avec le pattern **stratégie**, mais également avec le **décorateur** dans l'exercice avec les produits. L'injection de dépendance est partout !

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

  public static void main(String[]args) {
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

2. Testez de créer un compte universitaire pour l'enseignante "Bricot Judas".

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

5. Le compte de "Tarembois Guy" doit être généré en utilisant le générateur de login simple et celui de "Bricot Judas" avec le générateur par mélange. Testez.
</div>

Pour finir, nous allons travailler sur un exercice un poil plus conséquent divisé en différentes **couches** (cf partie architecture logicielle du cours sur les DSI).

Vous allez voir qu'en plus de rendre notre projet modulable, utiliser **l'inversion de dépendances** et globalement **ne pas dépendre d'implémentations concrètes** est plus qu'important, car une architecture ne respectant pas ce principe peut occasionner des effets de bords indésirables lors des **tests unitaires**.

<div class="exercise">

1. Ouvrez le paquetage `dip2`. Cette application permet de créer des tilisateurs, de hacher leur mot de passe, de se connecter...Il y a aussi un système de gestion de diverses erreurs. Prenez le temps d'examiner l'architecture, la répartition des classes. Exécutez le programme avec le `Main`.

2. Réalisez un **diagramme de classes de conception** de l'application (hors `Main`). Cela nous permettra de faire une comparaison après **refactoring**.

3. Une classe contenant des **tests unitaires** est présente dans `src/test/java/dip2`. Lancez les tests deux fois, tout devrait bien se passer.

4. On aimerait effectuer quelques changements dans le programme, notamment au niveau de `ServiceUtilisateur` :

    * Hasher le mot de passe avec `SHA256` au lieu de `MD5`.

    * Utiliser la classe `StockageUtilisateurFichier` pour gérer le stockage des utilisateurs. Contrairement à `StockageUtilisateurMemoire` qui stocke les données de manière volatile, ici, les utilisateurs seront stockés dans un fichier de manière persistante (que sera généré à la racine du projet).

    Effectuez ces changements, relancez le programme (`Main`) pour vérifier que tout fonctionne.

5. Lancez maintenant les tests unitaires **2 fois de suite**. Il y a une erreur ! Trouvez la raison de cette erreur.
</div>

Comme dans l'exercice précédent, l'architecture proposée ne respecte pas le principe d'inversion des dépendances, car la classe `ServiceUtilisateur` possède des dépendances vers des classes **concrètes** qui, de plus, ne sont pas injectées.

On se rend compte que cela pose un véritable problème au niveau des **tests unitaire**. Un test **unitaire**, comme son nom l'indique, teste le fonctionnement d'**une classe**, une **unité**. Or, quand on exécute les tests sur `ServiceUtilisateur`, les méthodes des dépendances concrètes utilisées sont aussi appelées ! Ce qui déclenche donc réellement l'enregistrement de l'utilisateur créé pour les tests dans la base de donnée, alors qu'on souhaitait simplement vérifier la méthode `creerUtilisateur`. Quand les tests sont exécutés une seconde fois, une erreur est détectée car l'utilisateur existe déjà.

Imaginez-vous dans un contexte plus concret, par exemple, dans un projet web : avec une telle conception, vos tests unitaires déclencheraient l'enregistrement d'utilisateurs de test sur votre base de données réelle ! Ce n'est pas envisageable.

Les tests unitaires **ne doivent pas dépendre de l'environnement de production**. Ils doivent pouvoir être lancé seulement à partir du code de la classe testée, sans dépendre de rien d'autre.

Vous avez sans doute constaté des messages **mail envoyé** lors de l'exécution des tests unitaires. Bien sûr, cela n'est pas vraiment le cas, mais de même, dans un cas concret, avec la conception actuelle, des mails seraient véritablement envoyés lors du test du programme (après création d'un utilisateur). C'est problématique.

Pour palier à cela, les testeurs mettent en place des **stubs**. Il s'agit de classes **bouchons** qui ne réalisent pas vraiment l'action demandée, ou alors pas de manière persistante. Aucun effet de bord est produit.

Plus tard, dans l'année, vous découvrirez les **mocks** qui permettent de créer de "fausses" classes destinées aux tests dont on peut facilement éditer les méthodes.

Ici, la classe `StockageUtilisateurMemoire` agit comme un **stub** qu'on peut utiliser pour les tests sans risque. Dans un environnement réel, on utiliserait un stockage avec une base de données dédiée aux tests, comme `SQLite`, qu'on viderait ensuite.

Cependant, comment faire pour garder le stockage avec fichier pur l'exécution "normale" du programme, et le stockage en mémoire pour les tests ? Devons-nous éditer le code source de la classe `ServiceUtilisateur` avant les tests, puis la remettre en ordre ensuite ? Bien sûr que non ! Il suffit de mettre en pratique le **principe d'inversion de dépendance** que vous connaissez.

<div class="exercise">

1. Refactorez les classes du paquetage **stockage** puis le code de `ServiceUtilisateur` afin de respecter le principe d'inversion des dépendances en utilisant des **abstractions** et surtout **l'injection de dépendances**.

2. Mettez à jour le code de `ControllerUtilisateur` afin que celui-ci utilise `ServiceUtilisateur` avec `StockageUtilisateurFichier`.

3. Mettez à jour le code de vos tests unitaires pour utiliser que l'objet de type `ServiceUtilisateur` utilisé dans les tests utilise `StockageUtilisateurMemoire`.

4. Vérifiez que votre programme fonctionne toujours correctement et vérifiez que vos tests unitaires passent plusieurs fois sans problèmes.

</div>

Il reste maintenant le problème des "mails envoyés" quand on exécute les tests. On aimerait également que plusieurs autres dépendances soient modulables dans le programme :

* L'envoi des mails. On veut pouvoir utiliser une autre classe et surtout une classe n'envoyant rien (un "Fake mailer") pour les tests.

* Le système de hachage du mot de passe. On veut pouvoir changer entre MD5 et SHA256. Et pour économiser du temps de calcul pour les tests, on voudrait un "Fake Hasher" qui ne hache rien et renvoie le mot de passe en clair.

* La classe `ServiceUtilisateur` elle-même, qui doit pouvoir être remplacée par autre chose dans le `ControllerUtilisateur`. Cela pourrait notamment être utile si on veut tester le controller indépendamment du code de `ServiceUtilisateur`.

<div class="exercise">

1. Refactorez votre code pour appliquer **l'inversion de dépendances** par rapport aux modules cités (mails, hasher, service utilisateur...). Il faudra créer de nouvelles interfaces et modifier des classes existantes (les hashers, le mailer...) et aussi créer deux classes de **stub** pour les tests : `FakeMailer` et `FakeHasher`.

2. Adaptez l'instanciation de `ServiceUtilisateur` dans vos tests unitaires et vérifiez qu'ils passent toujours. Vous ne devez plus constater aucun message "mail envoyé".

3. Vérifiez que le programme fonctionne toujours comme attendu.

4. Réalisez un **diagramme de classes de conception** de l'application (après refactoring donc) et comparez-le avec le premier diagramme que vous aviez réalisé.

5. Réalisez un **diagramme de séquence des interactions** du scénario nominal (le scénario où tout se passe bien et il n'y a pas d'erreur) du cas d'utilisation "Créer un nouvel utilisateur".

</div>

## Conclusion

Voilà, maintenant, vous savez tout des principes **SOLID** ! Vous êtes donc plus proche d'un ingénieur logiciel qu'un codeur.

Dorénavant, pour vos futurs projets (ou ceux actuels, comme la SAE) il faut systématiquement vous poser et réfléchir à la conception de votre programme **à long terme**. Il n'est jamais trop tard pour faire du **refactoring**, mais ne pas avoir besoin d'en faire en respectant une certaine qualité logicielle d'entrée de jeu est encore mieux.

Dans les prochains TPs, nous allons donc nous concentrer sur les **design patterns** (nous en avons déjà vu deux dans ce TP) qui permettront de vous donner des outils pour résoudre des problèmes de conception connus tout en mettant en facilitant le respect et la mise en ouvre les principes SOLID.