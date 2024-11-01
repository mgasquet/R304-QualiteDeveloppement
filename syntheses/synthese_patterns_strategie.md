---
title: Synthèse de cours - Le pattern stratégie
subtitle:
layout: tutorial
lang: fr
---

## Introduction

Le design pattern **stratégie** est un pattern **comportemental** qui va permettre de sélectionner une partie du **comportement** (algorithmes, etc) d'un objet dynamiquement, lors de l’exécution. L'idée est qu'une partie du **comportement** d'un objet soit définit comme **abstrait** (avec une classe abstraite ou une **interface**) ce qui permettra d'**injecter** la classe adéquate (via le constructeur ou un setter) implémentant un comportement précis pour le traitement voulu à un instant donné. Tout cela sans avoir besoin de modifier la classe principale (qui se **sert** du **comportement**), même si de nouveaux comportements sont ajoutés dans le futur.

Ce pattern exploite différentes notions que nous avons déjà abordées avec les principes **SOLID** : principe ouvert/fermé, faible couplage, inversion et injection des dépendances, abstraction, composition...

De manière générale, son **diagramme de classes** est le suivant :

<div style="text-align:center">
![Diagramme 1]({{site.baseurl}}/assets/syntheses/strategie/Diagramme1.svg){: width="50%" }
</div>

```java
interface Strategie {
    void operation();
}

class StrategieConcreteA implements Strategie {

    public void operation() {
        //Traitement A
        System.out.println("Traitement A");
    }
}

class StrategieConcreteB implements Strategie {

    public void operation() {
        //Traitement B
        System.out.println("Traitement B");
    }
}

class Composant {

    private Strategie strategie;

    public Composant(Strategie strategie) {
        this.strategie = strategie;
    }

    public void setStrategie(Strategie strategie) {
        this.strategie = strategie;
    }

    public void traitement() {
        System.out.println("Début du traitement");
        strategie.operation();
        System.out.println("Fin du traitement");
    }

}

class Main {

    public static void main(String[] args) {
        Composant c1 = new Composant(new StrategieConcreteA());

        /**
         * Affiche :
         * Début du traitement
         * Traitement A
         * Fin du traitement
         */ 
        c1.traitement();

        Composant c2 = new Composant(new StrategieConcreteB());

        /**
         * Affiche :
         * Début du traitement
         * Traitement B
         * Fin du traitement
         */ 
        c2.traitement();

        c2.setStrategie(new StrategieConcreteA());

        /**
         * Affiche :
         * Début du traitement
         * Traitement A
         * Fin du traitement
         */ 
        c2.traitement();
    }

}
```

Bien entendu, un composant peut posséder **plusieurs stratégies**. L'utilisation de la méthode d'injection est au choix : constructeur, setter (si on veut pouvoir en changer), etc.

Une **stratégie** n'est bien sûr pas limitée à une seule méthode : on peut définir autant de méthodes que l'on souhaite dans la partie abstraite (interface ou classe abstraite).

Les différentes **stratégies concrètes** peuvent avoir des propriétés et des constructeurs spécifiques.

Le design pattern **Strategie** est assez basique, mais beaucoup d'autres patterns sont des formes dérivées de celui-ci. Dans les patterns concernés, on retrouve souvent une forme d'inversion et d'injection des dépendances. Il y a généralement un élément **abstrait** (interface, classe abstraite) au centre du pattern, des éléments **concrets** qui implémentent le **contrat** définit par cette abstraction et un ou plusieurs composants qui sont seulement dépendants de l'élément abstrait qui, grâce au **polymorphisme**, peut prendre des formes diverses et variées lors de l'exécution du programme.

## Exemples

Nous allons maintenant voir trois exemples plus concrets pour illustrer le fonctionnement de ce pattern.

### Montage vidéo

Pour ce premier exemple, nous allons reprendre le concept d'un programme présenté dans [la synthèse sur les principes SOLID]({{site.baseurl}}/syntheses/synthese_solid#dip), au niveau du principe **d'inversion des dépendances**.

On se place dans le contexte d'une application de montage vidéo dans laquelle on peut exporter des vidéos sous certains formats (`MP4` ou en `MP3`) ce qui demande des traitements spécifiques et complexes.

