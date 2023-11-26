---
title: TP4 &ndash; Les design patterns créateurs
subtitle: Design Patterns, Qualité, SOLID, Abstraction, Dépendances
layout: tutorial
lang: fr
---

## Introduction

Quand on parle de **design patterns** on fait généralement référence aux patterns dits **GoF** (Gang of Four) présentés dans le livre **Design Patterns: Elements of Reusable Object-Oriented Software** qui est une référence dans le monde de l'ingénérie logicielle. Le **Gang of Four** fait référence au quatre auteurs de ce livre : **Erich Gamma**, **Richard Helm**, **Ralph Johnson** et **John Vlissides**.

Pour rappel, un **design pattern** est une solution ré-utilisable et adaptable vis-à-vis d'un problème de conception logicielle assez récurent. Un pattern est généralement présenté via un diagramme de classes de conception et un exemple d'implémentation. Un pattern a pour but est d'être applicable et adaptable à n'importe quel projet ou contexte.

Il existe d'autres types de design patterns (par exemple, les patterns GRASP) mais les plus connus et les plus utilisés sont ceux du **GoF** que nous allons explorer dans ce cours. Tous ces **patterns** permettent de renforcer l'application des principes **SOLID**.

Les design patterns **GoF** se divisent en trois catégories :

* Les patterns **créateurs** : concernent la **création d'objet**. Ils permettent de mettre en place des solutions et des structures pour permettre de contrôler l'instanciation des objets du programme. Cela permet de réduire les dépendances de type "create".

* Les patterns **stucturaux** : permettent d'organiser les objets en faisant notamment de l'abstraction pour augmenter la modularité du programme et l'ajout de nouvelles fonctionnalités (principe ouvert/fermé).

* Les patterns **comportementaux** : permettent d'organiser la collaboration et les communications entre les objets du programme afin de distribuer efficacement les **responsabilités**.

Dans le TP précédent, vous avez déjà vu un pattern **strucural** (Décorateur) et un pattern **comportemental** (Stratégie). Dans le premier TP **git**, le programme utilisait un pattern **créateur** (fabrique) et un autre pattern **comportemental** (commande). Bref, les design patterns sont partout !

Dans ce TP, nous allons voir **tous les patterns créateurs** et allons les mettre en application : **singleton**, **builder**, **prototype**, **fabrique** et enfin **fabrique abstraite**.

Nous verrons aussi un autre pattern **strucutral** appelé **adaptateur**. En fait, nous allons voir que beaucoup de ces patterns peuvent (et doivent) être combinés dans un projet plus large. Nous traitons souvent des problèmes "simple" avec quelques classes pour illustrer le fonctionnement d'un pattern, mais sur un projet plus large, il est tout à fait naturel de faire travailler en concert les différents patterns.

<div class="exercise">

1. Pour commencer, forkez [le dépôt gitlab suivant](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/tp4) en le plaçant dans le namespace `qualite-de-developpement-semestre-3/etu/votrelogin`.

2. Clonez votre nouveau dépôt en local. Ouvre le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur.

3. Pendant ce TP, on vous demandera de créer des **diagrammes UML** de conception (classes, séquences). Vous déposerez vos diagrammes dans un dossier `uml` (en image ou bien avec le fichier du projet **.mdj** si vous utilisez **StarUML**) que vous devrez créer à la racine du dépôt.

4. À la fin de chaque séance, n'oubliez pas de faire un **push** vers votre dépôt distant sur **Gitlab**.

</div>

## Le pattern Singleton

