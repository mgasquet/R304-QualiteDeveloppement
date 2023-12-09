---
title: TP5 &ndash; Le conteneur de dépendances
subtitle: Injection de dépendances, Inversion de contrôle, Framework, Configuration, XML, Autowiring, Annotations
layout: tutorial
lang: fr
---

## Introduction

Lors du dernier TP, nous avons résolu les problèmes liés à l'instanciation des objets en utilisant divers **patterns créateurs**. Notamment, l'utilisation du pattern **fabrique** et **fabrique abstraite** a permis de concentrer les dépendances de type "create" (qu'un un objet en créé un autre) dans le service particulier que représentent ces fabriques. Au lieu d'instancier les objets eux-mêmes, les différentes classes de l'application utilisent alors des **fabriques** (et d'autres patterns) ce qui permet, quand on applique bien les principes **SOLID** (notamment le `D`), une grande modularité de l'application.

En fait, nous avons vu deux types d'utilisation de la **fabrique** :

* Pour instancier de nouveaux objets dès qu'elle est sollicitée (comme par exemple, avec l'exercice sur les **donjons**).

* Pour gérer et stocker diverses **dépendances concrètes** et les fournir aux classes qui ont en besoin. Dans ce type de **fabrique**, les objets concrets ne sont instanciés qu'une seule fois (lors de l'initialisation) et les différentes méthodes de la fabrique concrète servent à renvoyer ces objets (sans les recréer). C'est donc une sorte de **gestionnaire des dépendances**. Cela permet aussi de limiter le nombre de services/dépendances type **singletons** mis en place dans l'application (les services gérés par la fabrique ne sont pas des singletons) tout en faisant en sorte qu'une seule instance du service soit effectivement utilisée par l'application (en allant la chercher dans la fabrique).

Cette deuxième utilisation de la fabrique est très intéressante car, en utilisant en plus une **fabrique abstraite** on peut **injecter** différentes **familles** d'instances dans des classes qui dépendent d'abstractions ("dépendre d'abstractions, pas d'implémentation concrète...") ce qui permet de très simplement modifier les **services concrets** utilisés par le programme (et aisni, son fonctionnement) en paramétrant la fabrique utilisée.

Nous l'avons déjà dit, mais dans l'architecture idéale, chaque classe doit être la moins dépendante possible de classes concrètes, pour pouvoir facilement intervertir les services utilisés, mais aussi pour rendre l'application testable. Les fabriques qui gèrent des dépendances nous aident donc en ce sens.

Cependant, il y a quelques inconvénients avec ce fonctionnement :

* Dès qu'on veut mettre en place une nouvelle configuration, on doit créer une nouvelle fabrique concrète dédiée (et donc recompiler le code).

* Si un seul ou deux services changent d'une configuration à l'autre, on est obligé de créer une fabrique dédiée et dupliquer une partie du code, à moins de bien diviser les fabriques en catégorie (ou en ayant une seule fabrique par type de dépendance, par exemple, une fabrique gérant le support de stockage, une fabrique pour le système du hachage de mot de passe...)

* Plus il y a de familles de services et de services différents, plus on multiplie les fabriques "gestionnaires de dépendances" dans l'application.

* "Switcher" d'une configuration à l'autre peut signifier qu'il faut modifier le code source.

Pour le dernier problème, nous avons apporté une solution dans le dernier TP en utilisant des **fichiers de configuration** textuels simplistes. En fait, cela va un peu être l'objectif de ce TP, mais en beaucoup plus large.

Les autres problèmes demeures et prouvent la nécessité d'avoir un autre système que des **fabriques** pour gérer les dépendances du programme (bien sûr, les fabriques restent toujours très utiles dans leur utilisation initiale, comme dans l'exercice "donjon").

L'outil ultime pour gérer la problématique des dépendances est **le conteneur de dépendances IoC**. Le terme **IoC** désigne un pattern (non **GoF**) signifiant "Inversion of Control". Ce pattern est utilisé dans la plupart des **frameworks** au travers d'un objet appelé **conteneur de dépendances** qui construit, stocke, contrôle, injecte et centralise toutes les **implémentations concrètes** des **dépendances abstraites** utilisées par les objets du programme. Cela peut être vu comme une "super-fabrique" gérant des dépendances **unique** et construite **dynamiquement** (lors du lancement du programme). Il est possible de charger différents assemblages de dépendances sans avoir besoin de modifier le code du conteneur.

Si le **conteneur de dépendances** est bien implémenté et possède suffisant de fonctionnalités, il devient alors très aisé de modifier le fonctionnement du programme **sans toucher au code source** en changeant la configuration des services chargés par le **conteneur**.

Un bon **conteneur de dépendances IoC** propose les fonctionnalités suivantes :

* **Enregistrement** de nouvelles **dépendances** concrètes.

* **Injection des dépendances** dans les classes qui ont en besoin.

* **Lazy-loading** des services.