Il serait **hors de question** de proposer cette solution qui **viole le principe ouvert/fermé** :

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

  private void exporterEnMP4() {
    //Traitement spécifique MP4
  }

  private void exporterEnMP3() {
    //Traitement spécifique MP3
  }

  public void exporter() {
    if(export.equals("MP4")) {
      exporterEnMP4();
    }
    else if(export.equals("MP3")) {
      exporterEnMP3();
    }
  }

}
```

On va alors refactorer cette solution peu qualitative afin d'introduire l'utilisation du pattern **startégie** :

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

Avec cette solution de nouveaux types d'export pourront être ajoutés sans qu'il y ait besoin de modifier la classe `Projet`.

### Taxes

Pour ce deuxième exemple, nous allons nous placer dans un contexte où une plateforme propose à des **entreprises** de faire de réaliser des **transactions en ligne** (c'est-à-dire, mettre en place un système de paiement pour les clients). Chaque fois qu'une transaction est réalisée, la plateforme applique une **taxe** pour récupérer une commission sur la vente.

Il existe deux types de taxes :

* La taxe avec **taux** : un pourcentage est prélevé sur le prix de la transaction.
* La taxe **fixe** : un montant fixe est prélevé sur le prix de la transaction. Si ce montant dépasse le prix de la transaction, on prélève 50% du prix à la place.

On peut facilement exploiter le pattern **stratégie** pour réaliser cette application de manière qualitative :

```java
interface Taxe {
    double calculerTaxe(double prix); 
}

class TaxeTaux implements Taxe {

    private double taux;

    public TaxeTaux(double taux) {
        this.taux = taux;
    }

    public double calculerTaxe(double prix) {
        return prix*taux;
    }

}

class TaxeFixe implements Taxe {

    private double montant;

    public TaxeFixe(double montant) {
        this.montant = montant;
    }

    public double calculerTaxe(double prix) {
        if(montant > prix) {
            return prix*0.5;
        }
        return montant;
    }

}

class Entreprise {

    private Taxe taxe;

    private double chiffreAffaires = 0.0;

    public Entreprise(Taxe taxe) {
        this.taxe = taxe;
    }

    public void setTaxe(Taxe taxe) {
        this.taxe = taxe;
    }

    public void effectuerTransactionEnLigne(double prix) {
        System.out.printf("Transaction de %s€\n", prix);
        double montantTaxe = taxe.calculerTaxe(prix);
        System.out.printf("Taxe de %s€ appliquée\n", montantTaxe);
        double gain = prix - montantTaxe;
        System.out.printf("Gain de %s€\n", gain);
        chiffreAffaires += gain;
        System.out.printf("Chiffre d'affaires : %s€\n", chiffreAffaires);
    }

}

class Main {

    public static void main(String[] args) {
        Taxe taxe1 = new TaxeTaux(0.2);
        Taxe taxe2 = new TaxeFixe(3.0);

        Entreprise e = new Entreprise(taxe1);

        /**
         * Affiche :
         * Transaction de 20.0€
         * Taxe de 4.0€ appliquée
         * Gain de 16.0€
         * Chiffre d'affaires : 16.0€
         */ 
        e.effectuerTransactionEnLigne(20.0);

        e.setTaxe(taxe2);

        /**
         * Affiche :
         * Transaction de 10.0€
         * Taxe de 3.0€ appliquée
         * Gain de 7.0€
         * Chiffre d'affaires : 23.0€
         */ 
        e.effectuerTransactionEnLigne(10.0);

        /**
         * Affiche :
         * Transaction de 2.0€
         * Taxe de 1.0€ appliquée
         * Gain de 1.0€
         * Chiffre d'affaires : 24.0€
         */ 
        e.effectuerTransactionEnLigne(2.0);
    }
}
```

<div style="text-align:center">
![Diagramme 2]({{site.baseurl}}/assets/syntheses/strategie/Diagramme2.svg){: width="70%" }
</div>

Si la méthode de calcul d'une taxe avec taux était plus complexe, on aurait pu opter pour cette conception pour `TaxeFixe` afin d'éviter la duplication de code :

```java
class TaxeFixe implements Taxe {

    private double montant;

    private TaxeTaux taxeTaux = new TaxeTaux(0.5);

    public TaxeFixe(double montant) {
        this.montant = montant;
    }

