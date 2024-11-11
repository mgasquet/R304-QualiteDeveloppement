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

L'idée du pattern **Singleton** est très simple : on souhaite garantir **qu'il n'existe qu'une seule instance d'une classe dans le programme et fournir un point d'accès global à cette instance**. Dès qu'un autre objet souhaite utiliser cette classe, il utilise l'instance "globale" définie dans l'application et **ne doit pas pouvoir en instancier lui-même** (l'utilisation de **new** doit être bloqué en dehors de la classe). L'instance globale doit être accessible à n'importe quel endroit de l'application (à travers une méthode qui l'expose).

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

<div style="text-align:center">
![Singleton 1]({{site.baseurl}}/assets/TP4/Singleton1.svg){: width="40%" }
</div>

Dans cet exemple, nous voyons qu'il y a au moins deux instances de la classe **Service** qui sont générées. Une dans `Client` et une autre dans `ClasseExemple`. S'il n'y a aucun intérêt à avoir plusieurs instances de la classe `Service`, nous pouvons alors la transformer en **Singleton** afin que toutes les classes qui souhaitent utiliser passent par la même instance.

Pour cela, il y a trois changements à réaliser dans la classe qu'on veut transformer en **Singleton** :

* Changer la **visibilité** du ou des **constructeurs** de la classe en **privé**. Ainsi, plus aucune autre entité pourra créer des instances de cette classe (hormis la classe elle-même).

* Dans la classe, créer un attribut **privé** et **statique** (un attribut de classe : `static` en Java) du même type que la classe. Cet attribut est généralement nommé `INSTANCE` (en majuscules).

* Enfin, créer une méthode **publique** et **statique** qui retourne un objet du type de la classe. Cette méthode est nommée `getInstance`. Tout d'abord, elle regarde si la variable `INSTANCE` a été initialisée ou non (si elle est `null` ou non). Si elle n'est pas encore initialisée, la classe l'instancie. Dans tous les cas, à la fin, on retourne `INSTANCE`.

Par la suite, toutes les entités qui souhaitent récupérer une instance de cette classe utilisent la méthode `getInstance` qui peut directement être appelée sur la classe, car **statique**. Lors du premier accès, l'instance "globale" sera alors initialisée.

Dans un environnement **multi-threadé** (exécution de plusieurs processus en parallèle, comme des `Runnable` ou des `Thread` en Java) il faut faire attention à ce que la méthode `getInstance` ne soit pas appelée en même temps par deux **Threads** différents. Pour régler cela en Java, il suffit d'ajouter le mot clé `synchronized` lors de la définition de la méthode.

Regardons ce que cela donne :