* Configuration du conteneur et des dépendances à partir d'un fichier (`XML`, `YAML`...) sans avoir besoin de toucher au code source (donc, sans avoir à recompiler l'application).

* **Parsing** des paramètres.

* Un certain degré d'**auto-wiring**.

Ces différents points abordent des termes qui sont sans doutes encore obscurs pour vous (notamment lazy-loading, parsing, auto-wiring...) mais nous allons y revenir en temps voulu.

Dans votre carrière, vous allez souvent être amené à utiliser (plutôt à configurer) un **conteneur de dépendances** au travers du fichier de configuration du framework que vous utiliserez (par exemple, **Spring** en Java, ou bien **Symfony** pour PHP...). Par ailleurs, dans les cours de complément web du semestre 4 (pour le parcours **RACDV**), un conteneur sera utilisé.

Comme toujours, en tant que "développeur" (et plus simplement "codeur") il est primordial que vous compreniez les rouages d'une telle technologie et son fonctionnement, en profondeur. Les **frameworks** donnent un peu l'impression d'être magique, notamment grâce à leur système de gestion des dépendances. Et cela peut s'avérer risqué car, dès lors, le développeur perd un peu la main sur son programme.

Afin de bien comprendre comment fonctionne le **conteneur IoC**, vous n'allez pas seulement en utiliser un... Vous allez en construire un ! Vous verrez qu'au final, si on découpe bien le problème étape par étape, ce n'est pas *trop* compliqué ! À la fin de ce TP, vous obtiendrez alors un conteneur hautement configurable (et assez complet) qui pourra être exporté en tant que librairie et utilisé sur n'importe quel projet (Java, mais le principe est le même sur n'importe quel langage...) 

Pour tester notre **conteneur** au fur et à mesure, nous allons utiliser un projet provenant du dernier TP, sur lequel nous voulions gérer les différentes dépendances.

<div class="exercise">

1. Pour commencer, forkez [le dépôt GitLab suivant](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/tp5) en le plaçant dans le namespace `qualite-de-developpement-semestre-3/etu/votrelogin`.

2. Clonez votre nouveau dépôt en local. Ouvrez le projet avec votre IDE et vérifiez qu'il n'y a pas d'erreur. Explorez les fichier, lancez-le programme pour tester.

3. À la fin de chaque séance, n'oubliez pas de faire un **push** vers votre dépôt distant sur **GitLab**.

</div>

## Bases du conteneur

Nous allons commencer par poser les bases de notre **conteneur** avec pour objectif de centraliser l'enregistrement, l'instanciation et la récupération des dépendances nécessaires au fonctionnement de l'application dans une seule classe (notre conteneur) et cela de manière dynamique. Ce conteneur doit donc être compatible avec n'importe quel type d'objet (contrairement aux fabriques qui sont spécialisées pour une "famille" donnée).

### Réorganisation du code

Comme vous avez pu le constater en parcourant l'application, nous utilisons actuellement un système composé de **fabriques abstraites** (et concrètes) pour gérer nos **dépendances**. Comme nous allons mettre en place un **conteneur**, nous ne pouvons pas garder ce fonctionnement. Nous allons donc supprimer le système en place et déplacer (temporairement) l'instanciation et le "câblage" des services dans le `Main`.

<div class="exercise">

1. Supprimez les différents fichiers liés aux **fabriques** : `AbstractServiceFactory`, `AbstractStorageFactory`, `SecureServiceFactory`, `NormalServiceFactory`, `FichierStockageFactory` et `MemoireStockageFactory`.

2. Tout est cassé ! Il faut donc mettre en place un fix temporaire. Tout cela va se jouer dans le `Main` où étaient utilisées les fabriques abstraites. Il va falloir fixer cela vous-même en faisant des `new` à la place. Pour les services utilisés, choisissez `StockageUtilisateurMemoire`, `ServiceMailerChiffre` et `HasheurSHA256`. Pour `ServiceMailChiffre`, il y a besoin d'un objet `ConnexionSMTP`. Instanciez cet objet avec les paramètres : `127.0.0.1` (chaîne), `587` (entier) et `true`;

3. Vérifiez que l'application fonctionne (pas d'erreur au lancement du moins).

</div>

### Conteneur basique - Enregistrement et récupération