    public double calculerTaxe(double prix) {
        if(montant > prix) {
            return taxeTaux.calculerTaxe(prix);
        }
        return montant;
    }

}
```

<div style="text-align:center">
![Diagramme 3]({{site.baseurl}}/assets/syntheses/strategie/Diagramme3.svg){: width="70%" }
</div>

### Règles d'un jeu de dés

Pour ce dernier exemple, on se place dans le contexte d'un jeu de dés. Dans ce jeu, deux joueurs lancent tour à tour deux dés.

Il existe diverses variantes de règles applicables à ce jeu :

* La règle **Nordique** :

    * Chaque joueur commence la partie avec 0 points.

    * On fait la somme des valeurs des dés de chaque joueur. Celui qui obtient plus grande valeur gagne le tour.

    * Le joueur qui gagne le tour gagne un nombre de points correspondant à la somme des valeurs de ses dés.

    * Le premier joueur qui obtient cent points gagne la partie.

* La règle **Sudiste** :

    * Chaque joueur commence la partie avec 20 points.

    * On compare la plus grande valeur de dé obtenu par chaque joueur. Celui a la plus grande valeur gagne le tour.

    * Le joueur qui gagne le tour enlève deux points du compteur de points de l'adversaire et augmente son propre compteur d'un point.

    * Le premier joueur qui arrive à 0 points (ou moins) perd la partie (et donc l'autre gagne).

Globalement, dans le jeu, quand il y a **égalité**, on ne fait rien et on passe au prochain tour.

Sans appliquer le pattern **stratégie**, on aurait une solution assez **indigeste**, violant le principe **ouvert/fermé** :

```java
class GestionDes {

    private Random random = new Random();

    private int genererDeAleatoire() {
        return random.nextInt(6) + 1;
    }

    public int[] lancerDes(int nombre) {
        int[] resultat = new int[nombre];
        for(int i=0; i < resultat.length; i++) {
            resultat[i] = genererDeAleatoire();
        }
        return resultat;
    }
}

class Jeu {

    private int[] scores = new int[2];

    private String regle;

    private GestionDes gestionnaire = new GestionDes();

    public Jeu(String regle) {
        if(!regle.equals("Nordique") && !regle.equals("Sudiste")) {
            throw new RuntimeException("La règle n'est pas valide!");
        }
        this.regle = regle;
    }

    private int additionnerValeursDes(int[] resultat) {
        return resultat[0] + resultat[1];
    }

    private int chercherJoueurAvecCentPointsOuPlus() {
        for(int i=0; i < scores.length; i++) {
            if(scores[i] >= 100) {
                return i;
            }
        }
        return -1;
    }

    private int obtenirValeurPlusGrandDe(int[] resultat) {
        return Math.max(resultat[0], resultat[1]);
    }

    private int chercherJoueurAvecZeroPointsOuMoins() {
        for(int i=0; i < scores.length; i++) {
            if(scores[i] <= 0) {
                return i;
            }
        }
        return -1;
    }

    private void jouerTour() {

        int[][] resultats = new int[2][];
        resultats[0] = gestionnaire.lancerDes(2);
        System.out.printf("Résultat joueur 1 : %s\n", Arrays.toString(resultats[0]));
        resultats[1] = gestionnaire.lancerDes(2);
        System.out.printf("Résultat joueur 2 : %s\n", Arrays.toString(resultats[0]));
        int numeroGagnantTour;

        if(regle.equals("Nordique")) {
            int sommeDesJ1 = additionnerValeursDes(resultatJ1);
            int sommeDesJ2 = additionnerValeursDes(resultatJ2);
            if(sommeDesJ1 == sommeDesJ2) {
                numeroGagnantTour = -1;
            }
            else if(sommeDesJ1 > sommeDesJ2) {
                numeroGagnantTour = 0;
            }
            else {
                numeroGagnantTour = 1;
            }
        }
        else if(regle.equals("Sudiste")) {
            int valeurMaxJ1 = obtenirValeurPlusGrandDe(resultatJ1);
            int valeurMaxJ2 = obtenirValeurPlusGrandDe(resultatJ2);
            if(valeurMaxJ1 == valeurMaxJ2) {
                numeroGagnantTour = -1;
            }
            else if(valeurMaxJ1 > valeurMaxJ2) {
                numeroGagnantTour = 0;
            }
            else {
                numeroGagnantTour = 1;
            }   
        }

        if(numeroGagnantTour >= 0) {
            System.out.printf("Le joueur %s remporte le tour!\n", (numeroGagnantTour + 1));
            if(regle.equals("Nordique")) {
               scores[numeroGagnant] += additionnerValeursDes(resultatGagnant);
            }
            else if(regle.equals("Sudiste")) {
                int numeroPerdant = numeroGagnant == 0 ? 1 : 0;
                scores[numeroGagnant] += 1
                scores[numeroPerdant] -= 2;
            }
        }
        else {
            System.out.println("Egalité");
        }
    }

