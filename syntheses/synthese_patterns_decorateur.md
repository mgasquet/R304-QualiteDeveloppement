---
title: Synthèse de cours - Le pattern décorateur
subtitle:
layout: tutorial
lang: fr
---

## Introduction

Le design pattern **décorateur** est un pattern **structural** qui va permettre d'ajouter d'ajouter de **nouveaux comportements et responsabilités** à un objet, dynamiquement.

Grâce à ce pattern, on va pouvoir ajouter de **nouvelles fonctionnalités** à une classe existante sans avoir besoin d'avoir recours à l'**héritage** ou au **multihéritage** (au niveau du composant visé).

Les **responsabilités** de l'objet décoré peuvent être ajoutées ou retirées dynamiquement lors de l’exécution du programme.

Ce pattern exploite différentes notions que nous avons déjà abordées avec les principes **SOLID** : principe ouvert/fermé, faible couplage, inversion et injection des dépendances, abstraction, composition...

De manière générale, son **diagramme de classes** est le suivant :

<div style="text-align:center">
![Diagramme 1]({{site.baseurl}}/assets/syntheses/decorateur/Diagramme1.svg){: width="60%" }
</div>

* L'interface `ComposantAbstrait` défini les opérations (méthodes) qui seront accessibles et décorables.

* La classe `ComposantConcret` implémente `ComposantAbstrait` est la classe que l'on souhaite décorer : elle peut éventuellement avoir elles-mêmes des sous-classes qui pourront être décorées.

* La classe abstraite `ComposantDecorateur` implémente `ComposantAbstrait` et contient un objet `ComposantAbstrait`. Il va implémenter toutes les méthodes de `ComposantAbstrait` en **déléguant** simplement le travail à son attribut `delegue`, lui-même de type `ComposantAbstrait`.

* Chaque **décorateur concret** hérite de `ComposantDecorateur` et réécrit au choix les opérations qu'il souhaite décorer. Dans le corps des méthodes réécrites, un appel vers l'opération parente est réalisé, afin d'appliquer tous les comportements (celui de base et celui des éventuels autres décorateurs). Ensuite (avant ou après l'appel à la méthode parente), on ajoute de la logique ou un nouveau comportement dans la méthode. Les décorateurs peuvent posséder leurs propres attributs.

* Comme `ComposantDecorateur` contient un `ComposantAbstrait` cela peut être n'importe quel type : un `ComposantConcret` ou un décorateur. Ainsi, on peut **composer** un objet avec les services qu'on désire (par concaténation) lors de l'instanciation. On terminera toujours par un composant concret, non-décorateur. C'est, en quelque sorte, des poupées russes.

```java
interface ComposantAbstrait {
    void operationA();
    void operationB();
}

class ComposantConcret implements ComposantAbstrait {

    @Override
    public void operationA() {
        System.out.println("Comportement operationA de base");
    }

    @Override
    public void operationB() {
        System.out.println("Comportement operationB de base");
    }

}

abstract class ComposantDecorateur implements ComposantAbstrait {

    private ComposantAbstrait delegue;

    public ComposantDecorateur(ComposantAbstrait delegue) {
        this.delegue = delegue;
    }

    @Override
    public void operationA() {
        delegue.operationA();
    }

    @Override
    public void operationB() {
        delegue.operationB();
    }

}

class DecorateurConcretA extends ComposantDecorateur {

    public DecorateurConcretA(ComposantAbstrait delegue) {
        super(delegue);
    }

    @Override
    public void operationA() {
        super.operationA();
        System.out.println("Nouveau comportement pour operationA ajouté par DecorateurConcretA");
    }

}

class DecorateurConcretB extends ComposantDecorateur {

    public DecorateurConcretB(ComposantAbstrait delegue) {
        super(delegue);
    }

    @Override
    public void operationB() {
        super.operationB();
        System.out.println("Nouveau comportement pour operationB ajouté par DecorateurConcretB");
    }

}

class DecorateurConcretC extends ComposantDecorateur {

    public DecorateurConcretC(ComposantAbstrait delegue) {
        super(delegue);
    }

    @Override
    public void operationA() {
        super.operationA();
        System.out.println("Nouveau comportement pour operationA ajouté par DecorateurConcretC");
    }

    @Override
    public void operationB() {
        super.operationB();
        System.out.println("Nouveau comportement pour operationB ajouté par DecorateurConcretC");
    }

}

class Main {
    public static void main(String[] args) {
        ComposantAbstrait obj1 = new DecorateurConcretB(new DecorateurConcretA(new ComposantConcret()));
        ComposantAbstrait obj2 = new DecorateurConcretB(new ComposantConcret());
        ComposantAbstrait obj3 = new ComposantConcret();
        ComposantAbstrait obj4 = new DecorateurConcretB(new DecorateurConcretC(new DecorateurConcretA(new ComposantConcret())));

        /**
         * Affiche :
         * Comportement operationA de base
         * Nouveau comportement pour operationA ajouté par DecorateurConcretA
         * Nouveau comportement pour operationA ajouté par DecorateurConcretC
        */ 
        obj4.operationA();

        /**
         * Affiche :
         * Comportement operationB de base
         * Nouveau comportement pour operationB ajouté par DecorateurConcretC
         * Nouveau comportement pour operationB ajouté par DecorateurConcretB
        */ 
        obj4.operationB();
    }
}
```