```java

public class Service {

  private static Service INSTANCE;

  //Interdit l'instanciation en dehors de la classe Service
  private Service() {}

  //On appelle systématiquement cette méthode pour récupérer l'instance "globale"
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

Commençons par une mise en application très simple.

<div class="exercise">

1. Ouvrez le paquetage `singleton1`. Cette petite application dispose d'une classe `Calculatrice` permettant de réaliser des opérations de gérer un historique de résultat afin de pouvoir revenir en arrière.

2. La classe `Calculatrice` est un service qui doit pouvoir être utilisé par toutes les classes de l'application (il n'y en a qu'une seule pour le moment, mais le programme va grandir dans le futur). On souhaite que pour réaliser des opérations, toutes les classes utilisent la même instance de la classe `Calculatrice`. Appliquez le pattern **Singleton** afin de transformer la classe `Calculatrice` en **Singleton**. 

3. Normalement, si vous avez bien traité la question précédente, vous allez avoir des erreurs dans `Client`. Adaptez le code de cette classe pour que tout fonctionne.

</div>

<!--
### Dépendance commune

Un cas un peu plus concret qui montre l'intérêt d'utiliser un `Singleton` est dans le contexte où deux objets différents dépendent de l'état d'une classe. Une classe `A` modifie l'état de `Service` et une classe `B` a besoin de connaître les modifications qu'a effectuées `A` dans `Service` pour fonctionner. Les deux classes `A` et `B` doivent alors dépendre de la même instance de `Service` !

Aussi, imaginons une classe d'accès à une base de données : celle-ci initialise une connexion vers la base qui peut prendre plusieurs secondes. Il serait inconscient d'instancier cette classe à chaque endroit où on en a besoin (cela dégraderait les performances !). On va plutôt utiliser un **Singleton**. C'est le cas de la classe `SQLUtils` que vous avez codé dans le TP "JDBC / Hibernate" en cours de base de données.

<div class="exercise">

1. Ouvrez le paquetage `singleton2`. Cette application permet de créer des animaux avec un nom et une vitesse, de les stocker dans la mémoire et de les lire.

2. Testez l'application. Créez plusieurs animaux puis tentez de les lire. Quels sont les deux problèmes que vous constatez ?

3. Réglez cela en appliquant le pattern **Singleton** sur la classe `StockageAnimaux` et en adaptant votre code.

4. Vérifiez que tout fonctionne et que les bugs sont bien résolus.

5. Le principe SOLID `D` (dependency inversion) est-il respecté sur les classes `CreationAnimal` et `LectureAnimaux` ? Si ce n'est pas le cas, refactorez votre code.

</div>
-->
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

    Un tel refactoring est-il possible ici? Essayez de refactorer et relevez les problèmes que vous rencontrez.

</div>

En essayant de refactorer, vous avez dû rencontrer divers problèmes :

* Une `interface` (dans la plupart des langages) ne peut pas posséder de signature de méthode de classe (`static`).

* Il est impossible d'injecter la classe statique comme paramètre d'un constructeur. Et oui, une classe n'est pas un objet et une instance ! Elle ne peut donc pas être passée en paramètre.

Bref, l'utilisation d'une **classe statique** rend les services qui l'utilisent étroitement dépendant de la classe. Ce qui rend l'application intestable car ces services ne peuvent pas être testés indépendamment des services concrets qui sont utilisés dans l'application. On ne peut pas remplacer le service par un "faux" service utilisé pour les tests unitaires (un **stub** ou un **mock**).

L'utilisation d'un **Singleton** résout tous ces problèmes :

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

7. Réalisez le **diagramme de classes de conception** de l'application.

</div>

### Avertissement

Vous maîtrisez maintenant le pattern **Singleton**, mais vous devez être très précautionneux quant à son utilisation. En conclusion du dernier TP vous étiez invité à aller jeter un coup d'œil aux [principes STUPID](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming) qui sont un ensemble de mauvaises pratiques en conception logicielle. Regardez à quoi correspond le `S`.

En effet, l'abus de **singletons** est dangereux pour la santé (du logiciel...) ! Il présente une solution qui semble plutôt efficace à un problème assez récurent : la gestion des dépendances vers les services de l'application. À tel point qu'on retrouve parfois dans certains projets beaucoup trop de singletons. 

Mais pourquoi est-il déconseillé d'utiliser "trop" de singletons :

* Il n'est pas possible de passer des paramètres à un singleton pour son initialisation (comme un objet classique) car c'est lui-même qui se construit, cependant, on peut éventuellement mettre en place un fichier de configuration que le singleton ira lire lors de son initialisation.

* Il est très difficile (voir impossible) de **tester** un singleton ! Comme le constructeur est **privé** et qu'il n'y a qu'une instance de l'objet dans l'application, on ne peut tester que cette instance. On ne peut pas instancier de nouveaux objets de cette classe pendant les tests unitaires.

* Il existe des solutions bien meilleures pour gérer les dépendances de l'application de manière plus flexibles tout en conservant la possibilité de réaliser des tests unitaires : les fabriques abstraites (dont nous allons bientôt parler) et le conteneur d'inversion de contrôle (conteneur IoC, dont nous parlerons au prochain TP).

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

    * Burger avec du pain au sésame, avec des tomates, de la salade.

    * Burger avec du pain classique, avec de la salade, des tomates, de la viande de bœuf et du cheddar.

3. Réalisez le **diagramme de classes de conception** de votre application.

**NB :** Certains IDE (dont IntelliJ) permettent de générer automatiquement le code d'un Builder à partir d'une classe. Sur IntelliJ, il faut faire un clic droit sur le constructeur de la classe pour laquelle vous souhaitez générer le builder, puis aller dans _Replace constructor with builder_. Le Builder sera généré comme une classe à part. Pour la rendre interne à la classe cible, il suffira juste de faire un Drag & Drop du Builder dans sa classe cible.

**Remarque :** lorsqu'il s'agit d'une hiérarchie de classes (par héritage) pour laquelle il faut créer des builders, la solution n'est pas forcément évidente. En effet, il faut faire une hiérarchie de builders pour éviter la duplication de code, tout en respectant le principe LSP, à savoir : les méthodes **with...** doivent retourner le bon type de builder. Pour plus de détails voir le [le dernier TP](https://gitlabinfo.iutmontp.univ-montp2.fr/dev-objets/tp11) de Développement Orienté Objets de première année).

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
![Prototype 1]({{site.baseurl}}/assets/TP4/Prototype1.svg){: width="50%" }
</div>


<div class="exercise">

1. Refactorez votre code en appliquant le pattern **prototype** sur vos comptes bancaires. Adaptez aussi le code de `getInformationsCompteNumero` en conséquence.

2. Vérifiez que le test unitaire passe toujours.

3. Réalisez le **diagramme de séquence des interactions** permettant de modéliser ce qu'il se passe lors de l'éxécution du code suivant :

    ```java
    Banque banque = new Banque();
    int numeroCompte = banque.ouvrirCompteCourant("Test", Formule.ADULTE);
    banque.crediterCompte(numeroCompte, 50);
    CompteBancaire compte = banque.getInformationsCompteNumero(numeroCompte);
    compte.crediter(100);
    ```

</div>

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
    System.out.println("Code de combat du slime contre le joueur...");
  }

}

public class Fantome implements Monstre {

  @Override
  public void combattre(Joueur joueur) {
    System.out.println("Code de combat du fantôme contre le joueur...");
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
![Fabrique 1]({{site.baseurl}}/assets/TP4/Fabrique1.svg){: width="80%" }
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
![Fabrique 2]({{site.baseurl}}/assets/TP4/Fabrique2.svg){: width="80%" }
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

Avec notre implémentation, il est éventuellement possible d'utiliser une autre marque de café qui possède son propre type d'expresso et de cappuccino (avec des graines de provenances différentes, et une autre marque de sucre). Il suffira de changer la fabrique sans impacter le reste des classes. Mais que se passerait-il si on souhaitait faire cohabiter ces différentes **marques** de café, avec leur propre machine ? Il sera possible de régler ce problème avec les patterns **méthode fabrique** et/ou **fabrique abstraite**.

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

public class ZoneChateauHante extends Service {

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

Le pattern s'appelle **méthode fabrique**, car la méthode abstraite implémentée par les classes filles sont elles-mêmes des fabriques ! D'ailleurs, dans l'exemple, nous avons supprimé `MonstreFactory` qui ne nous est plus utile.

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

Testons maintenant votre maîtrise du pattern **méthode fabrique** avec un nouvel exercice un peu plus complexe.

<div class="exercise">

1. Ouvrez le paquetage `fabrique3` puis `v1`. Il s'agit d'une application de restauration permettant de commander différents types de **burgers**. L'exercice est divisé en deux parties : `v1` que nous allons traiter maintenant puis `v2` que vous allez traiter plus tard. 

2. Un **restaurant** peut créer différents types de **Burger** : des **Cheese Burgers** et des **Egg Burgers**. L'application fonctionne actuellement pour un **restaurant Nîmois** qui fabrique les burgers ainsi :

  * **Cheese Burger** : Boeuf Charolais, Sauce à burger de Nîmes et Cheddar.
  * **Egg Burger** : Poulet Gardois, Sauce à burger de Nîmes et Oeuf de poule.

  Le restaurant cherche à se diversifier en ouvrant différents restaurants dans d'autres villes. Tous les restaurants devront proposer les **mêmes burgers**, mais les recettes pourront changer localement, dans une ville. Un nouveau restaurant a ouvert à **Montpellier** et propose les recettes suivantes :

  * **Cheese Burger** : Boeuf Limousin, Sauce à burger de Montpellier et Maroilles.
  * **Egg Burger** : Poulet de Bresse, Sauce à burger de Montpellier et Oeuf d'autruche.

  Actuellement, l'application fonctionne avec un seul type de classe `CheeseBurger` et `EggBurger` (qui sont les burgers du restaurant **Nîmois**). Une **fabrique simple** a été mise en place (mais vous allez peut-être devoir changer cela...?)

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

À noter qu'il est bien sûr possible de coupler cela avec des **singletons** pour les fabriques **concrètes** :

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

L'objectif du pattern **Fabrique Abstraite** est donc de disposer d'une abstraction (classe abstraite ou interface) qui définie le contrat que doivent remplir les fabriques concrètes. Pour chaque famille de classes, on crée une fabrique concrète qui implémente cette interface ou étend cette classe abstraite. Ensuite, toutes les classes qui souhaitent utiliser cette fabrique doivent dépendre de la **fabrique abstraite** et non plus d'une fabrique concrète. Couplé à de l'injection de dépendances, il est très facile de complètement changer le comportement d'une classe.

C'est globalement l'idée du pattern **Stratégie** que vous avez déjà vu lors du dernier TP, mais appliqué pour des fabriques ! On pourrait voir la **fabrique abstraite** comme une **stratégie de création**.

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

1. Ouvrez le paquetage `fabrique4`. Cette application permet de construire des **donjons** pour un jeu-vidéo. Un **donjon** est constitué de différentes salles (des pièces avec des coffres, des pièces avec des ennemis, des pièces avec des énigmes, des pièces avec des boss...). Une salle peut être complétée par le joueur ou non. Chaque donjon possède un algorithme de génération qui créé les salles dans un ordre précis (avec un peu d'aléatoire). Il est constitué de "salles normales", de "salles spéciales" et d'une "salle finale", dans cet ordre :

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

2. La configuration actuelle du Donjon est un mode "facile". On aimerait introduire le mode "difficile" (toujours en gardant le même algorithme/ordre de création des salles) où on a les correspondances suivantes :

    * Salle normale : Une salle contenant entre 20 et 40 ennemis.

    * Salle spéciale : Une salle avec une énigme (20% de chances) ou bien une salle avec un boss avec un niveau entre 30 à 50 (80% de chances).

    * Salle finale : Une salle avec un Boss de niveau 80.

    Refactorez votre code afin qu'il soit possible de construire des donjons "difficiles" en plus de donjons "facile" (qui est la configuration de salles implémentée par défaut).

3. Dans le `Main`, construisez des donjons difficiles et des donjons faciles.

4. La méthode `getInfosSalle` doit permettre de récupérer les informations d'une salle du donjon "à l'extérieur". Cependant, son implémentation est problématique... Par exemple, que pourriez-vous faire comme action indésirable en récupérant une salle d'un `Donjon` dans le `Main` (indice : seul le donjon devrait avoir le droit de modifier l'état de ses salles) ? Quel pattern que nous avons vu pendant ce TP pourriez-vous appliquer pour régler ce problème ? Refactorez votre code dans ce sens.

5. Réalisez le **diagramme de classes de conception** de votre application.

</div>

### Restaurants de burgers - Partie 2

Revenons une dernière fois sur l'application de gestion de restaurants afin de l'améliorer.

<div class="exercise">

1. Ouvrez le paquetage `fabrique3` puis `v2`. Il s'agit de la deuxième partie de l'exercice. Comme vous pouvez le constater, les différents ingrédients qui étaient jusqu'ici des **chaînes de caractères** sont remplacés par des **objets**.

  On a toujours les mêmes recettes que précédemment dans les restaurants **Nîmois** et les restaurants **Montpellierains** :

  * Nîmes : 
    * **Cheese Burger** : Boeuf Charolais, Sauce à burger de Nîmes et Cheddar.
    * **Egg Burger** : Poulet Gardois, Sauce à burger de Nîmes et Oeuf de poule.

  * Montpellier :
    * **Cheese Burger** : Boeuf Limousin, Sauce à burger de Montpellier et Maroilles.
    * **Egg Burger** : Poulet de Bresse, Sauce à burger de Montpellier et Oeuf d'autruche.

2. Commencez par importer et adapter votre ancien code afin de faire en sorte qu'il soit toujours possible de gérer les deux types de restaurants : les **restaurants Nîmois** et les **restaurants Montpelliérains** (la seule chose qui change sont les ingrédients qui sont maintenant des objets). Importez et/ou complétez aussi le code du `Main` et assurez-vous que tout fonctionne.

3. On remarque que les restaurants Nîmois et les restaurants Montpellierains utilisent **un ensemble d'ingrédients spécifique en local** pour la composition de leurs burgers :

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

La question est de savoir : où placer ce bout de code ? Il n'y a pas vraiment de réponse officielle à cette question. Cela pourrait être dans une classe indépendante avec une méthode statique. Cependant, dans la pratique, on retrouve parfois ce bout de code directement dans la **Fabrique Abstraite** qu'on mélange à un **Singleton**.

Par exemple, imaginons que nous souhaitons que notre **Jeu**, à un instant T, ne fonctionne qu'avec des **Plaines** ou qu'avec des **Châteaux Hantés** :

```java
//On transforme notre interface en classe abstraite, car elle contient du code
//Elle stocke l'instance cocnrète de la fabrique utilisée
public abstract class AbstractZoneFactory {

