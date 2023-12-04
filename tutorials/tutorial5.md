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

2. Tout est cassé ! Il faut donc mettre en place un fix temporaire. Tout cela va se jouer dans le `Main` où étaient utilisées les fabriques abstraites. Il va falloir fixer cela vous-même en faisant des `new` à la place. Pour les services utilisés, choisissez `StockageUtilisateurMemoire`, `ServiceMailerChiffre` et `HasheurSHA256`.

3. Vérifiez que l'application fonctionne (pas d'erreur au lancement du moins).

</div>

### Conteneur basique - Enregistrement et récupération

Nous allons créer notre classe `Cotneneur` qui répondra à des besoins simples (pour l'instant), à savoir : permettre d'associer des instances d'objets à un nom, les stocker puis permettre de le récupérer en utilisant leur nom.

Pour cela, le type le plus approrié semble être une `Map` qui associe des chaînes de caractères `String` à des objets `Object`. Pour rappel, en java, tous les objets descendent de la classe mère `Object`. Donc, une structure stockant des `Object` peut accueillir n'importe quelle instance.

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

class Exemple {

    private Service service;

    public Exemple(Service service) {
        this.service = service;
    }

    public void run() {
        service.action();
    }

}


//Le conteneur est déjà initialisé...
conteneur.registerService('service', new B());
conteneur.registerService('exemple', new Exemple(conteneur.getService('service')));

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

3. Dans la classe `Main`, nous allons créer une méthode `static` dédiée à l'enregistrement des services dans le conteneur au lieu de tout faire dans la fonction `main`. Créez donc une fonction statique `initContainerServices` qui commence par enregistrer les 3 premiers services de notre application dans le **container** : le `stockage`, le `mailer` et le `hasher` (reprenez les mêmes que ceux utilisés dans `main`). Utilisez les noms que vous voulez pour ces services. Pour rappel, le **container** est un singleton, on peut donc facilement y accéder !

4. Essayez maintenant d'enregistrer le service correspondant à `ServiceUtilisateur`. Attention, il faut impérativement le faire en récupérant les instances des trois services requis pour l'initialisation de ce service depuis le **container** en utilisant votre méthode `getservice` (comme dans l'exemple). Certes, dans le contexte actuel, vous auriez pu instancier les services au préalable puis les enregistrer et les réutiliser dans utiliser `getService`, mais cela ne sera pas toujours possible (nous 'en sommes qu'au début !). Maintenant, dès qu'on veut accéder à un service, on utilise le **container**. Bref, normalement, vous obtenez une erreur ! Avant de passer à al suite, prenez le temps de la comprendre (mais ne réparez rien pour le moment !)

</div>

Il y a un problème de type : `ServiceUtilisateur` a, par exemple, besoin d'un objet de type `StockageUtilisateur`, et `getService` renvoie un `Object` ! Ce n'est pas un type assez spécialisé ! Pourtant, nous, au départ, dans le **container**, on a bien stocké une classe concrète implémentant `StockageUtilisateur` ! C'est le même problème pour les deux autres objets demandés.

Malheureusement, nous ne pouvons pas non plus changer le type de valeur stocké dans la `Map` du container (`Object`) qui doit être le plus général possible pour pouvoir stocker n'importe quelle instance...

Vous connaissez sans doutes déjà la solution : il faut **caster**, c'est-à-dire changer le type (la classe) utilisé pour lire l'objet (il n'y a pas de "transformation" de l'objet, simplement du type de lecture). Ici, c'est à priori un **cast** "safe" car on sait que l'objet rentré dans le container et récupéré ensuite est bien du bon type. Mais il faut tout de même faire attention quand on utilise ce genre de fonctionnalité, car certains types ne sont bien sûr pas compatibles.

Par exemple, ici, il est tout à fait possible de caster un `Object` qui est en réalité (dans la mémoire lors de l'éxécution) une instance de `StockageUtilisateurMemoire` (ou de `StockageUtilisateurFichier`) en `StockageUtilisateur`. Il est d'ailleurs primordial d'utiliser le type abstrait pour le **cast** (dans notre situation) car la classe cible attend en paramètre ce type abstrait. Cela permettra de rendre ce **cast** compatible avec n'importe quelle instance implémentant l'interface mère `StockageUtilisateur`.

Cependant, qui doit effectuer ce **cast** ? Cela ne semble pas adéquat de faire cela à chaque fois qu'on appelle `getService` ! En fait, c'est aussi le rôle du **container**. Mais comment faire, vu que la méthode `getService` est paramétrée pour renvoyer le type `Object` ?

Il est temps de vous présenter une fonctionnalité de Java que vous ne connaissiez peut-être pas : **le type de retour paramétrable.**

### Paramétrage - Centralisation de l'instanciation

## Lazy loading et injection

## Fichier de configuration XML

### Bases

### Parsing

## Auto-wiring



