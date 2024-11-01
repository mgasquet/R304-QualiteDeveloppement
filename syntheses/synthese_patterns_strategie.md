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

Nous allons maintenant voir deux exemples plus concrets pour illustrer le fonctionnement de ce pattern.

### Règles d'un jeu de dés


### Chiffrement de messages