  private static AbstractZoneFactory INSTANCE;

  private String fabriqueSelectionee = "chateau";

  public synchronized static AbstractZoneFactory getInstance() {
    if(INSTANCE == null) {
      switch (fabriqueSelectionee) {
          case "plaine" :
            INSTANCE = new ZonePlaineFactory();
            break;
          case "chateau" : 
            INSTANCE = new ZoneChateauHanteFactory();
            break;
          default: 
            throw new IllegalArgumentException(String.format("Type de zone inconnue : %s", fabriqueSelectionee));
      }
    }
    return INSTANCE;
  }

  public abstract Monstre creerMonstreNormal();

  public abstract Boss creerBoss(); 

  public abstract Item creerRecompense();

}

//Les fabriques concrètes ne sont plus des singletons...
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

Avec cette nouvelle implémentation, il n'y a plus qu'à changer le paramètre `fabriqueSelectionee` dans la fabrique abstraite pour changer la fabrique concrète manipulée dans tout le programme. On notera qu'il n'y a plus besoin que les sous-classes soient des **singletons**, car elles sont instanciées par la fabrique abstraite.

Encore mieux : dans les faits, il faut (légèrement) changer le code source de la fabrique abstraite pour changer de fabrique... Donc il faut recompiler. Pour éliminer ce dernier problème, on peut plutôt utiliser un **fichier de configuration** : lors de son initialisation, la fabrique abstraite va lire dans ce fichier pour déterminer quelle fabrique instancier.