## Exemples

Nous allons maintenant voir trois exemples plus concrets pour illustrer le fonctionnement de ce pattern.

### Premier exemple : Salariés avec plusieurs responsabilités

* On possède une classe `Salarie` qui possède un salaire de base.

* On veut pouvoir connaître le **salaire** d'un salarié.

* Un salarié peut avoir diverses responsabilités qui peuvent faire évoluer son salaire :

    * Chef de projet : son salaire est augmenté de 100€ par projet géré.

    * Responsable de stagiaires : son salaire est augmenté de 50€ par stagiaire géré.

Le pattern **décorateur** est donc idéal pour gérer ce système de **responsabilités**. Le composant de base est la classe `Salarie` et les différentes responsabilités (chef de projet, responsable de stagiaires) sont les **décorateurs**. On pourra ainsi facilement ajouter de nouvelles responsabilités dans le futur.

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

class SalarieResponsableStagiaires extends SalarieDecorateur {

  private int nombreStagiairesGeres;

  public ResponsableDeStagiaires(SalarieInterface salarie, int nombreStagiairesGeres) {
    super(salarie);
    this.nombreStagiairesGeres = nombreStagiairesGeres;
  }

  @Override
  public double getSalaire() {
    return super.getSalaire() + 50 * (nombreStagiairesGeres);
  }

}

class Main {
    public static void main(String[]args) {
        SalarieInterface s1 = new Salarie(2000);
        SalarieInterface s2 = new SalarieChefProjet(s1, 3);
        SalarieInterface s3 = new SalarieResponsableStagiaires(s1, 2);
        SalarieInterface s4 = new SalarieChefProjet(new SalarieResponsableStagiaires(s1, 2), 3);

        //Affiche 2000
        System.out.println(s1.getSalaire());

        //Affiche 2300
        System.out.println(s2.getSalaire());

        //Affiche 2100
        System.out.println(s3.getSalaire());

        //Affiche 2400
        System.out.println(s4.getSalaire());
    }
}
```

<div style="text-align:center">
![Open close 3]({{site.baseurl}}/assets/TP3/OCP3.svg){: width="80%" }
</div>

### Deuxième exemple : Styles de textes

Voici le contexte du second exemple :

* On possède une classe `TexteBasique` qui contient une chaîne de caractères (`String`) et qu'on peut afficher.

* On souhaite pouvoir afficher ce texte en italique, en gras ou souligné. Pour cela, on utilisera le format suivant :
    * Texte en gras : `<b>Texte</b>`
    * Texte en italique : `<i>Texte</i>`
    * Texte souligné : `<u>Texte</u>`

* On souhaite pouvoir combiner plusieurs styles d'affichage. Par exemple, un texte en gras souligné, un texte en italique et en gras, etc. Par exemple : `<b><i>Texte</i></b>`, `<u><b>Texte</b></u>`, `<b><u><i>Texte</i></u></b>`, etc.

Ici aussi, le pattern **décorateur** est parfait pour cette tâche : le composant de base est le `TexteBasique` et les **décorateurs** sont les différents styles. On pourra ainsi facilement ajouter de nouveaux styles dans le futur.

```java
interface TexteInterface {
    void afficher();
}

