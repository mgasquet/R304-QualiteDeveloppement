---
title: TP4 &ndash; Les design patterns créateurs
subtitle: Design Patterns, Qualité, SOLID, Abstraction, Dépendances
layout: tutorial
lang: fr
---

## Introduction

Quand on parle de **design patterns** on fait généralement référence aux patterns dits **GoF** (Gang of Four) présentés dans le livre **Design Patterns: Elements of Reusable Object-Oriented Software**, qui est une référence dans le monde de l'ingénierie logicielle. Le **Gang of Four** fait référence au quatre auteurs de ce livre : **Erich Gamma**, **Richard Helm**, **Ralph Johnson** et **John Vlissides**.

Pour rappel, un **design pattern** est une solution réutilisable et adaptable vis-à-vis d'un problème de conception logicielle assez récurent. Un pattern est généralement présenté via un diagramme de classes de conception et un exemple d'implémentation. Un pattern a pour but d'être applicable et adaptable à n'importe quel projet ou contexte.

Il existe d'autres types de design patterns (par exemple, les patterns GRASP) mais les plus connus et les plus utilisés sont ceux du **GoF** que nous allons explorer dans ce cours. Tous ces **patterns** permettent de renforcer l'application des principes **SOLID**. Par ailleurs, certains langages comme `Java` proposent (dans leur librairie standard) des **classes** et **interfaces** permettant d'implémenter certains patterns **GoF** comme **observateur**, **itérateur**, **prototype**...

Les design patterns **GoF** se divisent en trois catégories :

* Les patterns **créateurs** : concernent la **création d'objet**. Ils permettent de mettre en place des solutions et des structures pour contrôler l'instanciation des objets du programme. Cela permet de réduire les dépendances de type "create".

* Les patterns **structuraux** : permettent d'organiser les objets en faisant notamment de l'abstraction pour augmenter la modularité du programme et l'ajout de nouvelles fonctionnalités (principe ouvert/fermé).

* Les patterns **comportementaux** : permettent d'organiser la collaboration et les communications entre les objets du programme afin de distribuer efficacement les **responsabilités**.

Dans le TP précédent, vous avez déjà vu un pattern **structurel** (Décorateur) et un pattern **comportemental** (Stratégie). Dans le premier TP **git**, le programme utilisait un pattern **créateur** (fabrique) et un autre pattern **comportemental** (commande). Bref, les design patterns sont partout !

Dans ce TP, nous allons voir **tous les patterns créateurs** et allons les mettre en application : **Singleton**, **Builder**, **Prototype** et enfin **Fabrique Abstraite**.

Nous verrons aussi un autre pattern **structurel** appelé **adaptateur**. En fait, nous allons voir que beaucoup de ces patterns peuvent (et doivent) être combinés dans un projet plus large. Nous traitons souvent des problèmes "simple" avec quelques classes pour illustrer le fonctionnement d'un pattern, mais sur un projet plus large, il est tout à fait naturel de faire travailler en concert les différents patterns.

**Attention** : Dans plusieurs exercices, il vous sera demandé de **générer un diagramme de classes** (avec `IntelliJ` ou autre IDE qui propose cette fonctionnalité). Bien que les diagrammes générés puissent être parfois légèrement erronés, et qu'il vaut généralement mieux faire le dessin soit-même, cela vous fera gagner du temps. Il est fortement conseillé de prendre des **captures d'écran** de chaque diagramme de classes et de les sauvegarder dans un sous-dossier de votre dépôt. Certains diagrammes permettent de comparer l'évolution de l'architecture et des dépendances avant/après **refactoring**.

<div class="exercise">

1. Pour commencer, clonez en local le **dépôt gitlab** forké dans votre espace privé dans le cours de qualité de développement : [https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/etu/votre_login/tp4](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/etu/votre_login/tp4) en remplaçant `votre_login` par le login que vous utilisez pour accéder au serveur gitlab du département.

2. Ouvrez le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur.

3. À la fin de chaque séance, n'oubliez pas de faire un **push** vers votre dépôt distant sur **GitLab**.

</div>

## Le pattern Singleton

L'idée du pattern **Singleton** est très simple : on souhaite garantir **qu'il n'existe qu'une seule instance d'une classe dans le programme et fournir un point d'accès global à cette instance**. Les autres objets/classes de l'application utilisent l'instance "globale" et **ne doivent pas pouvoir l'instancier directement** (l'utilisation de **new** doit être bloqué en dehors de la classe). L'instance globale doit être accessible à travers une méthode qui l'expose et qui a une visibilité appropriée.

On pourrait penser que l'utilisation d'une **classe statique** (toutes les méthodes et attributs statiques), pourrait aussi faire l'affaire. C'est une solution à éviter, nous verrons pourquoi par la suite.

Commençons avec un exemple :

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

<div style="text-align:center">
![Singleton 1]({{site.baseurl}}/assets/TP4/Singleton1.svg){: width="40%" }
</div>

Dans cet exemple, il y a au moins deux instances de la classe **Service** qui sont générées. Une dans `Client` et une autre dans `ClasseExemple`. S'il n'y a aucun intérêt à avoir plusieurs instances de la classe `Service`, nous pouvons alors la transformer en **Singleton** afin que toutes les classes qui souhaitent utiliser passent par la même instance. Pour cela, il y a trois changements à réaliser dans la classe qu'on veut transformer en **Singleton** :

* Changer la **visibilité** du ou des **constructeurs** de la classe en **privé**. Ainsi, plus aucune autre entité pourra créer des instances de cette classe (hormis la classe elle-même).

* Dans la classe, créer un attribut **privé** et **statique** (un attribut de classe : `static` en Java) du même type que la classe. Cet attribut est généralement nommé `INSTANCE` (en majuscules).

* Enfin, créer une méthode **publique** et **statique** qui retourne un objet du type de la classe. Cette méthode est nommée `getInstance`. Tout d'abord, elle regarde si la variable `INSTANCE` a été initialisée ou non (si elle est `null` ou non). Si elle n'est pas encore initialisée, la classe l'instancie. Dans tous les cas, à la fin, on retourne `INSTANCE`.

Par la suite, toutes les entités qui souhaitent récupérer une instance de cette classe utilisent la méthode `getInstance` qui peut directement être appelée sur la classe, car **statique**. Lors du premier accès, l'instance "globale" sera alors initialisée.

Dans un environnement **multi-threadé** (exécution de plusieurs processus en parallèle, comme des `Runnable` ou des `Thread` en Java) il faut faire attention à ce que la méthode `getInstance` ne soit pas appelée en même temps par deux **Threads** différents. Pour régler cela en Java, il suffit d'ajouter le mot clé `synchronized` lors de la définition de la méthode.

Regardons ce que cela donne :

```java

public class Service {

  private static Service INSTANCE;

  // Interdit l'instanciation en dehors de la classe Service
  private Service() {}

  // On appelle systématiquement cette méthode pour récupérer l'instance "globale"
  public synchronized static Service getInstance() {
    if(INSTANCE == null) {
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

<div style="text-align:center">
![Singleton 2]({{site.baseurl}}/assets/TP4/Singleton2.svg){: width="40%" }
</div>

Ici, on a la garantie que la classe `Client` et la classe `ClasseExemple` utilisent la même instance de `Service`.

Ce pattern s'avère très utile quand nous avons une classe (généralement un service) que plusieurs classes doivent utiliser et qu'il n'y a pas besoin d'instancier celui-ci à chaque fois (notamment si son paramétrage est complexe). Cependant, nous verrons aussi qu'il ne faut pas en abuser et limiter son utilisation, car cela peut engendrer certains problèmes, notamment au niveau des tests unitaires.

### Mise en application

Commençons par une mise en application assez simple dans un cas qui montre l'intérêt d'utiliser un `Singleton` dans le contexte où deux objets différents dépendent de l'état d'une classe. Un objet de classe `A` modifie l'état de `Service` et un objet de classe `B` a besoin de connaître les modifications qu'a effectuées `A` dans `Service` pour fonctionner. Les deux classes `A` et `B` doivent alors dépendre de la même instance de `Service` !

Aussi, imaginons une classe d'accès à une base de données : celle-ci initialise une connexion vers la base qui peut prendre plusieurs secondes. Il serait inconscient d'instancier cette classe à chaque endroit où on en a besoin (cela dégraderait les performances !). On va plutôt utiliser un **Singleton**.

<div class="exercise">

1. Ouvrez le paquetage `singleton1`. Cette application permet de créer des animaux avec un nom et une vitesse, de les stocker dans la mémoire et de les lire.

2. Testez l'application. Créez plusieurs animaux puis tentez de les lire. Quels sont les deux problèmes que vous constatez ?

3. Réglez cela en appliquant le pattern **Singleton** sur la classe `StockageAnimaux` et en adaptant votre code.

4. Vérifiez que tout fonctionne et que les bugs sont bien résolus.

5. Le principe SOLID `D` (dependency inversion) est-il respecté sur les classes `CreationAnimal` et `LectureAnimaux` ? Si ce n'est pas le cas, refactorez votre code.

6. Pensez-vous qu'il serait possible de se passer intégralement de singletons dans une application bien construite ? Vous pouvez discuter de votre réponse avec votre enseignant.

</div>

### Classe statique VS Singleton

En introduction de cette section, nous avions évoqué le fait d'utiliser une **classe statique** pour obtenir un résultat similaire au singleton. Une classe statique est une classe où il n'y a que des attributs et des méthodes **de classe** qui appartiennent donc à la classe et pas à une instance en particulier. Ainsi, tous les objets qui manipulent cette classe utilisent la même "entité" (en fait, il n'y a juste pas d'instance).

Par exemple, on pourrait remplacer ce **Singleton** :

```java
public class Service {

  private String data;

  private static Service INSTANCE;

  private Service() {}

