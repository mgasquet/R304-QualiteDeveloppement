---
title: Synthèse de cours - Les principes SOLID
subtitle:
layout: tutorial
lang: fr
---

## Sommaire

* [Introduction](#introduction)
* [Les principes SOLID](#solid)
  * [Principe de responsabilité unique](#srp)
  * [Principe Ouvert/Fermé](#ocp)
  * [Principe de substitution de Liskov](#lsp)
  * [Principe de ségrégation des interfaces](#isp)
  * [Principe d'inversion des dépendances](#dip)
* [Conclusion](#conclusion)

## Introduction
<div id="introduction"></div>

L'objectif des synthèses de cours est de reprendre les différentes notions de cours présentées dans les TPs, mais sans les mélanger aux exercices, afin de proposer un document à part en entière, qui peut notamment vous aider dans vos révisions.

Dans la première partie de cette ressource, nous avons parlé de **conception logicielle** et notamment comment modéliser cela à l'aide de **diagrammes de classes de conception** et de **diagrammes de séquences des interactions**.

Cependant, savoir modéliser la conception ne garantit en rien la qualité de celle-ci. Un plan de construction d'un bâtiment peut être tout à fait valide d'un point de vue technique, mais donnera potentiellement une bâtisse qui s'écroulera dans quelques années si elle a été mal pensée.

On a la même logique au niveau du développement logiciel. Un logiciel mal conçu peut répondre à un besoin et satisfaire le client et ses utilisateurs dans l'immédiat, mais il sera alors très difficile de le faire évoluer sur la durée.

De manière générale, les principes liés à la qualité du développement s'assurent que le logiciel que vous allez construire pourra évoluer facilement tout en satisfaisant les besoins actuels.

Tout cela est difficile à mettre en place au premier abord, car il peut parfois être bien plus rapide et facile de développer une solution peu qualitative, mais qui fonctionne. Néanmoins, le code produit ne tiendra pas au fur et à mesure que l'application va grossir ce qui conduira finalement à la réécriture d'une partie voir de la totalité du code ou pire, l'abandon du projet.

C'est un phénomène qui touche beaucoup d'entreprises du monde du développement. Face au besoin de délivrer une solution rapidement, l'aspect qualité est parfois négligé. Au bout de plusieurs années, il est très compliqué d'ajouter de nouvelles fonctionnalités et d'éviter les bugs. Une nouvelle personne rentrant dans le projet ne comprend rien au code. Le client n'est plus satisfait, car les nouvelles fonctionnalités sont délivrées moins fréquemment et de plus en plus de bugs apparaissent. C'est une barque qui prend l'eau sur laquelle on place du sparadrap pour boucher les trous. Mais à chaque fois qu'un trou est bouché, deux nouveaux apparaissent. Le client transfère le projet à une autre entreprise, qui ne comprend rien à ce qu'elle récupère... Plus formellement, on dit que la [**dette technique**](https://fr.wikipedia.org/wiki/Dette_technique) s'accumule.

Tout cela est aussi dur pour le développeur. Travailler dans un tel environnement est très désagréable et peut même dégoûter du développement. Jusqu'ici, vous avez travaillé sur des projets relativement petits (même pour vos SAEs) mais vous devriez être plus conscients de cette problématique après votre période de stage ou d'alternance.

L'ingénieur doit avoir une vision à long terme et prendre en compte les évolutions possibles de son programme. Pour l'aider dans cette tâche, il dispose de différents outils : les principes liés à la qualité du code, comme les principes **SOLID** et aussi les **design patterns**. La maîtrise de ces outils différencie un codeur (une IA ?) d'un ingénieur. Le codeur sait produire du code, l'ingénieur sait produire des logiciels durables.

Les **frameworks** sont des outils qui englobent différents **design patterns** et "forcent" le développeur (de par leur structure) à respecter un certain niveau de qualité dans la conception (parfois, sans qu'il s'en rende compte). Nous allons étudier plusieurs **frameworks** l'année prochaine.

Bref, dans ce cours, nous allons commencer par nous intéresser aux **principes SOLID** qui constituent la porte d'entrée vers un programme bien conçu.

## Les principes SOLID
<div id="solid"></div>

Les **principes SOLID** représentent un acronyme lié aux 5 principes clés pour obtenir un logiciel qualitatif :

* Le principe de **responsabiltié unique** (`S`ingle responsability)

* Le principe **ouvert/fermé** (`O`pen/Close)

* Le principe de **substitution de Liskov** (`L`iskov substitution)

* Le principe de **ségrégation des interfaces** (`I`nterface segregation)

* Le principe **d'inversion des dépendances** (`D`ependency inversion)

Le respect de ces principes permet d'améliorer le principe de **faible couplage** et de **forte cohésion** des classes (que nous avons abordé précédemment), l'évolutivité du logiciel, la réduction du risque de bugs liés à l'architecture...

Les **design patterns** sont des solutions à des problèmes bien définis qui fournissent des modèles réutilisables et adaptables sur n'importe quel projet. Ces patterns permettent notamment de respecter les principes **SOLID**.

Dans un logiciel développé d'une telle manière, généralement, l'ajout d'une nouvelle fonctionnalité se résume à l'ajout de nouvelles classes ou de méthodes **sans avoir besoin de modifier ou de récrire les classes existantes**. Le programme est ouvert à l'extension, mais fermé aux modifications (qui pourraient entraîner elles-mêmes d'autres modifications...).

Dans ce cours, nous allons étudier chaque principe à travers divers exemples et voir comment il est possible de **refactorer** un code mal conçu. **Refactorer** du code (ou réusiner du code en français) signifie retravailler le code source du programme sans pour autant ajouter de nouvelles fonctionnalités à l'application. Il s'agit d'améliorer la qualité du code.

### Principe de responsabilité unique (Single Responsability)
<div id="srp"></div>

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

### Principe Ouvert/Fermé (Open/Close)
<div id="ocp"></div>

Le **principe ouvert/fermé** est défini comme suit :

"_Les entités d'un logiciel (classes, modules, fonctions) doivent être **ouverts** aux extensions, mais **fermés** aux modifications._" (**Bertand Meyer**).

En d'autres termes, il doit être possible d'étendre les fonctionnalités/le **comportement** d'une entité comme une classe **sans pour autant avoir besoin de modifier son code source**.

Ce principe est un pilier fondamental de qualité de code. Avec ce principe, même une classe ou une librairie compilée (non modifiable) autorise le développeur à étendre les fonctionnalités proposées.

Malheureusement, dans de nombreux projets, on rencontre fréquemment des classes violant ce principe, car mal conçues. Les symptômes sont généralement :
* Utilisation d'énormes blocs `if/else if/else` ou de blocs `switch case` qui grossisent au fur et à mesure qu'on ajoute de nouvelles choses. Avec l'utilisation de `classes` et de l'héritage, on va en plus certainement se retrouver à utiliser des instructions `instanceof` (pour vérifier le type de l'objet) et de `cast` pour pouvoir utiliser des méthodes précises.
* Nécessité de dupliquer du code pour ajouter une nouvelle fonctionnalité (non-respect du principe [_DRY_](https://en.wikipedia.org/wiki/Don%27t_repeat_yourself)).
* Une classe mère qui dépend de ses classes filles.

Prenons un premier exemple avec des **figures géométriques** :

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

Voyons un autre exemple :

On se place dans le contexte d'un jeu de cartes avec différents types de cartes :

* Carte Arme : possède un certain type de matériau (énumération)
* Carte Bouclier : possède un niveau de défense
* Carte Armée : possède un nombre de soldats et un degré de qualité (deux entiers)
* Carte Etoiles : ne posdède rien de particulier

Certaines cartes rapportent un certain nombre de points qui dépendent de leurs caractéristiques propres :

* Carte Arme : la valeur de son type de matériau
* Carte Bouclier : la valeur de son niveau de défense
* Carte Armée : le nombre de soldats multiplié par le degré de qualité de l'armée
* Carte Etoiles : ne rapporte pas de points

Un joueur possède des **cartes** et gagne la partie s'il a **plus de 2000 points** ou s'il possède au moins une **carte étoiles**.

On veut calculer (dynamiquement) le nombre de points courant d'un joueur et savoir s'il est victorieux.

Une mauvaise solution (fonctionnelle, mais mal conçue) pourrait être la suivante :

```java
abstract class Carte {
    //Rien de particulier, pour l'héritage
}

enum Materiau {

    BOIS(10),
    CUIVRE(30),
    FER(50),
    OR(70),
    DIAMANT(100)
    ;
    
    private int valeur;

    public Materiau(int valeur) {
        this.valeur = valeur;
    }

    public int getValeur() {
        return valeur;
    }
}

class CarteArme extends Carte {

    private Materiau materiau;

    public CarteArme(Materiau materiau) {
        super();
        this.materiau = materiau;
    }

    public Materiau getMateriau() {
        return materiau;
    }

}

class CarteBouclier extends Carte {

    private int niveauDefense;

    public CarteBouclier(int niveauDefense) {
        super();
        this.niveauDefense = niveauDefense;
    }

    public int getNiveauDefense() {
        return niveauDefense;
    }
}

class CarteArmee extends Carte {

    private int nombreSoldats;

    private int qualite;

    public CarteArmee(int nombreSoldats, int qualite) {
        super();
        this.nombreSoldats = nombreSoldats;
        this.qualite = qualite;
    }

    public int getNombreSoldats() {
        return nombreSoldats;
    }

    public int getQualite() {
        return qualite;
    }

}

class CarteEtoiles extends Carte {

    public CarteEtoiles() {
        super();
    }

}

class Joueur {

    private List<Carte> cartes = new ArrayList();

    public void ajouterCarte(Carte carte) {
        this.cartes.add(carte);
    }

    public int compterPoints() {
        int somme = 0;
        for(Carte carte : cartes) {
            if(carte instanceof CarteArme) {
                CarteArme carteArme = (CarteArme) carte;
                somme += carteArme.getMateriau().getValeur();
            }
            else if(carte instanceof CarteBouclier) {
                CarteBouclier carteBouclier = (CarteBouclier) carte;
                somme += carteBouclier.getNiveauDefense();
            }
            else if(carte instanceof CarteArmee) {
                CarteArmee carteArmee = (CarteArmee) carte;
                somme += carteArmee.getNombreSoldats() * carteArmee.getQualite();
            }
        }
        return somme;
    }

    public boolean estVictorieux() {
        if(this.compterPoints() >= 2000) {
            return true;
        }
        for(Carte carte : cartes) {
            if(carte instanceof CarteEtoiles) {
                return true;
            }
        }

        return false;
    }

}
```

<div style="text-align:center">
![Synthèse Diagramme 1]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme1.svg){: width="50%" }
</div>

Cette implémentation est fonctionnelle, mais ne respecte pas le principe **ouvert/fermé** :

* Joueur est dépendant des types **concrets** de cartes (et même de l'énumération `Materiau`).

* Si la méthode de calcul des points que rapporte une carte change, il faut changer la classe `Joueur`.

* Si on ajoute une nouvelle carte qui fait gagner ou qui rapporte des points, il faut changer la classe `Joueur`.

* De même si on supprime une carte du jeu...

De plus, on ne respecte pas la **loi de Déméter** que nous avions vu dans le premier cours de conception : la structure interne des différentes `Carte` et même celle de l'énumération `Materiau` sont exposées !

Bref, il est possible d'exploiter correctement le **polymorphisme** afin que `Joueur` ne soit plus dépendant des différents sous-types de `Carte` :

```java
abstract class Carte {
    public abstract int calculerPoints();

    public abstract boolean faitGagnerPartie();
}

class CarteArme extends Carte {

    private Materiau materiau;

    public CarteArme(Materiau materiau) {
        super();
        this.materiau = materiau;
    }

    @Override
    public int calculerPoints() {
        return this.materiau.getValeur();
    }

    @Override
    public abstract boolean faitGagnerPartie() {
        return false;
    }

}

class CarteBouclier extends Carte {

    private int niveauDefense;

    public CarteBouclier(int niveauDefense) {
        super();
        this.niveauDefense = niveauDefense;
    }

    @Override
    public int calculerPoints() {
        return niveauDefense;
    }

    @Override
    public abstract boolean faitGagnerPartie() {
        return false;
    }
}

class CarteArmee extends Carte {

    private int nombreSoldats;

    private int qualite;

    public CarteArmee(int nombreSoldats, int qualite) {
        super();
        this.nombreSoldats = nombreSoldats;
        this.qualite = qualite;
    }

    @Override
    public int calculerPoints() {
        return nombreSoldats*qualite;
    }

    @Override
    public abstract boolean faitGagnerPartie() {
        return false;
    }

}

class CarteEtoiles extends Carte {

    public CarteEtoiles() {
        super();
    }

    @Override
    public int calculerPoints() {
        return 0;
    }

    @Override
    public abstract boolean faitGagnerPartie() {
        return true;
    }

}

class Joueur {

    private List<Carte> cartes = new ArrayList();

    public void ajouterCarte(Carte carte) {
        this.cartes.add(carte);
    }

    public int compterPoints() {
        int somme = 0;
        for(Carte carte : cartes) {
            somme += carte.calculerPoints();
        }
        return somme;
    }

    public boolean estVictorieux() {
        if(this.compterPoints() >= 2000) {
            return true;
        }
        for(Carte carte : cartes) {
            if(carte.faitGagnerPartie()) {
                return true;
            }
        }

        return false;
    }

}
```

Pour simplifier, comme la majorité des cartes ne font pas gagner la partie, on pourrait éventuellement ajouter à la classe abstraite un code par défaut :

```java
abstract class Carte {
    public abstract int calculerPoints();

    public boolean faitGagnerPartie() {
        return false;
    }
}
```

Afin d'éviter d'avoir à réécrire le code dans la plupart des cartes (mais c'est optionnel).

Autrement, comme la classe abstraite ne stocke pas d'attribut, on pourrait éventuellement utiliser une **interface** à la place :

```java
interface Carte {
    int calculerPoints();

    boolean faitGagnerPartie();
}

class CarteArme implements Carte {
    ...
}
```

Voire :

```java
interface Carte {
    int calculerPoints();

    default boolean faitGagnerPartie() {
        return false;
    }
}
```

<div style="text-align:center">
![Synthèse Diagramme 2]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme2.svg){: width="50%" }
</div>

Bref, avec cette modélisation, les changements dans les diverses cartes (modification de calcul, nouvelles cartes, suppression de cartes, etc) n'impacteront plus la classe `Joueur`: on peut ajouter de nouvelles choses (**ouvert aux extensions**) sans modifier `Joueur` (**fermé aux modifications**).

Certains **designs patterns** aident à respecter le principe ouvert/fermé afin de résoudre des problèmes de conception. Par exemple, le pattern comportemental [décorateur]({{site.baseurl}}/syntheses/synthese_patterns_decorateur) est utilisé pour ajouter dynamiquement de nouveaux **comportements** à un objet.

### Principe de substitution de Liskov (Liskov substitution)
<div id="lsp"></div>

Certains développeurs abusent de l'**héritage** par facilité au lieu d'utiliser d'autres solutions comme la **composition** d'objets. Un "mauvais" héritage est un héritage pour lequel il n'existe pas vraiment de relation de spécialisation entre la superclasse et la sous-classe. La sous-classe ne représente alors pas le même concept que sa classe mère, ce n'est pas réellement une spécialisation.

Tout cela occasionne parfois des problèmes inattendus qui sont mis en lumière par le principe de **substitution de Liskov** qui est fortement liée à la notion de **programmation par contrat**.

Quand on parle de **programmation par contrat** cela signifie que chaque classe possède un ensemble de **règles** (implicites ou explicites) autour de ses **méthodes** : **pré-conditions**, **post-conditions**, **effet de bords**, etc. Globalement, quelqu'un qui utilise une instance d'une **classe** donnée sait à quoi s'attendre quand on appelle telle ou telle méthode. Par exemple, on sait qu'un appel à la méthode `add` sur une instance de `ArrayList` va ajouter l'élément à la fin de la collection.

Le principe de **substitution de Liskov** a été introduit par **Barbara Liskov** et énonce qu'un **objet** d'une superclasse donnée doit pouvoir être remplacée par une de ses **sous-classes** sans "casser" le fonctionnement du programme. Une méthode provenant à l'origine d'une superclasse et appelée sur la sous-classe devrait **respecter le contrat** défini dans la superclasse.

Par exemple, si on étend `ArrayList` pour faire un sous-type de collection spécialisé `MonArrayList` : si on redéfinit la méthode `add` dans `MonArrayList`, à la fin d'un appel à cette méthode, l'élément ajouté doit se trouver à la fin de la collection, comme spécifié dans le contrat de `ArrayList`. Peut-être que le chemin et la manière de faire aura été différente de la classe mère, mais le résultat est le même : un code qui utiliserait une instance de `ArrayList` pourrait être remplacé par `MonArrayList` sans perturbation du programme : les tests unitaires passeraient toujours, par exemple.

L'utilisation inappropriée de l'héritage peut amener au non-respect de ce principe.

Voici un scénario illustrant plus en détail le problème de non-respect du principe de substitution de Liskov : on possède une classe `Ellipse` et on souhaite modéliser une classe `Cercle`.

En géométrie, une **éllipse** est une forme ovale (grossièrement) qui possède une **hauteur** et une **largeur** qui peuvent être **différentes**. Un **cercle** peut être considéré comme une **éllipse** particulière qui a la même **hauteur** et la même **largeur** (cette dimension est appelée **diamètre**). L'aire d'une **éllipse** (et donc d'un **cercle**) est calculé en appliquant la formule `π * hauteur * largeur`.

On pourrait donc faussement penser que la modélisation objet suivante est correcte :

```java
class Ellipse {

    private double hauteur;

    private double largeur;

    public Ellipse(double hauteur, double largeur) {
        this.hauteur = hauteur;
        this.largeur = largeur;
    }

    public void setHauteur(double hauteur) {
        this.hauteur = hauteur;
    }

    public void setLargeur(double largeur) {
        this.largeur = largeur;
    }

    public double getHauteur() {
        return hauteur;
    }

    public double getLargeur() {
        return largeur;
    }

    public double calculerAire() {
        return Math.PI*hauteur*largeur;
    }

}

class Cercle extends Ellipse {

    public Cercle(double diametre) {
        super(diametre, diametre);
    }
}
```

<div style="text-align:center">
![Synthèse Diagramme 3]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme3.svg){: width="30%" }
</div>

Ici, le principe de substituions de Liskov n'est pas violé (c'est normal, nous n'avons pas encore réécrit de méthodes). Cependant, l’implémentation n'est pas valide, car **nous ne respectons pas le contrat** de `Cercle`.

Une partie du **contrat** de la classe `Ellipse` est de pouvoir changer la hauteur et la largeur indépendamment. Alors que pour `Cercle`, son contrat stipule qu'on ne peut pas changer la hauteur et la largeur indépendamment : un cercle doit toujours avoir la même hauteur et la même largeur. En fait, on change son **diamètre**.

On pourrait avoir les tests unitaires suivants :

```java
@Test
public void testerHauteurLargeurEllipse() {
    Ellipse e = new Ellipse(5, 2);
    e.setHauteur(10);
    assertEquals(10, e.getHauteur());
    assertEquals(2, e.getHauteur());
    e.setLargeur(30);
    assertEquals(10, e.getHauteur());
    assertEquals(30, e.getHauteur());
}

@Test
public void testerHauteurLargeurCercle() {
    Cercle c = new Cercle(5);
    c.setHauteur(10);
    assertEquals(10, e.getHauteur());
    assertEquals(10, e.getHauteur());
    c.setLargeur(30);
    assertEquals(30, e.getHauteur());
    assertEquals(30, e.getHauteur());
}
```

Le second test unitaire ne passerait pas.

Pour régler cela, on pourrait envisager la **mauvaise solution suivante** :

```java
class Cercle extends Ellipse {

    public Cercle(double diametre) {
        super(diametre, diametre);
    }

    @Override
    public void setHauteur(double hauteur) {
        super.setHauteur(hauteur);
        super.setLargeur(hauteur);
    }

    @Override
    public void setLargeur(double largeur) {
        super.setLargeur(largeur);
        super.setHauteur(largeur);
    }
}
```

<div style="text-align:center">
![Synthèse Diagramme 4]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme4.svg){: width="30%" }
</div>


Avec cette implémentation, les tests précédents passent, le principe de substitution de Liskov n'est plus respecté ! On a **cassé** le contrat de `Ellipse` dans `Cercle`. `Cercle` est une `Ellipse` et on devrait pouvoir modifier sa hauteur et sa largeur librement ! Ainsi, le test suivant ne passerait pas : 

```java
@Test
public void testerHauteurLargeurEllipseQuiEstUnCercle() {
    Ellipse e = new Cercle(5);
    e.setHauteur(10);
    assertEquals(10, e.getHauteur());
    assertEquals(2, e.getHauteur());
    e.setLargeur(30);
    assertEquals(10, e.getHauteur());
    assertEquals(30, e.getHauteur());
}
```

De plus, si on utilise `Cercle` comme une `Ellipse`, des bugs étranges surviennent quand on utilise une méthode prévue pour un `Ellipse`.

Par exemple :

```java
private void agrandirEllipse(Ellipse e, int facteur) {
    e.setHauteur(e.getHauteur()*facteur);
    e.setLargeur(e.getLargeur()*facteur);
}

@Test
public void testerAgrandirEllipse() {
    Ellipse e = new Ellipse(5, 5);
    agrandirEllipse(e, 2);
    assertEquals(78.53, e.getAire(), 0.001);
}

@Test
public void testerAgrandirCercle() {
    Cercle c = new Cercle(5);
    agrandirEllipse(c, 2);
    assertEquals(78.53, c.getAire(), 0.001);
}
```

Le second test ne passera pas ! Car la largeur et la hauteur sont modifiées simultanément dans `Cercle`.

Bref, On ne peut pas substituer l'ellipse par un cercle sans produire de bugs logiques.

Une autre mauvaise solution possible serait d'ajouter une fonction `setDiametre` dans `Cercle` et de redéfinir les méthodes `setHauteur` et `setLargeur` dans `Cercle` de façon à ce qu'elles ne fassent rien :

```java
class Cercle extends Ellipse {

    public Cercle(double diametre) {
        super(diametre, diametre);
    }

    public void setDiametre(double diametre) {
        super.setHauteur(diametre);
        super.setLargeur(diametre);
    }

    @Override
    public void setHauteur(double hauteur) {

    }

    @Override
    public void setLargeur(double largeur) {

    }
}
```

Mais dans ce cas, on ne peut toujours pas utiliser `Cercle` comme une `Ellipse` (one ne respecte toujours pas `LSP`) et en plus :
* On crée des méthodes qui ne font rien et qui polluent le code.
* On duplique le code de `setHauteur` et `setLargeur` dans `Cercle` dans `setDiametre` !

Bref, cet héritage est une très mauvaise idée ! En fait, conceptuellement, en programmation, un cercle n'est pas une ellipse spécialisée, car les règles pour la hauteur et la largeur sont différentes... Cela peut être un peu dur à accepter.

Si on souhaite quand même utiliser une ellipse dans un cercle (pour ne pas dupliquer le calcul de l'aire ou des autres méthodes, par exemple) on peut éventuellement utiliser une **composition** en interdisant à un `Cercle` de redéfinir sa hauteur et sa largeur :

```java
interface FigureCirculaire {
    double calculerAire();
}

class Ellipse implements FigureCirculaire {

    //Mêmes attributs et méthodes qu'avant

    @Override
    public double calculerAire() {
        return Math.PI*hauteur*largeur;
    }
}

class Cercle implements FigureCirculaire {

    private Ellipse ellipse;

    public Cercle(double diametre) {
        ellipse = new Ellipse(diametre, diametre)
    }

    public void setDiametre(double diametre) {
        ellipse.setHauteur(diametre);
        ellipse.setLargeur(diametre);
    }

    @Override
    public double calculerAire() {
        return ellipse.calculerAire();
    }
    
}
```

<div style="text-align:center">
![Synthèse Diagramme 5]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme5.svg){: width="50%" }
</div>

Avec cette composition, les tests suivant n'ont plus lieu d'être (et ne compilent plus) :

```java
@Test
public void testerHauteurLargeurEllipseQuiEstUnCercle() {
    Ellipse e = new Cercle(5);
    e.setHauteur(10);
    assertEquals(10, e.getHauteur());
    assertEquals(2, e.getHauteur());
    e.setLargeur(30);
    assertEquals(10, e.getHauteur());
    assertEquals(30, e.getHauteur());
}

@Test
public void testerAgrandirCercle() {
    Cercle c = new Cercle(5);
    agrandirEllipse(c, 2);
    assertEquals(78.53, c.getAire(), 0.001);
}
```

C'est normal, car un `Cercle` n'est plus une `Ellipse`. Le principe de substitution de Liskov ainsi que le cotnrat propre à `Cercle` sont respectés !

La **composition forte** entre `Cercle` et `Ellipse` (initialisée dans `Cercle` et n'en sort pas) est en opposition avec la **composition faible**, qui indique aussi une composition, mais dans laquelle la dépendance est injectée (comme avec le pattern [décorateur]({{site.baseurl}}/syntheses/synthese_patterns_decorateur), par exemple).

Bien sûr, nous aurions pu quand même conserver la logique d'agrandissement d'une `FigureCirculaire`. À ce moment-là, il faudrait rajouter une méthode `agrandir(int facteur)` dans l'interface `FigureCirculaire` et implémenter les méthodes dans `Ellipse` et `Cercle`.

**Attention** ce n'est pas nécessairement parce qu'on réécrit une méthode de la classe mère dans une classe fille que le principe de substitution de Liskov est nécessairement violé. Il faut connaître le **contrat** de la classe mère et voir si la version réécrite dans la classe fille brise ce contrat ou non.

Maintenant, voyons un second exemple :

* On a une classe `ReserveDeCarte` qui permet de stocker des objets `Carte`.
* On a une classe `Deck` qui permet de stocker au maximum 32 objets `Carte`.

On pourrait penser qu `Deck` est un sous-type de `ReserveDeCarte`...

L'implémentation suivante ne respecte pas le principe de substitution de Liskov :

```java
class ReserveDeCarte {

    private List<Carte> reserve = new ArrayList();

    public Carte piocher() {
        if(!reserve.empty()) {
            return reserve.remove(0);
        }
        return null;
    }

    public void ajouter(Carte carte) {
        reserve.add(carte);
    }

    public int getNombreCartesReserve() {
        return reserve.size();
    }
}

class Deck extends ReserveDeCarte {

    public Deck() {
        super();
    }

    @Override
    public void ajouter(Carte carte) {
        if(getNombreCartesReserve() == 32) {
            throw new RuntimeException("On ne peut pas ajouter plus de 32 cartes au deck!");
        }
        super.ajouter(carte);
    }

}
```

<div style="text-align:center">
![Synthèse Diagramme 6]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme6.svg){: width="40%" }
</div>

Ici, on ne peut pas substituer un objet `ReserveDeCarte` par un objet `Deck`. Le contrat de la méthode `ajouter` n'est plus respecté (on ne peut plus ajouter autant de cartes qu'on souhaite).

Ici aussi, on pourrait régler cela avec de la composition (par exemple) :

```java
interface ConteneurCarte {
    Carte piocher();
    void ajouter(Carte carte);
    int getNombreCartesReserve();
}

class ReserveDeCarte implements ConteneurCarte {

    private List<Carte> reserve = new ArrayList();

    @Override
    public Carte piocher() {
        if(!reserve.empty()) {
            return reserve.remove(0);
        }
        return null;
    }

    @Override
    public void ajouter(Carte carte) {
        reserve.add(carte);
    }

    @Override
    public int getNombreCartesReserve() {
        return reserve.size();
    }
}

class Deck implements ConteneurCarte {

    private ReserveDeCarte reserve = new ReserveDeCarte();

    public Deck() {
        super();
    }

    @Override
    public Carte piocher(Carte carte) {
        return reserve.piocher();
    }

    @Override
    public void ajouter(Carte carte) {
        if(getNombreCartesReserve() == 32) {
            throw new RuntimeException("On ne peut pas ajouter plus de 32 cartes au deck!");
        }
        reserve.ajouter(carte);
    }

    @Override
    public int getNombreCartesReserve() {
        return reserve.getNombreCartesReserve();
    }

}
```

<div style="text-align:center">
![Synthèse Diagramme 7]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme7.svg){: width="50%" }
</div>

Attention, la composition n'est pas forcément la solution à tous les problèmes de conception. Néanmoins, elle revient souvent au cœur de divers **design patterns** comme **composite** ou bien encore [décorateur]({{site.baseurl}}/syntheses/synthese_patterns_decorateur).

### Principe de ségrégation des interfaces (Interface segregation)
<div id="isp"></div>

Le quatrième principe **SOLID** est le **principe de ségrégation des interfaces**.

Un objet ne doit pas être forcé de dépendre de méthodes qu'il n'utilise pas. Globalement, il ne faut pas qu'une **interface** définisse dans son contrat des méthodes qui ne seront voir ne pourront pas être implémentées par la classe implémentant l'interface.

Nous en avons déjà parlé, mais une interface est un **contrat**. Une classe qui implémente une interface est forcé d'implémenter toutes les méthodes de l'interface. Mais une classe ne devrait pas être forcée à implémenter un bout de contrat qu'elle ne peut pas remplir.

Voyons au travers d'un exemple comment ne pas respecter ce principe peut devenir très fastidieux au fur et à mesure que le projet grossit.

On commence par définir une classe `Exemple` qui possède une méthode `operationGlobale` et une méthode `operationA`. On définit aussi son interface :

```java
interface I_Exemple {
  void operationGlobale();
  void operationA();
}

class A implements I_Exemple {
  public void operationGlobale() {
    //Code...
  }

  public void operationA() {
    //Code...
  }
}
```

Maintenant, on ajoute une classe `B` qui va aussi avoir besoin d'utiliser `operationGlobale` en plus d'une méthode propre à `B` : `operationB`. On ajoute tout cela à l’interface `I_Exemple` : mais il y a un problème : `B` doit aussi implémenter `operationA` et `A` doit implémenter `operationB` : comme il n'y a pas de code adéquat, on lève une exception.

```java
interface I_Exemple {
  void operationGlobale();
  void operationA();
  void operationB();
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
}
```

On peut continuer comme ça et alourdir encore plus le programme :

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

Cela semble pénible, n'est-ce pas ? C'est normal, cette solution est très mauvaise et fastidieuse. À chaque nouvel ajout de classe, avec ses spécificités, on doit modifier tous les autres types et les forcer à implémenter des méthodes qui ne les concernent pas... Le fait de lever tant d'erreurs indique une très mauvaise conception.

Si le développeur avait bien raison de vouloir faire une interface lors de la création de la première classe, il a voulu regrouper trop de chose dans une seule et même interface : la méthode `operationGlobale` commune à toutes les classes et la méthode `operationA` ne cocnernant seulement que `A`. Par la suite, on a continué dans cette mauvaise logique. Il aurait dû dès le départ diviser cela en **deux interfaces** et on aurait dû créer plus d'interfaces à chaque nouveau type de sous-classe ayant ses spécificités. 

On rappelle qu'une **interface** peut hériter d'une autre interface ! Et qu'une classe peut implémenter autant d'interfaces qu'elle le désire.

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

### Principe d'inversion des dépendances (Dependency inversion)
<div id="dip"></div>

Enfin, il reste le **principe d'inversion des dépendances**.

Ce principe dit que :

* Les différentes classes ne doivent pas dépendre d'implémentations concrètes, mais d'abstractions (classes abstraites/interfaces).

* Les abstractions ne doivent pas dépendre des détails (les implémentations, les classes filles) mais les détails (les classes concrètes) doivent dépendre des abstractions. Nous l'avons bien vu avec l'exemple sur les **cartes** et le **joueur** lorsque nous étudions le principe **ouvert/fermé**.

Ce principe permet d'obtenir une très forte **modularité** du programme. Si on couple cela avec la technique **d'injection des dépendances** et des **design patterns créateurs**, tels que des **fabriques abstraites**, ou bien des **conteneurs de dépendances**, on obtient un logiciel dont on peut moduler le fonctionnement sans toucher au code source, simplement en ajoutant de nouvelles classes et/ou en éditant des fichiers de configuration. Les différents **frameworks** mettent en place une architecture favorisant l'inversion des dépendances.

En fait, ce principe découle de la bonne application des autres principes et notamment du principe **ouvert/fermé** et de la **substitution de Liskov**.

Nous verrons aussi qu'il est essentiel de bien respecter ce principe quand on réalise des tests unitaires.

Tout d'abord, illustrons ce principe avec un exemple : on se place dans le contexte d'une application de montage vidéo. Pour l'instant, on ne peut exporter les projets que sous le format `MP4`, ce qui demande un traitement complexe.

```java
class Projet {

  private String nom;

  private Video video;

  public Projet(String nom) {
    this.nom = nom;
    video = new Video();
  }

  public void exporter() {
    //Code complexe et spécifique exportant le projet au format MP4 en utilisant les objets nom et vidéo
  }

}
```

Déjà, cette implémentation n'est pas très bonne au niveau du principe de **responsabilité unique**. On va créer une classe dédiée pour l'export en `MP4` :

```java
class ExportMP4 {

  public void exporterEnMP4(String nom, Video video) {
    //Code complexe et spécifique exportant le projet au format MP4 en utilisant les objets nom et vidéo
    //Utilise les méthodes privées traitementMP4SpecifiqueA et traitementMP4SpecifiqueB 
    //(qui pourraient éventuellement être déléguées à d'autres classes...)
  }

  private void traitementMP4SpecifiqueA(Video video) {
    //...
  }

  private void traitementMP4SpecifiqueB(Video video) {
    //...
  }

}

class Projet {

  private String nom;

  private Video video;

  private ExportMP4 export;

  public Projet(String nom) {
    this.nom = nom;
    video = new Video();
    export = new ExportMp4();
  }

  public void exporter() {
    export.exporterEnMP4(nom, video);
  }

}
```

Maintenant, on aimerait pouvoir exporter des objets au format `MP3` avec cette classe :

```java
class ExportMP3 {

  public void exporterEnMP3(String nom, Video video) {
    //Code complexe et spécifique exportant le projet au format MP3 en utilisant les objets nom et vidéo
    //Utilise la méthode privée traitementAudio
  }

  private void traitementAudio(Video video) {
    //...
  }

}
```

On aimerait pouvoir utiliser au choix `ExportMP3` dans `Projet`. Mais c'est impossible dans l'état actuel, car `Projet`  utilise un objet de type `ExportMP4` et un `ExportMP3` n'est pas un `ExportMP4`.

<div style="text-align:center">
![Synthèse Diagramme 8]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme8.svg){: width="50%" }
</div>

Le problème souligné ici est qu'on a utilisé une **classe concrète** (`ExportMP4`) dans `Projet` à la place d'une **classe abstraite** ou d'une **interface**, ce qui empêche l'utilisation avec d'autres types de classes (ici, `ExportMP3`).

Et il serait **hors de question** de proposer cette solution qui **viole le principe ouvert/fermé** :

```java
class Projet {

  private String nom;

  private Video video;

  private String export;

  public Projet(String nom, String export) {
    this.nom = nom;
    video = new Video();
    this.export = export;
  }

  public void setExport(String export) {
    this.export = export;
  }

  public void exporter() {
    if(export.equals("MP4")) {
      ExportMP4 exportMP4 = new ExportMP4();
      exportMP4.exporterEnMP4(nom, video);
    }
    else if(export.equals("MP3")) {
      ExportMP3 exportMP3 = new ExportMP3();
      exportMP3.exporterEnMP3(nom, video);
    }
  }

}
```

Normalement, avec tout ce que nous avons vu avant, vous devez déjà connaître la solution adéquate. Mais développons ce problème de manière plus théorique :

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

Pour palier à ce problème, on utilise **l'injection de dépendance**. La classe concrète est injectée via le constructeur, au moment de l'instanciation de l'objet, mais la classe ne connaît que le type abstrait. Cela permet une modularité de la classe qui peut alors être utilisée avec n'importe quel service concret dérivé du type abstrait. Et on peut en ajouter dans le futur.

Vous verrez par la suite que **l'injection de dépendances abstraites** est un concept qui revient un peu partout quand on parle de **conception de qualité**, des **principes SOLID** ou de **design patterns**.

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

Pour notre problème initial, après refactoring, on aurait alors :

```java
interface Export {
  void exporterProjet(String nom, Video video);
}

class ExportMP4 implements Export {

  @Override
  public void exporterProjet(String nom, Video video) {
    //...
  }

  private void traitementMP4SpecifiqueA(Video video) {
    //...
  }

  private void traitementMP4SpecifiqueB(Video video) {
    //...
  }

}

class ExportMP3 implements Export {

  @Override
  public void exporterProjet(String nom, Video video) {
    //...
  }

  private void traitementAudio(Video video) {
    //...
  }

}

class Projet {

  private String nom;

  private Video video;

  private Export export;

  public Projet(String nom, Export export) {
    this.nom = nom;
    this.export = export;
    video = new Video();
  }

  public void exporter() {
    export.exporterProjet(nom, video);
  }

  public void setExport(Export export) {
    this.export = export;
  }

}

class Main {

  public static void main(String[] args) {
    Projet p1 = new Projet("Exemple 1", new ExportMP4());
    Projet p2 = new Projet("Exemple 2", new ExportMP3());
    p3.setExport(new ExportMP4());
  }

}
```

<div style="text-align:center">
![Synthèse Diagramme 9]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme9.svg){: width="50%" }
</div>

Cette solution est d'ailleurs un **design pattern comportemental** connu, appelé [stratégie]({{site.baseurl}}/syntheses/synthese_patterns_strategie). Ce pattern permet **d'injecter** un comportement spécifique dans une classe sans en modifier le code source (et éventuellement, le modifier plus tard). Ce pattern s'appuie sur **ouvert/fermé**, **l'inversion des dépendances** et aide à renforcer **responsabilité unique**. C'est exactement ce que vous venez de faire : la méthode d'export du projet est modulable et on peut même en ajouter de nouveaux types d'export dans le futur ! Et tout cela, sans modifier `Projet`.

**L'inversion des dépendances** et plus globalement, le fait qu'une classe **dépende d'abstractions** plutôt que de classes concrètes est aussi très important dans le cadre de la **testabilité** d'un projet.

Prenons l'exemple suivant :

```java
class Produit {

  //Généré par la base de données
  private int id;

  private String nom;

  private double prix;

  public Produit(String nom, double prix) {
    this.nom = nom;
    this.prix = prix;
  }

  //Getters et setters...

}

class ProduitRepository {

  //Classe permettant de communiquer avec la base de données
  private ConnexionBDD connexionBDD;

  public ProduitRepository() {
    connexionBDD = new ConnexionBDD();
  }

  public void enregistrerProduit(Produit produit) {
    //Enregistre réellement le produit dans la base de données
  }

  public List<Produit> recupererProduits() {
    //Récupère tous les produits enregistrés dans la base de données
  }

  public Produit recupererProduit(int id) {
    //Récupère un produit enregistré dans la base de données
  }

  public void modifierProduit(Produit produit) {
    //Modifie un produit enregistré dans la base de données
  }

  public void supprimerProduit(int id) {
    //Supprime un produit enregistré dans la base de données
  }

}

class ServiceFichierLog {

  public void logger(String contenu) {
    //Ecrit le contenu du log dans un fichier
  }

}

class ServiceProduit {

  private ProduitRepository repository;

  private ServiceFichierLog logger;

  public ServiceProduit() {
    repository = new ProduitRepository();
    logger = new ServiceFichierLog();
  }

  public void ajouterUnProduit(String nom, double prix) {
    if(nom.length() < 3) {
      throw new ServiceProduitException("Le nom du produit est trop court.");
    }
    if(nom.length() > 20) {
      throw new ServiceProduitException("Le nom du produit est trop long.");
    }
    if(prix <= 0) {
      throw new ServiceProduitException("Le prix ne peut pas être nul ou négatif.");
    }
    repository.enregistrerProduit(new Produit(nom, prix));
    logger.logger(String.format("Produit %s enregistré, prix : %s", nom, prix));
  }

}
```

<div style="text-align:center">
![Synthèse Diagramme 10]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme10.svg){: width="50%" }
</div>

On pourrait se dire que s'il n'y a pas d'autres sources de données (d'autres bases de données etc) ou d'autres systèmes de logger, ce n'est pas bien grave (ce qui est déjà mal en soi, car cela ne respecte pas le principe ouvert/fermé).

Mais que se passe-t-il si on essaye d'écrire des **tests unitaires** pour la classe `ServiceProduit` ?

```java
@Test
public void testAjouterProduitValide() {
  ServiceProduit service = new ServiceProduit();
  assertDoesNotThrow(() -> service.ajouterUnProduit("Test", 5.0));
}

@Test
public void testAjouterProduitNomTropCourt() {
  ServiceProduit service = new ServiceProduit();
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Te", 5.0));
}

@Test
public void testAjouterProduitNomTropLong() {
  ServiceProduit service = new ServiceProduit();
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Test Test Test Test Test Test Test", 5.0));
}

@Test
public void testAjouterProduitPrixNul() {
  ServiceProduit service = new ServiceProduit();
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Test", 0.0));
}

@Test
public void testAjouterProduitPrixNegatif() {
  ServiceProduit service = new ServiceProduit();
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Test", -5.0));
}
```
Après l’exécution de ces tests... Il y aura quatre produits qui auront été réellement enregistrés dans la base de données ! Et un fichier de log réellement écrit sur le système également !

L'architecture proposée ne respecte pas le principe d'inversion des dépendances, car la classe `ServiceProduit` possède des dépendances vers des classes **concrètes** qui, de plus, ne sont pas injectées.

On se rend compte que cela pose un véritable problème au niveau des **tests unitaire**. Un test **unitaire**, comme son nom l'indique, teste le fonctionnement d'**une classe**, une **unité**. Or, quand on exécute les tests sur `ServiceUtilisateur`, les méthodes des dépendances concrètes utilisées sont aussi appelées ! Ce qui déclenche donc réellement l'enregistrement du produit créé pour les tests dans la base de donnée, et l'écriture de fichiers de log, alors qu'on souhaitait simplement vérifier la méthode `ajouterUnProduit`.

Imaginez-vous dans un contexte plus concret, par exemple, dans un projet web : avec une telle conception, vos tests unitaires déclencheraient l'enregistrement de produits de test sur votre base de données réelle ! Ce n'est pas envisageable.

Les tests unitaires **ne doivent pas dépendre de l'environnement de production**. Ils doivent pouvoir être lancé seulement à partir du code de la classe testée, sans dépendre de rien d'autre.

L'écriture non désirée dans le fichier de log pendant les tests est aussi problématique.

Pour palier à cela, les testeurs mettent en place des **stubs**. Il s'agit de classes **bouchons** qui ne réalisent pas réellement l'action demandée, ou alors pas de manière persistante. Aucun effet de bord est produit.

Plus tard, dans l'année, vous découvrirez les **mocks** qui permettent de créer de "fausses" classes destinées aux tests dont on peut facilement éditer les méthodes.

Bref, réorganisons notre code en respectant le principe d'inversion des dépendances :

```java

interface ProduitRepositoryInterface {
  void enregistrerProduit(Produit produit);
  List<Produit> recupererProduits();
  Produit recupererProduit(int id);
  void modifierProduit(Produit produit);
  void supprimerProduit(int id);
}

class ProduitRepository implements ProduitRepositoryInterface {

  //Classe permettant de communiquer avec la base de données
  private ConnexionBDD connexionBDD;

  public ProduitRepository() {
    connexionBDD = new ConnexionBDD();
  }

  @Override
  public void enregistrerProduit(Produit produit) {
    //Enregistre réellement le produit dans la base de données
  }

  @Override
  public List<Produit> recupererProduits() {
    //Récupère tous les produits enregistrés dans la base de données
  }

  @Override
  public Produit recupererProduit(int id) {
    //Récupère un produit enregistré dans la base de données
  }

  @Override
  public void modifierProduit(Produit produit) {
    //Modifie un produit enregistré dans la base de données
  }

  @Override
  public void supprimerProduit(int id) {
    //Supprime un produit enregistré dans la base de données
  }

}

class FakeProduitRepository implements ProduitRepositoryInterface {

  private static int ID = 0;
  private static Map<Integer, Produit> produits = new HashMap<>();

  @Override
  public void enregistrerProduit(Produit produit) {
    //N'enregistre pas le produit dans la base de données réelle
    ID++;
    produit.setId(ID);
    produits.put(ID, produit);
  }

  @Override
  public List<Produit> recupererProduits() {
    //Ne récupère pas les produits réellement enregistrés dans la base de données
    return produits.values();
  }

  @Override
  public Produit recupererProduit(int id) {
    //Ne récupère pas le produit réellement enregistrés dans la base de données
    return produits.get(id);
  }

  @Override
  public void modifierProduit(Produit produit) {
    //Ne modifie pas réellement le produit enregistré dans la base de données
    produits.put(produit.getId(), produit);
  }

  @Override
  public void supprimerProduit(int id) {
    //Ne supprime pas réellement le produit enregistré dans la base de données
    return produits.remove(id);
  }
}

interface ServiceLogInterface {
  void logger(String contenu);
}

class ServiceFichierLog implements ServiceLogInterface {

  @Override
  public void logger(String contenu) {
    //Ecrit le contenu du log dans un fichier
  }

}

class FakeServiceLog implements ServiceLogInterface {

  private String dernierMessage;

  @Override
  public void logger(String contenu) {
    //N'écrit pas vraiment le contenu du log dans un fichier
    dernierMessage = contenu;
  }

  public String getDernierMessage() {
    return dernierMessage;
  }

}

class ServiceProduit {

  private ProduitRepositoryInterface repository;

  private ServiceLogInterface logger;

  public ServiceProduit(ProduitRepositoryInterface repository, ServiceLogInterface logger) {
    this.repository = repository;
    this.logger = logger;
  }

  public void ajouterUnProduit(String nom, double prix) {
    if(nom.length() < 3) {
      throw new ServiceProduitException("Le nom du produit est trop court.");
    }
    if(nom.length() > 20) {
      throw new ServiceProduitException("Le nom du produit est trop long.");
    }
    if(prix <= 0) {
      throw new ServiceProduitException("Le prix ne peut pas être nul ou négatif.");
    }
    repository.enregistrerProduit(new Produit(nom, prix));
    logger.logger(String.format("Produit %s enregistré, prix : %s", nom, prix));
  }

}
```

<div style="text-align:center">
![Synthèse Diagramme 11]({{site.baseurl}}/assets/syntheses/SOLID/SyntheseDiagramme11.svg){: width="75%" }
</div>

Ici, la classe `FakeProduitRepository` agit comme un **stub** qu'on peut utiliser pour les tests sans risque. Dans un environnement réel, on utiliserait un stockage avec une base de données dédiée aux tests, comme `SQLite`, qu'on viderait ensuite. On a le même système pour `FakeServiceLog`.

Ainsi, dans l'application principale, on aura le code suivant :

```java
class Main {
  public static void main(String[]args) {
    ServiceProduit service = new ServiceProduit(new ProduitRepository(), new ServiceFichierLog());
    //Code utilisant le service...
  }
}
```

Et dans les tests unitaires :

```java
@Test
public void testAjouterProduitValide() {
  ServiceProduit service = new ServiceProduit(new FakeProduitRepository(), new FakeServiceLog());
  assertDoesNotThrow(() -> service.ajouterUnProduit("Test", 5.0));
}

@Test
public void testAjouterProduitNomTropCourt() {
  ServiceProduit service = new ServiceProduit(new FakeProduitRepository(), new FakeServiceLog());
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Te", 5.0));
}

@Test
public void testAjouterProduitNomTropLong() {
  ServiceProduit service = new ServiceProduit(new FakeProduitRepository(), new FakeServiceLog());
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Test Test Test Test Test Test Test", 5.0));
}

@Test
public void testAjouterProduitPrixNul() {
  ServiceProduit service = new ServiceProduit(new FakeProduitRepository(), new FakeServiceLog());
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Test", 0.0));
}

@Test
public void testAjouterProduitPrixNegatif() {
  ServiceProduit service = new ServiceProduit(new FakeProduitRepository(), new FakeServiceLog());
  assertThrows(ServiceProduitException.class, () -> service.ajouterUnProduit("Test", -5.0));
}
```

A priori, `ServiceProduit` aurait pour vocation d'être utilisé dans diverses classes type **contrôleurs**, ou même dans d’autres services. Il serait donc judicieux que ce service soit aussi utilisé au travers d'une **abstraction** (une **interface** dans notre cas) afin qu'on puisse en produire un **stub** ou pour facilement changer le service utilisé si un autre service ou une autre classe en dépend :

```java
interface ServiceProduitInterface {
  void ajouterUnProduit(String nom, double prix);
}

class ServiceProduit implements ServiceProduitInterface {
  //...
}
```

## Conclusion
<div id="conclusion"></div>

Voilà, maintenant, vous savez tout des principes **SOLID** ! Vous êtes donc plus proche d'un ingénieur logiciel qu'un codeur. Il existe un acronyme opposé : les principes **STUPID** qui sont six pratiques qui rendent le code très peu qualitatif, intestable, non évolutif et qu'il faut donc absolument éviter ! Bref, des **mauvaises pratiques** qui sont souvent observées. Vous pouvez consulter de la documentation à ce propos [sur cette page](https://openclassrooms.com/en/courses/5684096-use-mvc-solid-principles-and-design-patterns-in-java/6417836-avoid-stupid-practices-in-programming).

Dorénavant, pour vos futurs projets (ou ceux actuels, comme la SAE) il faut systématiquement vous poser et réfléchir à la conception de votre programme **à long terme**. Il n'est jamais trop tard pour faire du **refactoring**, mais ne pas avoir besoin d'en faire en respectant une certaine qualité logicielle d'entrée de jeu est encore mieux.