class TexteBasique implements TexteInterface {

    private String texte;

    public TexteBasique(String texte) {
        this.texte = texte;
    }

    @Override
    public void afficher() {
        System.out.print(texte);
    }

}

abstract class TexteDecorateur implements TexteInterface {

    private TexteInterface texteDecore;

    public TexteDecorateur(TexteInterface texteDecore) {
        this.texteDecore = texteDecore;
    }

    @Override
    public void afficher() {
        texteDecore.afficher();
    }

}

class TexteEnGras extends TexteDecorateur {

    public TexteEnGras(TexteInterface texteDecore) {
        super(texteDecore);
    }

    @Override
    public void afficher() {
        System.out.print("<b>");
        super.afficher();
        System.out.print("</b>");
    }

}

class TexteEnItalique extends TexteDecorateur {

    public TexteEnItalique(TexteInterface texteDecore) {
        super(texteDecore);
    }

    @Override
    public void afficher() {
        System.out.print("<i>");
        super.afficher();
        System.out.print("</i>");
    }

}

class TexteSouligne extends TexteDecorateur {

    public TexteSouligne(TexteInterface texteDecore) {
        super(texteDecore);
    }

    @Override
    public void afficher() {
        System.out.print("<u>");
        super.afficher();
        System.out.print("</u>");
    }

}

class Main {
    public static void main(String[] args) {
        TexteInterface t1 = new TexteBasique("Hello");
        TexteInterface t2 = new TexteEnGras(new TexteSouligne(t1));
        TexteInterface t3 = new TexteSouligne(new TexteEnGras(new TexteEnItalique(t1)));

        //Affiche "Hello"
        t1.afficher();

        //Affiche "<b><u>Hello</u></b>"
        t2.afficher();

        //Affiche "<u><b><i>Hello</i></b></u>"
        t3.afficher();
    }
}
```

<div style="text-align:center">
![Diagramme 2]({{site.baseurl}}/assets/syntheses/decorateur/Diagramme2.svg){: width="75%" }
</div>

Bien sûr, comme ici le comportement est assez simple et identique pour chaque balise, on aurait pu *éventuellement* regrouper ces fonctionnalités dans un seul décorateur :

```java
class TexteAvecBalise extends TexteDecorateur {

    private String balise;

    public TexteAvecBalise(TexteInterface texteDecore, String balise) {
        super(texteDecore);
    }

    @Override
    public void afficher() {
        System.out.printf("<%s>", balise);
        super.afficher();
        System.out.printf("</%s>", balise);
    }

}