  public synchronized static Service getInstance() {
    if(INSTANCE == null) {
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

Si cette méthode pourrait paraître plus "facile" à mettre en place et à utiliser (pas de `getInstance`, etc.) c'est généralement une **mauvaise idée**. Nous allons voir pourquoi avec le prochain exercice. 

<div class="exercise">

1. Ouvrez le paquetage `singleton2`. Cette application permet de simuler des services de création d'utilisateurs et de gestion de commandes. Dans une application concrète, ces deux services sont susceptibles d'envoyer des mails. Testez un peu l'application. Aussi, deux classes de tests sont disponibles dans le dossier `java/singleton2`.

2. Il semble inutile d'instancier la classe `ServiceMail` à chaque fois. Cette fois-ci, au lieu d'utiliser un `Singleton`, nous allons transformer `ServiceMail` en **classe statique**. Faites ce changement et adaptez le code dans les classes `ServiceUtilisateur` et `ServiceCommande`.

3. Si ce n'est pas déjà fait, lancez les tests unitaires des classes `ServiceUtilisateurTest` et `ServiceCommandeTest`. On voit bien quand dans un contexte réel, les mails seraient vraiment envoyés à chaque test ! C'est un problème.

4. Nous avions apporté une solution à ce même problème dans le TP précédent en utilisant **l'injection de dépendances**. Au lieu d'instancier directement le service "mail" dans la classe qui en a besoin, nous l'avions **injecté** via le constructeur. L'idée serait alors de :

    * Créer une interface `ServiceMailInterface` avec la signature la méthode `envoyerMail`.

    * Faire implémenter cette interface à `ServiceMail`.

    * Créer une classe `FakeMailer` qui implémente `ServiceMailInterface` et qui ne fait rien (ou quelque chose relatif aux tests) dans `envoyerMail`.

    * Faire en sorte que `ServiceUtilisateur` et `ServiceCommande` possèdent un attribut de type `ServiceMailInterface` qui sera injecté via le constructeur et l'utilisent à la place de l'instance concrète `ServiceMail`.

    * Injecter le `ServiceMail` quand on instancie `ServiceUtilisateur` et `ServiceCommande` dans l'application.

    * Injecter le `FakeServiceMail` quand on instancie `ServiceUtilisateur` et `ServiceCommande` dans nos tests unitaires.

    Un tel refactoring est-il possible ici ? Essayez de refactorer et relevez les problèmes que vous rencontrez.

</div>

En essayant de refactorer, vous avez dû rencontrer divers problèmes :

* Une `interface` (dans la plupart des langages) ne peut pas posséder de signature de méthode de classe (`static`).

* Il est impossible d'injecter la classe statique comme paramètre d'un constructeur. Et oui, une classe n'est pas un objet et une instance ! Elle ne peut donc pas être passée en paramètre.

Bref, l'utilisation d'une **classe statique** rend les services qui l'utilisent étroitement dépendant de la classe. Ce qui rend l'application intestable car ces services ne peuvent pas être testés indépendamment des services concrets qui sont utilisés dans l'application. On ne peut pas remplacer le service par un "faux" service utilisé pour les tests unitaires (un **stub** ou un **mock**).

L'utilisation d'un **Singleton** résout ces problèmes :

* L'instance de la classe est une véritable instance, un objet. Elle peut donc être passée en paramètre dans un constructeur, par exemple.

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

2. Comme expliqué dans l'exercice précédent, introduisez une interface `ServiceMailerInterface` pour abstraire ce service.

3. Créez un nouveau service `FakeServiceMail` implémentant aussi `ServiceMailerInterface` mais qui ne fait rien dans sa méthode `envoyerMail`. Ce service sera aussi un singleton.

4. Refactorez `ServiceUtilisateur` et `ServiceCommande` pour injecter la dépendance nécessaire au lieu de directement récupérer l'instance du singleton dans la classe via `getInstance`.

5. Adaptez le `Main` afin que le service concret utilisé soit `ServiceMailer` dans les deux autres services.

6. Adaptez aussi les tests pour utiliser `FakeServiceMail`. Vérifiez que l'exécution des tests ne déclenche plus l'envoi (fictif) de mails.

7. Générez le **diagramme de classes de conception** de votre application (avec `IntelliJ`).

</div>

### Avertissement

Vous maîtrisez maintenant le pattern **Singleton**, mais vous devez être très précautionneux quant à son utilisation. En conclusion du dernier TP vous étiez invité à aller jeter un coup d'œil aux [principes STUPID](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming) qui sont un ensemble de mauvaises pratiques en conception logicielle. Regardez à quoi correspond le `S`.

En effet, l'abus de **singletons** est dangereux pour la santé (du logiciel...) ! Il présente une solution qui semble plutôt efficace à un problème assez récurent : la gestion des dépendances vers les services de l'application. À tel point qu'on retrouve parfois dans certains projets beaucoup trop de singletons. 

Mais pourquoi est-il déconseillé d'utiliser "trop" de singletons :

* Il n'est pas possible de passer des paramètres à un singleton pour son initialisation (comme un objet classique) car c'est lui-même qui se construit, cependant, on peut éventuellement mettre en place un fichier de configuration que le singleton ira lire lors de son initialisation.

* Il est très difficile de **tester** un singleton ! Comme le constructeur est **privé** et qu'il n'y a qu'une instance de l'objet dans l'application, on ne peut tester que cette instance. On ne peut pas facilement instancier de nouveaux objets de cette classe pendant les tests unitaires.

* Il existe des solutions bien meilleures pour gérer les dépendances de l'application de manière plus flexibles tout en conservant la possibilité de réaliser des tests unitaires : les fabriques abstraites (dont nous allons bientôt parler) et le conteneur d'inversion de contrôle (par exemple, le **conteneur IoC**).

Attention, tout cela ne veut pas dire que le singleton est inutile ! Seulement qu'il ne doit pas être utilisé pour tout et n'importe quoi. Il faut également se poser la question "_est-ce que cette instance doit pouvoir être accessible par tout le monde_" ?

On va notamment éviter d'appliquer **singletons** sur des classes qui contiennent du **code métier** relatif à des règles de notre application et que nous allons sûrement vouloir tester. À l'inverse, nous allons bientôt parler des **Fabriques** et du pattern **Fabrique Abstraite**. Les classes produites par ces applications ont pour but de créer et/ou fournir des objets (des dépendances). Ces classes doivent pouvoir être accessibles par toute l'application et on ne va pas spécialement les tester (pas de code métier). Il est alors judicieux d'appliquer **Singleton** sur ces classes.

Certains membres du **GoF** regrettent un peu la surutilisation maladroite de **Singleton** par certains développeurs. Ces développeurs ont l'illusion de coder proprement, car ils utilisent un design pattern, mais c'est tout l'inverse. Appliquer les design patterns ne veut pas forcément dire que votre conception est de qualité. Il faut savoir quand et comment les utiliser !

## Le pattern Builder

Le design pattern **Builder** est un pattern que vous avez déjà abordé l'année dernière en cours de développement orienté objets. Cela devrait donc vous rappeler quelques souvenirs.

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

3. Maintenant que nous avons ajouté ces deux options, quels sont tous les types de burgers qu'il est possible de créer ? Ajoutez de nouveaux **constructeurs** pour gérer tous les cas... Si vous bloquez à un moment, c'est normal ! Comprenez-vous pourquoi il n'est pas possible de poursuivre la conception actuelle ?

</div>

En effet, rien que le fait de pouvoir avoir des burgers avec du pain et des tomates et des burgers avec du pain et de la salade empêche de créer les constructeurs adéquats :

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

Dans l'exemple précédent, les deux constructeurs entrent en collision, car ils ont la même signature `Burger(String, PainBurger, boolean)`.

Pour pallier cela, on pourrait mettre en place la solution bancale suivante :

* Instancier un **Burger** seulement avec son nom et son type de pain.

* Utiliser des **setters** pour définir le fait d'ajouter de la salade ou des tomates.

Cette solution est mauvaise, car on part du principe que tous les **setters** nécessaires sont accessibles publiquement. Ce n'est pas forcément le cas et dans le cas du `Burger`, seul le **setter** du `nom` est accessible. On a décidé qu'une fois créé, on ne doit pas pouvoir modifier les ingrédients du Burger, mais qu'on peut le renommer. Il n'est donc pas possible d'ajouter des **setters** !

Le pattern **builder** permet de résoudre ce problème avec une classe qui permet de contrôler comment l'objet est créé. Cette classe est généralement placée **à l'intérieur de la classe à construire** même si on retrouve des versions et des variantes avec la classe "Builder" comme classe externe indépendante.

Cette classe possède :

* Les mêmes attributs que la classe cible (du moins ceux qu'on peut préciser lors de l'initialisation de l'objet).

* Un constructeur qui prend en paramètre tous les attributs qu'on doit obligatoirement initialiser lorsqu'on crée l'objet cible.

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

Dans cette classe, il y a deux attributs qu'il est obligatoire d'initialiser : `data` et `compteur`. Ensuite, il y a diverses options. L'attribut `data` et `optionB` peuvent être modifiés, mais pas le reste. Pour contrôler la construction d'instances de cette classe, nous pouvons donc mettre en place un `Builder` :

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

  //On rend le constructeur privé pour obliger à passer par le Builder
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

    //Par défaut, un booléen est à false, donc ajouter cette option signifie passer la valeur à true.
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
    Exemple ex2 = builderEx2.withOptionB().withOptionC(10.05).withOptionD().build();
  }

}
```

<div style="text-align:center">
![Builder 1]({{site.baseurl}}/assets/TP4/Builder1.svg){: width="50%" }
</div>

Sur **StarUML** le fait qu'une classe soit incluse dans une autre classe est représenté par la relation "Containment" qu'on trouve dans la section "Packages" dans la boîte à outil.

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
      return new Exemple(this);
    }
  }

}
```

<div class="exercise">

1. Refactorez le code de l'application de burgers pour mettre en place un `Builder`. Adaptez le `Main` en conséquence.

2. Vérifiez que vous pouvez bien ajouter les burgers suivants :

    * Burger avec du pain moisi, avec de la salade et du poulet.

    * Burger avec du pain au sésame, avec des tomates, de la salade.

    * Burger avec du pain classique, avec de la salade, des tomates, de la viande de bœuf et du cheddar.

3. Générez le **diagramme de classes de conception** de votre application (avec `IntelliJ`).

**NB :** Certains IDE (dont IntelliJ) permettent de générer automatiquement le code d'un Builder à partir d'une classe. Sur IntelliJ, il faut placer le curseur sur le constructeur de la classe pour laquelle vous souhaitez générer le builder, puis taper `ALT+Entree` puis sélectionner _Replace constructor with builder_. Le Builder sera généré comme une classe à part. Pour la rendre interne à la classe cible, il suffira juste de faire un Drag & Drop du Builder dans sa classe cible.

**Remarque :** lorsqu'il s'agit d'une hiérarchie de classes (par héritage) pour laquelle il faut créer des builders, la solution n'est pas forcément évidente. En effet, il faut faire une hiérarchie de builders pour éviter la duplication de code, tout en respectant le principe LSP, à savoir : les méthodes **with...** doivent retourner le bon type de builder. Pour plus de détails voir le [dernier TP](https://gitlabinfo.iutmontp.univ-montp2.fr/dev-objets/tp11) du cours de Développement Orienté Objets de première année (pas fait en 2024).

</div>

## Le pattern Prototype

Nous allons directement présenter le principe et l'intérêt du pattern **prototype** à travers un exercice.

<div class="exercise">

1. Ouvrez le paquetage `protoype1` et consultez les classes mises à disposition. Il s'agit d'une mini-application bancaire permettant de gérer des comptes. Pour le moment, la classe `Banque` permet de gérer des **comptes courants**. C'est elle qui gère intégralement ces comptes bancaires : leur création et le changement de solde (créditer/débiter). Elle est donc **composée des comptes bancaires** (ce qui se traduirait par une **agrégation forte** sur un diagramme de classes de conception).

2. Le développeur a pensé qu'il serait utile qu'un objet extérieur puisse récupérer un `CompteCourant` depuis la banque pour consulter le solde (ou autre). Il a donc créé une méthode `getInformationsCompteNumero`. Expérimentez dans le `Main` en créditant le compte d'un objet récupéré par cette méthode puis récupérez de nouveau ce compte depuis la banque et affichez son solde. Le solde du compte t-il était modifié ? Lancez le test unitaire situé dans la classe dans `src/test/java/prototype1`. Il ne passe pas... Comprenez-vous pourquoi ?

</div>

Le test unitaire n'est pas mal écrit. En fait, comme la banque gère exclusivement les différents **comptes bancaires**, il ne doit pas être possible qu'une autre classe puisse récupérer et modifier les objets que contient la banque. C'est toute la sémantique derrière la **composition forte** (ou *agrégation forte*) sur un diagramme de classe. Le "composant" est créé dans la classe (c'est le cas) et ne doit pas en sortir (ce n'est pas le cas ici).

Une première solution pourrait être d'ajouter une méthode `double recupererSolde(int numeroCompte)` dans la classe `Banque`. Mais dans certains cas, on a vraiment besoin d'obtenir l'objet `CompteCourant` cible, sans pour autant modifier l'original... alors comment faire ?

L'idée est de renvoyer une **copie** complète de l'objet ! Toutes les valeurs des attributs de l'objet copié seront identiques dans le nouvel objet, mais s'il est modifié, l'objet original (stocké dans `Banque`) ne sera pas impacté. L'objet renvoyé par `getInformationsCompteNumero` est alors un nouvel objet identique au compte, mais ce n'est pas l'objet original. Le principe de la composition est alors respecté.

Mais alors, qui doit faire cette copie ?

* Est-ce que `Banque` est habilité à faire cela ? Cela ne semble pas trop **Single responsability** friendly ! De plus, est-ce que `Banque` a la capacité de copier `CompteCourant` ? A priori, il n'a pas accès aux attributs privés ou protégés comme `solde`, alors que `CompteCourant`, oui.

* À la place, on peut définir un **constructeur par copie** dans `CompteCourant`. L'objectif d'un tel constructeur est de prendre un objet du même type et d'initialiser ses propres attributs avec les valeurs des attributs de l'autre objet. Vous avez sans doute utilisé de tels constructeurs en première année (notamment dans le cours d'initiation au développement) :

  ```java
  class Date {

    private int jour;

    private int mois;

    private int annee;

    //Constructeur de base
    public Date(int jour, int mois, int annee) {
      this.jour = jour;
      this.mois = mois;
      this.annee = annee;
    }

    //Constructeur par copie
    public Date(Date dateACopier) {
      this(dateACopier.jour, dateACopier.mois, dateACopier.annee);
    }
  }
  ```

<div class="exercise">

1. Refactorez votre code afin que `Banque` renvoie une **copie** du compte courant sélectionné. Attention au **solde** ! Il faut qu'il soit identique au compte copié. Vérifiez que cela fonctionne en lançant le test unitaire. Il devrait maintenant passer.

2. On aimerait maintenant que la `Banque` gère aussi des **comptes épargne**. En fait, il faut qu'elle puisse gérer des **CompteBancaire** et pas seulement des **comptes courants**. refactorez le code de la classe `Banque` pour rendre cela possible (en utilisant plutôt la classe abstraite `CompteBancaire` plutôt que `CompteCourant`). 

    Vous devrez néanmoins conserver la méthode `ouvrirCompteCourant` telle quelle, car elle ouvre spécifiquement un compte courant. Vous devrez aussi ajouter une méthode `ouvrirCompteEpargne` (tout cela ne respecte pas vraiment le principe ouvert/fermé, mais nous allons nous en contenter pour cet exercice). 
    
    Vous n'avez pas à ajouter de nouveaux attributs ou d'autres méthodes en dehors de `ouvrirCompteEpargne`. (Notamment, interdiction de faire une deuxième liste séparée gérant les comptes épargnes).

    Normalement, vous avez une erreur sur la méthode `getInformationsCompteNumero`. C'est normal.

3. Comprenez-vous pourquoi l'implémentation de `getInformationsCompteNumero` provoque des erreurs ?

</div>

Notre solution à base de copie semblait bonne, mais elle tombe à l'eau dès lors qu'on manipule des abstractions et plus des classes concrètes ! `Banque` ne peut plus utiliser le constructeur par copie de `CompteCourant`, car elle gère une liste de `CompteBancaire` abstraits (qui peuvent être des comptes courants, des comptes épargnes ou autre...).

Le pattern **prototype** permet de résoudre ce problème en précisant que :

  * Une méthode `cloner` doit être définie au niveau de l'entité abstraite (dans l'interface ou dans la classe abstraite). Cette méthode renvoie un objet du même type que la classe mère.

  * Chaque enfant implémente la méthode `cloner` qui renvoie une copie de lui-même.

  * Dans la signature de la méthode, l'enfant peut éventuellement remplacer le type abstrait par son propre type.

```java
interface Exemple {

  void action();

  Exemple cloner();
}

class A implements Exemple {

  private int data;

  public A(int data) {
    this.data = data;
  }

  public A(A objetACopier) {
    this(objetACopier.data);
  }

  @Override
  public void action() {
    //...
  }

  @Override
  public A cloner() {
    //Appel de son propre constructeur par copie
    return new A(this);
  }

}

class B implements Exemple {

  private boolean attribut;

  public B(boolean attribut) {
    this.attribut = attribut;
  }

  public B(B objetACopier) {
    this(objetACopier.attribut);
  }

  @Override
  public void action() {
    //...
  }

  @Override
  public B cloner() {
    //Appel de son propre constructeur par copie
    return new B(this);
  }

}
```

Avec cette nouvelle architecture, il suffit alors d'utiliser la méthode `cloner` sur l'objet abstrait :

```java
class Service {

  private Exemple ex;

  public Exemple getExemple() {
    return ex.cloner();
  }

}
```

<div style="text-align:center">
![Prototype 1]({{site.baseurl}}/assets/TP4/Prototype1.svg){: width="40%" }
</div>


L'application du prototype peut éventuellement être plus complexe dans des cas d'héritage. Par exemple, si un attribut dont a besoin une classe fille lors de sa construction est déclaré comme privé dans la classe mère, l'enfant n'y aura pas accès et ne pourra donc pas l'utiliser pour le clonage. Il faut donc prévoir cela et proposer des solutions pour que les classes filles puissent effectuer le clonage sans problème. On peut par exemple utiliser la visibilité `protected` sur l'attribut (dans ce cas, il faut bien organiser les **packages**) ou alors des **getters** (public ou `protected`) qui renvoient l'objet inaccessible désiré, ou bien le clonent (si c'est un objet et qu'il peut être cloné).

```java
abstract class ClasseMere {

  private int valeur;

  public ClasseMere(int valeur) {
    this.valeur = valeur;
  }

  public abstract ClasseMere clone();

}

class ClasseFille extends ClasseMere {

  private String texte;

  public ClasseFille(int valeur, String texte) {
    super(valeur);
    this.texte = texte;
  }

  @Override
  public ClasseFille clone() {
    //Erreur, valeur n'est pas accessible !
    return new ClasseFille(valeur, texte);
  }

}
```

Solutions :

```java
// Avec la visibilité protected, seules les classes du même paquetage et les classes qui étendent ClasseMere ont accès à l'attribut/méthode. Il faut donc bien gérer les paquetages pour s'assurer qu'une classe ne puisse pas y accéder alors qu'elle n'est pas censée pouvoir.
abstract class ClasseMere {

  //Permet à la classe fille de lire (mais d'aussi écrire) l'attribut valeur
  protected int valeur;

  //Ou bien : permet à la classe fille de lire l'attribut valeur
  protected int getValeur() {
    return valeur;
  }

  ...

}
```

<div class="exercise">

1. Refactorez votre code en appliquant le pattern **prototype** sur vos comptes bancaires. Adaptez aussi le code de `getInformationsCompteNumero` en conséquence.

2. Vérifiez que le test unitaire passe toujours.

</div>

<!--
Réalisez le **diagramme de séquence des interactions** permettant de modéliser ce qu'il se passe lors de l'éxécution du code suivant :

    ```java
    Banque banque = new Banque();
    int numeroCompte = banque.ouvrirCompteCourant("Test", Formule.ADULTE);
    banque.crediterCompte(numeroCompte, 50);
    CompteBancaire compte = banque.getInformationsCompteNumero(numeroCompte);
    compte.crediter(100);
    ```
-->

L'objectif du pattern **prototype** est donc de définir un moyen d'obtenir des **copies** d'un objet, notamment dans un contexte où vos classes manipulent des abstractions (comme c'est souvent le cas quand on applique les principes **SOLID** et les **design patterns**). Si on souhaite pouvoir copier un objet abstrait manipulé, chaque classe concrète de la hiérarchie doit définir sa propre logique de copie via la méthode `cloner`.

**Remarque technique (pour Java) :** En Java, un mécanisme de clonage est prévu à travers la fonction `clone` de la classe `Object`. Pour l'utiliser sur une classe que vous développez, il faut implémenter l'interface [`Cloneable`](https://docs.oracle.com/en/java/javase/17/docs/api/java.base/java/lang/Cloneable.html). Cette interface ne contient aucune méthode, mais elle permet de signaler que la classe peut être clonée. Le mécanisme interne de cette spécification est assez obscure et a été beaucoup critiqué (voir Item 13 du livre **Effective Java** de Joshua Bloch, ainsi que [les discussions en ligne](https://stackoverflow.com/questions/4081858/how-does-cloneable-work-in-java-and-how-do-i-use-it)). Il est donc préférable de ne pas utiliser cette interface et de définir votre propre méthode `cloner` comme nous l'avons fait dans l'exemple précédent.

## La Fabrique Simple - un concept très utile

Le concept de **Simple Fabrique** permet de centraliser l'instanciation d'une famille de classes dans une classe spécialisée. Les classes ayant besoin d'instancier des objets de cette famille ne vont plus faire elle-même des **new**, mais vont plutôt passer par la fabrique. Ainsi les dépendances vers les types **concrets** sont centralisées dans une seule classe, et les classes ayant besoin d'instancier des objets ne possèdent qu'une dépendance vers la fabrique.

**Remarque importante :** Bien que le concept de **Fabrique Simple** est extrêmement pratique (et utilisé dans différents __design patterns__), il ne s'agit pas d'un design pattern à proprement parler. Prenons-le plutôt comme une application de règles de bon sens. En l'occurrence, il ne faut pas confondre la **Fabrique Simple** avec les patterns **Méthode Fabrique** (**Factory Method**) et **Fabrique Abstraite** (**Abstract Factory**) du **GoF**, dont nous allons parler dans ce TP.

La fabrique connaît les différents types concrets à instancier, mais elle va généralement renvoyer des abstractions (classes abstraites/interfaces) pour que les classes ayant besoin de créer des objets ne dépendent plus du tout d'un objet concret, mais plutôt de son abstraction. Ainsi, l'impact du changement diminue (si on veut changer la classe concrète utilisée) ce qui renforce notamment le principe ouvert/fermé.

Dans une application où certaines classes sont instanciées à différents endroits, il est donc plutôt judicieux d'utiliser une fabrique pour réduire les dépendances de type _"create"_. Seule la fabrique est dépendante des objets concrets et les autres classes sont seulement dépendantes de la fabrique (et des abstractions).

Voyons l'application de **Fabrique Simple** sur un exemple. On se place dans le contexte d'un jeu dans lequel un joueur peut combattre des monstres dans une arène ou bien traverser une zone de jeu. Pour l'instant, l'application est configurée pour fonctionner intégralement avec le monstre **Slime** (c'est toujours ce type de monstre que rencontrera le joueur).

```java
class Joueur {

  private String nom;

  public Joueur(String nom) {
    this.nom = nom;
  }

  public String getNom() {
    return nom;
  }

}

public interface Monstre {
  void combattre(Joueur joueur);
}

public class Slime implements Monstre {

  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat du slime contre le joueur..." + joueur.getNom());
  }

}

public class Fantome implements Monstre {

  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat du fantôme contre le joueur..." + joueur.getNom());
  }

}

public class Arene {

  private Joueur combattant;

  public Arene(Joueur combattant) {
    this.combattant = combattant;
  }

  public void nouveauCombat() {
    Monstre monstre = new Slime();
    monstre.combattre(combattant);
  }

}

public class Zone {

  public void traverserZoneNormale(Joueur joueur) {
    Random random = new Random();
    int nbEnnemis = random.nextInt(3) + 1;
    for(int i = 0; i < nbEnnemis; i++) {
      Monstre monstre = new Slime();
      monstre.combattre(joueur);
    }
  }

}
```

<div style="text-align:center">
![Fabrique 1]({{site.baseurl}}/assets/TP4/Fabrique1.svg){: width="65%" }
</div>

Ici l'application est donc configurée pour faire apparaître des monstres **Slimes**. `Arene` et `Zone` sont fortement dépendants de `Slime`, car elles instancient des objets `Slime` dans son code. Et on ne peut pas simplement injecter les dépendances, car ces classes ont besoin de directement instancier ces objets dans leurs méthodes ! Si nous devons changer pour utiliser des objets `Fantome` à la place, il faut modifier ces deux classes !

Nous pouvons mettre en place une **Fabrique** pour régler ce problème :

```java

public class MonstreFactory {

  public Monstre creerMonstre() {
    return new Slime();
  }

}

public class Arene {

  private MonstreFactory factory = new MonstreFactory();

  public Arene(Joueur combattant) {
    this.combattant = combattant;
  }

  public void nouveauCombat() {
    Monstre monstre = factory.creerMonstre();
    monstre.combattre(combattant);
  }

}

public class Zone {

  private MonstreFactory factory = new MonstreFactory();

  public void traverserZoneNormale(Joueur joueur) {
    Random random = new Random();
    int nbEnnemis = random.nextInt(3) + 1;
    for(int i = 0; i < nbEnnemis; i++) {
      Monstre monstre = factory.creerMonstre();
      monstre.combattre(joueur);
    }
  }

}

```

Maintenant, si nous voulons utiliser des monstres type `Fantome` à la place de `Slime`, nous n'avons à faire ce changement que dans **une seule classe** : `MonstreFactory` !

<div style="text-align:center">
![Fabrique 2]({{site.baseurl}}/assets/TP4/Fabrique2.svg){: width="65%" }
</div>

Ici, il semble judicieux de transformer `MonstreFactory` en **Singleton** et de l'injecter comme dépendance pour éviter que chaque service instancie une version de la fabrique :

```java

public class MonstreFactory {

  private static MonstreFactory INSTANCE;

  private MonstreFactory() {}

  public synchronized static MonstreFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new MonstreFactory();
    }
    return INSTANCE;
  }

  public Monstre creerMonstre() {
    return new Slime();
  }

}

public class Arene {

  private MonstreFactory factory;

  public Arene(Joueur combattant, MonstreFactory factory) {
    this.combattant = combattant;
    this.factory = factory;
  }

  public void nouveauCombat() {
    Monstre monstre = factory.creerMonstre();
    monstre.combattre(combattant);
  }

}

public class Zone {

  private MonstreFactory factory;

  public Zone(MonstreFactory factory) {
    this.factory = factory;
  }

  public void traverserZoneNormale(Joueur joueur) {
    Random random = new Random();
    int nbEnnemis = random.nextInt(3) + 1;
    for(int i = 0; i < nbEnnemis; i++) {
      Monstre monstre = factory.creerMonstre();
      monstre.combattre(joueur);
    }
  }

}

public class Main {

  public static void main(String[]args) {
    Joueur j1 = new Joueur("Bob");
    Arene arene = new Arene(j1, MonstreFactory.getInstance());
    arene.nouveauCombat();
    Zone zone = new Zone(MonstreFactory.getInstance());
    zone.traverserZoneNormale(j1);
  }

}
```

<div style="text-align:center">
![Fabrique 3]({{site.baseurl}}/assets/TP4/Fabrique3.svg){: width="65%" }
</div>

En bref, il est possible de généraliser ce modèle ainsi :

<div style="text-align:center">
![Fabrique Simple 2]({{site.baseurl}}/assets/TP4/FabriqueSimple2.svg){: width="50%" }
</div>

Il est possible d'adapter et d'étendre ce modèle :

* On peut avoir plusieurs méthodes de création différentes dans la fabrique (mais attention au principe de responsabilité unique : on peut faire deux fabriques, au besoin).

* Une méthode de création peut retourner plusieurs sous-types d'objets de la même famille.

Prenons l'exemple suivant : on souhaite modéliser le fonctionnement de machines à café. 

Il existe différents types de cafés : 

* Café Expresso
* Café Cappuccino

Chaque café peut être composé d'un type de graine (arabica ou robusta) et le sucre versé dans le café appartient à une marque spécifique. Les types de graines peuvent venir de pays différents.

Pour l'instant, nos graines arabica viendront du brésil, les graines robusta d'Asie et la marque de sucre utilisée est Daddy.

Une fois l'instance d'un Café créé, il doit ensuite être **préparé** (c'est à ce moment qu'on initialisera les ingrédients utilisés).

```java
public abstract class Cafe {

  protected String typeGraine;

  protected String marqueSucre;

  public abstract void preparer();

  public void afficherComposition() {
    System.out.println("Composition du café : ");
    System.out.println(typeGraine);
    System.out.println(marqueSucre);
  }
}

public class Expresso extends Cafe {

  @Override
  public void preparer() {
    System.out.println("Préparation d'un café Expresso");
    this.typeGraine = "Graine Arabica Brésilienne";
    this.marqueSucre = "Daddy";
  }

}

public class Cappuccino extends Cafe {

  @Override
  public void preparer() {
    System.out.println("Préparation d'un café Cappuccino");
    this.typeGraine = "Graine Robusta Asiatique";
    this.marqueSucre = "Daddy";
  }

}

public class CafeFactory {

  private static CafeFactory INSTANCE;

  private CafeFactory() {}

  public synchronized static CafeFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new CafeFactory();
    }
    return INSTANCE;
  }

  public Cafe creerCafe(String type) {
      switch (type) {
          case "expresso" : return new Expresso();
          case "cappuccino" : return new Cappuccino();
          default: throw new IllegalArgumentException(String.format("Type de café inconnu : %s", type));
      }
  }
}

public class MachineCafe {

  private CafeFactory factory;

  public MachineCafe(CafeFactory factory) {
    this.factory = factory;
  }

  public void commanderCafe(String type) {
      Cafe cafe = factory.creerCafe(type);
      cafe.preparer();
      cafe.afficherComposition();
  }

}

public class Main {

  public static void main(String[]args) {
    MachineCafe machine = new MachineCafe(CafeFactory.getInstance());
    machine.commanderCafe("expresso");
    machine.commanderCafe("cappuccino");
  }

}
```

<div style="text-align:center">
![Fabrique 4]({{site.baseurl}}/assets/TP4/Fabrique4.svg){: width="40%" }
</div>

Ou bien, de manière plus générale :

<div style="text-align:center">
![Fabrique Simple 3]({{site.baseurl}}/assets/TP4/FabriqueSimple3.svg){: width="50%" }
</div>

Dans **certains contextes**, il est éventuellement possible de diviser la méthode de création en plusieurs méthodes :

```java
public class CafeFactory {

  private static CafeFactory INSTANCE;

  private CafeFactory() {}

  public synchronized static CafeFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new CafeFactory();
    }
    return INSTANCE;
  }

  public Cafe creerExpresso() {
    return new Expresso();
  }

  public Cafe creerCappuccino() {
    return new Cappuccino();
  }
}
```

**Cependant**, si les objets sont **de même nature** (ici, tous des **cafés**) et ont globalement besoin des mêmes entrées pour être instanciés, on préférera la première méthode et on préférera éviter celle-ci. On réservera le fait d'avoir plusieurs méthodes pour créer des objets de nature différentes (comme nous le ferons avec **la fabrique abstraite**).

La première méthode (avec le bloc **switch**) pourrait ressembler à du mauvais code, mais il s'agit bien de l'implémentation **souhaitée**. De plus, la seconde méthode n'aurait pas bien fonctionné avec la classe `Machine` à moins de la coder autrement. On se serait soit retrouvé avec de la duplication de code, soit à gérer un autre `switch` dans la classe `Machine`. Dans cet exemple, il est donc préférable d'utiliser la première méthode.

Avec notre implémentation, il est éventuellement possible d'utiliser une autre marque de café qui possède son propre type d'expresso et de cappuccino (avec des graines de provenances différentes, et une autre marque de sucre). Il suffira de changer la fabrique sans impacter le reste des classes. Mais que se passerait-il si on souhaitait faire cohabiter ces différentes **marques** de café, avec leur propre machine ? Il est possible de régler ce problème avec les patterns **méthode fabrique** et/ou **fabrique abstraite** (nous détaillerons plutôt cela dans la **synthèse de cours** dédiée).

### Animaux

Pour l'instant, testons votre compréhension de la **fabrique simple** :

<div class="exercise">

1. Ouvrez le paquetage `fabrique1`. Il s'agit de l'application avec des **animaux** que vous aviez développée lors du dernier TP. La nouveauté est qu'il y a aussi des **animaux normaux** et des **animaux robots** (qui ont seulement en plus une voix robotique quand ils font un cri...).

2. Actuellement, si on souhaite changer les animaux pour utiliser des animaux robotiques dans le `Main`, on est obligé de changer tout le code du `Main`. Il faut vous imaginer cela pour plusieurs classes : s'il faut changer les animaux pour des animaux robotiques, alors il faudra changer le code de toutes les classes qui créent des animaux ! Pour permettre plus de flexibilité, vous devez :

    * Mettre en place une fabrique `AnimalFactory` créant des animaux "normaux" pour le moment.

    * Faire en sorte que cette fabrique soit un **singleton**.

    * Utiliser cette fabrique dans `Main` au lieu de faire directement des `new`.

3. Si votre implémentation est bonne, vous devriez être capable d'utiliser des animaux robots seulement en changeant le code de votre fabrique. Vérifiez que cela est bien possible.

</div>

## Le pattern Méthode Fabrique

Le pattern **Méthode Fabrique** (Factory Method) va permettre à une **classe mère** souhaitant **créer un objet** (dérivé en plusieurs sous-types) lors d'une étape d'un traitement (dans une méthode) de **déléguer** l'instanciation (et donc le type concret utilisé) à ses **classes filles**. Ce pattern utilise le concept de **fabrique** au travers d'une **méthode abstraite** définie dans la classe mère et implémenté par les classes filles.

Pour que l'utilisation de ce pattern soit justifié, il faut que la **classe mère** (abstraite) effectue **d'autres traitements que simplement créer l'objet** (sinon c'est juste une fabrique). Dans une (ou plusieurs) méthode(s) de la classe mère où un traitement est effectué, la méthode abstraite est appelée ce qui permet de récupérer un objet dont le type concret sera décidé par les sous-classes. Ainsi, le traitement peut être effectué dans la classe mère sans avoir besoin d'être dépendant d'une classe concrète.

Reprenons notre exemple de l'application de jeu gérant des **monstres** de type **slime** ou **fantômes**.

```java
public interface Monstre {
  void combattre(Joueur joueur);
}

public class Slime implements Monstre {

  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat du slime contre le joueur...");
  }

}

public class Fantome implements Monstre {

  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat du fantôme contre le joueur...");
  }

}

public class MonstreFactory {

  private static MonstreFactory INSTANCE;

  private MonstreFactory() {}

  public synchronized static MonstreFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new MonstreFactory();
    }
    return INSTANCE;
  }

  public Monstre creerMonstre() {
    return new Slime();
  }

}

public class Zone {

  private MonstreFactory factory;

  public Zone(MonstreFactory factory) {
    this.factory = factory;
  }

  public void traverserZoneNormale(Joueur joueur) {
    Random random = new Random();
    int nbEnnemis = random.nextInt(3) + 1;
    for(int i = 0; i < nbEnnemis; i++) {
      Monstre monstre = factory.creerMonstre();
      monstre.combattre(joueur);
    }
  }

}
```

Nous avions utilisé une **fabrique simple** pour éviter d'avoir à instancier le type de **Monstre** dans la `Zone`. Cependant, avec cette configuration, il n'est pas possible d'avoir à la fois des instances de `Zone` qui utilisent des **slimes** et d'autres des **fantômes**.

Le pattern **méthode fabrique** permet de régler ce problème. L'idée est de rendre la création du monstre **abstrait** dans `Zone` (et donc rendre `Zone` abstrait) et de déléguer la création du type de monstre dans des classes dérivées.

```java
public abstract class Zone {

  public void traverserZoneNormale(Joueur joueur) {
    Random random = new Random();
    int nbEnnemis = random.nextInt(3) + 1;
    for(int i = 0; i < nbEnnemis; i++) {
      Monstre monstre = creerMonstre();
      monstre.combattre(joueur);
    }
  }

  protected abstract Monstre creerMonstre();

}

public class ZonePlaine extends Zone {

  @Override
  protected Monstre creerMonstre() {
    return new Slime();
  }

}

public class ZoneChateauHante extends Zone {

  @Override
  protected Monstre creerMonstre() {
    return new Fantome();
  }

}

public class Main {

  public static void main(String[]args) {
    Joueur j1 = new Joueur("Bob");
    Zone plaine = new ZonePlaine();
    plaine.traverserZoneNormale(j1);
    Zone chateau = new ZoneChateauHante();
    chateau.traverserZoneNormale(j1);
  }

}
```

<div style="text-align:center">
![Fabrique 5]({{site.baseurl}}/assets/TP4/Fabrique5.svg){: width="40%" }
</div>

Le pattern s'appelle **méthode fabrique**, car la méthode abstraite implémentée par les classes filles sont elles-mêmes des fabriques ! D'ailleurs, dans l'exemple, nous avons supprimé `MonstreFactory` qui ne nous est plus utile.

On peut généraliser ce **pattern** ainsi :

<div style="text-align:center">
![Méthode Fabrique 1]({{site.baseurl}}/assets/TP4/MethodeFabrique1.svg){: width="65%" }
</div>

Cependant, que se passe-t-il si plusieurs services différents doivent créer des **slimes** ou des **fantômes** (par exemple, la classe `Arene` que nous avions au début) ? Il faut vraiment créer une sous-classe par type de service et de monstre ? Non, rassurez-vous ! C'est justement un point que permettra de régler la **fabrique abstraite**.

### Age of Fantasy - Partie 1

Nous allons tester votre compréhension du problème sur un premier exercice simple.

<div class="exercise">

1. Ouvrez le paquetage `fabrique2` puis `v1`. Il s'agit d'une application d'un **jeu de stratégie type heroic fantasy** permettant de gérer différentes armées (humaine et orc). L'exercice est divisé en deux parties : `v1` que nous allons traiter maintenant puis `v2` que vous allez traiter plus tard. 

2. Une armée peut **recruter** des unités si elle possède assez d'argent. On souhaite pouvoir gérer **deux types d'armées** :

   * L'armée **humaine** qui recrute des `Humain` avec 50 points de vie.
   * L'armée **orc** qui recrute des `Orc` avec 80 points de vie.

3. Faites en sorte qu'il soit possible de gérer les deux types d'armées citées dans le point précédent. Vous ajouterez les classes et le code nécessaire et vous compléterez la méthode `recruter` de la classe `Armee` ainsi que le `main` de la classe `Jeu`. Chaque fois qu'une unité est créée dans une armée, elle est ajoutée à la liste des unités de l'armée.

</div>

<!--
Maintenant, voyons un exemple un peu plus complexe en reprenant le cas de la machine à café :

* Il existe maintenant **deux marques** qui possèdent leurs propres machines à café : `Pokafe` et `Digikafe`.

* Chaque marque ne prépare pas les cafés de la même manière (ils n'utilisent pas les mêmes ingrédients).

* On veut pouvoir créer des machines `Pokafe` et des machines `Difikafe`.

En refactorant le code initial et en appliquant le pattern **méthode fabrique** une telle implémentation est possible :

```java
public class ExpressoPokafe extends Cafe {

  @Override
  public void preparer() {
    System.out.println("Préparation d'un café Expresso de Pokafe");
    this.typeGraine = "Graine Arabica Brésilienne";
    this.marqueSucre = "Daddy";
  }

}

class CappuccinoPokafe extends Cafe {

  @Override
  public void preparer() {
    System.out.println("Préparation d'un café Cappuccino Pokafe");
    this.typeGraine = "Graine Robusta Asiatique";
    this.marqueSucre = "Daddy";
  }

}

public class ExpressoDigikafe extends Cafe {

  @Override
  public void preparer() {
    System.out.println("Préparation d'un café Expresso de Digikafe");
    this.typeGraine = "Graine Arabica Africaine";
    this.marqueSucre = "Erstein";
  }

}

class CappuccinoPokafe extends Cafe {

  @Override
  public void preparer() {
    System.out.println("Préparation d'un café Cappuccino Digikafe");
    this.typeGraine = "Graine Robusta Africaine";
    this.marqueSucre = "Erstein";
  }

}

public abstract class MachineCafe {

  public void commanderCafe(String type) {
      Cafe cafe = creerCafe(type);
      cafe.preparer();
      cafe.afficherComposition();
  }

  protected abstract Cafe creerCafe(String type);

}

public class MachinePokafe extends  MachineCafe {

  @Override
  protected Cafe creerCafe(String type) {
      switch (type) {
          case "expresso" : return new ExpressoPokafe();
          case "cappuccino" : return new CappuccinoPokafe();
          default: throw new IllegalArgumentException(String.format("Type de café inconnu : %s", type));
      }
  }

}

public class MachineDigikafe extends  MachineCafe {

  @Override
  protected Cafe creerCafe(String type) {
      switch (type) {
          case "expresso" : return new ExpressoDigikafe();
          case "cappuccino" : return new CappuccinoDigikafe();
          default: throw new IllegalArgumentException(String.format("Type de café inconnu : %s", type));
      }
  }

}

class Main {

  public static void main(String[]args) {
    MachineCafe machinePokekafe = new MachinePokafe();
    machinePokekafe.commanderCafe("expresso");
    machinePokekafe.commanderCafe("cappuccino");

    MachineCafe machineDigikafe = new MachineDigikafe();
    machineDigikafe.commanderCafe("expresso");
    machineDigikafe.commanderCafe("cappuccino");
  }

}
```

Il y a quelques aspects du code qui vous paraissent encore superflus ou redondants ? C'est normal ! Nous allons encore améliorer cet exemple plus tard en utilisant une **fabrique abstraite**.
-->

### Restaurants de burgers - Partie 1

Testons maintenant votre maîtrise du pattern **méthode fabrique** avec un nouvel exercice un peu plus complexe. Cet exercice (et sa suite) sont inspirés d'un exercice issu de l'excellent livre **Head First Design Patterns** qui propose une illustration des patterns **méthode fabrique** puis **fabrique abstraite** avec un exemple se basant sur des restaurants de **pizzas** (les exemples donnés dans ce livre sont d'ailleurs en Java).

<div class="exercise">

1. Ouvrez le paquetage `fabrique3` puis `v1`. Il s'agit d'une application de restauration permettant de commander différents types de **burgers**. L'exercice est divisé en deux parties : `v1` que nous allons traiter maintenant puis `v2` que vous allez traiter plus tard. 

2. Un **restaurant** peut créer différents types de **Burger** : des **Cheese Burgers** et des **Egg Burgers**. L'application fonctionne actuellement pour un **restaurant Nîmois** qui fabrique les burgers ainsi :

   * **Cheese Burger** : Boeuf Charolais, Sauce à burger de Nîmes et Cheddar.
   * **Egg Burger** : Poulet Gardois, Sauce à burger de Nîmes et Œuf de poule.

    Le restaurant cherche à se diversifier en ouvrant différents restaurants dans d'autres villes. Tous les restaurants devront proposer les **mêmes burgers**, mais les recettes pourront changer localement, dans une ville. Un nouveau restaurant a ouvert à **Montpellier** et propose les recettes suivantes :

   * **Cheese Burger** : Boeuf Limousin, Sauce à burger de Montpellier et Maroilles.
   * **Egg Burger** : Poulet de Bresse, Sauce à burger de Montpellier et Œuf d'autruche.

    On est dans une conception où un burger contient tous les éléments dont il peut être composé. S'il n'est pas composé d'un élément (par exemple, pas de fromage), cet élément vaudra simplement `null`. Ce n'est pas nécessairement une très bonne conception, mais elle est acceptable dans le cadre de l'exercice (et vous ne devrez pas modifier cette logique).

    Actuellement, l'application fonctionne avec un seul type de classe `CheeseBurger` et `EggBurger` (qui sont les burgers du restaurant **Nîmois**). Une **fabrique simple** a été mise en place (mais vous allez peut-être devoir changer cela... ?)

    **On souhaite garder les différentes méthodes des burgers**, notamment la méthode `preparerIngredients`. Les ingrédients **ne doivent pas être initialisés via le constructeur**, mais lors de l'appel à la méthode `preparerIngredients` par le restaurant (c'est ce qu'on pourrait qualifier de **lazy loading**).

3. Faites en sorte qu'il soit possible de gérer les deux types de restaurants : les **restaurants Nîmois** et les **restaurants Montpelliérains**. Vous ajouterez, adapterez et supprimerez les classes et le code nécessaire et vous compléterez la méthode `commanderBurger` de la classe `Restaurant` ainsi que le `main` de la classe `Main`.

</div>

## Le pattern Fabrique Abstraite

Le pattern **Fabrique Abstraite** (Abstract Factory) s’appuie aussi sur la notion de fabrique et va permettre de créer des **familles d'objets** qui sont plus ou moins liés et/ou dépendants (ou du moins, avec une thématique ou un but commun).

Ce pattern va notamment permettre de créer et de sélectionner différents types de fabriques et de les interchanger lorsqu'elles instancient différentes **familles** de classes concrètes. Ainsi, lorsqu'on souhaite changer la famille de classes à construire, au lieu de modifier le code de la fabrique, on changera plutôt l'instance de la fabrique concrète utilisée par le programme ou une classe en particulier. Cela peut paraître encore un peu abstrait... regardons donc directement l'exemple suivant.

### Age of Fantasy - Partie 2

<div class="exercise">

1. Ouvrez le paquetage `fabrique2` puis `v2`. Il s'agit de la deuxième partie du **jeu de stratégie type heroic fantasy**. De nouvelles classes sont à votre disposition :

   * Diverses **armes de siège** : chaque armée peut construire des armes de siège spécifiques avec lesquelles elle peut attaquer.

   * Divers **sorts** : chaque armée possède un **sort** de prédilection qu'elle peut déclencher.

2. En plus du recrutement, chaque **armée** peut construire un type d'arme de siège spécifique et utiliser un type de sort spécifique.

   * L'armée **humaine** construit des **canons** et utilise le sort **boule de feu** avec une puissance de feu de 10.
   * L'armée **orc** construit des **catapultes** et utilise le sort **aveuglement** avec une durée de 30 secondes.

3. Commencez par importer le code que vous aviez déjà réalisé afin de mettre en place le **recrutement** des unités (depuis le package `v1`).

4. Maintenant, faites en sorte que chaque armée (humaine et orc) puisse créer ses armes de siège spécifiques et créer et utiliser leurs sorts spécifiques. Chaque arme de siège créée est ajoutée dans la liste correspondante. Un sort, quand il est créé est seulement déclenché (il n'est pas stocké). Normalement, vous devriez pouvoir trouver une solution avec vos connaissances actuelles et les patterns que nous avons vu jusqu'ici. Si vous n'y arrivez pas, passez à la suite des explications.

</div>

Vous avez probablement trouvé une solution exploitant plusieurs **méthodes fabriques** (une pour les unités, comme initialement, une pour les armes de siège et une pour les sorts...).

Cependant, cette solution, même si globalement acceptable, n'est pas forcément la plus qualitative. En effet, quand on utilise la **méthode fabrique**, on s'attend plutôt à ce que la classe mère ne contienne **qu'une seule méthode fabrique** (responsable de la création des objets du même type). Ici, il y en a 3 : les classes filles commencent à avoir trop de responsabilités. De plus, on utilise fortement **l'héritage**, alors que nous avons vu qu'il est généralement préférable de favoriser **la composition** et **l'injection de dépendances**.

Au-delà de l'aspect qualitatif, cette implémentation pourrait aussi poser un problème si on veut pouvoir **changer dynamiquement le comportement de création** souhaité. Par exemple, imaginons que nous souhaitons faire en sorte qu'une armée puisse être **vaincue** par une autre armée. L'armée vaincue n'est pas détruite et continue d'exister (et on conserve les soldats encore vivants et les armes). Cependant, l'armée vainqueuse impose son mode de fonctionnement à l'armée vaincue : elle produira maintenant les mêmes unités, les mêmes armes et les mêmes sorts que l'armée vainqueuse.

Par exemple, si l'armée orc vainc l'armée humaine, les unités humaines et les canons restent (mais ils sont maintenant forcés de travailler pour les orcs) et les prochaines unités créées seront des orcs, les prochaines armes des catapultes et les prochains sorts des sorts d'aveuglement. En fait, l'armée **humaine** et l'armée **orc** ont leur propre **configuration** ! Et on voudrait pouvoir changer la **configuration** d'une armée dynamiquement.

Il semble compliqué d'obtenir un tel fonctionnement facilement avec une **méthode fabrique**. La solution est alors de plutôt utiliser une **fabrique abstraite** !

Reprenons l'exemple des **zones** qui créent et font combattre des **monstres** avec un joueur. Dans le jeu, il y a maintenant des **Boss** qui sont des monstres spéciaux pouvant charger une attaque spéciale et des **Items** qui ont des caractéristiques et un prix de revente.

Dans une zone, un type de monstre "normal" est créé (comme avant) . On peut aussi traverser la zone du boss qui fait apparaitre deux monstres normaux et un boss et les font combattre. Quand le joueur ouvre un coffre dans cette zone, il obtient tout le temps un type d'item spécifique (pour simplifier).

Nous allons définir deux configurations ("biomes") de zones :

* La zone **Plaine** créée des monstres normaux de type `Slime`, des boss de type `Troll` (qui possèdent une puissance de massue aléatoire entre 5 et 10) et les coffres ouverts donnent des items type `Potion` qui peuvent être revendus pour 15 pièces d'or.

* La zone **Château Hanté** créée des monstres normaux de type `Fantome`, des boss de type `Dracula` et les coffres ouverts donnent des items type `Parchemin` qui peuvent être revendus pour 30 pièces d'or.

On souhaite pouvoir créer des zones avec ces configurations.

```java
public interface Boss extends Monstre {
  void chargerAttaqueSpeciale();
}

public class Troll implements Boss {

  private int puissanceMassue;

  public Troll(int puissanceMassue) {
    this.puissanceMassue = puissanceMassue;
  }

  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat du Troll contre le joueur...");
  }

  @Override
  public void chargerAttaqueSpeciale() {
    System.out.printf("Chargement de l'attaque coup de massue, puissance : %s\n", puissanceMassue);
  }
}

public class Dracula implements Boss {
  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat de Dracula contre le joueur...");
  }

  @Override
  public void chargerAttaqueSpeciale() {
    System.out.println("Chargement de l'attaque morsure mortelle...");
  }  
}

public abstract class Item {

  private int prixRevente;

  public Item(int prixRevente) {
    this.prixRevente = prixRevente;
  }

  public abstract void afficherCaracteristiques();

  public int getPrixRevente() {
    return this.prixRevente;
  }
}

public class Potion implements Item {

  public Potion(int prixRevente) {
    super(prixRevente);
  }

  @Override
  public void afficherCaracteristiques() {
    System.out.println("Potion qui soigne complètement le joueur.");
  }    
}

public class Parchemin implements Item {

  public Parchemin(int prixRevente) {
    super(prixRevente);
  }

  @Override
  public void afficherCaracteristiques() {
    System.out.println("Parchemin permettant d'invoquer une boule de feu.");
  }    
}

public interface AbstractZoneFactory {

  Monstre creerMonstreNormal();

  Boss creerBoss(); 

  Item creerRecompense();

}

public class ZonePlaineFactory implements AbstractZoneFactory {

  Random random = new Random();

  @Override
  public Monstre creerMonstreNormal() {
    return new Slime();
  }

  @Override
  public Boss creerBoss() {
    return new Troll(5 + random.nextInt(6));
  }

  @Override
  public Item creerRecompense() {
    return new Potion(15);
  }

}

public class ZoneChateauHanteFactory implements AbstractZoneFactory {

  @Override
  public Monstre creerMonstreNormal() {
    return new Fantome();
  }

  @Override
  public Boss creerBoss() {
    return new Dracula();
  }

  @Override
  public Item creerRecompense() {
    return new Parchemin(30);
  }

}

class Joueur {

  private String nom;

  private List<Item> items;

  public Joueur(String nom) {
    this.nom = nom;
  }

  public String getNom() {
    return nom;
  }

  public void ajouterItem(Item item) {
    items.add(item);
  }

}

public class Zone {

  private AbstractZoneFactory factory;

  public Zone(AbstractZoneFactory factory) {
    this.factory = factory;
  }

  public void traverserZoneNormale(Joueur joueur) {
    Random random = new Random();
    int nbEnnemis = random.nextInt(3) + 1;
    for(int i = 0; i < nbEnnemis; i++) {
      Monstre monstre = factory.creerMonstreNormal();
      monstre.combattre(joueur);
    }
  }

  public void traverserZoneBoss(Joueur joueur) {
    Monstre monstre1 = factory.creerMonstreNormal();
    Monstre monstre2 = factory.creerMonstreNormal();
    Boss boss = factory.creerBoss();
    boss.chargerAttaqueSpeciale();
    monstre1.combattre(joueur);
    monstre2.combattre(joueur);
    boss.combattre(joueur);
  }

  private void ouvrirCoffre(Joueur joueur) {
    System.out.println("Le joueur ouvre un coffre!");
    Item recompense = factory.creerRecompense();
    recompense.afficherCaracteristiques();
    System.out.printf("Prix de revente : %s\n", recompense.getPrixRevente());
    joueur.ajouterItem(recompense);
  }

}

public class Main {

  public static void main(String[]args) {
    Zone plaine = new Zone(new ZonePlaineFactory());
    plaine.traverserZoneNormale();
    plaine.ouvrirCoffre();
    plaine.ouvrirCoffre();
    plaine.traverserZoneBoss();

    Zone chateau = new Zone(new ZoneChateauHanteFactory());
    chateau.traverserZoneNormale();
    chateau.ouvrirCoffre();
    chateau.ouvrirCoffre();
    chateau.traverserZoneBoss();
  }

}
```

<div style="text-align:center">
![Fabrique 6]({{site.baseurl}}/assets/TP4/Fabrique6.svg){: width="80%" }
</div>

Cette solution aurait pu être implémentée en utilisant trois méthodes fabriques, mais nous avons préféré séparer la logique de création des objets dans une classe à part et l'injecter dans la classe `Zone` plutôt que de créer plusieurs sous-classes zones spécifiques (comme auparavant). Cette approche permet de renforcer l'application du principe **d'inversion des dépendances**, par ailleurs.

Il est très facile d'adapter cette solution afin de **changer de famille utilisée dans la zone** (si besoin), sans avoir besoin de changer le code de notre fabrique. De plus, on respecte ainsi le principe ouvert/fermé, car si on souhaite créer une nouvelle famille de classes (un nouveau type de zone), on a juste à ajouter une nouvelle fabrique. Cela permet aussi de limiter la duplication de code si un autre type de **service** utilise notre fabrique.

Adaptons un peu notre solution :

```java
public class Zone {

  private AbstractZoneFactory factory;

  public Zone(AbstractZoneFactory factory) {
    this.factory = factory;
  }

  ...

  //Permet de changer dynamiquement la fabrique utilisée
  public void setFactory(AbstractZoneFactory factory) {
    this.factory = factory;
  }

}

public class Arene {

  private AbstractZoneFactory factory;

  public Arene(Joueur combattant, AbstractZoneFactory factory) {
    this.combattant = combattant;
    this.factory = factory;
  }

  public void nouveauCombat() {
    Monstre monstre = factory.creerMonstreNormal();
    monstre.combattre(combattant);
    Item recompense = factory.creerRecompense();
    item.afficherCaracteristiques();
    joueur.ajouterItem(item);
  }

}

public class Main {

  public static void main(String[]args) {
    Zone zone = new Zone(new ZonePlaineFactory());
    zone.traverserZoneNormale();
    zone.ouvrirCoffre();
    zone.ouvrirCoffre();
    zone.traverserZoneBoss();

    //Le joueur change de zone...
    zone.setFactory(new ZoneChateauHanteFactory());
    zone.traverserZoneNormale();

    //Arene dans une plaine...
    Arene arenePlaine = new Arene(new ZonePlaineFactory());
    arenePlaine.nouveauCombat();
  }

}
```

À noter qu'il est bien sûr possible de coupler cela avec des **singletons** pour les fabriques **concrètes** (même si ce 'nest pas du tout obligatoire et qu'on pourrait s'en passer) :

```java
public class ZonePlaineFactory implements AbstractZoneFactory {

  private static AbstractZoneFactory INSTANCE;

  private ZonePlaineFactory() {}

  public synchronized static AbstractZoneFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new ZonePlaineFactory();
    }
    return INSTANCE;
  }

  ...

}

public class ZoneChateauHanteFactory implements AbstractZoneFactory {

  private static AbstractZoneFactory INSTANCE;

  private ZoneChateauHanteFactory() {}

  public synchronized static AbstractZoneFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new ZoneChateauHanteFactory();
    }
    return INSTANCE;
  }

  ...
}

public class Main {

  public static void main(String[]args) {
    Zone plaine = new Zone(ZonePlaineFactory.getInstance());
    plaine.traverserZoneNormale();
    plaine.ouvrirCoffre();
    plaine.ouvrirCoffre();
    plaine.traverserZoneBoss();

    Zone chateau = new Zone(ZoneChateauHanteFactory.getInstance());
    chateau.traverserZoneNormale();
    chateau.ouvrirCoffre();
    chateau.ouvrirCoffre();
    chateau.traverserZoneBoss();
  }

}
```

<div style="text-align:center">
![Fabrique 7]({{site.baseurl}}/assets/TP4/Fabrique7.svg){: width="80%" }
</div>

L'objectif du pattern **Fabrique Abstraite** est donc de disposer d'une abstraction (classe abstraite ou interface) qui définie le contrat que doivent remplir les fabriques concrètes. Pour chaque famille de classes, on crée une fabrique concrète qui implémente cette interface ou étend cette classe abstraite. Ensuite, toutes les classes qui souhaitent utiliser cette fabrique doivent dépendre de la **fabrique abstraite** et non plus d'une fabrique concrète. Couplé à de l'injection de dépendances, il est très facile de complètement changer le comportement d'une classe.

C'est globalement l'idée du pattern **Stratégie** que vous avez déjà vu lors du dernier TP, mais appliqué pour des fabriques ! On pourrait voir la **fabrique abstraite** comme une **stratégie de création**.

On peut généraliser ce **pattern** ainsi :

<div style="text-align:center">
![Fabrique Abstraite 1]({{site.baseurl}}/assets/TP4/FabriqueAbstraite1.svg){: width="60%" }
</div>

<div class="exercise">

1. Refactorez le code de la classe `Armee` (toujours dans `fabrique2.v2`) afin d'utiliser une **fabrique abstraite** à la place de votre solution (certaines classes vont probablement disparaître...).

2. Insérez et complétez la méthode suivante dans `Armee` :

  ```java
  /**
   * Action : l'armée "this" bat l'armée "armee" passée en paramètre et lui impose sa stratégie de création de ressources (unites, armes, sort).
   * L'armée vaincue doit donc changer de comportement : les ressources créées dans le futur correspondront à ceux de l'armée vainqueuse "this".
   *
   */
  public void vaincre(Armee armee) {
  
  }
  ```

  Vous pouvez éventuellement ajouter une autre méthode, au besoin.

3. Vérifiez que le code suivant fonctionne (à ajouter à la fin du `Main`) :

  ```java
  //L'armée humaine bat l'armée orc
  armeeHumaine.vaincre(armeeOrc);

  armeeOrc.fabriquerUneArmeDeSiege();
  armeeOrc.recruterUnite();

  System.out.println("Nouvelle attaque de l'ancienne armée orc battue par les humains");
  //Il y a les anciennes catapultes et un canon
  armeeOrc.attaquerAvecArmesDeSiege();

  //Il y a les anciens orcs et un humain
  armeeOrc.attaquerAvecUnites();

  //C'est un sort de boule de feu
  armeeOrc.utiliserSortSpecial();
  ```

</div>

### Construction de donjons

<div class="exercise">

1. Ouvrez le paquetage `fabrique4`. Cette application permet de construire des **donjons** pour un jeu-vidéo. Un **donjon** est constitué de différentes salles (des pièces avec des coffres, des pièces avec des ennemis, des pièces avec des énigmes, des pièces avec des boss...). Une salle peut être complétée par le joueur ou non. Chaque donjon possède un algorithme de génération qui permet de l'agrandir en créant de nouvelles salles. Quand on étend le donjon, on crée et on ajoute des salles au donjon dans un ordre précis (avec un peu d'aléatoire). Une extension du donjon ajoute des "salles normales", des "salles spéciales" et une "salle finale", dans cet ordre :

    * Une salle normale

    * Cinq salles spéciales

    * Une salle normale

    * Une salle spéciale

    * Une salle normale

    * Une salle finale

    Pour l'instant, dans sa configuration actuelle, on a les correspondances suivantes :

    * Salle normale : Une salle avec un coffre

    * Salle spéciale : Une salle contenant entre 1 et 5 ennemis ou bien une salle avec une énigme (une chance sur deux)

    * Salle finale : Une salle avec un Boss avec un niveau entre 1 à 10.

2. Actuellement, le donjon est configuré pour créer des configurations de salles "faciles" quand il est étendu. On aimerait introduire le fait d'étendre le donjon avec des configurations de salles "difficile" (toujours en gardant le même algorithme/ordre de création des salles) où on a les correspondances suivantes :

    * Salle normale : Une salle contenant entre 20 et 40 ennemis.

    * Salle spéciale : Une salle avec une énigme (20% de chances) ou bien une salle avec un boss avec un niveau entre 30 à 50 (80% de chances).

    * Salle finale : Une salle avec un Boss de niveau 80.

    Refactorez votre code afin qu'il soit possible d'étendre le donjon avec des salles "difficiles" en plus du fait de pouvoir l'étendre avec des salles faciles (qui est la configuration des salles ajoutées actuellement dans la méthode `etendreDonjon`).

3. Dans le `Main`, adaptez le code pour faire en sorte d'étendre le donjon d'exemple fournit une fois avec des salles **faciles** et deux fois avec des salles **difficiles**. 

4. La méthode `getInfosSalle` doit permettre de récupérer les informations d'une salle du donjon "à l'extérieur". Cependant, son implémentation est problématique... Par exemple, que pourriez-vous faire comme action indésirable en récupérant une salle d'un `Donjon` dans le `Main` (indice : seul le donjon devrait avoir le droit de modifier l'état de ses salles) ? Quel pattern que nous avons vu pendant ce TP pourriez-vous appliquer pour régler ce problème ? Refactorez votre code dans ce sens.

5. Générez le **diagramme de classes de conception** de votre application (avec `IntelliJ`).

</div>

### Restaurants de burgers - Partie 2

Revenons une dernière fois sur l'application de gestion de restaurants afin de l'améliorer.

<div class="exercise">

1. Ouvrez le paquetage `fabrique3` puis `v2`. Il s'agit de la deuxième partie de l'exercice. Comme vous pouvez le constater, les différents ingrédients qui étaient jusqu'ici des **chaînes de caractères** sont remplacés par des **objets**.

    On a toujours les mêmes recettes que précédemment dans les restaurants **Nîmois** et les restaurants **Montpelliérains** :

   * Nîmes : 
     * **Cheese Burger** : Boeuf Charolais, Sauce à burger de Nîmes et Cheddar.
     * **Egg Burger** : Poulet Gardois, Sauce à burger de Nîmes et Œuf de poule.

   * Montpellier :
     * **Cheese Burger** : Boeuf Limousin, Sauce à burger de Montpellier et Maroilles.
     * **Egg Burger** : Poulet de Bresse, Sauce à burger de Montpellier et Oeuf d'autruche.

2. Commencez par importer et adapter votre ancien code afin de faire en sorte qu'il soit toujours possible de gérer les deux types de restaurants : les **restaurants Nîmois** et les **restaurants Montpelliérains** (la seule chose qui change sont les ingrédients qui sont maintenant des objets). Importez et/ou complétez aussi le code du `Main` et assurez-vous que tout fonctionne.

3. On remarque que les restaurants Nîmois et les restaurants Montpelliérains utilisent **un ensemble d'ingrédients spécifique en local** pour la composition de leurs burgers :

   * Nîmes :
     * Bœuf : Bœuf Charolais
     * Poulet : Poulet Gardois
     * Fromage : Cheddar
     * Sauce : Sauce à burger de Nîmes

   * Montpellier :
     * Bœuf : Bœuf Limousin
     * Poulet : Poulet de Bresse
     * Fromage : Maroilles
     * Sauce : Sauce à burger de Montpellier

    Globalement, à Nîmes, tous les burgers qui auront besoin de fromage utiliseront du Cheddar et à Montpellier du Maroilles. Pareil pour le bœuf, le poulet et la sauce.

    En sachant cela, il y a donc une duplication de code au niveau de la création des burgers. Par exemple, on sait très bien que chaque fois qu'un burger nîmois aura besoin de bœuf, on utilisera du bœuf Charolais. Pareil pour la sauce, etc. Et on veut pouvoir facilement changer le type de bœuf utilisé (ou autre) sans avoir à changer le code de tous les burgers !

4. Proposez une solution adéquate pour faire en sorte d'utiliser un ensemble d'ingrédient spécifique (qui soit facile de changer) pour la création des burgers selon le type de restaurant (Nîmes / Montpellier). Vous adapterez au besoin le `main` de la classe `Main`.

</div>

### Combats de monstres

Parfois, il n'est pas nécessairement souhaitable d'avoir la possibilité d'utiliser toutes les fabriques en même temps (on doit alors pointer l'instance de la fabrique qu'on souhaite utiliser). Il faut donc trouver un moyen d'en sélectionner une seule, mais aussi de pouvoir facilement changer la fabrique concrète utilisée. Nous allons voir cela dans cet exercice.

<div class="exercise">

1. Ouvrez le paquetage `fabrique5`. C'est le retour des **pokémons** ! Mais il y a également une nouvelle famille de monstres : **les digimons** qui ont un fonctionnement similaire aux pokémons mais ont en plus un système d'énergie. En tout cas, ils se créent de la même manière que les pokémons ou plus généralement, qu'un "monstre".

2. Actuellement, dans le `Main`, on crée des pokémons et on utilise le simulateur de combat pour en faire combattre deux. À la place des pokémons, on voudrait parfois utiliser des digimons. Maintenant que vous connaissez le pattern **Fabrique Abstraite** refactorez le code afin de pouvoir facilement switcher entre des combats avec divers pokémons et des combats avec divers digimons. Si vous rencontrez quelques petits problèmes, regardez les méthodes de `Digimon`... ne serait-il pas judicieux de lui faire implémenter une certaine interface ? Et pour les différentes sous-classes de `Digimon` ? (`DigimonEau`, `DigimonFeu`...). Vous devrez aussi adapter le `Main` et `SimulateurCombat`.

3. Contrairement à l'exercice précédent sur les **donjons**, on ne veut pas que les deux fabriques cohabitent à un instant t du programme. On veut que l'application fonctionne exclusivement avec des pokémons ou bien fonctionne exclusivement avec des digimons. Mais on ne veut pas changer manuellement l'instance de la fabrique utilisée partout dans le code source. Il faut imaginer que cette fabrique est probablement utilisée à divers endroits et surtout, qu'on ne souhaite pas recompiler le code source à chaque changement. Comment pourrions-nous faire ?

</div>

Nous sommes dans un cas particulier où tout le programme va utiliser une seule et même instance d'une fabrique donnée, même s'il y a en a plusieurs à disposition. Par exemple, imaginons qu'une application utilise des fabriques pour gérer la connexion à une source de données afin de stocker les données du programme. Une première fabrique permet de stocker les informations dans une base de données, une deuxième dans un fichier XML. Pendant que le programme tournera, on utilisera qu'une seule source de données, mais pas les deux à la fois. Néanmoins, on utilise quand même une fabrique abstraite pour pouvoir changer facilement de source de stockage à l'avenir (par exemple, avec une configuration "test" utilisant une base de données en mémoire...)

Mais comment faire cela sans modifier l'instance concrète utilisée un peu partout ? (car elle est surement injectée à différentes classes). La réponse est simple : il faut regrouper la logique qui instancie la classe concrètement utilisée à un seul endroit. On peut ensuite mettre un système de paramétrage qui permet de changer la fabrique utilisée facilement. Les classes qui ont besoin de cette fabrique iront donc appeler une méthode de cette classe afin de récupérer la fabrique concrète à utiliser.

La question est de savoir : où placer ce bout de code ? Il n'y a pas vraiment de réponse officielle à cette question. Cela pourrait être dans une classe indépendante (qui gère la **configuration** du programme) avec une méthode statique. Parfois, on retrouve aussi ce bout de code directement dans la **Fabrique Abstraite** par exemple en stockant l'instance de la fabrique concrète utilisée, couplé à une méthode statique permettant de renvoyer l'instance. C'est une sorte de dérivé du pattern `Singleton` (sans l'être réellement).

Pour gérer l'instance concrète utilisée, on pourrait par exemple utiliser un **fichier de configuration** : lors de son initialisation, le code chargé de déterminer quelle est la fabrique à utiliser va lire dans ce fichier pour déterminer quelle fabrique instancier et stocker.

Par exemple, imaginons que nous souhaitons que notre **Jeu**, à un instant T, ne fonctionne qu'avec des **Plaines** ou qu'avec des **Châteaux Hantés** :

```java
// On transforme notre interface en classe abstraite, car elle contient du code
// Elle stocke l'instance concrète de la fabrique utilisée
public abstract class AbstractZoneFactory {

private static AbstractZoneFactory INSTANCE;

  public synchronized static AbstractZoneFactory getInstance() {
    if(INSTANCE == null) {
      try {
            InputStream stream = ClassLoader.getSystemResourceAsStream("config/zone_factory_config.txt");
            if(stream == null) {
                throw new RuntimeException("Fichier de configuration manquant.");
            }
            BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
            String config = reader.readLine();
            switch (config) {
              case "plaine" :
                INSTANCE = new ZonePlaineFactory();
                break;
              case "chateau" : 
                INSTANCE = new ZoneChateauHanteFactory();
                break;
              default: 
                throw new IllegalArgumentException(String.format("Type de zone inconnue : %s", config));
            }
      } catch (IOException e) {
          throw new RuntimeException("Fichier de configuration corrompu.");
      }
    }
    return INSTANCE;
  }

  public abstract Monstre creerMonstreNormal();

  public abstract Boss creerBoss(); 

  public abstract Item creerRecompense();

}

//Les fabriques concrètes ne sont plus des singletons (si c'était le cas avant)
public class ZonePlaineFactory extends AbstractZoneFactory {
  ...
}

public class ZoneChateauHanteFactory extends AbstractZoneFactory {
  ...
}

public class Main {

  public static void main(String[]args) {
    Zone zone = new Zone(AbstractZoneFactory.getInstance());
    zone.traverserZoneNormale();
    zone.ouvrirCoffre();
    zone.ouvrirCoffre();
    zone.traverserZoneBoss();
  }

}
```

<div style="text-align:center">
![Fabrique 8]({{site.baseurl}}/assets/TP4/Fabrique8.svg){: width="70%" }
</div>

La fabrique abstraite vise un fichier qui se situe dans `src/main/resources/config/zone_factory_config.txt` qui contient simplement une chaîne de caractères. Par exemple : `chateau`.

Avec cette nouvelle implémentation, il n'y a plus qu'à changer le contenu du fichier de configuration pour changer la fabrique concrète manipulée dans tout le programme. On notera qu'il n'y a plus besoin que les sous-classes soient des **singletons** (si c'était le cas avant), car elles sont instanciées par la fabrique abstraite. Cependant, on pourrait empêcher le fait que n'importe qui puisse instancier les fabriques concrètes en passant leurs constructeurs en visibilité `protected` (afin que seule `AbstractZoneFactory` puisse les instancier).

Bien sûr, cette implémentation n'est pas forcément souhaitable dans tous les contextes ! C'est seulement si, à un instant T, on veut uniquement avoir un seul type de fabrique concrète utilisé et pouvoir en changer facilement (d'ailleurs, l'exemple donné est discutable, parce qu'on voudrait à priori pouvoir créer plusieurs types de zones différentes à la fois).

De plus, on peut aussi discuter du fait que le code gérant la sélection de la fabrique concrète soit stocké dans la fabrique abstraite. Pour obtenir une meilleure répartition des **responsabilités**, on pourrait éventuellement déléguer cela à une classe dédiée (et donc laisser la fabrique abstraite comme une interface).

<div class="exercise">

1. Créez un dossier `config` dans `src/main/resources/` puis, à l'intérieur de ce nouveau répertoire, un fichier `monstres_factory_config.txt`.

2. Refactorez le code de l'application afin qu'il soit possible d'utiliser soit les pokémons, soit les digimons en changeant simplement le contenu du fichier de configuration.

3. Testez les deux versions !

4. Générez le **diagramme de classes de conception** de votre application (avec `IntelliJ`).

</div>

Ici, cet exemple d'implémentation avec un fichier de configuration n'est bien sûr pas spécifique au pattern fabrique abstraite. On pourrait l'appliquer sur tout ce qui est abstrait et qui n'a besoin que d'une instance lors de l'exécution du programme. On pourra faire la même chose couplée au pattern **Stratégie** par exemple.

La gestion des instances concrète se fait généralement au travers d'un outil dédié appelé **conteneur de dépendances** (ou **conteneur IoC**) qui est utilisé dans de nombreux **frameworks**. Il permet notamment de limiter la multiplication des singletons inutiles.

### Intégrer une librairie externe

Les pokémons et les digimons sont des classes qui ont été créées par le développeur de ce projet et où il est donc possible de réarranger le code pour que tout fonctionne. Mais que se passerait-il si nous voulions intégrer à notre système du code sur lequel nous n'avons pas la main (dont nous ne pouvons pas éditer le code source) ? Par exemple, des classes compilées qui proviennent d'une librairie.

Pour illustrer ce problème, voyons un nouvel exemple. Vous souhaitez développer une application qui permet à un utilisateur de saisir le titre d'un film afin d'afficher la note moyenne et les critiques (des utilisateurs) de ce dernier. Dans ce scénario, on considérera qu'il n'existe pas deux films avec le même titre.

Pour récupérer les différentes informations (savoir si le film existe, note, critiques...) vous souhaitez vous servir du site **Allociné**. Il n'existe pas de librairie dédiée qui permet d'extraire les informations de ce site, il est donc nécessaire d'implémenter le code correspondant.

```java
public class ClientFilm {

  private Scanner scan = new Scanner(System.in);

  public void chercherInformationsFilm() {
    System.out.print("Saisir le nom du film : ");
    String nomFilm = scan.nextLine();
    if(!filmExiste(nomFilm)) {
      System.err.println("Le film n'existe pas");
      return;
    }
    double note = recupererNoteMoyenneUtilisateurs(nom);
    String[] avisUtilisateurs = recupererAvis(nom);
    System.out.printf("Le film a une note de : %s\n", note);
    System.out.println("Avis : ");
    for(String avis : avisUtilisateurs) {
      System.out.println(avis);
    }
  }

  private boolean filmExiste(String nomFilm) {
    // Code complexe permettant de déterminer si un film est bien répertorié sur Allociné
  }

  private double recupererNoteMoyenneUtilisateurs(String nomFilm) {
    // Code complexe permettant de récupérer la note moyenne du film, donnée par les utilisateurs sur Allociné
  }

  private String[] recupererAvis(String nomFilm) {
    // Code complexe permettant de récupérer les avis des utilisateurs à propos du Film sur Allociné
  }

}
```

Comme vous êtes maintenant un expert des principes `SOLID`, vous vous rendez-compte que cette implémentation ne respecte pas bien le principe de **responsabilité unique**. En effet, si le code relatif à l'extraction des données du film change ou que le code interagissant avec l'utilisateur change, la classe `ClientFilm` doit changer. Elle possède trop de responsabilité.

Vous proposez donc une nouvelle implémentation de meilleure qualité :

```java
public class ExtracteurAllocine {

  public boolean filmExiste(String nomFilm) {
    //Code complexe permettant de déterminer si un film est bien repertorié sur Allociné
  }

  public double recupererNoteMoyenneUtilisateurs(String nomFilm) {
    //Code complexe permettant de récupérer la note moyenne du film, donnée par les utilisateurs sur Allociné
  }

  public String[] recupererAvis(String nomFilm) {
    //Code complexe permettant de récupérer les avis des utilisateurs à propos du Film sur Allociné
  }

}

public class ClientFilm {

  private Scanner scan = new Scanner(System.in);

  private ExtracteurAllocine extracteur = new ExtracteurAllocine();

  public void chercherInformationsFilm() {
    System.out.print("Saisir le nom du film : ");
    String nomFilm = scan.nextLine();
    if(!extracteur.filmExiste(nomFilm)) {
      System.err.println("Le film n'existe pas");
      return;
    }
    double note = extracteur.recupererNoteMoyenneUtilisateurs(nom);
    String[] avisUtilisateurs = extracteur.recupererAvis(nom);
    System.out.printf("Le film a une note de : %s\n", note);
    System.out.println("Avis : ");
    for(String avis : avisUtilisateurs) {
      System.out.println(avis);
    }
  }

}
```

Le code est déjà mieux, mais on pourrait encore améliorer cela en faisant en sorte que `ClientFilm` dépende plutôt d'une **abstraction** afin d'appliquer le principe **d'inversions des dépendances**. On pourrait aussi utiliser **l'injection de dépendances** plutôt que d'initialiser `ExtracteurAllocine` dans `ClientFilm`. Cela permettrait de rendre le code plus flexible (et testable) et prévoir l'ajout d'éventuelles extensions de l'application :

```java
public interface Extracteur {
  boolean filmExiste(String nomFilm);
  double recupererNoteMoyenneUtilisateurs(String nomFilm);
  String[] recupererAvis(String nomFilm);
}

public class ExtracteurAllocine implements Extracteur {

  @Override
  public boolean filmExiste(String nomFilm) {
    //Code complexe permettant de déterminer si un film est bien repertorié sur Allociné
  }

  @Override
  public double recupererNoteMoyenneUtilisateurs(String nomFilm) {
    //Code complexe permettant de récupérer la note moyenne du film, donnée par les utilisateurs sur Allociné
  }

  @Override
  public String[] recupererAvis(String nomFilm) {
    //Code complexe permettant de récupérer les avis des utilisateurs à propos du Film sur Allociné
  }

}

public class ClientFilm {

  private Scanner scan = new Scanner(System.in);

  private Extracteur extracteur;

  public ClientFilm(Extracteur extracteur) {
    this.extracteur = extracteur;
  }

  public void setExtracteur(Extracteur extracteur) {
    this.extracteur = extracteur;
  }

  public void chercherInformationsFilm() {
    System.out.print("Saisir le nom du film : ");
    String nomFilm = scan.nextLine();
    if(!extracteur.filmExiste(nomFilm)) {
      System.err.println("Le film n'existe pas");
      return;
    }
    double note = extracteur.recupererNoteMoyenneUtilisateurs(nom);
    String[] avisUtilisateurs = extracteur.recupererAvis(nom);
    System.out.printf("Le film a une note de : %s\n", note);
    System.out.println("Avis : ");
    for(String avis : avisUtilisateurs) {
      System.out.println(avis);
    }
  }

}
```

Avec cette nouvelle implémentation, il est possible d'ajouter de nouvelles **stratégies** pour récupérer des informations. Par exemple, si on souhaite utiliser d'autres sites (à la place de **Allocine**). D'ailleurs, c'est ce que nous allons faire tout de suite ! 

Vous souhaitez qu'on puisse aller extraire les informations du film cherché sur les plateformes **Sens Critique** et **Rotten Tomatoes**. Contrairement à **Allocine**, il existe des **librairies** (dans notre exemple) qui permettent de récupérer les informations des films sur ces deux sites ! Vous n'aurez donc pas à implémenter le code correspondant !

Vous installez donc les deux librairies correspondantes au travers de `Maven`, ce qui installe et configure correctement le fichier `.jar` contenant les classes qui vont vous êtres utiles.

Du côté de **Sens Critique**, on a une classe `SensCritiqueAPI` qui permet de réaliser les actions désirées (et d'autres qui sont inutiles). Lors de la création de l'objet, il faut préciser la version de l'API utilisée.

```java
public final class SensCritiqueAPI {

  public SensCritiqueAPI(int versionApi) {
    System.out.printf("Connexion à la version %s de l'API...\n", versionApi);
  }

  /**
   * Renvoie 0 si le film n'existe pas et 1 si le film existe.
   */
  public int verifierFilm(String film) {
    /* 
      Code complexe permettant de savoir si un film existe ou non.
      Le type de retour est étrange (il aurait été préférable de renvoyer un booléen) mais la librairie ne nous appartient pas, 
      on ne peut pas modifier cela.
    */
  }

  public double obtenirNoteUtilisateurs(String film) {
    //Code complexe permettant de récupérer la note moyenne du film, donnée par les utilisateurs sur Sens Critique
  }

  public double obtenirNotePresse(String film) {
    //Code complexe permettant de récupérer la note moyenne du film, donnée par la presse sur Sens Critique
  }

  public List<String> obtenirCritiquesUtilisateurs(String film) {
    //Code complexe permettant de récupérer les critiques des utilisateurs à propos du Film sur Allociné
  }

  public Map<String, String> obtenirInformationsTechniquesFilm(String film) {
    //Code complexe permettant d'obtenir les informations techniques du film (genre, annee, realisateur, etc...)
  }

}
```

Du côté de **Roten Tomatoes**, on a une classe `Movie` qui contient toutes les informations relatives à un film (dont celles désirées) et une classe `RottenTomatoesDataExtractor` qui permet d'obtenir des objets type `Movie` à partir de leur nom. Cette classe est d'ailleurs un **singleton**.

```java
public class Movie {

  private String name;

  private String category;

  private double note;

  private String[] reviews;

  public Movie(String name, String category, double note, String[] reviews) {
    this.name = name;
    this.category = category;
    this.note = note;
    this.review = reviews;
  }

  public String getName() {
    return name;
  }

  public String getCategory() {
    return category;
  }

  public double getNote() {
    return note;
  }

  public String[] getReviews() {
    return reviews;
  }

}

public final class RottenTomatoesDataExtractor {

  private static RottenTomatoesDataExtractor INSTANCE;

  private RottenTomatoesDataExtractor() {}

  public static synchronized RottenTomatoesDataExtractor getInstance() {
    if(INSTANCE == null) {
      INSTANCE = RottenTomatoesDataExtractor();
    }
    return INSTANCE;
  }

  /**
   * Renvoie null si le film n'existe pas
   */ 
  public Movie getMovieInformation(String movieName) {
    //Code complexe permettant d'obtenir un objet type "Movie" contenant les informations d'un film à partir du site Rotten Tomatoes
  }

}
```

<div style="text-align:center">
![Adaptateur 1]({{site.baseurl}}/assets/TP4/Adaptateur1.svg){: width="70%" }
</div>

Tout est donc parfait ! Non...?

Peut-être que vous vous en êtes rendu compte, mais il est impossible de faire fonctionner ce code avec notre classe `ClientFilm`, elle attend des objets de type `Extracteur`. Or, les classes `SensCritiqueAPI` et `RottenTomatoesDataExtractor` n'implémentent pas cette interface (ce qui est normal : elles viennent d'une librairie externe). Et de toute manière les classes en question ont un fonctionnement un peu différent. Les types d'objets retournés et les méthodes utilisées ne sont pas forcément compatibles. Et il est bien sûr **impossible de modifier le code de ces classes** (toujours parce qu'elles viennent d'une librairie que vous ne pouvez pas éditer). Ces classes ne peuvent pas être utilisées en l'état, dans notre système.

Que faire alors ? Laisser tomber ces librairies et écrire notre propre code (deux nouvelles classes implémentant `Extracteur`) ? Cela serait réinventer la roue. Ou bien copier/coller le code de ces classes ? Cela serait du plagiat (et donc du vol) ! Etendre les classes et faire implémenter l'interface `Extracteur` aux classes filles ? Cela ne sent pas très bon, et c'est de toute façon impossible, car les deux classes sont déclarées comme `final`.

Cela semble compromis ! Mais pas de panique, un design pattern résout ce problème : `Adaptateur`.

L'objectif de ce pattern est de faire en sorte qu'une classe "incompatible" avec notre architecture puisse tout de même être utilisée en passant par une classe dite **adaptateur** qui fait le pont entre votre architecture et cette classe grâce à de la **composition** (encore et toujours !). C'est un peu comme quand vous voyagez au Royaume-Uni par exemple. Les prises électriques ne sont pas compatibles avec la prise de votre chargeur de téléphone. Vous devez alors utiliser un adaptateur entre la prise de votre chargeur et celle anglaise.

Ici, la "prise du chargeur" est votre architecture, les interfaces, les abstractions, l'adaptateur la classe qui va être amenée par le pattern et la prise anglaise la classe "externe" que vous souhaitez utiliser.

Voici comment appliquer ce pattern :

1. Créer une classe dite **Adapter** qui possède un attribut du type de la classe à adapter. Cet attribut peut être injecté via le constructeur ou bien, dans certains cas, directement construit dans la classe **Adapter**.

2. Faire implémenter à notre **Adapter** l'interface souhaitée ou lui faire implémenter l'interface souhaitée ou bien étendre la classe abstraite souhaitée.

3. L'implémentation de chaque méthode de l'interface (ou méthodes abstraites) se fera par **délégation** en appelant des méthodes sur la classe cible. Le code de l'adaptateur fera donc une **adaptation** du code en réalisant des appels sur le **délégué** afin de réaliser la bonne action et/ou renvoyer la bonne information (bon type, bonne structure, etc).

Ce pattern s'appelle `Adaptateur`, car il utilise et **adapte** les fonctionnalités (méthodes) fournies par une classe pour les rendre compatibles avec notre besoin. Dans certains cas, un simple appel de méthode au **délégué** ne suffit pas, il faut faire différentes opérations intermédiaires afin de réaliser l'action souhaitée.

Donc notre exemple, nous allons donc créer deux **adaptateurs** : un pour la classe `SensCritiqueAPI` et l'autre pour `RottenTomatoesDataExtractor`. L'objectif est d'utiliser ces classes pour renvoyer les différentes informations souhaitées par l'interface `Extracteur` et ainsi rendre le tout compatible avec `ClientFilm` en profitant du code déjà écrit dans les librairies.

```java
public class ExtracteurSensCritiqueAdaptateur implements Extracteur {

  private SensCritiqueAPI api;

  public SensCritiqueAdaptateur(SensCritiqueAPI api) {
    this.api = api;
  }

  @Override
  public boolean filmExiste(String nomFilm) {
    return api.verifierFilm(nomFilm) == 1;
  }

  @Override
  public double recupererNoteMoyenneUtilisateurs(String nomFilm) {
    return api.obtenirNoteUtilisateurs(nomFilm);
  }

  @Override
  public String[] recupererAvis(String nomFilm) {
    List<String> avis = api.obtenirCritiquesUtilisateurs(nomFilm);
    String[] avisTab = new String[avis.size()];
    avis.toArray(avisTab);
    return avisTab;
  }

}

public class ExtracteurRottenTomatoesAdaptateur implements Extracteur {

  private RottenTomatoesDataExtractor extractor;

  public RottenTomatoesDataExtractor(RottenTomatoesDataExtractor extractor) {
    this.extractor = extractor;
  }

  @Override
  public boolean filmExiste(String nomFilm) {
    return extractor.getMovieInformation(nomFilm) != null;
  }

  @Override
  public double recupererNoteMoyenneUtilisateurs(String nomFilm) {
    Movie movie = extractor.getMovieInformation(nomFilm);
    return movie.getNote();
  }

  @Override
  public String[] recupererAvis(String nomFilm) {
    Movie movie = extractor.getMovieInformation(nomFilm);
    return movie.getReviews();
  }

}

public class Main {
  
  public static void main(String[] args) {
    Extracteur allocine = new ExtracteurAllocine();
    Extracteur sensCritique = new ExtracteurSensCritiqueAdaptateur(new SensCritiqueAPI(2));
    Extracteur rottenTomatoes = new ExtracteurRottenTomatoesAdaptateur(RottenTomatoesDataExtractor.getInstance());
    ClientFilm client = new ClientFilm(allocine);

    //Recherche des informations d'un film sur Allociné
    client.chercherInformationsFilm();

    //Recherche des informations d'un film sur Sens Critique
    client.setExtracteur(sensCritique);
    client.chercherInformationsFilm();

    //Recherche des informations d'un film sur Rotten Tomatoes
    client.setExtracteur(rottenTomatoes);
    client.chercherInformationsFilm();
  }

}
```

<div style="text-align:center">
![Adaptateur 2]({{site.baseurl}}/assets/TP4/Adaptateur2.svg){: width="90%" }
</div>

Maintenant, revenons à nos petits monstres...

<div class="exercise">

1. Une librairie nommée `patternmon` est importée dans le projet ! Explorez ses classes en allant dans `src/main/resources/libs/patternmons.jar` (normalement, l'IDE vous permet de voir les classes contenues dans le `.jar`). **Attention**, si vous travaillez sur une machine de l'IUT, il est probable que vous deviez utiliser le JDK 19 que vous pouvez installer via IntelliJ (dans **File**, **Project Structure**...). Dans ce cas il faudra aussi changer le fichier `pom.xml` du projet en changeant les deux "17" et "19".

2. Comme vous pouvez le constater, cette librairie définit de nouveaux monstres "patternmons" qu'on souhaite maintenant intégrer à notre système de simulation de combat. Comme vous l'avez deviné, nous allons donc devoir mettre en place un `Adaptateur` ! Cependant, comme il y a une hiérarchie de classes ici, la mise en place va être un poil plus complexe que sur notre exemple, donc nous allons le faire pas à pas :

    * Commencez par implémenter une classe abstraite `PatternmonAdapter` qui permet d'adapter la classe abstraite `Patternmon`. Normalement, vous ne devriez pas trop avoir de difficulté, c'est quasiment comme dans l'exemple.

    * `Patternmon` est une classe abstraite et nous avons besoin de pouvoir adapter ses classes filles concrètes (correspondant à `MonstreEau`, `MonstreFeu`, etc.). Il faut créer un adaptateur par classe fille ! Cet adaptateur devra **étendre** votre adaptateur abstrait `PatternmonAdapter` et implémenter l'interface `MonstreX` correspondante (`MonstreEau` pour l'adaptation de `WaterPatternmon` par exemple).
    
    * Commencez par tenter d'adapter `WaterPatternmon`. Vous allez sans doute rencontrer une difficulté lorsque vous allez essayer d'implémenter les méthodes propres à l'interface. Dans un premier temps, essayez de résoudre cela par vous-même, puis, après quelques essais, lisez la prochaine section.

</div>

Le problème que vous avez dû rencontrer est le suivant : dans un de vos adaptateurs concrets, vous n'aviez pas accès au `Patternmon` passé à la classe parente. Une solution que vous avez peut-être mise en place et de changer la visibilité de cet attribut en `protected`, mais même là, vous aviez sans doute des erreurs ! 

Voyons un peu tout ça :

```java 
public abstract class PatternmonAdapter implements Monstre {

    protected Patternmon patternmon;

    //...

}

public class PatternmonEauAdapter extends PatternmonAdapter implements MonstreEau {

    //Prend un Waterpatternmon en paramètre et pas un Patternmon !
    public PatternmonEauAdapter(WaterPatternmon patternmon) {
        super(patternmon);
    }

    @Override
    public int getTemperatureMaxEau() {
        //Erreur !
        return this.patternmon.getWaterTemperature();
    }

}
```

Si vous avez bien une implémentation similaire (faites les changements nécessaires si ce n'est pas le cas) vous obtenez une erreur au niveau de la méthode `getTemperatureMaxEau`. Cela est dû au fait que dans la classe mère, l'attribut `patternmon` est du type abstrait `Patternmon` et pas un `Waterpatternmon` ! Donc, dans la classe fille, impossible d'utiliser `getWaterTemperature`.

La première solution "simple" serait de **caster** le patternmon. Normalement, comme on est sûr d'avoir passé au constructeur parent un `Waterpatternmon`, c'est un **cast** sans risques :

```java 
@Override
public int getTemperatureMaxEau() {
    return ((Waterpatternmon) this.patternmon).getWaterTemperature();
}
```

Mais cette solution n'est pas élégante et il en existe une bien meilleure : la **généricité**. Dans la classe mère, il est possible de définir un (ou plusieurs) "type paramétré" qu'on peut par exemple nommer `T`. On peut imposer des restrictions, par exemple, que `T` soit une classe qui descende d'une autre classe spécifique.

Quand une classe enfant étend la classe mère, elle peut alors préciser la classe concrète utilisée à la place de `T`. Ainsi, la classe mère est configurée pour utiliser ce type.

Petite démonstration sur `PatternmonAdapter` et `PatternmonEauAdapter` :

```java 
// On définit le paramètre générique T lors de la déclaration de la classe
// et on est assuré que T soit un objet qui étend la classe Patternmon
public abstract class PatternmonAdapter<T extends Patternmon> implements Monstre {

    //Peut-être n'importe quel patternmon.
    //Je peux appeler les méthodes de "patternmon" sur cet objet
    protected T patternmon;

    public PatternmonAdapter(T patternmon) {
      this.patternmon = patternmon;
    }

    //...

}

//Quand on étend PatternmonAdapter, on précise la classe concrète utilisée (ici, Watterpatternmon)
//Il faut imaginer que dans la classe mère, le "T" est remplacé par Watterpatternmon.
public class PatternmonEauAdapter extends PatternmonAdapter<Waterpatternmon> implements MonstreEau {

    //Prend un Waterpatternmon en paramètre et pas un Patternmon !
    //Maintenant, on est "forcé" d'utiliser ce constructeur.
    public PatternmonEauAdapter(WaterPatternmon patternmon) {
        super(patternmon);
    }

    @Override
    public int getTemperatureMaxEau() {
        //Plus d'erreurs, car l'attribut "patternmon" dans la classe mère est un Waterpatternmon !
        return this.patternmon.getWaterTemperature();
    }

}
```

Si vous n'avez pas tout compris, n'hésitez pas à en parler avec votre enseignant.

<div class="exercise">

1. Adaptez votre code pour introduire la généricité comme dans l'exemple ci-dessus puis implémentez les classes restantes : `PatternmonElectriqueAdapter`, `PatternmonPsyAdapter`, `PatternmonFeuAdapter` et `PatternmonPlanteAdapter`.

2. Créez une nouvelle fabrique permettant de créer des `patternmons`.

3. Adaptez le code de votre **fabrique abstraite** afin de pouvoir gérer votre nouvelle fabrique.

4. Un simple changement dans le fichier de configuration doit suffire pour utiliser les patternmons. Testez et vérifiez que tout marche bien (les attaques des monstres devraient avoir des noms anglais).

</div>

## Combinaison de patterns

### Décorateur avec Builder

Dans le dernier TP, vous avez découvert le pattern **Décorateur** permettant d'ajouter des nouvelles fonctionnalités de manière dynamique. Nous avions notamment vu un exemple portant sur des salariés, puis un exercice portant sur différents types de produits.

Comme l'objet créé avec le pattern **Décorateur** peut être assez complexe, il peut être intéressant de le coupler avec un **Builder**.

Reprenons l'exemple des salariés et essayons d'appliquer ces deux patterns :

```java
interface SalarieInterface {
  double getSalaire();
  //Prototype
  SalarieInterface clone();
}


class Salarie implements SalarieInterface {

  private double salaire;

  public Salarie(double salaire) {
    this.salaire = salaire;
  }

  private Salarie(Salarie salarieACopier) {
    this(salarieACopier.salaire);
  }

  public double getSalaire() {
    return salaire;
  }

  public SalarieInterface clone() {
    return new Salarie(this);
  }

}

abstract class SalarieDecorateur implements SalarieInterface {

  //Visibilité "protected" nécessaire afin que les classe filles puissent le cloner
  //On aurait aussi pu définir une méthode protected qui clone le salarie délégué (pour que les classes filles ne puissent pas le modifier)
  protected SalarieInterface salarie;

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

  private SalarieChefProjet(SalarieChefProjet chefProjetACopier) {
    this(chefProjetACopier.salarie.clone(), chefProjetACopier.nombreProjetsGeres);
  }

  @Override
  public double getSalaire() {
    return super.getSalaire() + 100 * (nombreProjetsGeres);
  }

  @Override
  public SalarieInterface clone() {
    return new SalarieChefProjet(this);
  }

}

class SalarieResponsableDeStagiaires extends SalarieDecorateur {

  private int nombreStagiairesGeres;

  public SalarieResponsableDeStagiaires(I_Salarie salarie, int nombreStagiairesGeres) {
    super(salarie);
    this.nombreStagiairesGeres = nombreStagiairesGeres;
  }

  private SalarieResponsableDeStagiaires(SalarieResponsableDeStagiaires responsableACopier) {
    this(responsableACopier.salarie.clone(), responsableACopier.nombreStagiairesGeres);
  }

  @Override
  public double getSalaire() {
    return super.getSalaire() + 50 * nombreStagiairesGeres;
  }

  @Override
  public I_Salarie clone() {
    return new SalarieResponsableDeStagiaires(this);
  }

}
```

On peut créer : des salariés simples, des salariés chefs de projet, des salariés responsables de stagiaires et des salariés à la fois chefs de projets et responsables de stagiaires. Si on ajoutait un nouveau type de `Salarie`, cela multiplierait les possibilités...

Sans pattern créateur, il faut donc créer les salariés ainsi :

```java
SalarieInterface salarie1 = new Salarie(2000);
SalarieInterface salarie2 = new SalarieChefProjet(new Salarie(2500), 3);
SalarieInterface salarie3 = new SalarieResponsableDeStagiaires(new Salarie(2300), 5);
SalarieInterface salarie4 = new SalarieChefProjet(new SalarieResponsableDeStagiaires(new Salarie(1800), 4), 2); 
```

Essayons de mettre en place un `Builder` !

Attention, l'implémentation de `Builder` que nous allons présenter est une **adaptation** du pattern `Builder` tel que nous l'avons présenté dans l'exercice correspondant, afin de rendre le tout compatible avec le décorateur :

  * La classe `Builder` va se trouver à l'extérieur de `Produit`. Autrement, cela voudrait dire que `Produit` dépendrait de toutes ses classes filles, et cela ne semble pas très adéquat.

  * Le produit va être instancié dès le départ puis augmenté au fur et à mesure alors que normalement, la cible du builder n'est instanciée que quand on appelle la méthode `build`.

  * La méthode `build` renvoie une **copie** (clone) de l'instance (prototype).

Bref, retenez simplement que c'est une adaptation un peu particulière et qui s'éloigne un peu du pattern de base. Néanmoins, nous allons voir que cette adaptation s'emboîte assez bien avec **décorateur** :

```java
class SalarieBuilder {

  private SalarieInterface salarie;

  public SalarieBuilder(double salaire) {
    salarie = new Salarie(salaire);
  }

  public SalarieBuilder withChefProjet(int nombreProjetsGeres) {
    salarie = new SalarieChefProjet(salarie, nombreProjetsGeres);
    return this;
  }

  public SalarieBuilder withResponsableStagiaires(int nombreStagiairesGeres) {
    salarie = new SalarieResponsableDeStagiaires(salarie, nombreStagiairesGeres);
    return this;
  }

  public SalarieInterface build() {
    return salarie.clone();
  }

}

class Main {

  public static void main(String[]args) {
    SalarieInterface salarie1 = new SalarieBuilder(2000).build();
    SalarieInterface salarie2 = new SalarieBuilder(2500).withChefProjet(3).build();
    SalarieInterface salarie3 = new SalarieBuilder(2300).withResponsableStagiaires(5).build();
    SalarieInterface salarie4 = new SalarieBuilder(1800).withChefProjet(4).withResponsableStagiaires(2).build();
  }

}
```

<div class="exercise">

1. Ouvrez le paquetage `decorateur`. Il s'agit du code complété de l'exercice sur les **produits** du dernier TP où on a mis en place un décorateur pour pouvoir avoir à la fois des produits avec des réductions et des produits qui périment bientôt.

2. Comme dans l'exemple des salariés, refactorez votre code pour mettre en place un **builder** (adapté) qui doit permettre de construire vos produits décorés. Adaptez le code de `Main` en conséquence.

</div>

### Amélioration du générateur de donjons

Et si nous essayons de combiner plus de patterns ? Nous avons l'application idéale pour ça : le générateur de donjon (paquetage `fabrique4`). Il y a déjà la **Fabrique Abstraite**, peut-être le **Singleton** et **Prototype**.

<div class="exercise">

1. Nous aimerions maintenant que les différentes salles puissent être combinées afin de créer une "super-salle". Par exemple, on aimerait avoir des salles avec des coffres et 20 ennemis, une salle avec une énigme et un boss, une salle avec tout à la fois... ! Quel design pattern pouvez-vous utiliser pour mettre en place une telle fonctionnalité ? La seule méthode qui nous intéresse est `toString`. À l'affichage, on doit avoir les informations de toutes les salles qui composent une salle. Après vos refactoring, vous devrez logiquement adapter le code de vos deux **fabriques**. Pour la configuration des salles **difficile**, on souhaite faire des changements supplémentaires :

    * Une salle normale est une salle avec un coffre et entre 20 et 40 ennemis.

    * Une salle spéciale est soit une salle avec un coffre et 20 ennemis (une chance sur cinq) ou bien une salle avec un boss avec un niveau entre 30 et 50.

    * La salle finale est une salle avec une énigme, un boss de niveau 80 et 30 ennemis.

2. On aimerait améliorer la création des **salles** composées. Par exemple, avec un **Builder** (adapté)... ?

3. On aimerait pouvoir changer dynamiquement la manière dont est étendu le donjon. C'est-à-dire, la manière et l'ordre dont les salles sont ajoutées. Par exemple, on considérera que l'algorithme actuel de répartition des salles est celui "classique". On a maintenant un algorithme dit "hardcore" qui répartit les nouvelles salles ajoutées ainsi :

    * Quatre salles spéciales

    * Aléatoirement : soit deux salles normales (50%), soit deux salles spéciales (50%).

    * Quatre salles finales

    On doit pouvoir changer dynamiquement l'algorithme utilisé. C'est-à-dire étendre une fois avec l'algorithme classique, une autre fois avec l'algorithme hardcore, etc. D'autres algorithmes pourraient être ajoutés dans le futur.

4. Si ce n'est pas déjà fait, adaptez le `Main` et testez que tout fonctionne.

5. Rafraichissez le diagramme de classes de conception que vous aviez initialement généré pour cette application.
</div>

## Conclusion

Vous maîtrisez maintenant l'ensemble des **design patterns créateurs** ainsi que le pattern **Adaptateur**. Ce TP vous a aussi logiquement permis de renforcer votre pratique de la conception logicielle et de l'application des principes `SOLID`.

Toutefois, attention à ne pas attraper la **patternite** : c'est une maladie connue qu'attrapent les jeunes ingénieurs logiciels qui découvrent les **design patterns**. Cela se manifeste par une envie de mettre des patterns partout à tort et à travers même quand cela n'est pas nécessaire. Comme pour le **singleton**, il faut se poser la question de savoir si un pattern est nécessaire ou non. Normalement, l'utilisation d'un pattern vient assez naturellement quand on souhaite résoudre le problème qui lui est lié. Si son utilisation semble un peu trop forcée, c'est que cela est probablement injustifié, ou pire : on est en train de construire un [anti-pattern](https://en.wikipedia.org/wiki/Anti-pattern), une solution non-seulement injustifiée, mais aussi qui a plus de conséquences négatives que positives. Bref, comme toujours, il faut avoir une vision générale et sur le long terme !

Bref, ce TP conclut le cours de **Qualité de développement** du semestre 3. 

Voici un bilan de ce que vous avez appris :

* Utilisation plus poussée de git, notamment plus conforme à ce qui est attendu dans le monde professionnel : travail sur plusieurs branches, nommage des commits et des branches, merging, réécriture d'historique, automatisation de tâches et déploiement continu.

* Modélisation de la conception d'un logiciel à l'aide de **diagrammes de classes** et de **séquences**.

* Organisation de l'**architecture** d'un logiciel en différentes **couches**.

* Les principes `SOLID` et le **refactoring** de code. Deux notions clés à retenir : exploiter les **compositions d'objets** (faibles ou fortes) notamment à la place de certains héritages et préférer **dépendre d'abstractions plutôt que de classes concrètes**.

* La notion de **design pattern** et les différents patterns **créateurs** : `singleton`, `builder`, `prototype`, `méthode fabrique` et `fabrique abstraite`.

* D'autres **design patterns** : `stratégie`, `décorateur`, `adaptateur`.

Concernant les **design patterns GoF**, n'hésitez pas à aller consulter (et expérimenter) ceux que nous n'avons pas abordés dans ce cours (ceux comportementaux et architecturaux). Pour rappel, il y en a 23 ! Il peut être particulièrement intéressant d'aller voir **observateur**, **état**, **itérateur**, **visiteur**.

Il peut aussi être intéressant que vous vous renseignez sur le concept de **conteneur de dépendances** (ou bien **conteneur IoC**) qui est au cœur de nombreux frameworks et permet de gérer facilement toutes les dépendances d'un programme sans avoir besoin de gérer pleins de singletons (et donc, être moins [STUPID](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming)!).

Vous devez maîtriser toutes ces notions abordées dans ce cours pour la suite de votre cursus (et de votre carrière) et ainsi développer dès le début d'un projet un code d'une certaine qualité qui prévoit l'évolutivité et la modularité du projet sur le long terme. Si vous réussissez à appliquer cela, vous n'êtes alors plus un "simple" codeur, mais véritablement un "développeur", voir un **ingénieur logiciel**. 

À vous de jouer !
