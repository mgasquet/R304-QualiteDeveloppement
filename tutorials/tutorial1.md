---
title: TP1 &ndash; Git avancé 1/2
subtitle: Versioning, Historique, Branches, Merging, Conflits
layout: tutorial
lang: fr
---

## Introduction

Dans ce premier TP, vous allez découvrir des fonctionnalités un peu "avancées" du logiciel **git** que vous utilisez déjà.

Au-delà de l'aspect versioning que vous connaissez déjà, git est aussi un outil central dans le cadre de la gestion du développement d'un projet en équipe. En effet, git permet d'intégrer les modifications et ajouts de code provenant de deux commits différents et même de différentes **branches**. Cette activité est appelée **merging** et peut se faire automatiquement ou à la main en cas de **conflits**.

Par exemple, dans un projet, plusieurs personnes vont travailler sur différentes fonctionnalités (par exemple, une **user story** dans un sprint **SCRUM**). À un moment (à la fin du sprint) il y a besoin d'intégrer ces fonctionnalités au produit final. C'est là qu'intervient le **merging**. Dans certains cas, si deux développeurs ont modifié le même fichier et qu'il est difficile d'appliquer les règles de fusion automatique, un **conflit** survient. C'est alors au développeur de prendre la main est de décider du fichier final qui sera conservé (version du fichier 1, version du fichier 2, ou bien, un mix des deux versions).

Comme vous le savez, différentes plateformes permettent de gérer des dépôts distants : **GitHub**, **GitLab**, **Bitbucket**.... En plus de gérer la "mise en cloud" du dépôt que vous connaissez déjà, ces plateformes proposent aussi des services que nous allons explorer durant les 2 TPs. Lors de la prochaine séance, nous parlerons notamment des fonctionnalités **d'intégration et de déploiement continu** qui permettent de tester, construire, publier notre programme de manière automatique et s'assurer que toutes les fonctionnalités s'intègrent bien ensemble.

Lors des deux séances, le fil rouge sera une application **JAVA** (déjà existante mais incomplète) sur laquelle vous travaillerez. D'abord seul et ensuite en collaboration avec d'autres membres de votre groupe. Le but sera alors de versionner son projet et d'y ajouter des nouvelles fonctionnalités. Pendant le premier TP, nous allons utiliser la plateforme **GitLab** du département informatique, puis, lors du second TP, nous étudierons les **workflows** de la plateforme **GitHub** qui permettront de tester et déployer automatiquement cette application (et d'autres !).

## Rappels