L'idée du pattern **Singleton** est très simple : on souhaite **qu'il n'existe qu'une seule instance d'une classe** donnée dans tout le programme. Dès qu'un autre objet souhaite utiliser cette classe, il utilise l'instance "globale" définie dans l'application et **ne doit pas pouvoir en instancier lui-même** (l'utilisation de **new** doit être bloqué en dehors de la classe). L'instance globale doit être accessible à n'improte quel endroit de l'appliation.

Pour faire cela, il existe deux solutions :

* Utilisation d'une **classe statique** (toutes les méthodes et attributs statiques). C'est une solution à éviter, nous verrons pourquoi par la suite.

* Utilisation du pattern **Singleton**.

Voyons un exemple :

```java

public class Service {

  public void actionA() {
    ...
  }

  public void actionB() {
    ...
  }

  public int calcul() {
    ...
  }

}

public class Client {

  public static void main(String[]args) {
    Service s = new Service();
    s.actionA();
    s.actionB();
    ClasseExemple c = new ClasseExemple();
    c.operation();
  }

}

public class ClasseExemple {

  private Service service;

  private int data;

  public ClasseExemple() {
    service = new Service();
    data = service.calcul();
  }

  public void operation() {
    service.actionB();
  }

}

```

Dans cet exemple, nous voyons qu'il y a au moins deux instances de la classe **Service** qui sont générées. Une dans `Client` et une autre dans `ClasseExemple`. S'il n'y a aucun intérêt à avoir plusieurs instances de la classe `Service`, nous pouvons alors la transformer en **Singleton** afin que toutes les classes qui souhaitent utiliser passent par la même instance.

Pour cela, il y a trois changements à réaliser dans la classe qu'on veut transformer en **Sungleton** :

* Changer la **visibilité** du ou des **constructeurs** de la classe en **privé**. Ainsi, plus aucune autre entité pourra créer des instances de cette classe (hormis la classe elle-même).

* Dans la classe, créer un attribut **privé** et **statique** (un attribut de classe : `static` en Java) du même type que la classe. Cet attribut est généralement nommé `INSTANCE` (en majuscules).

* Enfin, créer une méthode **publique** et **statique** qui retourne un objet du type de la classe. Cette méthode est nommée `getInstance`. Tout d'abord, elle regarde si la variable `INSTANCE` a été initialisée ou non (si elle est `null` ou non). Si elle n'est pas encore initialisée, la classe l'instancie. Dans tous les cas, à la fin, on retourne `INSTANCE`.

Par la suite, toutes les entités qui souhaitent récupérer une instance de cette classe utilisent la méthode `getInstance` qui peut directement être appelée sur la classe car **statique**. Lors du premier accès, l"instance "globale" sera alors initialisée.

Dans un environnement **multi-threadé** (exécution de plusieurs processus en parallèle, comme des `Runnable` ou des `Thread` en Java) il faut faire attention à ce que la méthode `getInstance` ne soit pas appelée en même temps par deux **Threads** différents. Pour régler cela en java, il suffit d'ajouter le mot clé `synchronized` lors de la définition de la méthode.

Regardons ce que cela donne :

```java

public class Service {

  private static Service INSTANCE;

  //Interdit l'instanciation en dehors de la classe Service
  private Service() {}

  //On appelle systématiquement cette méthode pour récupérer l'instance "globale"
  public synchronized static Service getInstance() {
    if(INSTANCE == NULL) {
      INSTANCE = new Service();
    }
    return INSTANCE;
  }

  public void actionA() {
    ...
  }

  public void actionB() {
    ...
  }

  public int calcul() {
    ...
  }

}

public class Client {

  public static void main(String[]args) {
    Service s = Service.getInstance();
    s.actionA();
    s.actionB();
    ClasseExemple c = new ClasseExemple();
    c.operation();
  }

}

public class ClasseExemple {

  private int data;

  public ClasseExemple() {
    data = Service.getInstance().calcul();
  }

  public void operation() {
    Service.getInstance().actionB();
  }

}

```

Ici, on a la garantie que la classe `Client` et la classe `ClasseExemple` utilisent la même instance de `Service`.

Ce pattern s'avère très utile quand nous avons une classe (généralement un service) que plusieurs classes doivent utiliser et qu'il n'y a pas besoin d'instancier celui-ci à chaque fois (notamment si son paramétrage est complexe). Cependant, nous verrons aussi qu'il ne faut pas en abuser et limiter son utilisation, car cela peut engendrer certains problèmes, notamment au niveau des tests unitaires.

### Mise en application

Commençons par une mise en application très simple.

<div class="exercise">

1. Ouvrez le paquetage `singleton1`. Cette petite application dispose d'une classe `Calculatrice` permettant de réaliser des opérations de gérer un historique de résultat afin de pouvoir revenir en arrière.

2. La classe `Calculatrice` est un service qui doit pouvoir être utilisé par toutes les classes de l'application (il n'y en a qu'une seule pour le moment, mais le programme va grandir dans le futur). On souhaite que pour réaliser des opérations, toutes les classes utilisent la même instance de la classe `Calculatrice`. Appliquez le pattern **Singleton** afin de transformer la classe `Calculatrice` en **Singleton**. 

3. Normalement, si vous avez bien traité la question précédente, vous allez avoir des erreurs dans `Client`. Adaptez le code de cette classe pour que tout fonctionne.

</div>

### Dépendance commune

Un cas un peu plus concret qui montre l'intérêt d'utiliser un `Singleton` est dans le contexte où deux objets différents dépendent de l'état d'une classe. Une classe `A` modifie l'état de `Service` et une classe `B` a besoin de connaître les modifications qu'a effectuées `A` dans `Service` pour fonctionner. Les deux classes `A` et `B` doivent alors dépendre de la même instance de `Service` !

Aussi, imaginons une classe d'accès à une base de données : celle-ci initialise une connexion vers la base qui peut prendre plusieurs secondes. Il serait inconscient d'instancier cette classe à chaque endroit où on en a besoin (cela dégraderait les performances !). On va plutôt utiliser un **Singleton**. C'est le cas de la classe `SQLUtils` que vous avez codé dans le TP "JDBC / Hibernate" en cours de base de données.

<div class="exercise">

1. Ouvrez le paquetage `singleton2`. Cette application permet de créer des animaux avec un nom et une vitesse, de les stocker dans la mémoire et de les lire.

2. Testez l'application. Créez plusieurs animaux puis tentez de les lire. Quels sont les deux problèmes que vous constatez ?

3. Réglez cela en appliquant le pattern **Singleton** sur la classe `StockageAnimaux` et en adaptant votre code.

4. Vérifiez que tout fonctionne et que les bugs sont bien résolus.

5. Le principe SOLID `D` (dependency inversion) est-il respecté sur les classes `CreationAnimal` et `LectureAnimaux` ? Si ce n'est pas le cas, réfactorez votre code.

</div>

### Classe statique VS Singleton

En introduction de cette section, nous avions évoqué le fait d'utiliser une **classe statique** pour obtenir un résultat similaire au singleton. Une classe statique est une classe où il n'y a que des attributs et des méthodes **de classe** qui apprtiennent donc à la classe et pas à une instance en particulier. Ainsi, tous les objets qui manipulent cette classe utilisent la même "entité" (en fait, il n'y a juste pas d'instance).

Par exemple, on pourrait remplacer ce **Singleton** :

```java
public class Service {

  private String data;

  private static Service INSTANCE;

  private Service() {}

  public synchronized static Service getInstance() {
    if(INSTANCE == NULL) {
      INSTANCE = new Service();
    }
    return INSTANCE;
  }

  public void action() {
    ...
  }

  public String getData() {
    return data;
  }

  public String setData(String data) {
    this.data = data;
  }

}

class Main {

  public static void main(String[]args) {
    Service service = Service.getInstance();
    service.setData("test");
    System.out.println(service.getData())
  }

}
```

Par cela :

```java
public class Service {

  private static String data;

  static {
    //Opérations à réaliser lors de l'initialisation de la classe
  }

  public static void action() {
    ...
  }

  public static String getData() {
    return data;
  }

  public static String setData(String data) {
    Service.data = data;
  }
}

class Main {

  public static void main(String[]args) {
    Service.setData("test");
    System.out.println(Service.getData())
  }

}
```

Si cette méthode pourrait paraître plus "facile" à mettre en place et à utiliser (pas de `getInstance`, etc...) c'est généralement une **mauvaise idée**. Nous allons tout de suite voir pourquoi avec le prochain exercice. 

<div class="exercise">

1. Ouvrez le paquetage `singleton3`. Cette application permet de simuler des services de création d'utilisateurs et de gestion de commandes. Dans une application concrète, ces deux services sont susceptibles d'envoyer des mails. Testez un peu l'application. Aussi, deux classes de tests sont disponibles dans le dossier `java/singleton3`.

2. Il semble inutile d'instancier la classe `ServiceMail` à chaque fois. Cette fois-ci, au lieu d'utiliser un `Singleton`, nous allons transformer `ServiceMail` en **classe statique**. Faites ce changement et adaptez le code dans les classes `ServiceUtilisateur` et `ServiceCommande`.

3. Si ce n'est pas déjà fait, lancez les tests unitaires des classes `ServiceUtilisateurTest` et `ServiceCommandeTest`. On voit bien quand dans un contexte réel, les mails seraient vraiment envoyés à chaque test ! C'est un problème.

4. Nous avions apporté une solution à ce même problème dans le TP précédent en utilisant **l'injection de dépendances**. Au lieu d'instancier directement le service "mail" dans la classe qui en a besoin, nous l'avions **injecté** via le constructeur. L'idée serait alors de :

  * Créer une interface `ServiceMailInterface` avec la signature la méthode `envoyerMail`.

  * Faire implémenter cette interface à `ServiceMail`.

  * Créer une classe `FakeMailer` qui implémente `ServiceMailInterface` et qui ne fait rien (ou quelque chose relatif aux tests) dans `envoyerMail`.

  * Faire en sorte que `ServiceUtilisateur` et `ServiceCommande` possèdent un attribut de type `ServiceMailInterface` qui sera injecté via le constructeur et l'utilisent à la place de l'instance concrète `ServiceMail`.

  * Injecter le `ServiceMail` quand on instancie `ServiceUtilisateur` et `ServiceCommande` dans l'application.

  * Injecter le `FakeServiceMail` quand on instancie `ServiceUtilisateur` et `ServiceCommande` dans nos tests unitaires.

  Un tel refactoring est-il possible ici...? Essayez de réfactorer et relevez les problèmes que vous rencontrez.

</div>

En essayant de refactorer, vous avez dû rencontrer divers problèmes :

* Une `interface` (dans la plupart des langages) ne peut pas posséder de signature de méthode de classes (`static`).

* Il est impossible d'injecter la classe statique comme paramètre d'un constructeur ! Et oui, une classe n'est pas un objet et une instance ! Elle ne peut donc pas être passée en paramètre.

Bref, l'utilisation d'une **classe statique** rend les services qui l'utilisent étroitement dépendant de la classe. Ce qui rend l'application intestable car ces services ne peuvent pas être testés indépendamment des services concrets qui sont utilisés dans l'application. On ne peut pas remplacer le service par un "faux" service utilisé pour les tests unitaires (un **stub** ou un **mock**).

L'utilisation d'un **Singleton** résout tous ces problèmes :

* L'instance de la classe est une véritable instance, un objet. Il peut donc être passé en paramètre dans un constructeur, par exemple.

* La classe peut hériter, implémenter des interfaces...

```java
public interface Service {

  void action();

}


public class ServiceConcret implements Service {

  private static ServiceConcret INSTANCE;

  private ServiceConcret() {}

  public static ServiceConcret getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new ServiceConcret();
    }
    return INSTANCE;
  }

  public void action() {
    ...
  }

}

public class Exemple {

  private Service service;

  public Exemple(Service service) {
    this.service = service;
  }

}

class Main {

  public static void main(String[]args) {
    Exemple ex = new Exemple(ServiceConcret.getInstance());
  }

}
```

<div class="exercise">

1. À la place d'une classe statique, utilisez le pattern `Singleton` pour refactorer la classe `ServiceMailer`.

2. Comme expliqué dans l'exercice précédent, introduisez une interface `ServiceMailerInterface` pour abstraite ce service.

3. Créez un nouveau service `FakeServiceMail` implémentant aussi `ServiceMailerInterface` mais qui ne fait rien dans sa méthode `envoyerMail`. Ce service sera aussi un singleton.

4. Refactorez `ServiceUtilisateur` et `ServiceCommande` pour injecter la dépendance nécessaire au lieu de directement récupérer l'instance du singleton dans la classe via `getInstance`.

5. Adaptez le `Main` afin que le service concret utilisé soit `ServiceMailer` dans les deux autres services.

6. Adaptez aussi les tests pour utiliser `FakeServiceMail`. Vérifiez que l'exécution des tests ne déclenche plus l'envoi (fictif) de mails.

</div>

### Avertissement

Vous maîtrisez maintenant le pattern **Singleton**, mais vous devez être très précautionneux quant à son utilisation. En conclusion du dernier TP, vous étiez invité à aller jeter un coup d'œil aux [principes STUPID](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming) qui sont un ensemble de mauvaises pratiques en conception logicielle. Regardez à quoi correspond le `S`.

En effet, l'abus de **singletons** est dangereux pour la santé ! (du logiciel...). Il présente une solution qui semble plutôt efficace à un problème assez récurent : la gestion des dépendances vers les services de l'application. À tel point qu'on retrouve parfois dans certains projets beaucoup trop de singletons. 

Mais pourquoi est-il déconseillé d'utiliser "trop" de singletons :

* Il n'est pas possible de passer des paramètres à un singleton pour son initialisation (comme un objet classique) car c'est lui-même qui se construit, cependant, on peut éventuellement mettre en place un fichier de configuration que le singleton ira lire lors de son initialisation.

* Il est très difficile (voir impossible) de **tester** un singleton ! Comme le constructeur est **privé** et qu'il n'y a qu'une instance de l'objet dans l'application, on ne peut tester que cette instance. On ne peut pas instancier de nouveaux objets de cette classe pendant les tests unitaires.

* Il existe des solutions bien meilleures pour gérer les dépendances de l'application de manière plus flexibles tout en conservant la possibilité de réaliser des tests unitaires : les fabriques astraites (dont nous allons bientôt parler) et le conteneur d'inversion de contrôle (conteneur IoC, dont nous parlerons au prochain TP).

Attention, tout cela ne veut pas dire que le singleton est inutile ! Seulement qu'il ne doit pas être utilisé pour tout et n'importe quoi. Il faut également se poser la question "est-ce que cette instance doit pouvoir être accessible par tout le monde" ?

On va notamment éviter d'appliquer **singletons** sur des classes qui contiennent du **code métier** relatif à des règles de notre application et que nous allons surement vouloir tester. A l'inverse, nous allons bientôt parler du pattern **fabrique** et **fabrique abstraite**. Les classes produites par ces applications ont pour but de créer et/ou fournir des objets (des dépendances). Ces classes doivent pouvoir être accessibles par toute l'application et on ne va pas spécialement les tester (pas de code métier). Il est alors judicieux d'appliquer **Singleton** sur ces classes.

Certains membres du **GoF** regrettent un peu la surutilisation maladroite de **Singleton** par certains développeurs. Ces développeurs ont l'illusion de coder proprement, car ils utilisent un design pattern, mais c'est tout l'inverse. Appliquer les design patterns ne veut pas forcément dire que votre conception est de qualité. Il faut savoir quand et comment les utiliser !

## Le pattern Builder

Le design pattern **Builder** est un pattern que vous avez déjà abordé l'année dernière (sans vraiment le nommer) en cours de développement orienté objets. Cela devrait donc vous rapeller quelques souvenirs !

Ce pattern permet de résoudre le problème de création d'un objet qui a beaucoup d'options. Voyons donc cela avec un petit exercice.

<div class="exercise">

1. Ouvrez le paquetage `builder1`. Dans cette application, nous voulons construire des **burgers**. Dans le restaurant, le client peut composer son burger. Un **Burger** est obligatoirement composé d'un nom (donné par le client) et d'un type de pain (oui, s'il veut, un client peut avoir un burger juste avec du pain). Le client peut ensuite décider d'ajouter une viande, ou des tomates, ou les deux.

  À ce stade, il y a donc quatre types de burger possibles (même si les types de pains et de viandes diffèrent) :

  * Un burger avec du pain.

  * Un burger avec du pain et une viande.

  * Un burger avec du pain et des tomates.

  * Un burger avec du pain, de la viande et des tomates.

  Pour gérer tout cela, nous avons donc créé une classe `Burger` avec quatre constructeurs, pour gérer chaque cas. Cela fonctionne.

2. Le restaurant ajoute de nouvelles **options** : 

  * L'ajout d'un certain type de fromage dans le burger.

  * L'ajout de salade dans le burger.

  Le fromage sera géré par un attribut `typeFromage` de type `Fromage` dans la classe `Burger` et la salade par un **booléen** (comme pour les tomates).

  Ajoutez ces nouveaux attributs à la classe `Burger`.

3. Maintenant que nous avons ajouté ces deux options, quels sont tous les types de burgers qu'il est possible de créer ? Ajoutez de nouveaux **constructeurs** pour gérer tous les cas... Si vous bloquez à un moment, c'est normal ! Comprenez-vous pourquoi il n'est pas possible de poursuivre la conception actuelle...?

</div>

En effet, rien que le fait de pouvoir avoir des burgers avec du pain et des tomates et des bugers avec du pain et de la salade empeêche de créer les constructeurs adéquats :

```java
public class Burger {

  ...

  public Burger(String nom, PainBurger typePain, boolean tomates) {
      this(nom, typePain);
      this.tomates = tomates;
  }

  //Erreur !
  public Burger(String nom, PainBurger typePain, boolean salade) {
      this(nom, typePain);
      this.salade = salade;
  }

}
```

Dans l'exemple précédent, les deux constructeurs entre en collision car ils ont la même signature `Burger(String, PainBurger, boolean)`.

Pour palier à cela, on pourrait mettre en place la solution bancale suivante :

* Instancier un **Burger** seulement avec son nom et son type de pain.

* Utiliser des **setters** pour définir le fait d'ajouter de la salade ou des tomates.

Cette solution est mauvaise, car on part du principe que tous les **setters** nécessaires sont accessibles publiquement. Ce n'est pas forcément le cas et dans le cas du `Burger`, seul le **setter** du `nom` est accessible. On a décidé qu'une fois créé, on ne doit pas pouvoir modifier les ingrédients du Burger, mais qu'on peut le renommer. Il n'est donc pas possible d'ajouter des **settters** !

Le pattern **builder** permet de résoudre ce problème avec une classe qui permet de contrôler comment l'objet est créé. Cette classe est généralement placée **à l'intérieur de la classe à construire** même si on retrouve des versions et des variantes avec la classe "Builder" comme classe externe indépendante.

Cette classe possède :

* Les mêmes attributs que la classe cible (du moins ceux qu'on peut préciser lors de l'initialisation de l'objet).

* Un constructeur qui prend en paramètre tous les attributs qu'on doit obligatoirement initialiser lorsqu'on créé l'objet cible.

* Pour chaque option, une méthode `WithNomOption(valeur)` qui permet d'ajouter une option (initialise l'attribut correspondant dans la classe du Builder). Cette méthode renvoie `this` (donc, l'instance du Builder) afin qu'on puisse enchaîner les appels des méthodes `with` pour ajouter d'autres options.

* Une méthode `build` qui permet d'instancier l'objet cible :

  * Soit en instanciant l'objet puis en modifiant ses attributs : cela est possible même si les attributs de la classe cible sont privés, car la classe `Builder` est définie à l'intérieur de la classe cible !

  * Soit en définissant un constructeur prenant en paramètre un Builder dans la classe cible. L'instance se construit en allant chercher les données dans l'instance du Builder. On peut notamment ajouter des `getters` au Builder dans ce cas-là. Cette méthode a l'avantage d'aussi être compatible avec une classe Builder définie à l'extérieur de la classe.

Si le builder est **interne**, il faut aussi éliminer les constructeurs "classiques" et le constructeur "vide" de la classe (par exemple, en les rendant privés).

Voyons un exemple :

```java
class Exemple {

  //Obligatoire
  private String data;
  private int compteur;

  //Options
  private String optionA;
  private boolean optionB;
  private double optionC;
  private boolean optionD;

  public void setData(String data) {
    this.data = data;
  }

  public void setOptionB(boolean optionB) {
    this.optionB = optionB;
  }

}
```

Dans cette classe, il y a deux attributs qu'il est obligatoire d'initialiser : `data` et `compteur`. Ensuite, il y a diverses options. L'attribut `data` et `optionB` peuvent être modifiés, mais pas le reste. Pour contrôler la construction d'instances de cette classe nous pouvons donc mettre en place un `Builder` :

```java
class Exemple {

  //Obligatoire
  private String data;
  private int compteur;

  //Options
  private String optionA;
  private boolean optionB;
  private double optionC;
  private boolean optionD;

  private Exemple() {}

  public void setData(String data) {
    this.data = data;
  }

  public void setOptionB(boolean optionB) {
    this.optionB = optionB;
  }

  public static class Builder {
    private String data;
    private int compteur;
    private String optionA;
    private boolean optionB;
    private double optionC;
    private boolean optionD;

    public Builder(String data, int compteur) {
      this.data = data;
      this.compteur = compteur;
    }

    public Builder withOptionA(String optionA) {
      this.optionA = optionA;
      return this;
    }

    //Par défaut, un booléen est à false, donc ajouter cet option signfit passer la valeur à true.
    // Mais on pourrait éventuellement aussi autoriser un paramètre ici.
    public Builder withOptionB() {
      this.optionB = true;
      return this;
    }

    public Builder withOptionC(double optionC) {
      this.optionC = optionC;
      return this;
    }

    public Builder withOptionD() {
      this.optionD = true;
      return this;
    }

    public Exemple build() {
      Exemple exemple = new Exemple();
      exemple.data = data;
      exemple.compteur = compteur;
      exemple.optionA = optionA;
      exemple.optionB = optionB;
      exemple.optionC = optionC;
      exemple.optionD = optionD;
      return exemple;
    }
  }

}

public class Main {

  public static void main(String[]args) {
    Builder builderEx1 = new Exemple.Builder("test", 5);
    Exemple ex1 = builderEx1.withOptionA("truc").withOptionD().build();

    Builder builderEx2 = new Exemple.Builder("test2", 50);
    Exemple ex2 = builderEx2.withOptionB().withOptionC(10.05)..withOptionD().build();
  }

}
```

Comme annoncé précédemment, on pourrait adapter le `Builder` pour le passer en paramètre au constructeur à la place :

```java
class Exemple {

  ...

  private Exemple(Builder builder) {
      exemple.data = builder.data;
      exemple.compteur = builder.getCompteur();
      exemple.optionA = builder.getOptionA();;
      exemple.optionB = builder.getOptionB();
      exemple.optionC = builder.getOptionC();
      exemple.optionD = builder.getOptionD();
  }

  ...

  public static class Builder {
    
    ...

    //Des getters ici...

    public Exemple build() {
      Exemple exemple = new Exemple(this);
      return exemple;
    }
  }

}
```

<div class="exercise">

1. Refactorez le code de l'application de burgers pour mettre en place un `Builder`. Adaptez le `Main` en conséquence.

2. Vérifiez que vous pouvez bien ajouter les burgers suivants :

  * Burger avec du pain moisi, avec de la salade et du poulet.

  * Burger avec du pain sésames, avec des tomates, de la salade.

  * Burger avec du pain classique, avec de la salade, des tomates, de la viande de bœuf et du cheddar.

</div>

## Le pattern Prototype


## Le pattern Fabrique

Le pattern **fabrique** va permettre de centraliser l'instanciation d'une famille de classes dans une classe spécialisée. Les classes ayant besoin d'instancier des objets de cette famille ne vont plus faire elle-même des **new** mais votn plutôt passer par la fabrique.

La fabrique connaît les différents types concrets à instancier, mais elle va généralement déclarer renvoyer des abstractions (classes abstraites/interfaces) pour que les classes ayant besoin de créer des objets ne dépendent plus du tout d'un objet concret, mais plutôt de son abstraction. Ainsi, l'impact du changement diminue (si on veut changer la classe concrète utilisée) ce qui renforce notamment le principe ouvert/fermé.

Dans une application où certaines classes sont instanciées à différents endroits, il est donc plutôt judicieux d'utiliser une fabrique pour réduire les dépendances de type "create". Seule la fabrique est dépendante des objets concrets et les autres classes sont seulement dépendante de la fabrique (et des abstractions).

Voyons l'application de **Fabrique** sur un exemple :
```java

public interface FigureGeometrique {

  int getAire();

  void afficherFigure();

}

public class CarreSimple implements FigureGeometrique {

  private int tailleCote;

  public CarreSimple(int tailleCote) {
    this.tailleCote = tailleCote;
  }

  @Override
  public int getAire() {
    return tailleCote * tailleCote;
  }

  @Override
  public void afficherFigure() {
    //Affichage simple en console...
  }

}

public class CarreGraphique implements FigureGeometrique {

  //Composition
  private CarreSimple carre;

  public CarreGraphique(int tailleCote) {
    carre = new CarreSimple(tailleCote);
  }

  @Override
  public int getAire() {
    return carre.getAire();
  }

  @Override
  public void afficherFigure() {
    //Affichage grpahique du carré...
  }

}

public class CercleSimple implements FigureGeometrique {

  private int rayon;

  public CercleSimple(int rayon) {
    this.rayon = rayon;
  }

  @Override
  public int getAire() {
    return Math.PI * Math.pow(rayon, 2);
  }

  @Override
  public void afficherFigure() {
    //Affichage simple en console...
  }

}

public class CercleGraphique implements FigureGeometrique {

  //Composition
  private Cercle cercle;

  public CercleSimple(int rayon) {
    cercle = new CercleSimple(rayon);
  }

  @Override
  public int getAire() {
    return cercle.getAire();
  }

  @Override
  public void afficherFigure() {
    //Affichage grpahique du cercle...
  }

}

public class ServiceA {

  public void action() {
    FigureGeometrique c = new Cercle(10);
    c.afficherFigure();
  }

}

public class ServiceB {

  public void action() {
    FigureGeometrique c1 = new Carre(10);
    c1.afficherFigure();

    FigureGeometrique c2 = new Cercle(5);
    c2.afficherFigure();

    Sytem.out.println(c2.getAire());
  }

}
```

Dans cet exemple, `ServiceA` et `ServiceB` sont fortement dépendants de `CarreSimple` et `CercleSimple`. Et on ne peut pas simplement injecter les dépendances, car ces services ont besoin d'instancier ces classes dans leurs méthodes ! Si nous devons changer pour utiliser des `CarreGraphique` et des `CercleGraphique`, il faut modifier ces deux classes !

Nous pouvons mettre en place une **fabrique** pour règle ce problème :

```java

public class FigureGeometriqueFactory {

  public FigureGeometrique creerCarre(int tailleCote) {
    return new CarreSimple(tailleCote);
  }

  public FigureGeometrique creerCercle(int rayon) {
    return new CercleSimple(rayon);
  }

}

public class ServiceA {

  private FigureGeometriqueFactory factory = new FigureGeometriqueFactory();

  public void action() {
    FigureGeometrique c = factory.creerCercle(10);
    c.afficherFigure();
  }

}

public class ServiceB {

  private FigureGeometriqueFactory factory = new FigureGeometriqueFactory();

  public void action() {
    FigureGeometrique c1 = factory.creerCarre(10);
    c1.afficherFigure();

    FigureGeometrique c2 = factory.creerCercle(5);
    c2.afficherFigure();

    Sytem.out.println(c2.getAire());
  }

}

```

Maintenant, si nous voulons utiliser `CarreGraphique` et `CercleGraphique` à la place, nous n'avons à faire ce changement que dans **une seule classe** : `FigureGeometriqueFactory` ! Avec le pattern **fabrique abstraite** nous pourrons encore plus facilement changer de "familles".

Ici, il semble judicieux de transformer `FigureGeometriqueFactory` en **Singleton** et de l'injecter comme dépendance pour éviter que chaque service instancie une version de la fabrique :

```java

public class FigureGeometriqueFactory {

  private static FigureGeometriqueFactory INSTANCE;

  private FigureGeometriqueFactory() {}

  public synchronized static FigureGeometriqueFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new FigureGeometriqueFactory();
    }
    return INSTANCE;
  }

  public FigureGeometrique creerCarre(int tailleCote) {
    return new CarreSimple(tailleCote);
  }

  public FigureGeometrique creerCercle(int rayon) {
    return new CercleSimple(rayon);
  }

}

public class ServiceA {

  private FigureGeometriqueFactory factory;

  public ServiceA(FigureGeometriqueFactory factory) {
    this.factory = factory;
  }

  //...

}

public class ServiceB {

  private FigureGeometriqueFactory factory;

  public ServiceB(FigureGeometriqueFactory factory) {
    this.factory = factory;
  }

  //...

}

public class Main {

  public static void main(String[]args) {
    ServiceA s1 = new ServiceA(FigureGeometriqueFactory.getInstance());
    ServiceB s2 = new ServiceB(FigureGeometriqueFactory.getInstance());
  }

}
```

<div class="exercise">

1. Ouvrez le paquetage `fabrique1`. Il s'agit de l'application avec des **animaux** que vous aviez développés lors du dernier TP. La nouveauté est qu'il y a aussi des **animaux robots** (qui ont seulement en plus une voix robotique quand ils font un cri...).

2. Actuellement, si je veux changer mes animaux pour utiliser des animaux robotiques dans le `Main`, je suis obligé de changer tout le code du `Main`. Il faut vous imaginer cela pour plusieurs classes : si je veux changer mes animaux pour des animaux robotiques, je dois changer le code de toutes les classes qui créent des animaux ! Pour permettre plus de flexibilité, vous devez :

  * Mettre en place une fabrique `AnimalFactory` créant des animaux "normaux" pour le moment.

  * Faire en sorte que cette fabrique soit un **singleton**.

  * Utiliser cette fabrique dans `Main` au lieu de faire directement des `new`.

3. Si votre implémentation est bonne, vous devriez être capable d'utiliser des animaux robots seulement en changeant le code de votre fabrique. Vérifiez que cela est bien possible.

</div>

Dans certains exemples, vous pouvez rencontrer une fabrique avec une seule méthode `creerAnimal` se présentant ainsi : 

```java
public class AnimalFactory {

  public Animal creerAnimal(String type, String nom) {
      return switch (type) {
          case "chat" -> new Chat(nom);
          case "chien" -> new Chien(nom);
          case "oiseau" -> new Oiseau(nom);
          case "poule" -> new Poule(nom);
          default -> throw new RuntimeException("Animal inconnu");
      };
  }
 
}
```

Néanmoins, cette solution n'est pas forcément conseillée car :

* Elle implique que toutes les classes concrètes instanciées ont les mêmes paramètres (ce qui n'est pas toujours le cas, par exemple, si nous avions eu une figure `Rectangle` dans l'exemple des figures géométriques...)

* Il faut gérer le cas où `type` n'est pas un type connu. cCe qui ne peut pas arriver si on sépare les instanciations en différentes méthodes (et évite les bugs style faute de frappe...).

Bref, on préférera donc généralement séparer chaque instanciation dans une méthode distincte, comme ce que vous avez probablement fait sur l'exercice ou comme dans l'exemple des figures géométriques.

Pour l'instant, si nous voulons changer de "famille" de classes utilisée (animaux normaux / animaux robots) nous sommes obligés de changer le code de la classe `AnimalFactory`. Avec le pattern suivant **"fabrique abstraite"** nous allons pouvoir résoudre ce problème (et même faire cohabiter deux familles).

## Le pattern Fabrique abstraite



## Mise en pratique sur une application plus large

## Bonus

## Conclusion