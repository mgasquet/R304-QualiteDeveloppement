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

Bref, dans ce cours, nous allons commencer par nous intéresser aux **principes SOLID** qui constituent la porte d'entrée vers un programme bien conçu. Nous allons également commencer à parler de **design patterns** mais nous allons les étudier plus en détail dans un prochain TP.

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

Ensuite, nous allons voir comme un des principes **SOLID** permet de régler cela.

<div class="exercise">

1. Pour commencer, forkez [le dépôt gitlab suivant]() en le plaçant dans le namespace `qualite-de-developpement/votrelogin`.

2. Clonez votre nouveau dépôt en local. Ouvre le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur.

</div>

Ce projet contient divers **paquetages** contenant le code de base pour chaque exercice que nous allons traiter.

### Principe de responsabilité unique (Single Responsability)

Pour mener à bien le déroulement d'une fonctionnalité, le programme va faire appel à diverses classes qui vont interagir entre elles (comme nous l'avons vu avec le DSI). Ces classes vont **traiter** la demande. Chaque classe possède la **responsabilité** d'effecteur une partie de ce traitement. 

Le principe de **responsabilité unique** indique qu'une classe ne doit pas posséder plus d'une responsabilité. Une responsabilité concerne des **opérations** (traitement, méthodes) de **même nature**. Nous avions déjà abordé cela plus tôt dans le cours sur les diagrammes de séquences en parlant d'architecture centralisée et distribuée. Nous avions vu qu'une **distribution** du traitement (et donc des responsabilités) était plus conseillée. C'est un peu le même principe ici.

**Robert C. Martin** dit : "Si une classe a plus d’une responsabilité, alors ces responsabilités deviennent couplées. Des modifications apportées à l’une des responsabilités peuvent porter atteinte ou inhiber la capacité de la classe de remplir les autres. Ce genre de couplage amène à des architectures fragiles qui dysfonctionnent de façon inattendue lorsqu’elles sont modifiées."

En bref, **une classe ne doit changer que pour une seule raison**. Si diverses raisons liées à des responsabilités différentes impliquent de modifier la classe, le principe de responsabilité unique n'est donc pas respecté.

Par exemple, considérons le code suivant :

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

  public String getSujet() {return sujet;}

  public void envoyerMail() {
    //Code complexe pour envoyer un mail...
  }

}

class Main {

  public static void main(String[]args) {
    Mail m = new Mail("Hello", new String[]{"test@example.com"}, "Hello world!");
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

  public String getSujet() {return sujet;}
}

class ServeurMail {

  public void envoyerMail(Email mail) {
      //Code complexe pour envoyer un mail...
  }

}

class Main {