Nous allons créer notre classe `Cotneneur` qui répondra à des besoins simples (pour l'instant), à savoir : permettre d'associer des instances d'objets à un nom, les stocker puis permettre de le récupérer en utilisant leur nom.

Pour cela, le type le plus approprié semble être une `Map` qui associe des chaînes de caractères `String` à des objets `Object`. Pour rappel, en java, tous les objets descendent de la classe mère `Object`. Donc, une structure stockant des `Object` peut accueillir n'importe quelle instance.

Petit rappel du fonctionnement d'une `Map` en java :

```java
//Permet d'associer des "clé" de type Type1 avec des valeurs de type Type2
//Map est un type abstrait (interface), HashMap est un type concret
Map<Type1, Type2> map = new HashMap<>();

//Associe la valeur de cle (qui a pour type Type1) avec une valeur (de type Type2)
map.put(cle, valeur);

//Récupère la valeur associée à la clé dans la Map
Type2 val = map.get(cle);

//Exemple d'une map associant des caractères à des booléens :
Map<Character, Boolean> exMap = new HashMap<>();
exMap.put('a', false);
exMap.put('d', true);
exMap.put('z', true);

boolean valD = exMap.get('d');
```

Pour l'instant, on aimerait pouvoir utiliser deux **méthodes** avec notre **conteneur** :

* `registerService(String nomService, Object instance)` : permet de stocker l'instance `instance` dans le **conteneur** en l'associant au nom désigné par `nomService`.

* `getService(String nomService)` : permet de renvoyer un `Object` correspondant au service désigné par `nomService` dans le **conteneur**.

On pourra alors commence à utiliser notre **conteneur** ainsi :

```java
interface Service {
    void action();
}

class A implements Service {

    public action() {/*...*/}

}

class B implements Service {

    public action() {/*...*/}

}

class MaClasse {

    private String var1;

    private int var2;

    public MaClasse(String var1, int var2) {
        this.var1 = var1;
        this.var2 = var2;
    } 

}

class Exemple {

    private Service service;

    private MaClasse maClasse;

    public Exemple(Service service, MaClasse maClasse) {
        this.service = service;
        this.maClasse = maClasse;
    }

    public void run() {
        service.action();
    }

}


//On imagine que le "conteneur" est déjà initialisé...
conteneur.registerService('service', new B()); //On aurait pu rempalcer par A !

conteneur.registerService('objet_pour_exemple', new MaClasse("coucou", 5));

conteneur.registerService('exemple', new Exemple(conteneur.getService('service'), conteneur.getService('objet_pour_exemple')));

//Autre part dans le code :
Exemple ex = conteneur.getService('exemple');
ex.run();
```

<div class="exercise">


1. Dans le paquetage `ioc`, créez la classe `Conteneur` en complétant le squelette de code suivant :

        ```java
        public class Conteneur {

            //Structure stockant les différents services en associant des chaînes de caractères à des instances d'objets
            private ??? services;

            private Conteneur() {
                services = ???;
            }

            //Permet de stocker l'instance "instance" dans le conteneur en l'associant au nom désigné par "nomService"
            public void registerService(String nom, Object instance) {
                
            }

            //Permet de renvoyer un Object correspondant au service désigné par "nomService" dans le conteneur
            public Object getService(String name) {
                
            }

        }
        ```

2. Il semble judicieux (et justifié) que `Conteneur` soit un **singleton**. En effet, il semble cohérent qu'il n'y ai qu'une seule instance de cette classe et que le conteneur permettant de récupérer n'importe quelle dépendance du projet soit accessible partout. Le conteneur ne fait pas partie du code métier, il ne sera donc pas non plus testé unitairement, à priori. Transformez donc `Conteneur` en **singleton**.

3. Dans la classe `Main`, nous allons créer une méthode `static` dédiée à l'enregistrement des services dans le conteneur au lieu de tout faire dans la fonction `main`. Créez donc une fonction statique `initContainerServices` qui commence par enregistrer un service `smtp` correspondant à un objet `ConnexionSMTP` avec les paramètres `127.0.0.1`, `581` et `true`.

4. Ensuite, enregistrez les 2 premiers services de notre application dans le **conteneur** : le `stockage` et le `hasher` (reprenez les mêmes que ceux utilisés dans `main`). Utilisez les noms que vous voulez pour ces services. Pour rappel, le **conteneur** est un singleton, on peut donc facilement y accéder !

5. Essayez maintenant d'enregistrer le service correspondant au `mailer`. Attention, il faut impérativement le faire en récupérant l'instance de `ConnexionSMTP` requis pour l'initialisation de ce service depuis le **conteneur** en utilisant votre méthode `getService` (comme dans l'exemple). Certes, dans le contexte actuel, vous auriez pu instancier les services au préalable puis les enregistrer et les réutiliser dans utiliser `getService`, mais cela ne sera pas toujours possible (nous n'en sommes qu'au début !). Maintenant, dès qu'on veut accéder à un service, on utilise le **conteneur**. Bref, normalement, vous obtenez une erreur ! Avant de passer à la suite, prenez le temps de la comprendre (mais ne réparez rien pour le moment !)

</div>

Il y a un problème de type : Votre `mailer` (que cela soit `ServiceMailerBasique` ou bien `ServiceMailerChiffre`) a besoin d'un objet de type `ConnexionSMTP`, et `getService` renvoie un `Object` ! Ce n'est pas un type assez spécialisé ! Pourtant, nous, au départ, dans le **conteneur**, on a bien stocké une classe concrète implémentant `ConnexionSMTP` !

Malheureusement, nous ne pouvons pas non plus changer le type de valeur stocké dans la `Map` du conteneur (`Object`) qui doit être le plus général possible pour pouvoir stocker n'importe quelle instance...