    public void jouer() {
        if(regle.equals("Nordique")) {
               scores[0] = 0;
               scores[1] = 0;
        }
        else if(regle.equals("Sudiste")) {
               scores[0] = 20;
               scores[1] = 20;
        }
        int numeroGagnant = -1;
        int numeroPerdant;
        while(numeroGagnant == - 1) {
            jouerTour();
            if(regle.equals("Nordique")) {
               numeroGagnant = chercherJoueurAvecCentPointsOuPlus();
            }
            else if(regle.equals("Sudiste")) {
               numeroPerdant = chercherJoueurAvecZeroPointsOuMoins();
                if(numeroPerdant != -1) {
                    numeroGagnant = numeroPerdant == 0 ? 1 : 0;
                }
            }
        }
        System.out.printf("Le joueur %s remporte la partie!\n", (numeroGagnant + 1));
    }

}

class Main {

    public static void main(String[] args) {
        Jeu jeu1 = new Jeu("Nordique");
        Jeu jeu2 = new Jeu("Sudiste");
        jeu1.jouer();
        jeu2.jouer();
        Jeu jeu3 = new Jeu("Coucou"); //Exception
    }

}
```

Malgré le fait que cela fonctionne, cela n'est pas une solution acceptable. Imaginez qu'on rajoute d'autres règles !

On peut facilement modéliser ce jeu (et le fait d'utiliser une règle ou l'autre) plus proprement et qualitativement avec le pattern **stratégie** :

```java
interface Regle {

    /**
     * Initialise les scores des deux joueurs en début de partie.
     */
    void initialiserScores(int[] scores);

    /**
     * Renvoie le numéro du gagnant du tour (0 ou 1) ou -1 s'il y a égalité.
     */
    int obtenirNumeroGagnantTour(int[][] resultats);

    /**
     * Met à jour les scores des joueurs
     */
    void mettreAJourScores(int numeroGagnant, int[][] resultats, int[] scores);

    /**
     * Renvoie true si la partie est terminée, false dans le cas contraire
     */
    boolean partieEstTerminee(int[] scores);

    /**
     * Pré-requis : la partie est terminée
     * Renvoie le numéro du gagnant de la partie
     */
    int obtenirNumeroGagnantPartie(int[] scores);
}

class RegleNordique implements Regle {

    private int additionnerValeursDes(int[] resultat) {
        return resultat[0] + resultat[1];
    }