class Main {
    public static void main(String[] args) {
        TexteInterface t1 = new TexteBasique("Hello");
        TexteInterface t2 = new TexteAvecBalise(new TexteAvecBalise(t1, "u"), "b");
        TexteInterface t3 = new TexteAvecBalise(new TexteAvecBalise(new TexteAvecBalise(t1, "i"), "b"), "u");

        //Affiche "Hello"
        t1.afficher();

        //Affiche "<b><u>Hello</u></b>"
        t2.afficher();

        //Affiche "<u><b><i>Hello</i></b></u>"
        t3.afficher();
    }
}
```

### Troisième exemple : Robots

Pour ce dernier exemple plus complet, nous allons nous placer dans le contexte suivant :

* Une entreprise vend des **robots** dont le prix varie selon la gamme : 1000€ pour les robots entrée de gamme, 5000€ pour les robots milieu de gamme, 10000€ pour les robots haut de gamme.

* Chaque robot effectue une routine quotidienne qu'il débute le matin.

* Pour tous les robots, on peut :

    * Décrire le robot (sa gamme, ses services, etc)
    * Calculer son prix
    * Calculer la durée de sa routine (en minutes)
    * Exécuter sa routine

* Un robot seul ne sert pas à grand-chose... C'est pour cela qu'on peut lui ajouter des **services optionnels** :

    * Fonction **café** : coûte 250€, augmente la durée de la routine quotidienne de 5 minutes, permet au robot de préparer du café lors de sa routine quotidienne. Ce service est également mentionné dans la description du robot.

    * Fonction **ménage** : coûte 500€, augmente la durée de la routine quotidienne de 120 minutes, permet au robot de faire le ménage lors de sa routine quotidienne. Ce service est également mentionné dans la description du robot.

    * Fonction **lessive** : coûte 400€, augmente la durée de la routine quotidienne de 30 minutes, permet au robot de lancer une lessive lors de sa routine quotidienne. Ce service est également mentionné dans la description du robot.

    * **Mise à jour automatique** : service gratuit, augmente la durée de la routine quotidienne de 5 minutes, permet au robot de se mettre à jour avant de commencer sa routine quotidienne. Ce service est également mentionné dans la description du robot.

    * Une **assurance** qui coûte 1000€. Le fait que le robot soit assuré est également mentionné dans la description du robot.

* En plus de cela, certains de ces services sont **premium** et ne doivent pas pouvoir être appliqués à des robots bas de gamme. Les services **premium** sont : la fonction **lessive**, la **mise à jour automatique** et l'**assurance**.

C'est un peu plus complexe que les exemples précédents ! Mais on garde toujours la structure de base du **décorateur**, avec quelques ajouts.

```java
interface RobotInterface {
    void decrire();
    int calculerPrix();
    int calculerDureeRoutine();
    void effectuerRoutine();
}

interface RobotPremiumInterface extends RobotInterface {
    //Rien, c'est normal (on n'ajoute pas de nouvelles opérations...)
}  

abstract class Robot implements RobotInterface {

    private int prixDeBase;

    public Robot(int prixDeBase) {
        this.prixDeBase = prixDeBase;
    }

    @Override
    public int calculerPrix() {
        return prixDeBase;
    }

    @Override
    public int calculerDureeRoutine() {
        return 0;
    }

    @Override
    public void effectuerRoutine() {
        System.out.println("Début de la routine...");
    }

}

class RobotEntreeGamme extends Robot {

    public RobotEntreeGamme() {
        super(1000);
    }

    @Override
    public void decrire() {
        System.out.println("Robot entrée de gamme");
    }

}

class RobotMilieuGamme extends Robot implements RobotPremiumInterface {

    public RobotMilieuGamme() {
        super(5000);
    }

    @Override
    public void decrire() {
        System.out.println("Robot moyenne gamme");
    }

}

class RobotHautGamme extends Robot implements RobotPremiumInterface {

    public RobotHautGamme() {
        super(10000);
    }

    @Override
    public void decrire() {
        System.out.println("Robot haut gamme");
    }

}

abstract class RobotDecorateur implements RobotInterface {

    private RobotInterface robotDecore;

    public RobotDecorateur(RobotInterface robotDecore) {
        this.robotDecore = robotDecore;
    }

    @Override
    public void decrire() {
        robotDecore.decrire();
    }
    
    @Override
    public int calculerPrix() {
        return robotDecore.calculerPrix();
    }

    @Override
    public int calculerDureeRoutine() {
        return robotDecore.calculerDureeRoutine();           
    }

    @Override
    public void effectuerRoutine() {
        robotDecore.effectuerRoutine();
    }
}

abstract class RobotDecorateurPremium extends RobotDecorateur implements RobotPremiumInterface {

    public RobotDecorateurPremium(RobotPremiumInterface robotDecore) {
        super(robotDecore);
    }

}

class RobotAvecFonctionCafe extends RobotDecorateur {

    public RobotAvecFonctionCafe(RobotInterface robotDecore) {
        super(robotDecore);
    }

    @Override
    public void decrire() {
        super.decrire();
        System.out.println("Fonction café activée");
    }
    