Vous connaissez sans doutes déjà la solution : il faut **caster**, c'est-à-dire changer le type (la classe) utilisé pour lire l'objet (il n'y a pas de "transformation" de l'objet, simplement du type de lecture). Ici, c'est à priori un **cast** "safe" car on sait que l'objet rentré dans le container et récupéré ensuite est bien du bon type. Mais il faut tout de même faire attention quand on utilise ce genre de fonctionnalité, car certains types ne sont bien sûr pas compatibles.

Par exemple, ici, il est tout à fait possible de caster un `Object` qui est en réalité (dans la mémoire lors de l'exécution) une instance de `ConnexionSMTP`. 

Cependant, qui doit effectuer ce **cast** ? Cela ne semble pas adéquat de faire cela à chaque fois qu'on appelle `getService` ! En fait, c'est aussi le rôle du **container**. Mais comment faire, vu que la méthode `getService` est paramétrée pour renvoyer le type `Object` ?

Il est temps de vous présenter des fonctionnalités de Java que vous ne connaissiez peut-être pas : **la généricité des méthodes** et **le type de retour paramétrable.**

Vous connaissez probablement la notion de type **générique** que nous avons déjà abordé dans le dernier TP. Pour rappel, il est possible de créer une classe java **générique** en précisant un ou plusieurs **types paramétrables** lors de la définition de la classe. Ces types ne sont pas connus dans le code de la classe et sera précisé lors de l'instanciation d'un objet de ce type. Cela permet notamment d'avoir des classes gérant différents types de données avec le même code. Par exemple `List` est un type générique permettant de préciser un type paramétrable (lez type géré par la liste). `Map` esr aussi une classe générique et permet d'accueillir deux types paramétrables (un pour la clé, un pour la valeur).

Pour rappel, on définit une classe **générique** comme cela :

```java
//Classe possédant un type générique référencé par la lettre "T" (cela peut être une autre lettre)
public class Exemple<T> {

    //On peut utiliser le type générique "T" un peu partout dans le code de la classe (attributs, paramètres, type de retour...).
    //Il utilise comme tout autre type "normal"
    private T var1;
    private HashMap<String, T> map;

    public Exemple(T var) {
        //...
    }

    public List<T> action() {
        //...
    }

    public T getVar() {
        //...
    }

}

//On peut alors créer différentes instances de "Exemple" paramètrées avec un type différent :
//Comme le constructeur attend un paramètre de type "T" (dans notre exemple), il verifiera que le paramètre spécifié est bien du type paramétré cette instance.
Exemple<Integer> ex1 = new Exemple(1);
Exemple<String> ex2 = new Exemple("coucou");
```

Bref, vous aviez sans doutes déjà un souvenir complet ou incomplet de cette fonctionnalité.

Mais saviez-vous qu'il est aussi possible de définir une **fonction générique** en ajoutant des types paramétrables au niveau de la définition d'une fonction ? On parle bien de types qui ne seraient définis **que pour cette fonction** et pas pour la classe entière (donc, pas comme les méthodes de `Exemple<T>`) !

Pour faire cela, il suffit d'utiliser la même notation que pour la classe : `<T, K, V, ...>`, mais au niveau de la méthode/fonction. Les types paramétrés peuvent alors être utilisés dans le **type de retour** de la fonction, notamment. Par contre, il faut impérativement que ces types soient précisé quelque part dans les paramètres de la fonction (et on peut aussi avoir des paramètres avec des types connus, bien entendu).

C'est quand on va appeler la fonction avec des paramètres ayant des types concrets que la fonction va se "configurer" avec les types précisés. Cela peut être un peu difficile à comprendre au premier abord !

Illustrons tout cela avec un exemple :

```java

public static <T> T action(T var) {
    //...
}

//J'appelle "action" avec une chaîne de caractère (String) : ma fonction me renvoie donc un String
//C'est comme si la fonction était devenue "public static String action(String var)"
//C'est l'appel (ce qu'on passe en paramètre) qui définit le type de retour.
String s = action("coucou");

Integer b = action(5);

Boolean c = action(false);

//Le type de retour peut aussi faire référence à un paramètre générique configuré dans une classe : 
public static <T> T rechercheMinimum(List<T> var) {
    //...
}

List<String> maListeNoms = new ArrayList(Arrays.asList("Paul", "Nicolas", "Amandine"));
//Renvoie la plus petite chaîne (dans l'ordre alphabetique)
String plusPetiteChaine = rechercheMinimum(maListeNoms);

List<Integer> maListeNombres = new ArrayList(Arrays.asList(5, 2, 0, -1, 9));
//Renvoie le plus petite nombre 
int plusPetitNombre = rechercheMinimum(maListeNombres);

//On aurait pu faire la même chose avec un tableau :
public static <T> T rechercheMinimum(T[] var) {
    //...
}

//On est pas obligé de renvoyer simplement T (et les autres paramètres), il peuvent aussi servir comme paramètre dans une classe générique.
//Par ailleurs, on peut tout à fait avoir des paramètres de tpyes connus dans la méthode ! (en plus des paramètres génériques)
public static <T, V> Map<T, V> exemple(K valeur, T val, boolean filter) {

}

Map<String, Double> map = exemple("coucou", 1.3, false);

//On peut bien sûr utiliser la généricité des foncitons sur une méthode non statique dans une classe
class MaClasse {

    public void action() {/*...*/}

    public <T> T maMethode(boolean val, Set<T> test) {
        //...
    }
}
```

Les **fonctions génériques** vont permettre de règle notre problème de **cast**. L'idée serait donc de modifier la méthode `getService` pour lui préciser en paramètre **le type** (la classe) du service ciblé et que la méthode renvoie alors le service **casté** dans ce type. La fonction se basera sur le type précisé en paramètre pour son type de retour !

En **Java**, une classe particulière permet de modéliser des "types" : La classe...`Class` ! Cette classe est **générique** et attend un type en paramètre. Il s'agit du type de la classe ciblée. Il est possible de récupérer cet objet `Class` à partir de n'importe quelle classe ou interface de l'application :

```java
Class<Integer> classeInt = Integer.class;
Class<String> classeString = String.class;
Class<MaClasse> classeMaClasse = MaClasse.class;
Class<MonInterface> classeMonInterface = MonInterface.class;
```

Cet objet est très utile car, plus tard, il nous permettra de faire de la **métaprogrammation** en récupérant des constructeurs de la classe afin d'instancier des nouveaux objets dynamiquement, en analysant ses données, ses **annotations**...

Pour l'instant, une méthode en particulier nous intéresse : `cast` : permet de **caster** un objet dans le type représenté par l'instance de `Class` :

```java
Object o = new String("Coucou");
Class<String> classeString = String.class;
String texte = classeString.cast(o);
```

Attention, si le type n'est pas compatible avec l'instance réelle de l'objet **casté**, il y aura une erreur ! Par exemple, à l'exécution, il y aurait eu une erreur si on avait eu une instance d'un `Integer` dans `o` à la place d'un `String`...

Il est bien sûr possible de caster dans une **abstraction** (classe abstraite / interface) si l'instance implémente l'interface visée ou dérive de cette classe.

Dans notre cas, on aimerait donc utiliser `getService` ainsi :

```java
interface Service {
    //...
}

class ServiceA implements Service {
    //...
}

class ServiceB implements Service {
    //...
}

class Manager {
    private Service service;

    public(Service service) {
        this.service = service;
    }
}

container.registerService("service", new ServiceA());

//Cherche l'instance "Object" associée au nom "service" puis la renvoie en la castant en "Service"
Service service = conteneur.getService("service", Service.class);

container.registerService("manager", new Manager(service));
//Ou bien :
container.registerService("manager", new Manager(conteneur.getService("service", Service.class)));

//Cherche l'instance "Object" associée au nom "manager" puis la renvoie en la castant en "Manager"
Manager manager = container.getService("manager", Manager.class);
```

<div class="exercise">

1. Modifiez la méthode `getService` afin de la rendre **générique** puis en lui ajoutant un second paramètre correspondant au **type** de la classe dans laquelle doit être **casté** le service récupéré dans la `Map` du conteneur. La méthode doit maintenant renvoyer un objet casté dans le type souhaité. Relisez bien toute la section sur la généricité des fonctions pour comprendre comment faire cela, en regardant notamment les exemples. Si jamais vous bloquez réellement, n'hésitez pas à demander un peu d'aide à votre enseignant.

2. Adaptez votre fonction `initContainerServices` en enregistrant le service correspondant à votre `mailer` en utilisant la nouvelle version de `getService` pour injecter le service dont dépend cette classe.

3. Enregistrez un service correspondant à une instance de `ServiceUtilisateur`. Là aussi, il faudra injecter les trois services dont dépend cette classe en utilisant `getService`.

5. De la même manière, enregistrez le service correspondant au **controller**.

6. Dans la fonction `main`, supprimez tout le code et remplacez-le par :

    * Un appel à `initContainerServices` afin d'initialiser le conteneur et les services.

    * La récupération du **controller** depuis le conteneur.

    * Un appel à la méthode `startIHM` du controller.

7. Lancez votre application et vérifiez que tout fonctionne comme attendu !

8. Dans `initContainerServices`, changez les instances concrètes utilisées pour le `mailer`, le `hasher` et le `stockage`. Normalement, si tout est bien implémenté, vous ne devez que modifier les paramètres des trois appels à `registerService` et rien d'autre. Relancez le programme et vérifiez que tout fonctionne encore. S'il y a une erreur, c'est que vous avez probablement utilisé une classe concrète au lieu d'une abstraction à certains endroits (lors d'appels à `getService` pour initialiser `ServcieUtilisateur`, par exemple...) ! En effet, il est tout à fait possible de **caster** une classe dans un type abstrait qu'elle implémente (son interface, sa classe abstraite mère...).

</div>

### Paramétrage - Centralisation de l'instanciation

Notre base de conteneur est fonctionnelle, mais nous faisons toujours des `new` dans le `Main` pour instancier les dépendances. Le but du conteneur est aussi de **centraliser** l'instanciation de ces dépendances. Nous allons donc remédier à cela en modifiant la méthode `registerService`. À la place de donner simplement à cette méthode un `Object` correspondant à l'instance déjà créée d'une dépendance, nous allons plutôt fournir toutes les données nécessaires à son instanciation : le type de la classe **concrète** que l'on veut créer et l'ensemble des **paramètres** à fournir à son **constructeur**. 

Concernant la **classe**, nous allons à nouveau utiliser l'objet `Class` comme dans l'exercice précédent. On rappelle que quand on utilise un objet `Class`, il est attendu de spécifier le type paramétré utilisé : `Class<...>`. Cependant, dans notre cas, pour l'enregistrement, nous n'attendons pas de classe spécifique. La généricité n'est pas forcément une bonne une solution ici, car, lors de l'enregistrement, le but n'est pas de pouvoir utiliser différentes versions de cette méthode par type, mais simplement de la rendre compatible avec n'importe quelle `Class` passée en paramètre. De plus, le type de retour ne dépend pas de ce type paramétré dans le cas de `registerService`. 

Il existe une solution très simple pour ce problème : utiliser le type `?` comme type paramétré pour `Class` : `Class<?>`. Le `?` sert simplement à dire "n'importe quel type". Cependant, contrairement au type paramétré, ce `?` ne pourra pas être réutilisé comme retour de la fonction, par exemple (on n'aurait pas pu l'utiliser pour `getService`).

```java
//Accepte des listes de n'importe quel type
public void traitementListe(List<?> param) {

}

//Accepte des classes de n'importe quel type
public void traitementClasse(Class<?> param) {

}

//On aurait aussi pu utiliser la générécité ici, mais cela aurait été inutile, car on ne se sert pas de T dans le type de retour !
//Dans ce cas, on préférera donc utiliser la syntaxe utilisant "?"
public <T> void traitementClasse(Class<T> param) {

}

//Attention par contre, dans cet exemple que nous avions vu précédemment, on a besoin du type paramétré dans le retour !
//L'utilisation de "?" ne marcherait donc pas
public <T> T rechercheMinimum(T[] var) {
    //...
}
```

Pour la suite, nous avons besoin de spécifier la liste correspondant aux valeurs des **paramètres** du constructeur que nous souhaitons utiliser pour cette classe. Comme ces paramètres peuvent être de n'importe quelle nature, nous devons donc utiliser la classe la plus générale dans la hiérarchie : `Object`.

Nous pourrions donc utiliser un tableau d'objets `Object[]` mais, pour des questions d'ergonomie, nous pouvons aussi utiliser plus simplement la notation Java permettant de spécifier autant de valeurs (d'un même type) que l'on souhaite. Ces valeurs sont ensuite converties en un tableau dans la fonction. 

```java
public double moyenne(int..valeurs) {
    //valeurs est un tableau d'entiers : int[]
    double somme = 0.0;
    for(int val : valeurs) {
        somme += val;
    }
    return (somme / valeurs.length);
}

//Tous ces appels sont valides
moyenne(1,5,6,7);
moyenne(1,2);
moyenne(5,6,7,8,9,10,1,12,33):

//Il est aussi de faire un appel en passant directement un tableau
moyenne(new int[]{1,2,6,7,8}):

//On peut utiliser d'autres paramètres dans la fonctions, mais dans ce cas, la notation Type..var doit être en dernière position !
public void exemple(String ex, Object..vals) {
    //vals est un tableau d'objets : Object[]
}
```

Enfin, pour instancier un nouvel objet à partir de son objet `Class` et de la liste de ses paramètres (les `Object`) on utilise le code suivant :

```java
//type est un objet Class<?>, valeurs est un tableau d'objets Object[]
Object instance = new Expression(type, "new", valeurs).getValue();
```

À terme, notre objectif sera donc de transformer ce genre de code :

```java
container.registerService("service", new ServiceA());
container.registerService("maClasse", new MaClasse("Coucou", 5));
container.registerService("manager", new Manager(conteneur.getService("service", Service.class), conteneur.getService("maClasse", MaClasse.class)));
```

En :

```java
container.registerService("service", ServiceA.class);
container.registerService("maClasse", MaClasse.class, "Coucou", 5);
container.registerService("manager", Manager.class, conteneur.getService("service", Service.class), conteneur.getService("maClasse", MaClass.class));
```

<div class="exercise">

1. Modifiez la méthode `registerService` afin qu'elle instancie maintenant elle-même l'objet en question (puis l'enregistre dans la `Map` de ses services) :

        ```java
        public void registerService(String name, Class<?> type, Object... parameters) {

        }
        ```
2. Adaptez le code de la fonction statique `initContainerServices` dans `Main` pour utiliser la nouvelle version de `registerService`. Il faudra donc, pour chaque service utilisé :

    * Préciser un **nom** (comme c'était déjà le cas avant).

    * Préciser le **type** d'objet enregistré (avec `Type.class`).

    * Préciser les différentes valeurs nécessaires pour construire l'objet : dans notre cas, les services enregistrés dans le conteneur. Grossièrement, ce que vous passiez au `new` auparavant.

3. Lancez votre application et vérifiez que tout fonctionne.
</div>

À ce stade, nous avons centralisé l'instanciation des objets dans notre conteneur ! Il n'y a plus aucun `new` dans `initContainerServices` ! Peut-être que vous ne voyez pas encore l'intérêt de tout cela à ce stade, mais cela nous permettra prochainement d'automatiser l'enregistrement des services à l'aide d'un fichier de configuration.

### Références

Plutôt que de devoir faire appel à `getService` lorsque nous initialisons nos `services` dès qu'il y a des dépendances, nous pourrions déléguer ce travail au **conteneur**. L'idée serait d'aovir un objet `Reference` contenant le nom d'un service qu'on utiliserait comme paramètre normal dans `registerService` au lieu de faire appel à `getService`.

De son côté, le **conteneur** transformera cette **référence** en l'objet cible désiré en allant chercher dans sa `Map` lors de l'enregistrement. Au-delà de l'aspect ergonomique, ce système nous permettra de mettre en place un système de **lazy-loading** dont nous reparlerons bientôt.

La classe `Reference` est très simple : elle est initialisée avec un paramètre `name` correspondant au nom du service ciblé et on possède un `getter` pour y accéder :

```java
public class Reference {

    private final String serviceName;

    public Reference(String serviceName) {this.serviceName = serviceName;}

    public String getServiceName() {return serviceName;}

}
```

Cependant, comme cette classe est très simple et sert seulement à lire des données (`final`, seulement un `getter`...) il est possible d'utiliser à la place une classe de type `Record`, introduite depuis la version 14 de Java :

```java
//A la place de définir la classe comme au-dessus
public record Reference(String serviceName){}
```

Il est ensuite possible d'accéder à `serviceName` ainsi :

```java
Reference ref1 = new Reference("coucou");
String name = ref1.serviceName();
```

Au niveau du **conteneur**, pour "transformer" une référence en objet lors de l'enregistrement, il faut :

* Initialiser un tableau d'objets ayant la même à la taille que le tableau d'objets (`Object[]`) correspondant aux paramètres utilisés pour instancier le service cible (passé dans `registerServices`).

* Parcourir le tableau d'objets contenant les paramètres, puis :

    * Quand on trouve une **référence**, aller chercher l'objet correspondant au nom stocké dans la référence (avec `getService`) puis le placer dans le nouveau tableau. Ici, on peut caster en `Object`, cela n'aura pas d'influence sur la suite.

    * Sinon, (dans le cas où ce n'est donc pas un objet `Reference`), simplement placer l'objet dans le novueau tableau.

* Utiliser le nouveau tableau produit comme paramètre pour instancier le service (au lieu de celui passé de base dans `registerServices`).

Afin de déterminer si un objet est une `Reference`, on peut utiliser `instanceof` puis faire un `cast` :

```java
if(obj instanceof Reference) {
    Reference ref = (Reference) obj;
    String name = ref.serviceName();
    Object obj = getService(name, Object.class);
}
```

Attention, ce fonctionnement ne respecte pas vraiment le principe ouvert/fermé (par exemple, si on est amené à ajouter de nouveaux objets du style de `Reference` qu'on doit transformer...) mais, pour le moment, nous allons maintenir ce fonctionnement pour ne pas trop compléxifier le code.

Une fois que tout cela est mis en place, on peut alors passer de ça :

```java
container.registerService("service", ServiceA.class);
container.registerService("maClasse", MaClasse.class, "Coucou", 5);
container.registerService("manager", Manager.class, conteneur.getService("service", Service.class), conteneur.getService("maClasse", MaClass.class));
```

À ça :

```java
container.registerService("service", ServiceA.class);
container.registerService("maClasse", MaClasse.class, "Coucou", 5);
container.registerService("manager", Manager.class, new Reference("service"), new Reference("maClasse"));
```

<div class="exercise">

1. Dans le paquetage `ioc`, créez la classe `Reference` (en utilisant plutôt un `record`).

2. Dans votre classe `Conteneur`, ajoutez une méthode privée `transformParameters` qui prend en paramètre un tableau d'objets et renvoie un tableau d'objets de la même taille avec les mêmes objets excepté pour les **références** qui doivent être transformées en objet (correspondant au service ciblé par la référence) :

        ```java
        private Object[] transformParameters(Object[] parameters) {

        }
        ```

3. Dans la méthode `registerService`, utilisez votre nouvelle méthode `transformParameters` afin d'utiliser les paramètres "transformés" lors de l'instanciation du service.

4. Adaptez le code de la fonction statique `initContainerServices` dans `Main` afin d'utiliser des objets `Reference` au lieu de faire appel à `getService` lors de l'enregistrement d'un nouveau service.

5. Vérifiez que tout fonctionne.

</div>

## Lazy loading

Note conteneur fonctionne et permet de centraliser efficacement nos dépendances. Cependant, comme ces dépendances sont enregistrées lors du lancement de l'application, elles sont toutes instanciées à ce moment-là. Cela signfit qu'il y a des services potentiels qui sont initialisés, mais dont nous n'allons peut-être pas nous servir !

Dans notre mini-application, nous nous servons de tout, à priori, car il n'y a qu'un seul **controller**, qu'un seul **service**, etc... Mais il faut s'imaginer que sur une grosse application, il peut être couteux d'initialiser tous ces services au lancement ! Dans le cadre d'une application **web** par exemple, il ne serait pas judicieux d'initialiser les dépendances de tous les contrôleurs alors que la requête d'un utilisateur n'en vise qu'un seul.

Le **lazy loading** permet de résoudre ce problème en faisant en sorte d'initialiser un service donné seulement quand on en a besoin : quand on le récupère (avec `getService`) ou bien quand on récupère un autre service qui a besoin de ce service pour être initialisé (on provoque donc des initialisations en chaîne).

Pour mettre en place un tel système, l'idée est la suivante :

* Créer une classe permettant de stocker les données d'initialisation du service (son type `Class<?>` et ses paramètres `Object[]`)

* Avoir une deuxième `Map` dans le **conteneur** stockant les données d'initialisation de chaque service.

* Avoir une méthode permettant de savoir si un service est chargé/instancié, et une autre pour réellement l'instancier et le stocker comme service.

* Lors de l'enregistrement du service (`registerService`), ne pas l'instancier, mais plutôt enregistrer ses données d'initialisation dans la nouvelle `Map`.

* Lors de la récupération d'un service (`getService`), vérifier si le service est déjà chargé et le faire si ce n'est pas le cas.

<div class="exercise">

1. Dans le paquetage `ioc`, créer une classe `ServiceConfiguration` qui permet de stocker et de récupérer un attribut `type` du type `Class<?>` (type du service) et un tableau d'objets `parameters` (paramètres pour initialiser le service). Vous pouvez réutiliser le système de `record` que nous avons vu plus tôt pour simplifier grandement la création de cette classe ! (une seule ligne nécessaire).

2. Dans votre **conteneur**, ajoutez un nouvel attribut de type `Map` nommé `configurations` permettant d'associer des noms de services (String) à des objets de type `ServiceConfiguration`. N'oubliez pas d'initialiser cet attribut !

3. Toujours dans le **conteneur**, créez une méthode privée `isLoaded` qui permet de savoir si le service a déjà été chargé (et donc initialisé) ou non. Le service n'est pas chargé s'il ne se trouve pas encore dans la map des **services** du conteneur :

        ```java
        private boolean isLoaded(String serviceName) {

        }
        ```

4. Toujours dans le **conteneur**, créez une méthode privée `loadService` qui permet de charger un service à partir de son nom. Il s'agit de récupérer les informations du services depuis la `Map` contenant les configurations puis, de l'initialiser (en instanciant le service) et enfin, de le stocker dans la `Map` contenant les services. Il est aussi préférable de retirer le service de la `Map` stockant les configurations. Pour cette méthode, il faut reprendre une partie du code de `registerService` !


        ```java
        private void loadService(String serviceName) {

        }
        ```

5. Modifiez le code de `registerService` afin que le service ne soit plus instancié et enregistré dans `services`. À la place, on osuhaite stocker ses données d'initialisation dans `configurations`.

6. Modifiez le code de `getService` afin de vérifier que le service est déjà chargé ou non et, si ce n'est pas le cas, déclencher son chargement. Le reste de la méthode reste inchangé, on renvoie (et on **caste**) le service obtenu comme auparavant.

7. Lancez le programme et vérifiez que tout fonctionne.

</div>

## Fichier de configuration XML

Nous arrivons au pont pivot de ce TP qui va nous permettre d'exporter toute la partie "configuration" dans un fichier. Après cette étape, il n'y aura pas besoin d'éditer le code source afin d'initialiser et de relier nos dépendances (comme nous le faisons actuellement dans `initContainerServices`). Toute notre application sera alors modulable grâce à ce fichier ! En plus d'être globalement plus pratique et plus lisible que du code, cela permet aussi d'éditer les dépendances concrètes utilisées sans avoir besoin de recompiler notre programme.

### Mise en place

Notre fichier de configuration va utiliser le langage de balises `XML` (Extensible Markup Language).

### Parsing

### Chargement

### Gestionnaire de parsers

## Auto-wiring