    private int chercherJoueurAvecCentPointsOuPlus(int[] scores) {
        for(int i=0; i < scores.length; i++) {
            if(scores[i] >= 100) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public void initialiserScores(int[] scores) {
        scores[0] = 0;
        scores[1] = 0;
    }

    @Override
    public int obtenirNumeroGagnantTour(int[][] resultats) {
        int sommeDesJ1 = additionnerValeursDes(resultats[0]);
        int sommeDesJ2 = additionnerValeursDes(resultats[1]);
        if(sommeDesJ1 == sommeDesJ2) {
            return -1;
        }
        else if(sommeDesJ1 > sommeDesJ2) {
            return 0;
        }
        else {
            return 1;
        }
    }

    @Override
    public void mettreAJourScores(int numeroGagnant, int[][] resultats, int[] scores) {
        scores[numeroGagnant] += additionnerValeursDes(resultats[numeroGagnant]);
    }

    @Override
    public boolean partieEstTerminee(int[] scores) {
        return chercherJoueurAvecCentPointsOuPlus(scores) != -1;
    }

    @Override
    public int obtenirNumeroGagnantPartie(int[] scores) {
        return chercherJoueurAvecCentPointsOuPlus(scores);
    }
}

class RegleSudiste implements Regle {

    private int obtenirValeurPlusGrandDe(int[] resultat) {
        return Math.max(resultat[0], resultat[1]);
    }

    private int chercherJoueurAvecZeroPointsOuMoins(int[] scores) {
        for(int i=0; i < scores.length; i++) {
            if(scores[i] <= 0) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public void initialiserScores(int[] scores) {
        scores[0] = 20;
        scores[1] = 20;
    }

    @Override
    public int obtenirNumeroGagnantTour(int[][] resultats) {
        int valeurMaxJ1 = obtenirValeurPlusGrandDe(resultats[0]);
        int valeurMaxJ2 = obtenirValeurPlusGrandDe(resultats[1]);
        if(valeurMaxJ1 == valeurMaxJ2) {
            return -1;
        }
        else if(valeurMaxJ1 > valeurMaxJ2) {
            return 0;
        }
        else {
            return 1;
        }
    }

    @Override
    public void mettreAJourScores(int numeroGagnant, int[][] resultats, int[] scores) {
        int numeroPerdant = numeroGagnant == 0 ? 1 : 0;
        scores[numeroGagnant] += 1
        scores[numeroPerdant] -= 2;
    }

    @Override
    public boolean partieEstTerminee(int[] scores) {
        return chercherJoueurAvecZeroPointsOuMoins(scores) != -1;
    }

    @Override
    public int obtenirNumeroGagnantPartie(int[] scores) {
        int numeroPerdant = chercherJoueurAvecZeroPointsOuMoins(scores);
        return numeroPerdant == 0 ? 1 : 0;
    }
}

class GestionDes {

    private Random random = new Random();

    private int genererDeAleatoire() {
        return random.nextInt(6) + 1;
    }

    public int[] lancerDes(int nombre) {
        int[] resultat = new int[nombre];
        for(int i=0; i < resultat.length; i++) {
            resultat[i] = genererDeAleatoire();
        }
        return resultat;
    }
}

class Jeu {

    private int[] scores = new int[2];

    private Regle regle;

    private GestionDes gestionnaire = new GestionDes();

    public Jeu(Regle regle) {
        this.regle = regle;
    }

    private void jouerTour() {
        int[][] resultats = new int[2][];
        resultats[0] = gestionnaire.lancerDes(2);
        System.out.printf("Résultat joueur 1 : %s\n", Arrays.toString(resultats[0]));
        resultats[1] = gestionnaire.lancerDes(2);
        System.out.printf("Résultat joueur 2 : %s\n", Arrays.toString(resultats[0]));
        int numeroGagnantTour = regle.obtenirNumeroGagnantTour(resultats);
        if(numeroGagnantTour >= 0) {
            System.out.printf("Le joueur %s remporte le tour!\n", (numeroGagnantTour + 1));
            regle.mettreAJourScores(numeroGagnant, resultats, scores);
        }
        else {
            System.out.println("Egalité");
        }
    }

    public void jouer() {
        regle.initialiserScores(scores);
        while(!regle.partieEstTerminee(scores)) {
            jouerTour();
        }
        int gagnant = regle.obtenirNumeroGagnantPartie(scores);
        System.out.printf("Le joueur %s remporte la partie!\n", (gagnant + 1));
    }

}

class Main {

    public static void main(String[] args) {
        RegleNordique regleNordique = new RegleNordique();
        RegleSudiste regleSudiste = new RegleSudiste();
        Jeu jeu1 = new Jeu(regleNordique);
        Jeu jeu2 = new Jeu(regleSudiste);
        jeu1.jouer();
        jeu2.jouer();
    }

}
```

<div style="text-align:center">
![Diagramme 4]({{site.baseurl}}/assets/syntheses/strategie/Diagramme4.svg){: width="80%" }
</div>

A l'avenir, on pourra alors ajouter de nouvelles **règles** (ou modifier celles existantes) sans modifier la classe `Jeu`.

C'est mieux, non ? De plus, le fait de ne pas pouvoir spécifier de règles inexistantes est naturellement géré.

On pourrait aussi envisager d'avoirs des règles différentes :

* Pour savoir qui gagne le tour
* Pour le calcul des scores, qui savoir qui gagne la partie, etc.

Ce qui donnerait alors lieu à deux types (abstrait) de stratégies différentes !