    @Override
    public int calculerPrix() {
        return super.calculerPrix() + 250;
    }

    @Override
    public int calculerDureeRoutine() {
        return super.calculerDureeRoutine() + 5;           
    }

    @Override
    public void effectuerRoutine() {
        super.effectuerRoutine();
        System.out.println("Le robot fait le café...");
    }

}

class RobotAvecFonctionMenage extends RobotDecorateur {

    public RobotAvecFonctionMenage(RobotInterface robotDecore) {
        super(robotDecore);
    }

    @Override
    public void decrire() {
        super.decrire();
        System.out.println("Fonction ménage activée");
    }
    
    @Override
    public int calculerPrix() {
        return super.calculerPrix() + 500;
    }

    @Override
    public int calculerDureeRoutine() {
        return super.calculerDureeRoutine() + 120;           
    }

    @Override
    public void effectuerRoutine() {
        super.effectuerRoutine();
        System.out.println("Le robot nettoie la maison...");
    }
}

class RobotAvecFonctionLessive extends RobotDecorateurPremium {

    public RobotAvecFonctionLessive(RobotPremiumInterface robotDecore) {
        super(robotDecore);
    }

    @Override
    public void decrire() {
        super.decrire();
        System.out.println("Fonction lessive activée");
    }
    
    @Override
    public int calculerPrix() {
        return super.calculerPrix() + 400;
    }

    @Override
    public int calculerDureeRoutine() {
        return super.calculerDureeRoutine() + 30;           
    }

    @Override
    public void effectuerRoutine() {
        super.effectuerRoutine();
        System.out.println("Le robot fait la lessive..");
    }
}

class RobotAvecMiseAJourAutomatique extends RobotDecorateurPremium {

    public RobotAvecMiseAJourAutomatique(RobotPremiumInterface robotDecore) {
        super(robotDecore);
    }

    @Override
    public void decrire() {
        super.decrire();
        System.out.println("Mise à jour automatique activée");
    }
    
    @Override
    public int calculerDureeRoutine() {
        return super.calculerDureeRoutine() + 5;           
    }

    @Override
    public void effectuerRoutine() {
        System.out.println("Mise à jour...");
        super.effectuerRoutine();
    }  
}

class RobotAvecAssurance extends RobotDecorateurPremium {

    public RobotAvecAssurance(RobotPremiumInterface robotDecore) {
        super(robotDecore);
    }

    @Override
    public void decrire() {
        super.decrire();
        System.out.println("Robot assuré");
    }
    
    @Override
    public int calculerPrix() {
        return super.calculerPrix() + 1000;
    }
}

class Main {

    public static void main(String[] args) {
        RobotInterface robot1 = new RobotAvecFonctionCafe(new RobotAvecMiseAJourAutomatique(new RobotAvecAssurance(new RobotMilieuGamme())));
        
        //Affiche 6250
        System.out.println(robot1.calculerPrix());

        /**
         * Affiche :
         * Mise à jour...
         * Début de la routine...
         * Le robot fait le café...
         */
        robot1.effectuerRoutine();

        /**
         * Affiche :
         * Robot moyenne gamme
         * Robot assuré
         * Mise à jour automatique activée
         * Fonction café activée
         */
        robot1.decrire();


        //Impossible : l'assurance est un service premium !
        RobotInterface robot2 = new RobotAvecFonctionMenage(new RobotAvecAssurance(new RobotEntreeGamme()));

        /**
         * Impossible : Malgré le fait que RobotHautGamme soit un RobotPremiumInterface, 
         * RobotAvecFonctionMenage est un RobotInterface simple!
         * Et RobotAvecAssurance attend un RobotPremiumInterface...
         * Il faut donc faire attention à l'ordre ici!
        */
        RobotInterface robot3 = new RobotAvecAssurance(new RobotAvecFonctionMenage(new RobotHautGamme()));
    }

}
```

<div style="text-align:center">
![Diagramme 3]({{site.baseurl}}/assets/syntheses/decorateur/Diagramme3.svg){: width="100%" }
</div>