Normalement, vous avez appris à vous servir de **git** (et du [**GitLab** de l'IUT](https://gitlabinfo.iutmontp.univ-montp2.fr/)) depuis l'année dernière. Nous allons revenir rapidement sur les notions élémentaires de base sans trop approfondir. Si vous êtes déjà à l'aise avec **git** vous pouvez survoler cette section, mais il peut être intéressant de la lire pour se remettre dans le bain ou si vous n'avez pas touché à git (et GitLab) depuis longtemps ! Quoi qu'il en soit, ces bases doivent déjà globalement être maîtrisées. N'y passez donc pas trop de temps.

En complément, vous pouvez aussi aller consulter le [tutoriel d'introduction à git de première année](https://gitlabinfo.iutmontp.univ-montp2.fr/valicov/tutoGit1ereAnnee). Il existe également des nombreux tutoriels en ligne. Nous vous recommandons le [Git-it-electron](https://github.com/jlord/git-it-electron) qui est à la fois interactif et ludique.

### Identification et clé de sécurité

Pour que vous puissiez versionner vos projets avec le [**GitLab** de l'IUT](https://gitlabinfo.iutmontp.univ-montp2.fr/), il faut que vous soyez identifié grâce à une clé de sécurité (principe de clé de chiffrement publique/privée). Normalement, vous avez déjà réalisé cette étape l'année dernière ou en début de semestre (en cours de Développement Web - PHP), mais au cas où, voici les actions à réaliser :

* Dans un terminal, exécutez la commande suivante :

```bash
ssh-keygen
```

Une **paire de clés** va être générée. Vous pouvez entrer un mot de passe pour sécuriser votre clé (utile, en cas de vol, personne ne pourra l'utiliser...). Vous pouvez également changer le répertoire de destination et le nom du fichier... Mais il est préférable de garder vos clés dans le dossier `.ssh` ciblé.

Il faut partager la clé **publique** à GitLab. Pour cela, copiez la clé dans votre presse-papier avec la commande suivante :

```bash
clip < ~/.ssh/id_rsa.pub
```

À adapter si vous avez changé le nom/la destination de la clé.

Connectez-vous ensuite au [GitLab de l'IUT](https://gitlabinfo.iutmontp.univ-montp2.fr/users/sign_in) en utilisant vos identifiants du département (même chose que pour accéder aux machines).

En haut à gauche, cliquez sur votre image de profil puis `Preférences`. Sur la nouvelle page, cliquez sur `SSH Keys`. Dans la zone `SSH Fingerprints` collez votre clé publique. Donnez lui un titre et sauvegardez-la. Vous êtes prêt à travailler !

### Créer et cloner un dépôt distant

Il y a deux moyens de réaliser le versioning d'un projet : 

* Cloner un dépôt distant (un déjà existant ou bien un fraîchement créé) ce qui permet de récupérer les sources sur une machine. Le projet est alors automatiquement lié au dépôt distant.

* Initialiser le dépôt en local puis le publier sur un nouveau dépôt distant. Par exemple, pour un projet qui existe déjà, mais qui n'a pas encore été versionné.

Nous allons d'abord voir comment faire dans la première situation. Nous allons travailler sur **GitLab**, mais cela fonctionne de la même manière sur toutes les plateformes.

Rendez-vous sur [le GitLab de l'IUT](https://gitlabinfo.iutmontp.univ-montp2.fr). Cliquez sur le bouton `New project` puis `Create blank project`. Pensez à décocher la case proposant d'initialiser le projet avec un fichier **README**, puis créez le projet.

Afin de **cloner** ce projet, récupérez son adresse en cliquant sur le bouton `Clone`. Prenez la première adresse dans le champ `Clone with SSH`.

Sur votre machine, exécutez la commande suivante pour cloner le projet :

```bash
git clone adresse
```

Cette commande fonctionne également pour les projets déjà existants, bien entendu ! D'ailleurs, vous allez récupérer les sources du mini-projet sur lequel nous allons travailler en le clonant.

**Identité du développeur**

```bash
git config --global user.name "nom"
git config --global user.email "adresse"
```

Les différents **commits** réalisés doivent porter des informations sur leur auteur. De plus, les plateformes de gestion de dépôts distants ont besoin de ces informations pour identifier le profil de l'utilisateur (sur le site) ayant effectué un commit.

Ces commandes configurent l'identité du développeur de manière **globale** (pour tous les dépôts). Il est néanmoins possible de définir une identité **locale** (pour un dépôt en particulier) si on se place dans le dépôt concerné et qu'on exécute la commande sans spécifier le paramètre `--global`.

Pour le **Gitlab** du département, précisez votre nom/prénom pour `user.name` et votre adresse mail universitaire pour `user.email`.

### Les quatre commandes essentielles

Quand on travaille sur un projet avec **git**, les trois commandes "basiques" que vous devez absolument maîtriser (depuis l'année dernière) sont : **add**, **commit**, **push** et **pull**.

**Add**

La première commande va vous permettre d'ajouter des fichiers à versionner :

```bash
git add element
```

Par défaut, tous les changements de fichiers ne sont pas automatiquement versionnés par **git**. Avant d'effectuer un **commit**, il faut dire les fichiers qu'on ajoute. Si on précise un dossier, tous ses fichiers (et sous-dossiers) seront ajoutés, récursivement. Donc, si on souhaite ajouter tous les fichiers, il suffit de faire, depuis la racine du **dépôt** :

```bash
git add .
```

En effet, le point "." désigne le dossier courant. Cette commande ajoute donc tous les fichiers du dossier courant (et de ses sous-dossiers). Attention à ne pas inclure de fichiers indésirables (notamment des fichiers cachés n'apparaissant pas dans le navigateur)!

On le rappelle encore, il faut systématiquement ajouter les fichiers qui ont subi des changements (si on souhaite toujours les versionner) avant de réaliser un **commit** (de toute façon, si aucun fichier n'est ajouté, **git** ne vous laissera pas faire de commit).

**Commit**

```bash
git commit -m "Message du commit"
```

Cette commande permet donc de créer un **point d'ancrage** pour versionner l'état actuel de votre code. Une **référence** unique (à votre dépôt) est alors créée. On l'utilise donc comme une commande de sauvegarde.

Le **message** est un élément obligatoire. Il indique ce qui a changé depuis le dernier commit, et s'affichera aussi dans l'historique.

**Push**

Enfin, à tout moment, on peut **pousser** tous les **commits** effectués en local afin de les synchroniser avec le dépôt distant en utilisant la commande :

```bash
git push nom_distant nom_branche
```

Le paramètre `nom_branche` correspond à la **branche** dans laquelle vous vous trouvez. Par défaut, il s'agit de la branche nommée **master** (ou **main** dans certains cas). Nous reviendrons bientôt sur cette notion de branche. Pour l'instant, vous pousserez donc seulement sur la branche **master**.

**Pull**

De l'autre côté, si vous souhaitez récupérer les modifications apportées sur un dépôt distant afin de mettre à jour votre dépôt local (par exemple, si un commit a été poussé par un collègue sur le dépôt distant) il faut utiliser :

```bash
git pull nom_distant nom_branche
```

Cette commande peut générer des **conflits** si la version locale n'est pas compatible avec la version distante. Nous y reviendrons.

### Déplacement vers un commit

Si besoin, vous pouvez revenir à une version précédente de votre projet en vous déplaçant vers un commit spécifique avec :

```bash
git checkout referenceCommit
```

Néanmoins, on préférera se déplacer vers une **branche** ou bien un **tag** avec cette commande plutôt que sur un **commit**. Nous en reparlerons plus tard.

### Ignorer certains éléments

Parfois, dans l'environnement de travail, il y a des éléments (fichiers/dossiers) qu'il n'est pas souhaitable de versionner. Par exemple, les **dépendances** d'un projet (qui sont généralement lourdes et installées de manière externe) ou bien encore, les **fichiers de classes compilées** qui ne font pas partie du code source.

Pour faire en sorte que **git** ne versionne pas certains éléments, il suffit de créer un fichier **.gitignore** à la racine du dépôt. On peut alors lui préciser des chemins de fichiers ou des chemins de dossiers à ignorer (chemin depuis la racine du dépôt). Les chemins des dossiers doivent se terminer par le séparateur **/**. On peut aussi utiliser le symbole **\*** pour filtrer des chaînes de caractères, et par exemple inclure tous les fichiers avec une certaine extension.
Par exemple :

```bash
exemple/a/mon_fichier_inutile.txt
mon_fichier_inutile2.txt
exemple/a/dossier_a_ignorer/
*.class
```
### Créer et publier un dépôt

Au lieu de **cloner** un dépôt distant, on peut aussi en créer un en local puis le publier sur un dépôt distant vierge. Pour cela :

1. On crée le dépôt distant

2. On initialise le dépôt en local avec la commande suivante, exécutée à la racine du projet :

    ```bash
    git init
    ```

3. On associe le dépôt local avec le dépôt distant :

    ```bash
    git remote add origin adresse
    ```

    L'adresse est la même que celle utilisée lorsqu'on clone le dépôt.

4. On réalise un **commit** initial (après un **add**!) :

    ```bash
    git add .
    git commit -m "Initialisation du dépôt"
    ```

5. Et enfin, on fait un **push** vers le dépôt distant :

    ```bash
    git push origin master
    ```

## Prise en main

Le but de cette première section est de prendre en main l'application qui vous est fournie, de la comprendre, et de travailler dessus avec **git**. Pour la plateforme en ligne, nous utiliserons [le GitLab du département informatique](https://gitlabinfo.iutmontp.univ-montp2.fr). Les fonctionnalités présentées à travers **GitLab** sont applicables à d'autres plateformes ! Il suffit de s'adapter au fonctionnement et spécificités de la plateforme (comme quand vous apprenez un nouveau langage de programmation).

### Installation du projet

Afin de récupérer les **sources du projet** vous allez réaliser un **fork**.

Cette action consiste à copier un dépôt dans votre espace de travail, ce qui vous permet alors de travailler sur une version dérivée de l'application sans directement affecter le dépôt d'origine (où vous n'avez le plus souvent pas les droits).

À terme, vous pouvez proposer d'intégrer vos ajouts directement au dépôt principal. Ce mécanisme peut s'avérer utile si un développeur externe au projet veut proposer une amélioration ou bien simplement un **bugfix**. Le(s) propriétaire(s) du dépôt pourront intégrer automatiquement (ou refuser) les changements proposés.

Pour l'instant, vous allez simplement utiliser un **fork** pour créer votre propre version dérivée du projet du TP.

<div class="exercise">

1. Comme vous avez l'habitude depuis le Semestre 2 (Dev-Objets, IHM, Intro Archi), le code source des TPs à faire sur GitLab va résider dans le groupe GitLab correspondant : [https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/). Dans ce groupe normalement, il y a un sous-groupe qui vous est dédié : `etu/votrelogin` (nom + première lettre du nom + éventuellement un chiffre). Ce **namespace** va permettre de regrouper vos projets liés à ce cours au même endroit. Rendez-vous sur [le dépôt du projet](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/editeur-de-texte/) puis réalisez un **fork**. Sur GitLab, il s'agit du bouton en haut à droite du dépôt. Au niveau de **Project URL**, dans le champ **Select a namespace** précisez `qualite-de-developpement-semestre-3/etu/votrelogin` (nom + première lettre du nom + éventuellement un chiffre).

2. Une fois le **fork** achevé, vous obtenez alors un nouveau dépôt dans votre espace personnel. Sur votre machine, **clonez** ce dépôt (en utilisant la bonne commande git).

3. Configurez vos informations sur le dépôt courant (**username** et **email**)

4. Ouvrez le projet avec **IntelliJ IDEA**. Laissez le temps au projet de se configurer.

5. Explorez le code mis à disposition et déduisez le fonctionnement de l'application. N'hésitez pas à demander des explications s'il y a des éléments que vous ne comprenez pas.

</div>

L'application fournie est un mini éditeur de texte en mode lignes de commande. Le programme est capable de recevoir et gérer des commandes et d'exécuter des actions sur le "document texte" que gère l'application.

On a le fonctionnement suivant :

- La classe **Document** contient une chaîne de caractères ainsi que diverses méthodes qui permettent de manipuler cette chaîne de caractères.

- Les classes de "commandes" (comme **CommandeAjouter**) contiennent le document et interagissent avec. Chaque commande possède également un ensemble de paramètres (sous la forme d'un tableau de chaînes de caractères). Quand une commande est exécutée, celle-ci utilise les informations des paramètres pour appeler une action sur le document.  

- La classe **CommandFactory** est une classe qui permet d'instancier une commande à partir d'un nom (et le document ainsi que les paramètres). Cette classe permet donc de faire l'association entre le nom d'une commande tapée par l'utilisateur et la classe correspondante.

- La classe **CommandInvoker** permet simplement d'exécuter une commande. Pour l'instant, cette classe peut vous sembler assez inutile, mais vous l'améliorerez dans le futur (si vous êtes en avance !).

- Enfin, la méthode principale (classe **Main**) va lire les entrées utilisateurs, extraire le nom de la commande et les paramètres. La factory est ensuite appelée pour instancier la commande correspondante et enfin, l'**invoker** l'exécute. On se fixe comme règle que l'utilisateur doit séparer les différents paramètres d'une commande par des **points virgules**.

**Attention**, dans les commandes, le tableau des paramètres est passé tel quel, sans autre traitement. Donc, la première case de ce tableau (index 0) contient le **nom de la commande**. Pour obtenir les paramètres qui intéressent la commande, il faut aller chercher à partir de la seconde case (d'index 1).

Au lancement, le programme contient un document "vide". Après l'exécution d'une commande, la chaîne de caractères est ré-affichée. Pour le moment, une seule commande est disponible, **la commande d'ajout**. Pour l'utiliser, il faut donc écrire (dans la console, une fois le programme lancé) : 

```bash
ajouter;texte à ajouter
```

On peut donc faire, par exemple :

```bash
ajouter;hello
hello
ajouter; world
hello world
```
Vous l'aurez compris, votre objectif sera de doter notre document de **nouvelles fonctionnalités** accessibles au travers de nouvelles commandes.

<div class="exercise">

1. Si ce n'est pas déjà fait, ouvrez un terminal et rendez-vous dans le dossier de l'application que vous avez clonée. Laissez-le ouvert, de côté, afin d'exécuter vos commandes, plus tard.

2. Ajoutez un fichier **.gitignore** permettant d'ignorer le dossier `target/`. Il s'agit de fichiers générés à chaque exécution du projet depuis l'IDE, cela ne doit pas être versionné. Faites aussi en sorte d'ignorer le dossier `.idea/` (fichiers caches relatifs à l'IDE).

3. Ajoutez tous les nouveaux fichiers, afin qu'ils soient disponibles pour le **commit**.

4. Effectuez un **commit** ayant pour message "ajout gitignore".

5. Exécutez la commande **git log** pour observer l'historique des commits, vous devriez en voir deux (celui du dépôt original et le nouveau).

6. Effectuez un petit changement, par exemple, l'ajout d'un fichier **README.md**. Faites en sorte de faire un nouveau commit et observez de nouveau l'historique avec **git log**.

7. Synchronisez vos changements avec le dépôt distant en utilisant **git push**. Au niveau de la page du projet sur **GitLab** vérifiez que les dossiers/fichiers que vous avez spécifiés dans le fichier **.gitignore** ne sont pas versionnés.

</div>

### Ajout de fonctionnalités

Vous allez maintenant ajouter quelques nouvelles commandes à l'application d'édition de texte ! 

Pour le prochain exercice (et pour pouvoir vous montrer quelque chose d'intéressant dans la prochaine section), vous devez effectuer **plusieurs commits** pendant le développement de la fonctionnalité (ne pas avoir un seul commit par fonctionnalité). À vous de voir quand effectuer ces commits.

<div class="exercise">

1. On souhaite ajouter une commande pour **remplacer** une portion du texte par une autre chaîne de caractères. Tout d'abord, commencez par ajouter la méthode suivante dans la classe `Document` :

    ```java
    public void remplacer(int debut, int fin, String remplacement) {
        String partieGauche = texte.substring(0, debut);
        String partieDroite = texte.substring(fin + 1);
        texte = partieGauche + remplacement + partieDroite;
    }
    ```
2. On souhaite donc créer une commande `remplacer` qui s'exécutera ainsi :

    ```bash
    remplacer;debut;fin;chaine
    ```
   
   Cette commande remplace la portion du texte du document située entre l'index `debut` (inclus) et l'index `fin` (inclus) par la chaîne de caractères `chaine` (qui n'est pas obligée d'avoir la même longueur que la zone remplacée).

   Voici un exemple d'exécution utilisant la commande `ajouter` et `remplacer` :

    ```bash
    ajouter;hello world!
    hello world!
    remplacer;0;4;banane
    banane world!
    remplacer;0;2;
    ane world!
    ```

    En vous inspirant de la classe `CommandeAjouter`, créez une classe `CommandeRemplacer`. Attention, les paramètres fournis dans la commande sont de type `String` et vous avez besoin de nombres entiers (`int`). Vous pouvez alors utiliser la méthode de classe `Integer.parseInt(...)` pour convertir une chaîne de caractères en `int`.

    N'oubliez pas de faire plusieurs commits (comme demandé plus haut) pendant le développement de cette fonctionnalité ! Par exemple, vous pouvez en faire trois en laissant un bug volontairement dans le code du premier commit puis le fixer avec le second commit, et enfin ajouter des commentaires ou de la documentation avec le troisième commit.

    Techniquement (comme montré dans l'exemple), le paramètre contenant le texte peut être vide...à vous de gérer cela!

3. Enregistrez cette nouvelle commande dans la méthode **createCommand** de `CommandeFactory`, en vous basant sur l'exemple de la commande `ajouter`.

4. Testez que votre nouvelle commande fonctionne comme attendu.

5. Normalement, vous avez effectué plusieurs `commits`. Poussez vos modifications sur le dépôt distant.
</div>

### Regrouper des commits (et éventuellement réparer ses bêtises !)

Parfois, lors du développement d'une fonctionnalité, il arrive de faire plusieurs commits (et pas juste un seul, quand la fonctionnalité est terminée et fonctionnelle). Cela peut vite alourdir l'historique des commits et le rendre assez peu clair. Néanmoins, c'est une bonne chose de versionner régulièrement son travail ! Il faut juste ne pas le faire de manière excessive (pas un commit après chaque ligne de code !).

Là aussi, git propose une solution : la **réécriture d'historique** aussi appelée **squash de commits**. Cette fonctionnalité permet de sélectionner un ensemble de commits (par exemple, les 5 derniers commits) et de le regrouper en un seul et même commit. Ainsi, quand une fonctionnalité a fini d'être développée, on peut regrouper tous les commits qui ont été réalisés lors du développement de cette partie en un seul commit et ainsi, rendre l'historique plus élégant.

Pour cela, on utilise la commande suivante :

```bash
git rebase -i HEAD~N
```

Ici, `N` doit être remplacé par le nombre de commits à sélectionner (les `N` derniers commits). Si on souhaite sélectionner jusqu'au premier commit du dépôt, on remplace le `HEAD~N` par `--root`. Une fois la commande exécutée, une interface s'affiche, en console ou dans un éditeur de texte, selon votre configuration.

Par exemple :

```bash
pick 2e5d3fd debut ajout chat
pick earc042 chat progression
pick f2ep173 chat fini
pick t2du1z9 ah non en fait, fix du chat...
```

Les commits sélectionnés sont présentés du plus ancien au plus récent. Il suffit alors de remplacer le mot clé `pick` par `s` (pour squash) pour tous les commits qu'on veut **squasher**. Tous les commits libellés par **s** seront alors fusionnés dans le premier commit libellé **pick** au-dessus d'eux. Il faut donc **obligatoirement libeller au moins un commit en pick**. 

Sur nano/vim, on quitte ensuite cette interface en faisant `Echap` puis `:wq` (écrire et quitter). Sur une autre interface type éditeur de texte (par exemple, **gedit**) il suffit de sauvegarder et quitter.

```bash
pick 2e5d3fd debut ajout chat
s earc042 chat progression
s f2ep173 chat fini
s t2du1z9 ah non en fait, fix du chat...
```

Une autre interface s'affiche alors. Elle présente le "nouveau message" du commit qui combine les messages de tous les commits précédents. Vous pouvez alors réécrire un autre message de commit. On quitte cette interface de la même manière que précédemment (`Echap` puis `:wq`).

```bash
#1st commit message
debut ajout chat

#2nd commit message
chat progression

#3rd commit message
chat fini

#4rd commit message
ah non en fait, fix du chat...
```

Peut devenir : 

```bash
#Commit message
Ajout du chat
```

Le **rebasing** s'effectue alors. On peut consulter l'historique pour constater le changement (`git log`).

Depuis cet état, votre dépôt distant va refuser d'intégrer vos changements, car des commits ont disparu... Il ne sait plus où vous en êtes. Vous pouvez alors forcer le changement en utilisant l'option `--force` lors du push. Attention à ne pas abuser de cette option, car il force le dépôt distant à se synchroniser sur votre version et donc, effacer les différences entre son contenu et votre dépôt. Il est donc conseillé d'utiliser cette option seulement dans le cas du rebase, comme nous venons de le voir. De plus, on va plutôt utiliser le **rebase** quasi-exclusivement sous les sous-branches (et jamais le `main`/ `master`) comme nous allons le voir bientôt.

Attention, sur **Gitlab**, la branche **master** est protégée contre le `--force`, par défaut. Pour désactiver cette sécurité : sur la page du dépôt, dans le menu à gauche → **Settings** → **Repository** → **Protected Branches** → **Expand**. Un peu plus bas sont listées toutes les branches protégées. Si on veut annuler cette protection, il suffit d'activer l'option **Allowed to force push**. 

La protection contre le `--force` a du sens dans un projet concret où on ne travaille jamais directement sur **master**, mais sur les sous-branches.

Il est possible de faire plusieurs fusions avec un seul **rebase** en indiquant plusieurs commits en **pick** :

```bash
pick 2e5d3fd debut etape importante 1
s earc042 ok
s f2ep173 fin etape importante 1
pick t2du1z9 debut etape importante 2
s y1fqsf9 ok 2
s uyf8788 fin etape importante 3
```

Il ne restera alors que deux commits (dont on peut changer le message).

<div class="exercise">

1. Regroupez tous les commits ayant servi au développement de la commande `remplacer` en un seul.

2. Observez l'historique des commits.

3. Sur **Gitlab**, désactivez la protection contre le `--force` sur la branche `master` (c'est une mauvaise pratique comme évoqué plus haut, mais pour l'instant, nous n'avons pas le choix, car nous ne travaillons que sur une seule branche.)

4. Poussez sur votre dépôt sur GitLab **en forçant**.

</div>

Maintenant, nous allons ajouter une troisième commande ! Là aussi, effectuez plusieurs commits.

<div class="exercise">

1. On souhaite ajouter une commande pour mettre en **majuscules** une portion du texte. Commencez par définir et compléter le code de la méthode suivante dans `Document` :

    ```java
    public void majuscules(int debut, int fin) {
        //TO-DO!
    }
    ```

    **Astuces** : 
    - Pour extraire une portion d'une chaîne de caractères, servez-vous de la méthode `substring`. Attention, dans cette fonction, le deuxième index (index de fin) est exclus (le caractère se trouvant a cette position n'est pas extrait).
    - Pour passer l'intégralité d'une chaîne de caractères, on utilise la méthode `toUpperCase`.
    - Votre code respecte-t-il le principe [DRY](https://fr.wikipedia.org/wiki/Ne_vous_r%C3%A9p%C3%A9tez_pas) ? Pensez à réutiliser la méthode `remplacer`...

2. On souhaite appeler la commande ainsi :

    ```bash
    majuscules;debut;fin
    ```

    Définissez donc une classe adéquate pour cette `commande` et enregistrez là dans la `factory`.

3. Testez votre commande. Regroupez vos commits puis poussez vos modifications sur votre dépôt **GitLab**.

</div>

L'intitulé de cette section contient **"réparer vos bêtises"** car ce mécanisme permet aussi d'effacer certains commits intermédiaires contenant des informations sensibles, entre autres.

Par exemple, imaginons le scénario suivant :

1. On a créé un **site web PHP** avec une base de données.

2. On ajoute un fichier de configuration pour la base de données, **avec les identifiants de connexion !** (login / mot de passe)

3. On a oublié de mettre ce fichier de configuration dans le `.gitignore` ! Et on a fait des commits qu'on a poussés sur le dépôt distant ! N'importe qui peut donc accéder aux identifiants.

4. On fait un nouveau commit où le fichier est ajouté au .gitignore...on exécute la commande `git rm -r --cached .` pour prendre en compte cet ajout tardif, comme ça, le fichier de configuration ne sera plus versionné par git. Mais c'est trop tard, on peut remonter l'historique des commits et retourner à une version où ce fichier est bien là !

5. Eurêka ! Avec la technique de rebasing, on peut regrouper mon dernier commit "sain" avec le commit précédent. Ainsi, il en résultera un seul commit où ce fichier de configuration n'a jamais été versionné... ! On force le `push`, l'incident est réparé !

### Conventions pour les commits

Jusqu'ici, vous avez écrit des messages de commits comme bon vous semble. En réalité, les messages des commits doivent respecter des **conventions** et un certain **format** :

```bash
git commit -m "<type>[portée (optionnel)]: <description>"
```

On y retrouve :

- Le `type` : la nature des changements apportés lors de ce commit, par exemple :

    - `feat` : un commit qui ajoute une nouvelle fonctionnalité
    - `fix` : un commit qui corrige un bug
    - `refactor` : un commit qui retravaille l'architecture du code (sans affecter les fonctionnalités)
    - `docs` : un commit qui affecte seulement la documentation
    - Et bien d'autres !

- La `portée` : paramètre **optionnel**, donne des informations supplémentaires sur le contexte (par exemple "sprint1").

- La `description` : Une description rapide de ce qui a changé, ce qu'apporte le commit (presque équivalent aux messages de commits que vous avez écrit jusqu'ici).

On peut également rajouter (optionnellement) tout un corps au commit, pour donner plus de détails.

On pourrait avoir, par exemple, le commit suivant :

`refactor: utilisation de l'injection de dépendances`

Plus d'informations sur [cette ressource](https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13).

Bien sûr, si vous faites beaucoup de commits, ce format peut vite devenir lourd ! Vous pouvez donc utiliser l'approche suivante lors du développement d'une fonctionnalité :

- Faire des commits simples pendant le développement.  
- À la fin, regrouper les commits en un seul et appliquer un message respectant les conventions.

### Les branches

Vous pouvez visualiser votre **dépôt** git comme un **arbre**. Une branche est un endroit où on peut effectuer des commits. Au début, cet "arbre" ne possède qu'une seule **branche** (la branche master/main). Sur une branche, à partir de n'importe quel point (un commit, ou même dans un dépôt qui vient d'être initialisé), il est possible de démarrer une **nouvelle branche** à partir de ce point.

La nouvelle **branche** créée est une dérivation de la branche d'où elle a été créée. Par contre, elle évolue différemment. Tous les commits effectués sur cette branche n'affectent pas la branche d'origine.  

Il est alors possible de changer la branche de travail à n'importe quel moment (tant que les derniers changements sur la branche ont été **commit**). On retourne alors dans la version définie par le commit le plus récent de la branche.

À un moment donné, il est alors possible de **fusionner** une branche avec une autre. La branche "receveuse" tente alors d'intégrer les commits de l'autre branche.

Si cette visualisation est encore trop abstraite pour vous, imaginez-vous dans un univers de science-fiction où vous auriez le pouvoir de créer différentes dimensions parallèles à la nôtre et d'y voyager librement ! À terme, si cela est possible, vous aimeriez réunir plusieurs éléments de chaque dimension dans la nôtre ! Mais cela peu parfois occasionner certains soucis... (c'est tout le sujet du comics DC **Crisis on Infinite Earths** où à la fin, cinq terres se retrouvent réunies en une seule).

Dans un dépôt **git** professionnel, vous allez usuellement trouver des **branches permanentes** et des **branches temporaires**.

Par exemple, pour les **branches permanentes** :

- `master` (ou parfois, `main`) : la branche principale dite de `production`. Elle contient une version stable et fonctionnelle du code. Pendant le développement, on ne `commit` jamais directement dessus ! (oups, c'est ce qu'on a fait jusqu'ici... ! Et c'est aussi ce que la plupart d'entre vous font dans leur propre projet, par ailleurs...)

- `development` : la branche dérivée de `master` et utilisée pour le développement. Généralement, on s'en sert pendant la phase de développement pour intégrer peu à peu les différentes branches de fonctionnalités développées pendant le cycle (un **sprint**, par exemple). Cette branche sera alors fusionnée, une fois **stable**, sur `master`.

- `docs` : une branche contenant la documentation... Elle n'est pas vraiment dérivée du code de base, mais peut par exemple servir à stocker un petit site web contenant la documentation de votre projet (générée automatiquement).

Pour les **branches temporaires**, on peut avoir :

- `feature/nom_feature` : branche dérivée de `development` et utilisée pour développer une fonctionnalité `nom_feature`. À terme, cette branche sera fusionnée sur `development`.

- `bugfix/description_bug` : branche dérivée de `development` et utilisée pour réparer un bug (décrit succinctement par `description_bug`).

- `hotfix/description_bug` : similaire à un **bugfix**, mais fait dans l'urgence, car la situation l'exige. Le code n'est pas forcément de qualité, c'est une solution **temporaire**.

- `test/description_test` : branche pour essayer des choses, pour expérimenter.

Ces branches sont temporaires, car elles ne sont plus utiles une fois fusionnées et intégrées, par exemple. Elles seront donc supprimées après la fusion.

On peut aussi ajouter des identifiants : `feature/1/nom_feature`, etc. 

Pour **créer une nouvelle branche** dérivée de la branche sur laquelle vous travaillez actuellement, il suffit d'utiliser la commande suivante :

```bash
git branch nom_branche
```

Ensuite, pour se **déplacer** dans la branche en question (depuis n'importe où) :

```bash
git checkout nom_branche
```

On peut combiner ces deux opérations ainsi afin de créer une branche et d'immédiatement s'y déplacer :

```bash
git checkout -b nom_branche
```

Il y a plusieurs possibilités pour connaître la branche sur laquelle on se trouve actuellement :

   * ```bash
        git rev-parse --abbrev-ref HEAD
     ```
   * ```bash
        git branch --show-current
      ```
   * ```bash
        git branch
      ```
     La commande `git branch` (sans arguments) permet de lister les branches existantes en mettant un `*` à côté de la branche courante.

[//]: # (Mais généralement, votre terminal peut aussi vous l'indiquer à côté du chemin du répertoire courant.)

**Attention**, une fois sur une nouvelle branche, quand vous voudrez réaliser **push**, il faudra bien préciser la branche où vous vous trouvez (et donc pas forcément `master`!) :

```bash
git push origin nom_branche
```

Pour **supprimer une branche** en **local**, on utilise la commande suivante :

```bash
git branch -D nom_branche
```

Pour supprimer une **branche** sur le **dépôt distant** vous pouvez utiliser la commande suivante :

```bash
git push --delete origin nom_branche
```

Enfin, quand on souhaite **fusionner** deux branches, **on se déplace dans la branche receveuse** (celle qui va **intégrer** les changements) et on exécute la commande suivante :

```bash
git merge nom_branche_a_integrer
```

Par exemple, si on se trouve sur la branche `development` et qu'on souhaite intégrer les changements de la branche `feature/chat` :

- On se déplace sur la branche `development` (si on n'y ait pas déjà) :

```bash
git checkout development
```

Et enfin :

```bash
git merge feature/chat
```

Si tout va bien et qu'il n'y a pas de **conflits**, la fusion va s'opérer. Sinon, s'il y a des conflits, il faudra les régler à la main. Dans tous les cas, une fois la fusion finalisée, il ne faut pas oublier de **push** tout ça !

Une fois fusionnée, la branche `feature/chat` n'est plus utile, on peut la supprimer :

```bash
git branch -D feature/chat
```

Lors d'un merge, en cas de conflit (si le **merge** automatique échoue) il faut :

- Ouvrir les fichiers concernés par les conflits. Chacun des fichiers présente des sections avec la source des conflits (les deux versions qui différent). Voici un exemple de fichier contenant un conflit :
    
        ```bash
        <<<<<<< HEAD
        <p>Du texte</p>
        =======
        <p>Autre chose qui n'a rien à avoir</p>
        >>>>>>> 77976da35a11db4580b80ae27e8d65caf5208086
        ```
   
   Ici, on a deux versions différentes de la même ligne. La première version est celle de la branche courante (HEAD) et la seconde est celle de la branche à intégrer. Il faut alors choisir la version qui nous intéresse et supprimer le reste. On peut aussi choisir de garder les deux versions et de les fusionner à la main.
- Éditer ces fichiers pour ne garder que les modifications qui nous intéressent et adapter si besoin.

- Ajouter les fichiers (`git add .`), faire un `commit`, et terminer avec un `push`.

Il est aussi tout à fait possible (si besoin) de resynchroniser une sous-branche dérivée de `development` en faisant un `pull` de la branche `development` depuis la sous-branche (si la branche `development` a évoluée entre temps...).

Ainsi, la sous-branche intégrera les derniers ajouts réalisés sur la branche de développement. Il faut utiliser ce mécanisme seulement si nécessaire, c'est-à-dire si la fonctionnalité doit avoir besoin qu'une autre fonctionnalité soit complétée afin de poursuivre le développement, par exemple.

On peut donc avoir le processus suivant pour mettre en place le développement d'une nouvelle fonctionnalité :

- Créer et se déplacer sur une nouvelle branche à partir de la branche `development`.
- Faire des commits simples pendant le développement de la fonctionnalité.  
- À la fin du développement, regrouper les commits en un seul et appliquer un message respectant les conventions.
- Fusionner la branche sur `development` puis la supprimer.

Et, à la fin du sprint/cycle, fusionner la branche `development` sur `master`.

### Développement

Nous allons mettre en application ce que vous avez appris sur les **branches** et les **commits** pour le développement de l'éditeur de texte.

<div class="exercise">

1. Depuis votre branche `master`, créez et déplacez-vous dans une nouvelle branche nommée `development`.

2. Dans l'éditeur, on souhaite ajouter une commande pour `effacer` une partie du texte (entre deux positions). Depuis `development`, créez et déplacez-vous dans une **nouvelle branche** nommée adéquatement et développez cette fonctionnalité (commencez par ajouter une fonction `efface` dans `Document`, puis créez et enregistrez la commande).

    Vous ferez attention aux **messages de commit** qui doivent respecter les conventions qui vous ont été présentées plus tôt (en tout cas, au moins le "dernier" regroupant tous vos commits, s'il y en a plusieurs).

    Pensez aussi au principe [DRY](https://fr.wikipedia.org/wiki/Ne_vous_r%C3%A9p%C3%A9tez_pas) (la fonction `effacer` de la classe `Document` devrait être toute petite !).

3. Une fois cette fonctionnalité développée, revenez dans votre branche `development`. Fusionnez la branche correspondant à la commande `effacer`. Normalement, il ne devrait pas y avoir de conflits, mais si par malchance, vous en avez créé, pensez à les résoudre. Vous pouvez faire un **push** de la branche `development`.

4. On souhaite ajouter une commande `clear` qui efface tout le texte. Réappliquez le même processus que pour la question précédente (création d'une nouvelle branche, écriture du code correspondant). 

    Cependant, vous **ajouterez un petit bug léger** (qui ne fait pas planter l'application). Par exemple, après avoir effacé le contenu, on ajoute une lettre quelconque dans le texte, ou n'importe quoi. Nous reviendrons sur ce bug plus tard qui nous sera utile lorsque vous travaillerez en équipe.

5. Comme précédemment, revenez dans votre branche `development` et fusionnez avec la branche correspondant à la commande `clear`. Vous pouvez faire un **push** de la branche `development`.

6. Vérifiez que tout fonctionne bien (sans tenir compte du fait que la commande `clear` soit buguée), puis, faites en sorte d'intégrer vos fonctionnalités à la branche principale `master`. N'oubliez pas de push tout ça !

</div>

## Collaborer sur un projet

Jusqu'ici, vous avez travaillé seul, mais le but de **git** est aussi de pouvoir travailler en équipe ! Nous allons voir comment collaborer efficacement et aussi voir ce que **GitLab** propose comme outils, dans ce sens.

### Ouverture et gestion d'une issue

Vous et les autres étudiants de votre groupe ont inséré un mini bug lors de l'exercice précédent. Nous nous plaçons alors dans le contexte où vous découvrez cette application et rencontrez ce bug ! (évidemment, le projet n'a pas de tests unitaires, sinon il aurait été détecté plus tôt !).  

Comment faire pour reporter ce bug au développeur ? GitLab propose simplement une rubrique `Issues` (dans le menu de gauche du dépôt) qui va servir à l'ouverture et la fermeture de **tickets**. Ces **tickets** sont souvent des signalements de bug, mais on peut aussi avoir des suggestions de fonctionnalités, etc. Un autre utilisateur peut même réaliser du code solution et le proposer en résolution du ticket, si le propriétaire du dépôt l'accepte !

Pour la suite des exercices, trouvez-vous un binôme qui est au même point que vous. C'est très important, **vous ne pouvez pas faire le reste du TP seul**. Si l'attente est trop longue, vous pouvez directement passer à la section 4 **"Bonus (pour les plus rapides)"**, en attendant. Éventuellement, vous pouvez essayer de vous débrouiller à 3 si vous mettre en binôme n'est pas possible avec la configuration du groupe.

<div class="exercise">

1. Invitez votre collègue en tant que collaborateur de votre dépôt : **Manage** → **Members** → **Invite Members**. Vous pouvez lui donner le rôle de **Developer**, mais tout autre rôle devrait suffire pour ce qui va suivre.

2. **Clonez** le dépôt d'un collègue qui en est au même point que vous et exécutez son programme pour trouver le bug qu'il a inséré au niveau de la commande `clear`.

3. Sur le dépôt **GitLab** de votre collègue, créez une `issue` et expliquez le bug que vous rencontrez. Une **issue** est en fait un fil de discussion où différentes personnes peuvent intervenir.

4. Lorsque votre collègue a fait de même avec **votre dépôt**, **relevez l'identifiant** (numéro) de l'issue (normalement : `1`) puis retournez dans votre projet et développez un **bugfix** à partir d'une branche dérivée de `development`. Il faudra respecter les conventions citées plus tôt pour les branches. Pour le message final du commit, veillez à bien indiquer dans la description le texte suivant : `Closes #numeroIssue` (en remplaçant `numeroIssue`, bien sûr).

5. Une fois le **bugfix** publié puis ultimement intégré à `master` via la fusion de la branche `development`, retournez voir l'issue sur **GitLab**. Vous constaterez que votre commit a automatiquement été attaché à cette **issue** et qu'elle a même été fermée !

</div>

Ce qui vient de se passer exploite la notion de **patterns** sur **GitLab** qui permet de réaliser des actions annexes en se basant sur les messages de **commit**.

Par exemple, le message de commit `Closes #13, #15` ferme les **issues** 13 et 15. Le message `Related to #5` attache le commit sur l'issue 5 sans la fermer (le commit est alors visible sur la page de l'issue). Il est tout à fait possible de combiner plusieurs messages "patterns" et une description normale : `Description..., Closes #6, Related to #13`.

### Extension d'un projet existant

Quand on fait un **fork**, on crée une copie "dérivée" du projet de base. Même si nous faisons nos propres commits sur ce "nouveau" projet, nous ne pouvons pas pousser les commits sur le projet d'origine sur lequel nous n'avons probablement pas les droits. Cependant, il est possible de demander aux propriétaires du projet d'origine d'intégrer nos changements !

Le fait de faire une demande d'intégration de son code dans le projet d'origine se nomme `merge request` (ou parfois `pull request`) : on demande à ce que le projet "récupère" (pull) notre code / branche. Il va donc en résulter une fusion (`merge`).

<div class="exercise">

1. Encore une fois, rendez-vous dans le dépôt de votre collègue. En haut à droite, appuyez sur le bouton **fork**. Configure le **namespace** pour le placer dans votre sous-groupe `etu/login` puis validez. Un nouveau dépôt "forké" à partir de celui de votre collègue est alors disponible.

2. Clonez ce "nouveau" dépôt sur votre machine : comme ce dépôt forké vous appartient, vous aurez droit de faire des push dessus !

3. Dans l'application récupérée, ajoutez une commande `inserer` qui permet d'insérer une chaîne de caractères après une position donnée. Par exemple :

    ```bash
    ajouter;bonjour monde
    bonjour monde
    inserer;6; le 
    bonjour le monde
    ```

    Il faudra bien respecter le fait d'aller sur la branche de développement puis une branche pour la fonctionnalité, etc. Poussez la branche contenant la fonctionnalité (sans la merger sur `development`).

4. Une fois la fonctionnalité prête et poussée sur GitLab, rendez-vous dans votre dépôt forké puis cliquez sur la rubrique **Code** et **Merge Requests**. Cliquez ensuite sur **New merge request**.

5. Dans la partie gauche de l'interface est présenté votre dépôt. Sélectionnez la branche contenant votre nouvelle fonctionnalité. À droite, il s'agit du dépôt de votre collègue. Sélectionnez la branche de destination (`development`).

6. Cliquez sur **Compare branches and continue**. Dans la nouvelle fenêtre, donnez un **titre** puis une **description** de votre nouvelle fonctionnalité dans les zones prévues à cet effet. Ensuite, cliquez simplement sur **Create merge request**

7. Une fois que votre collègue aura fait la même chose pour vous, rendez-vous dans votre dépôt, également dans la catégorie **Merge Requests**. Vous pouvez alors consulter le détail de la requête. Cliquez sur le bouton **Merge** pour finaliser la fusion puis allez constater le changement, sur la branche `development`. N'oubliez pas de **pull** les modifications, en local !

</div>

Si jamais une `merge request` ne satisfait pas le(s) propriétaire(s) du dépôt, ils peuvent laisser des commentaires et/ou la fermer.

### Travailler en équipe

Dans un projet où il y a plusieurs **collaborateurs** le processus de **merge request** est également utilisé et est même primordial : jusqu'ici, nous avons réalisé nous-même la fusion des sous-branches de type "features" vers la branche `development`. Néanmoins, dans un projet professionnel (avec plusieurs membres), vous n'êtes pas vraiment autorisé à faire cela seul. Vous devez créer une **merge request** en interne et **l'assigner** à un autre membre du projet.

La personne qui a été assignée à la `merge request` est chargée d'examiner le code de celle-ci et de la valider. C'est le moment d'avoir un œil neuf sur votre code. La personne assignée doit notamment vérifier si le code est bien commenté et documenté, s'il respecte les normes de nommage (CamelCase par exemple, ou bien des normes de l'entreprise), l'indentation... Bref, on vérifie d'abord que le code est propre. Il faut aussi vérifier que, a priori, le code fonctionne, ne contient pas de failles de sécurité potentielles, etc. Cela peut aussi être des problèmes relatifs au placement des fichiers, par exemple.

S'il y a des choses à corriger, le membre de l'équipe peut laisser plusieurs commentaires ce qui permet à l'auteur de la fonctionnalité de corriger et de faire une nouvelle merge request.

Dans l'exercice précédent, vous avez collaboré avec un collègue mais celui-ci était "extérieur" au projet. Il est bien sûr tout à fait possible d'intégrer d'autres personnes à un dépôt pour qu'ils aient les mêmes droits que vous. C'est donc ce que nous allons faire dès maintenant !

<div class="exercise">

1. Vous allez maintenant travailler sur le même dépôt. Choisissez un membre du binôme qui jouera le rôle du **propriétaire** (celui qui possède le dépôt) et l'autre du **collaborateur** (celui qui sera invité sur le projet).

2. Pour le **propriétaire** :
    
    * Dans votre dépôt GitLab (pas celui **forké**, celui original), donnez le rôle **Owner** à votre collègue.

    * Ajoutez une **nouvelle fonctionnalité** permettant d'afficher la description de chaque commande. Pour cela, vous allez ajouter une méthode `getDescriptionCommande` (qui renvoie une donnée de type `String`) dans l'interface `Commande` et donc l'implémenter dans toutes les commandes (avec une description simple). Respectez bien le processus que vous avez jusqu'ici : création d'une sous-branche, commits conventionnels, rebasing, etc. Poussez la branche de votre fonctionnalité sur gitlab.
    
    * Une fois terminé, ne fusionnez pas tout de suite la branche de votre fonctionnalité sur `development`.

3. Pour le **collaborateur** :

    * Le projet où vous avez été invité devrait apparaître à [la racine du gitlab du département](https://gitlabinfo.iutmontp.univ-montp2.fr/).

    * Clonez ce dépôt. Vous avez maintenant les droits d'accès et surtout d'écriture.

    * Sur ce dépôt, ajoutez une nouvelle commande `minuscules` similaire à `majuscules`, mais pour les minuscules (on utilise `toLowerCase`). Respectez bien le processus que vous avez jusqu'ici : création d'une sous-branche, commits conventionnels, rebasing, etc. Poussez la branche de votre fonctionnalité sur gitlab.
    
    * Une fois terminé, ne fusionnez pas la branche de votre fonctionnalité sur `development`.

4. Pour chacun des 2 membres du projet (**propriétaire** et **collaborateur**) : depuis **GitLab**, créez une **merge request** proposant de fusionner la branche contenant votre **feature** vers `development`. Cette fois, dans la page où vous devez entrer le titre et la description de la requête, précisez votre collègue au niveau du champ `Assignees` et validez.

5. À partir de [la page principale du site](https://gitlabinfo.iutmontp.univ-montp2.fr/), cliquez sur la catégorie `Merge Requests` puis `Assigned`. Vous pouvez alors visualiser toutes les `merge requests` qui vous ont été assignées.

6. Faites la review de la requête qui vous a été assignée (explorez l'onglet **Commits**, **Changes**) puis validez-la. Votre collègue ayant fait de même avec votre branche, tout devrait être fusionné sur `development` à ce stade ! Bien sûr, si nous avions un peu plus de temps, nous aurions pu refuser la requête, laisser des commentaires, recommencer... ce qui arrive souvent en entreprise (et c'est normal) ! Généralement, les **développeurs seniors** vérifient les `merge requests` des **développeurs juniors** (vous, bientôt). Les **seniors** se vérifient entre eux ou bien sont se considèrent comme assez expérimentés pour se passer de `merge request` et de revue de code... (mais cela est déconseillé).

7. En local, récupérez les mises à jour sur la branche `development` en faisant un **pull**.

8. Jetez un œil à votre code. Bien que le `merge` ait été réalisé avec succès, il ne devrait plus compiler. Pourquoi ? Choisissez un des membres de votre binôme qui devra corriger les erreurs sur une nouvelle branche (à lui de bien la nommer) puis faire une `merge request` en assignant l'autre membre... L'autre membre fait la revue de code et valide la requête.

9. Chaque membre doit bien penser à récupérer toutes les modifications en local avec un `pull`.

</div>

### Gestion des conflits

Jusqu'ici, nous n'avons fait que des **merge** sans conflits bloquants, c'est-à-dire qui pouvaient fusionner automatiquement sans problèmes. Nous allons maintenant simuler un conflit qui devra être résolu manuellement, par le développeur.

<div class="exercise">

1. Reprenez les rôles de l'exercice précédent, vous travaillez toujours sur le même dépôt.

2. Pour le **propriétaire** :

    * Créez une nouvelle branche où vous changez le nom de l'attribut `texte` en `texteDocument` dans la classe `Document`.

    * Créez une `Merge Request` assignée à votre binôme.

    * Ne validez pas tout de suite la merge request que votre binôme vous a affecté une fois qu'il aura terminé.

3. Pour le **collaborateur** :

    * Créez une nouvelle branche où vous changez le nom de l'attribut `texte` en `contentDocument` dans la classe `Document`.

    * Créez une `Merge Request` assignée à votre binôme.

    * Validez la merge request que votre binôme vous a affecté une fois qu'il aura terminé.

4. Maintenant, le propriétaire doit essayer de valider la merge request sur laquelle il est assigné... cela ne marche pas ! Gitlab détecte immédiatement que la fusion ne sera pas possible et affiche un message d'erreur ("Merge blocked") sur la page.

</div>

En effet, comme les deux fonctionnalités développées touchent la même partie du code, il y a un conflit qui ne peut pas être résolu automatiquement. Quand cela arrive, il faut régler le conflit en local sur la branche concernée, pousser les modifications et re-valider la `merge request`.

Pour l'exercice suivant, le membre ayant le rôle de **collaborateur** va principalement agir. Mettez-vous donc sur le même ordinateur (en pair programming) afin que le **proprietaire** puisse également suivre la résoltuion du conflict.

<div class="exercise">

1. En local, le **collaborateur**, toujours sur sa branche dérivée (là où il a codé sa fonctionnalité) doit récupérer la dernière version de la branche `development` :

    ```bash
    git pull origin development
    ```

    Git indique alors qu'il y a un conflit qu'il faut régler.

2. De retour sur l'IDE, vous constatez alors que la classe `Document` (source du conflit) présente les modifications des deux fichiers. Vous pouvez vous servir des outils de l'IDE (clic droit sur `Document`, puis `git` et `Resolve Conflicts`) ou bien agir manuellement afin de produire la version "finale" de ce fichier : accepter les modifications de l'un ou l'autre des fichiers ou bien fusionner les deux quand cela est possible. Pour notre cas, vous ne garderez qu'un seul des noms pour l'attribut (soit `texteDocument` soit `contentDocument`).

3. Une fois le fichier correctement édité, il ne reste plus qu'à faire un `add`, un `commit` et un `push` sur la branche de la fonctionnalité. Le message du `commit` doit indiquer qu'une résolution du conflit a eu lieu.

4. Une fois que les modifications de la branche sont poussés, le **propriétaire** peut finalement valider la `merge request` de son côté ! Faites-le.

5. Pour finir, vous pouvez fusionner la branche `development` dans `master` (en local après avoir récupéré les modifications de la branche `development`, ou bien en ligne avec une merge request).

</div>

## Bonus (pour les plus rapides)

Si vous êtes en avance, imaginiez et codez une fonctionnalité `undo` permettant **d'annuler** la dernière commande exécutée (et donc, revenir à l'état précédent du document). Si vous arrivez à implémenter cette fonctionnalité, vous pouvez aussi implémenter le `redo`, c'est-à-dire **re-exécuter** une action qui a été annulée. En gros, le `CTRL+Z` et le `CTRL+Y`

## Conclusion

Si vous avez bien tout suivi et intégré, vous devez maintenant être beaucoup plus compétent dans la bonne gestion d'un projet git, notamment lorsqu'il s'agit de travailler en équipe. Vous devez maintenant impérativement respecter tout cela dans votre parcours étudiant (dans vos SAÉs et pour vos futurs projets) et vous y serez forcément confronté en entreprise, notamment dans les SSII. Il faut que les notions abordées lors de ce TP deviennent des automatismes.

Dans le prochain TP, nous allons étudier les **workflows** permettant d'automatiser certaines tâches sur la plateforme en ligne, comme le **test**, le **déploiement** et la publication des programmes, à partir du dépôt. Pour cela, nous allons changer de plateforme et utiliser **GitHub**.

Nous avons exploré pas mal de nouvelles commandes de **git** à travers ce premier TP, mais il en existe beaucoup d'autres et certaines très utiles ! Je vous conseille donc de vous informer sur ce sujet, en complément.