```java
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
```

<div style="text-align:center">
![Fabrique 4]({{site.baseurl}}/assets/TP4/Fabrique4.svg){: width="80%" }
</div>

La fabrique abstraite vise un fichier qui se situe dans `src/main/resources/config/zone_factory_config.txt` qui contient simplement une chaîne de caractères. Par exemple : `chateau`.

Bien sûr, cette implémentation n'est pas forcément souhaitable dans tous les contextes ! C'est seulement si, à un instant T, on veut uniquement avoir un seul type de fabrique concrète utilisé et pouvoir en changer facilement (d'ailleurs, l'exemple donné est discutable, parce qu'on voudrait à priori pouvoir créer plusieurs types de zones différentes à la fois).

<div class="exercise">

1. Créez un dossier `config` dans `src/main/resources/` puis, à l'intérieur de ce nouveau répertoire, un fichier `monstres_factory_config.txt`.

2. Refactorez le code de l'application afin qu'il soit possible d'utiliser soit les pokémons, soit les digimons en changeant simplement le contenu du fichier de configuration.

3. Testez les deux versions !

4. Réalisez le **diagramme de classes de conception** de votre application. Pour ne pas trop perdre de temps, ne mettez que deux pokémons, deux digimons (et les fabriques), ne détaillez pas les méthodes et les attributs. Le plus important est de faire apparaitre les associations et les dépendances.

</div>

### Intégrer une librairie externe

Les pokémons et les digimons sont des classes qui ont été créées par le développeur de ce projet et où il est donc possible de réarranger le code pour que tout fonctionne. Mais que se passerait-il si nous voulions intégrer à notre système du code sur lequel nous n'avons pas la main (dont nous ne pouvons pas éditer le code source)? Par exemple, des classes compilées qui proviennent d'une librairie.

Pour illustrer ce problème, reprenons notre exemple de figures géométriques. Imaginons que vous souhaitez pouvoir afficher des carrés et des cercles de manière "complexe" (à voir ce que "complexe" veut dire dans ce contexte). Au lieu de réinventer la roue, vous avez trouvé une librairie `FiguresComplexes` qui fait cela pour vous ! Via `Maven`, vous installez cette librairie sur votre projet.

```java
interface Publicateur {

  public void connexion(String login, String motDePasse);

  public void publierMessage(String contenu);

}

class PublicateurFacebook implements Publicateur {

  public void connexion(String login, String motDePasse) {
    System.out.println("Code de connexion au compte via l'API de Facebook...");
  }

  public void publierMessage(String contenu) {
    System.out.println("Publication d'un message sur le compte via l'API de Facebook...");
  }

}

class PublicateurTwitter implements Publicateur {

  public void connexion(String login, String motDePasse) {
    System.out.println("Code de connexion au compte via l'API de Twitter...");
  }

  public void publierMessage(String contenu) {
    System.out.println("Publication d'un message sur le compte via l'API de Twitter...");
  }

}
```

Vous ne pouvez pas modifier le code source de cette classe, mais vous pouvez étudier leur documentation. Vous êtes notamment intéressés par les deux classes suivantes :

```java
public class InstagramMessageSender {

  private int apiVersion;

  public InstagramMessageSender(int apiVersion) {
    this.apiVersion = apiVersion;
  }

  public void connect(String email, String password) {
    System.out.printf("Connecting to API %s...\n", apiVersion);
    System.out.println("Connecting to the instagram account using the provided email and password...");
  }

  public void logout() {
    System.out.println("Logging out...");
  }

  public void publishMessage(String content, int timer) {
    System.out.printf("Publishing content on the instagram account in %s seconds...\n", timer);
  }

}
```

Ces deux classes répondent à tous les besoins...mais, de prime abord, il semble impossible de les intégrer dans notre système de fabrique :

* Les noms des méthodes ne sont pas les mêmes.

* On ne peut pas faire implémenter à ces classes `Carre` ou `Circle`...

* On ne peut pas modifier le code source de ces classes...

Cela semble compromis ! Mais pas de panique, un design pattern résout ce problème : `Adaptateur`.

L'objectif de ce pattern est de faire en sorte qu'une classe "incompatible" avec notre architecture puisse tout de même être utilisée en passant par une classe dîte **adaptateur** qui fait le pont entre votre architecture et cette classe grâce à de la **composition** (encore et toujours !). C'est un peu comme quand vous voyagez au Royaume-Uni par exemple. Les prises électriques ne sont pas compatibles avec la prise de votre chargeur de téléphone. Vous devez alors utiliser un adaptateur entre la prise de votre chargeur et celle anglaise.

Ici, la "prise du chargeur" est votre architecture, les interfaces, les abstractions, l'adaptateur la classe qui va être amenée par le pattern et la prise anglaise la classe "externe" que vous souhaitez utiliser.

Voici comment appliquer ce pattern :

1. Créer une classe dite "Adapter" qui possède un attribut du type de la classe à adapter. Cet attribut peut être injecté via le constructeur ou bien, dans certains cas, directement construit dans la classe Adapter.

2. Faire implémenter à notre Adapter l'interface souhaitée ou lui faire étendre la classe abstraite souhaitée.

3. L'implémentation de chaque méthode abstraite se fera par **délégation** en appelant la méthode d'origine sur la classe cible.

Mettons cela en application sur notre exemple :

```java
public class InstagramMessageSenderAdapter implements Publicateur {

  private InstagramMessageSender delegue;

  public InstagramMessageSenderAdapter(InstagramMessageSender delegue) {
    this.delegue = delegue;
  }

  public void connexion(String login, String motDePasse) {
    delegue.connect(login, motDePasse);
  }

  public void publierMessage(String contenu) {
    delegue.publishMessage(contenu, 0);
  }

}
```

<div style="text-align:center">
![Adaptateur 1]({{site.baseurl}}/assets/TP4/Adaptateur1.svg){: width="80%" }
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
    public int getDureeRespiration() {
        //Erreur !
        return this.patternmon.getBreathingTime();
    }

}
```

Si vous avez bien une implémentation similaire (faites les changements nécessaires si ce n'est pas le cas) vous obtenez une erreur au niveau de la méthode `getDureeRespiration`. Cela est dû au fait que dans la classe mère, l'attribut `patternmon` est du type abstrait `Patternmon` et pas un `Waterpatternmon` ! Donc, dans la classe fille, impossible d'utiliser `getBreathingTime`.

La première solution "simple" serait de **caster** le patternmon. Normalement, comme on est sûr d'avoir passé au constructeur parent un `Waterpatternmon`, c'est un **cast** sans risques :

```java 
@Override
public int getDureeRespiration() {
    return ((Waterpatternmon) this.patternmon).getBreathingTime();
}
```

Mais cette solution n'est pas élégante et il en existe une bien meilleure : la **généricité**. Dans la classe mère, il est possible de définir un (ou plusieurs) "type paramétré" qu'on peut par exemple nommer `T`. On peut imposer des restrictions, par exemple, que `T` soit une classe qui descende d'une autre classe spécifique.

Quand une classe enfant étend la classe mère, elle peut alors préciser la classe concrète utilisée à la place de `T`. Ainsi, la classe mère est configurée pour utiliser ce type.

Petite démonstration sur `PatternmonAdapter` et `PatternmonEauAdapter` :

```java 
//On définit le paramètre générique T lors de la déclaration de la classe
//Je suis assuré que T est un objet qui étend la classe Patternmon
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
    public int getDureeRespiration() {
        //Plus d'erreurs, car l'attribut "patternmon" dans la classe mère est un Waterpatternmon !
        return this.patternmon.getBreathingTime();
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

### Gestion des dépendances

Jusqu'ici, nous avons vu des fabriques qui instancient systématiquement un objet à chaque appel d'une méthode type `creer...`. Cependant, ce fonctionnement n'est pas obligatoire. Par exemple, on pourrait avoir une fabrique qui **instancie** et stocke certains objets lors de son initialisation puis renvoie une référence vers ces objets lorsqu'on la sollicite.

Avec un tel fonctionnement, une **fabrique** permet alors de gérer les **dépendances** d'un programme. Elle pourrait par exemple stocker différentes instances de **services** concrets de l'application. Couplé avec le pattern **Fabrique Abstraite**, cela nous permet de rendre les dépendances de notre programme fortement modulables !

```java
interface ServiceA {
  void actionA();
}

interface ServiceB {
  void actionB();
}

public class ServiceA1 implements ServiceA {

  public void actionA() {
    //...
  }

}

public class ServiceA2 implements ServiceA {

  public void actionA() {
    //...
  }

}

public class ServiceB1 implements ServiceB {

  public void actionB() {
    //...
  }

}

public class ServiceB2 implements ServiceB {

  public void actionB() {
    //...
  }

}

public class ServiceV1Factory extends AbstractServiceFactory {

  private ServiceA serviceA;

  private ServiceB serviceB;

  public ServiceV1Factory() {
    this.serviceA = new ServiceA1();
    this.serviceB = new ServiceB1();
  }

  public ServiceA getServiceA() {
    return serviceA;
  }

  public ServiceB getServiceB() {
    return serviceB;
  }

}

public class ServiceV2Factory extends AbstractServiceFactory {

  private ServiceA serviceA;

  private ServiceB serviceB;

  public ServiceV2Factory() {
    this.serviceA = new ServiceA2();
    this.serviceB = new ServiceB2();
  }

  public ServiceA getServiceA() {
    return serviceA;
  }

  public ServiceB getServiceB() {
    return serviceB;
  }

}

public abstract class AbstractServiceFactory {

  public abstract ServiceA getServiceA();

  public abstract ServiceB getServiceB();

  private static AbstractServiceFactory INSTANCE;

  public synchronized static AbstractServiceFactory getInstance() {
      if(INSTANCE == null) {
          try {
              InputStream stream = ClassLoader.getSystemResourceAsStream("config/services.txt");
              if(stream == null) {
                  throw new RuntimeException("Fichier de configuration manquant.");
              }
              BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
              String config = reader.readLine();
              if(config.equals("V1")) {
                  INSTANCE = new ServiceV1Factory();
              }
              else if(config.equals("V2")) {
                  INSTANCE = new ServiceV2Factory();
              }
              else {
                  throw new RuntimeException("Fabrique inconnue.");
              }

          } catch (IOException e) {
              throw new RuntimeException("Fichier de configuration corrompu.");
          }
      }
      return INSTANCE;
  }

}

public class Main {

  public static void main(String[]args) {
    ServiceA s1 = AbstractServiceFactory.getInstance().getServiceA();
    s1.action();

    ServiceB s2 = AbstractServiceFactory.getInstance().getServiceB();
    s2.action();
  }

}
```

<div style="text-align:center">
![Fabrique 5]({{site.baseurl}}/assets/TP4/Fabrique5.svg){: width="40%" }
</div>

Dans l'exemple ci-dessus, un simple changement dans le fichier de configuration permet de changer les services concrets utilisés pour `ServiceA` et `ServiceB`. Contrairement aux exercices précédents, dans le cas d'un service, il n'est pas utile (voire, il ne faut pas) le réinstancier chaque fois. Par exemple, dans le cas d'une classe "repository" permettant de faire des requêtes sur une base de données.

C'est un peu comme si toutes les dépendances stockées dans ces fabriques étaient de singletons, car on ne manipule qu'une seule instance de ces objets dans le programme. Mais cela est encore mieux qu'un singleton, parce que ces classes (`ServiceA1`, `ServiceB1`, etc.) ne sont pas construites comme des singletons ! Elles sont donc beaucoup plus adaptées aux tests unitaires. Comme mentionné dans la section "Avertissement" sur les singletons, nous préférerons utiliser des fabriques plutôt que de multiplier les singletons dans l'application.

Il est toléré d'avoir un **singleton** pour les classes telles que les fabriques abstraites ou leurs sous-classes, car elles n'ont pas vraiment pour but d'être testées (unitairement). Mais sur les services qui contiennent du code métier, il faut éviter le **singleton** quand cela est possible. Les fabriques et les fabriques abstraites répondent à ce problème.

Dans le prochain TP, nous verrons un outil encore plus puissant pour gérer les dépendances : le **conteneur IoC**.

Pour le moment, revenons à nos moutons et appliquons ce que nous avons appris sur un nouvel exercice.

<div class="exercise">

1. Ouvrez le paquetage `fabrique6`. Il s'agit de la dernière application que vous aviez refactoré lors du dernier TP permettant de simuler l'inscription et la connexion d'un utilisateur. L'application est fonctionnelle. Lancez-la et explorer aussi les différentes classes mises à disposition si vous ne vous souvenez pas bien de son fonctionnement.

2. Actuellement, si nous voulons changer la méthode de stockage (en mémoire ou dans un fichier) il faut éditer à la main `IHMUtilisateur` pour remplacer les paramètres injectés lors de la création de `ServiceUtilisateur`. On souhaite rendre cela plus modulable. Refactorez le code pour mettre en place et utiliser une **fabrique abstraite** et des **fabriques** pour gérer les deux types de méthodes stockage disponibles dans l'application. La configuration du type stockage utilisé devra se faire via un fichier de configuration textuel simple. Aussi, vos fabriques doivent stocker les **dépendances** qu'elles gèrent et ne pas les ré-instancier à chaque fois qu'on en a besoin. 

    Normalement, vous n'avez pas besoin de toucher la classe `ServiceUtilisateur`, mais il faudra probablement adapter le code de `IHMUtilisateur`.

3. Testez que tout fonctionne en alternant entre les deux méthodes de stockage via votre fichier de configuration.

4. Il existe divers autres services que nous utilisons fréquemment dans l'application : le service permettant d'envoyer des mails (mailer) et le service de chiffrement (hasheur). On voudrait définir deux configurations correspondantes à ces deux "familles" de services :

    * Une configuration "basique" utilisant `ServiceMailerBasique` et `HasheurMD5`.

    * Une configuration "sécurisée" utilisant `ServiceMailerChiffre` et `HasheurSHA256`.

    Là aussi, on veut pouvoir facilement switcher entre ces deux configurations sans changer le code, mais en éditant simplement un fichier de configuration.

    Mettez en place un système pour pouvoir gérer ces deux configurations. Encore une fois, vous ne devriez pas avoir besoin d'éditer d'autres classes que `IHMUtilisateur` après la mise en place de votre système.

5. Vérifiez que tout fonctionne en alternant entre les deux configurations.

</div>

Le **conteneur IoC** que nous allons utiliser dans le prochain TP permet de ne pas multiplier les fabriques pour gérer les différentes dépendances en centralisant le tout. C'est une sorte de super-fabrique hautement configurable gérant des dépendances (mais avec un objectif assez différent des fabriques que vous avez vues avant comme avec les figures géométriques, les pokémons ou les donjons).

<!--
### Mise en pratique sur une application plus large

Vous allez maintenant mettre en application ce que vous avez appris sur une application un peu plus large : l'application de gestion des étudiants (OGE) sur laquelle vous avez travaillé dans le cours de base de données.

<div class="exercise">

1. Forkez [le dépôt GitLab suivant](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/tp4-qualite-oge) en le plaçant dans le namespace `qualite-de-developpement-semestre-3/etu/votrelogin`.

2. Clonez votre nouveau dépôt en local. Ouvre le projet avec `IntelliJ` et vérifiez qu'il n'y a pas d'erreur. Si vous exécutez le programme, il y aura une erreur, c'est normal pour le moment.

3. Pour rappel, ce programme peut se connecter à une base de données par deux moyens : en utilisant l'API `JDBC` en "brut" ou bien en passant par l'ORM `Hibernate`. Vous n'avez pas nécessairement besoin d'avoir fini ce TP dans son intégralité en base de données pour pouvoir faire cet exercice. Il y a un peu de configuration à faire pour que vous puissiez vous connecter à votre BDD par JDBC et Hibernate :

    * Dans la classe `storage/jdbc/JDBCUtils`, remplacez les valeurs `aCompleter` par vos identifiants d'accès à la base de données `Oracle` de l'IUT.

    * Faites de même dans le fichier `hibernate.cfg.xml` dans `src/main/java/resources`.

    Lancez l'application et vérifiez que tout fonctionne.

4. De base cette application est configurée pour utiliser `JDBC` et pas `Hibernate`. Si on souhaite changer la méthode de stockage en BDD utilisée, il faut changer le code source des classes `RessourceService`, `EtudiantService` et `NoteService`. On aimerait pouvoir plus facilement switcher entre `JDBC` et `Hibernate` en utilisant un simple **fichier de configuration**. On vous demande donc de **refactorer** le code afin de mettre en place un tel système (avec une **fabrique abstraite** gérant des dépendances, comme dans l'exercice précédent). Quelques commentaires :

    * L'interface **Stockage** (dans le paquetage `storage`) permet de définir un repository. Vous pouvez notamment aller jeter un œil aux repositories **concrets** qui utilisent `JDBC` et implémentent cette interface dans `storage/jdbc`.

    * Il faudra utiliser votre fabrique abstraite directement dans la méthode `getInstance` des trois services. Comme vous pouvez le constater, ces services sont des **singletons**. Ils sont donc difficilement testables...mais nous allons régler ce problème dans le prochain TP !

    * Dans les trois services, vous avez des exemples d'instanciation des repositories JDBC simples (définis dans l'application).

    * On accède aux repositories issus de `Hibernate` différemment. Pour rappel, ils sont fournis via une **librairie externe** nommée `HibernateRepositories`. Vous n'avez donc pas la main dessus ! De plus, les noms des méthodes différents de celle de votre interface `Stockage`... Quel pattern allez-vous utiliser pour résoudre ce problème ? Vous l'avez vu pendant ce TP. On rappelle comment manipuler les repositories de `Hibernate` (vous n'étiez peut-être pas allé jusque-là dans le TP) :

      * La classe `EntityRepository<T>` permet de gérer un repository correspondant à une entité `T` (paramètre générique, qui peut être instancié, par exemple par `EntityRepository<Ressource>`).

      * Les méthodes qu'on peut utiliser sur un tel **repository** sont : `create`, `update`, `deleteById`, `findById`, `findAll` qui sont similaires aux méthodes définies dans l'interface `Stockage`.

      * On n'instancie pas directement ces repositories, on les récupère via l'instruction suivante :

      ```java
      EntityRepository<MonEntite> repository = RepositoryManager.getRepository(MonEntite.class);

      //Par exemple :
      EntityRepository<Ressource> repository = RepositoryManager.getRepository(Ressource.class);
      ```

      * Si vous gérez bien le concept de **généricité** adapter les `EntityRepository` à votre architecture ne devrait demander qu'une seule classe (peut-être un peu dure à trouver si vous n'êtes pas encore trop à l'aise avec cette notion). Sinon, il y a aussi une solution plus basique utilisant trois classes.

5. Une fois le refactoring terminé, vérifiez que tout fonctionne en alternant entre `JDBC` et `Hibernate` en modifiant votre fichier de configuration. Comme les deux systèmes utilisent la même base, cela n'est pas forcément évident de repérer quand l'un ou l'autre est utilisé. au démarrage, `Hibernate` va vous mettre divers messages d'informations dans la console contrairement à `JDBC`. Sinon, essayez de mettre un mauvais mot de passe dans une des configurations (dans `JDBCUtils` ou bien le fichier de configuration d'Hibernate) et alternez entre les deux méthodes. L'application ne devrait pas fonctionner seulement dans un cas sur deux.

6. N'oubliez pas de push ce projet sur GitLab. **Attention**, si vous ne voulez pas que vos identifiants soient visibles, supprimez-les avant de push. Mais, à priori, seuls les enseignants ont accès à vos dépôts GitLab si vous l'avez placé dans le bon `namespace`.
</div>

Avec votre refactoring, il devient très facile d'ajouter et d'utiliser une nouvelle source de stockage de données, comme un fichier XML par exemple ou une base de données `SQLite` dédiées aux tests ! Et passer d'une méthode à l'autre ne demande alors plus aucune modification du code source.
-->

## Décorateur : Builder ou Fabrique ?

Dans le dernier TP, vous avez découvert le pattern **Décorateur** permettant d'ajouter des nouvelles fonctionnalités de manière dynamique. Nous avions notamment vu un exemple portant sur des salariés, puis un exercice portant sur différents types de produits.

Comme l'objet créé avec le pattern **Décorateur** peut être assez complexe, il peut être intéressant de le coupler avec une **Fabrique** ou bien un **Builder**.

Reprenons l'exemple des salariés et essayons d'appliquer ces deux patterns :

```java
interface I_Salarie {
  double getSalaire();
  //Prototype
  I_Salarie clone();
}


class Salarie implements I_Salarie {

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

  public I_Salarie clone() {
    return new Salarie(this);
  }

}

abstract class SalarieDecorator implements I_Salarie {
   protected I_Salarie salarie;

   public SalarieDecorator(I_Salarie salarie) {
      this.salarie = salarie;
   }
}

class ChefProjet extends SalarieDecorator {

  private int nombreProjetsGeres;

  public ChefProjet(I_Salarie salarie, int nombreProjetsGeres) {
    super(salarie);
    this.nombreProjetsGeres = nombreProjetsGeres;
  }

  private ChefProjet(ChefProjet chefProjetACopier) {
    this(chefProjetACopier.salarie.clone(), chefProjetACopier.nombreProjetsGeres);
  }

  @Override
  public double getSalaire() {
    return salarie.getSalaire() + 100 * (nombreProjetsGeres);
  }

  @Override
  public I_Salarie clone() {
    return new ChefProjet(this);
  }

}

class ResponsableDeStagiaires extends SalarieDecorator {

  private int nombreStagiairesGeres;

  public ResponsableDeStagiaires(I_Salarie salarie, int nombreStagiairesGeres) {
    super(salarie);
    this.nombreStagiairesGeres = nombreStagiairesGeres;
  }

  private ResponsableDeStagiaires(ResponsableDeStagiaires responsableACopier) {
    this(responsableACopier.salarie.clone(), responsableACopier.nombreStagiairesGeres);
  }

  @Override
  public double getSalaire() {
    return salarie.getSalaire() + 50 * nombreStagiairesGeres;
  }

  @Override
  public I_Salarie clone() {
    return new ResponsableDeStagiaires(this);
  }

}
```

On peut créer : des salariés simples, des salariés chefs de projet, des salariés responsables de stagiaires et des salariés à la fois chefs de projets et responsables de stagiaires. Si on ajoutait un nouveau type de `Salarie`, cela multiplierait les possibilités...

Sans pattern créateur, il faut donc créer les salariés ainsi :

```java
I_Salarie salarie1 = new Salarie(2000);
I_Salarie salarie2 = new SalarieChef(new Salarie(2500), 3);
I_Salarie salarie3 = new ResponsableDeStagiaires(new Salarie(2300), 5);
I_Salarie salarie4 = new SalarieChef(new ResponsableDeStagiaires(new Salarie(1800), 4), 2); 
```

Essayons d'abord d'utiliser le concept de **Fabrique** :

```java
class SalarieFactory {

  private static SalarieFactory INSTANCE;

  private SalarieFactory() {}

  public static SalarieFactory getInstance() {
    if(INSTANCE == null) {
      INSTANCE = new SalarieFactory();
    }
    return INSTANCE;
  }

  public Salarie creerSalarie(double salaire) {
    return new Salarie(salaire);
  }

  public SalarieChef creerSalarieChef(I_Salarie salarie, double nombreProjetsGeres) {
    return new SalarieChef(salarie, nombreProjetsGeres);
  }

  public ResponsableDeStagiaires creerResponsableStagiaires(I_Salarie salarie, int nombreStagiairesGeres) {
    return new ResponsableDeStagiaires(salarie, nombreStagiairesGeres);
  }

}

class Main {

  public static void main(String[]args) {
    SalarieFactory factory = SalarieFactory.getInstance();
    I_Salarie salarie = factory.creerSalarieChef(factory.creerResponsableStagiaires(factory.creerSalarie(1800), 4), 2);
  }

}
```

<div class="exercise">

1. Ouvrez le paquetage `decorateur`. Il s'agit du code complété de l'exercice sur les **produits** du dernier TP où on a mis en place un décorateur pour pouvoir avoir à la fois des produits avec des réductions et des produits qui périment bientôt.

2. Comme dans l'exemple des salariés, refactorez votre code pour mettre en place une **fabrique** qui permettant de construire vos produits. Adaptez le code de `Main` en conséquence.

</div>

Bon, cela fonctionne, mais à part déplacer la création dans la fabrique, il est toujours assez complexe de créer l'objet comme quand nous utilisions les `new` directement dans `Main`... Essayons plutôt avec un `Builder` !

Attention, l'implémentation de `Builder` que nous allons présenter ici n'est pas un vrai `Builder` comme nous l'avons fait dans l'exercice des builders, mais plutôt une **adaptation** pour fonctionner avec le décorateur :

  * La classe `Builder` va se trouver à l'extérieur de `Produit`. Autrement, cela voudrait dire que `Produit` dépendrait de toutes ses classes filles, et cela ne semble pas très adéquat.

  * Le produit va être instancié dès le départ puis augmenté au fur et à mesure alors que normalement, la cible du builder n'est instanciée que quand on appelle la méthode `build`.

  * La méthode `build` renvoie une **copie** (clone) de l'instance (prototype).

Bref, retenez simplement que c'est une adaptation un peu particulière et qui s'éloigne quand même pas mal du pattern de base (retenez plutôt l'exemple des burgers). Néanmoins, nous allons voir que cette adaptation s'emboîte assez bien avec **décorateur** :

```java
class SalarieBuilder {

  private I_Salarie salarie;

  public SalarieBuilder(double salaire) {
    salarie = new Salarie(salaire);
  }

  public SalarieBuilder withChefProjet(int nombreProjetsGeres) {
    salarie = new SalarieChef(salarie, nombreProjetsGeres);
    return this;
  }

  public SalarieBuilder withResponsableStagiaires(int nombreStagiairesGeres) {
    salarie = new ResponsableDeStagiaires(salarie, nombreStagiairesGeres);
    return this;
  }

  public I_Salarie build() {
    return salarie.clone();
  }

}

class Main {

  public static void main(String[]args) {
    I_Salarie salarie1 = new SalarieBuilder(2000).build();
    I_Salarie salarie2 = new SalarieBuilder(2500).withChefProjet(3).build();
    I_Salarie salarie3 = new SalarieBuilder(2300).withResponsableStagiaires(5).build();
    I_Salarie salarie4 = new SalarieBuilder(1800).withChefProjet(4).withResponsableStagiaires(2).build();
  }

}
```

<div class="exercise">

1. Refactorez le code de votre application pour ajouter un builder (adapté) pour vos **produits**.

2. Adaptez le code de `Main` pour utiliser votre builder au lieu de la fabrique.

</div>

La version utilisant le **builder** semble bien plus pratique que la **fabrique** ! C'est donc une solution plutôt satisfaisante pour ce problème qu'on pourra retenir.

## Amélioration du générateur de donjons

Et si nous essayons de combiner plus de patterns ? Nous avons l'application idéale pour ça : le générateur de donjon (paquetage `fabrique2`). Il y a déjà la **Fabrique Abstraite**, le **Singleton** et **Prototype**.

<div class="exercise">

1. Nous aimerions maintenant que les différentes salles puissent être combinées afin de créer une "super-salle". Par exemple, on aimerait avoir des salles avec des coffres et 20 ennemis, une salle avec une énigme et un boss, une salle avec tout à la fois...! Quel design pattern pouvez-vous utiliser pour mettre en place une telle fonctionnalité ? La seule méthode qui nous intéresse est `toString`. À l'affichage, on doit avoir les informations de toutes les salles qui composent une salle. Après vos refactoring, vous devrez logiquement adapter le code de vos deux **fabriques**. Pour la configuration **difficile**, on souhaite faire des changements supplémentaires :

    * Une salle normale est une salle avec un coffre et entre 20 et 40 ennemis.

    * Une salle spéciale est soit une salle avec un coffre et 20 ennemis (une chance sur cinq) ou bien une salle avec un boss avec un niveau entre 30 et 50.

    * La salle finale est une salle avec une énigme, un boss de niveau 80 et 30 ennemis.

2. On aimerait améliorer la création des **salles** composées. Par exemple, avec un **Builder** (adapté)...?

3. Testez que tout fonctionne.

4. Mettez à jour le diagramme de classes de conception que vous aviez initialement produit pour cette application.
</div>

## Conclusion

Vous maîtrisez maintenant l'ensemble des **design patterns créateurs** ainsi que le pattern **Adaptateur**. Ce TP vous a aussi logiquement permis de renforcer votre pratique de la conception logicielle et de l'application des principes `SOLID`.

Toutefois, attention à ne pas attraper la **patternité** : c'est une maladie connue qu'attrapent les jeunes ingénieurs logiciels qui découvrent les **design patterns**. Cela se manifeste par une envie de mettre des patterns partout à tort et à travers même quand cela n'est pas nécessaire. Comme pour le **singleton**, il faut se poser la question de savoir si un pattern est nécessaire ou non. Normalement, l'utilisation d'un pattern vient assez naturellement quand on souhaite résoudre le problème qui lui est lié. Si son utilisation semble un peu trop forcée, c'est que cela est probablement injustifié, ou pire : on est en train de construire un [anti-pattern](https://en.wikipedia.org/wiki/Anti-pattern), une solution non-seulement injustifiée, mais aussi qui a plus de conséquences négatives que positives. Bref, comme toujours, il faut avoir une vision générale et sur le long terme !

Dans le prochain TP, nous verrons comment encore plus optimiser la **gestion des dépendances** de notre programme en construisant notre propre **conteneur IoC** afin de gérer dynamiquement les dépendances majeures de nos applications.