  public static void main(String[]args) {
    Mail m = new Mail("Hello", new String[]{"test@example.com"}, "Hello world!");
    ServeurMail serveur = new ServeurMail();
    serveur.envoyerMail(m);
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

  * Pour la saisie, on veut plutôt utiliser un `Scanner` et la méthode `nextInt` au lieu d'un `BufferedReader` (il faudra enlever le **catch** de `IOException` et les `parseInt`).

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

3. Certaines applications aimeraient aussi utiliser simplement la classe `Rectangle` pour faire des calculs géométriques sans pour autant avoir besoin de l'afficher. A ce stade, vous avez sans doute clairement identifié que la classe `Rectangle` possède trop de responsabilités : la gestion de la forme géométrique et de ses propriétés (aire, peut-être plus tard périmètre, etc...) et l'affichage graphique. La classe peut changer si on ajoute de nouvelles opérations ou si l'affichage graphique change. Le principe de responsabilité unique n'est pas respecté.

4. L'idée est d'avoir deux classes : une première gérant la forme rectangle et l'autre permettant de l'afficher. Mais pour autant, il ne faut pas dupliquer de code ! Refactorez votre code en conséquence afin de mettre en place cette nouvelle conception.

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

1. Ouvrez le paquetage `oc1`. Dans ce projet, une classe `Animal` permet de gérer différents types d'animaux et leur cri, selon l'attribut `type` de l'objet.

2. On aimerait prendre en charge les chiens et les poules. Modifiez la classe `Animal` en conséquence et testez dans le `Main`.

3. Que se passe-t-il si vous essayez de créer un animal qui n'existe pas et d'afficher son cri ? Pour régler cela, ajoutez une clause `default` dans le `switch` affichant simplement "Animal inconnu".

</div>

Votre programme fonctionne ? C'est super ! Mais votre code serait-il encore lisible s'il y avait une centaine d'animaux...?

Continuons maintenant avec de petits monstres bien populaires : les **pokémons**.

Le programme sur lequel nous allons travailler fait combattre des pokémons dans un simulateur. Il y a différents types de pokémons (feu, eau, plante...) et chaque type de pokémon possède une attaque (le type feu attaque toujours avec lance-flamme). Bien sûr, cette analyse est un peu bizarre et ne correspond pas à la réalité du jeu (où chaque pokémon possède plusieurs attaques, et pas une attaque précise selon le type) mais nous allons l'utiliser ainsi pour ne pas plus compliquer l'exercice.

En plus de l'attaque, le type de pokémon est aussi lié à un nombre de dégâts. Par exemple, le type **feu** fait toujours 60 dégâts et le type plante entre 40 et 80 dégâts.

Pour modéliser tout cela, le développeur a choisi de mettre en place un héritage pour gérer les différents types. Pour savoir quelle attaque annoncer dans le simulateur et quels dégâts infliger, il a besoin de vérifier quel est le pokémon qui attaque.

De même, dans la classe `Pokemon`, pour que le pokémon puisse se présenter avec son `type` (dans la méthode `toString`), la classe vérifie de quel type concret elle est.

<div class="exercise">

1. Ouvrez le paquetage `oc2`. Explorez les classes. Etudiez notamment la classe `SimulateurCombat`.

2. On souhaite ajouter un nouveau type de pokémon : le pokémon type **électricité**. Son attaque est **Eclair** et il fait entre 20 et 100 dégâts. Faites en sorte de prendre en charge ce nouveau type.

3. On souhaite ajouter un nouveau type de pokémon : le pokémon type **psy**. Son attaque est **Choc mental** et il fait précisément 60 dégâts. Faites en sorte de prendre en charge ce nouveau type.

4. Modifiez le `Main` pour faire combattre un pokémon possédant le type **électrique** contre un pokémon possédant le type **psy**.

5. Ajoutez encore un nouveau pokémon (avec le type, l'attaque et les dégats de votre choix...)

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

L'ajout d'une nouvelle figure géométrique (par exemple, un carré) nécessite la modification de la classe `FigureGeometrique` et de la méthode `dessiner`. Le principe ouvert/fermé n'est pas respecté. De plus, un bug (à l'exécution) se produira si on essaie de traiter une figure géométrique qui n'existe pas!

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

L'ajout d'une nouvelle figure nécessite donc simplement l'ajout d'une nouvelle classe correspondant à la figure et l'implémentation des méthodes requises (ici, dessiner la figure). Aucune autre classe est modifiée. L'extension est possible (ajout de nouvelles figures) sans modification du code source déjà présent. Par ailleurs, il est maintenant impossible de créer des figures géométriques qui n'existent pas au préalable dans notre programme (c'est une bonne chose !).

Comme `FigureGeometrique` ne contient aucun attribut (qui pourraient être communs à toutes les figures) et définit simplement des méthodes `abstraites`, il serait plus judicieux d'utiliser une `interface` ! Par contre, si la classe abstraite possède des attributs et/ou définit un bout de comportement commun à toutes les sous-classes, on utilisera bien une classe abstraite.

Ceci devrait vous permettre de refactorer le code du paquetage `oc1` (animaux). Pour `oc2` (pokémons) cela peut sembler un peu plus dur (car il y a déjà un système d'héritage), mais cela ne devrait pas être trop dur à adapter.

<div class="exercise">

1. Refactorez le code du paquetage `oc1` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne. Il ne doit plus être possible de gérer des animaux inconnus, et c'est bien normal !

2. Réaliser un diagramme de classes de l'application du paquetage `oc2` (avant refactoring). Indiquez bien les **dépendances**.

3. Refactorez le code du paquetage `oc2` afin de respecter le principe ouvert/fermé. Adaptez le `Main` en conséquence et vérifiez que tout fonctionne.

4. Réaliser un diagramme de classes de l'application du paquetage `oc2` (après refactoring). Indiquez bien les **dépendances**.

</div>

En comparant vos deux diagrammes de classes, on peut facilement voir ce qui différencie la "mauvaise" conception de la "bonne" : dans votre premier diagramme, les classes `SimulateurCombat` et `Pokemon` ont autant de dépendances qu'il y a de sous-classes de type de pokémon. S'il y a 30 types de pokémons, `SimulateurCombat` et `Pokemon` auront chacune 30 dépendances. Après refactoring, ces dépendances disparaissent. `SimulateurCombat` est seulement dépendant de `Pokemon`.

Dans un code de qualité **les abstractions ne dépendent pas des implémentations**. En d'autres termes, une superclasse ne devrait pas dépendre de ses sous-classes. Seules les sous-classes peuvent dépendre de leurs parents (et on verra que parfois, là aussi il faut faire attention qu'on utilise l'héritage.). Sur votre premier diagramme, il est clair que ce principe n'est pas respecté, car `Pokemon` dépendait de ses différentes sous-classes, ce qui n'est plus les cas sur le deuxième diagramme.



### Principe de substitution de Liskov (Liskov substitution)



### Principe de ségrégation des interfaces (Interface segregation)

### Principe d'inversion des dépendances (Dependency inversion)



