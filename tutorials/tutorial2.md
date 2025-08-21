---
title: TP2 &ndash; Git avancé 2/2
subtitle: Gitlab CI/CD, Tests automatisés, Intégration et déploiement continu
layout: tutorial
lang: fr
---

Dans ce second (et dernier) TP portant sur **git**, nous allons étudier les outils de **CI/CD** (continuous integration/continuous delivery) proposés par GitLab. Globalement, il s'agit d'automatiser différentes tâches qui seraient fastidieuses (et chronophages) de faire "à la main" comme le fait de tester l'intégration de différents modules de code, la construction et la mise à disposition de l'exécutable de l'application, le déploiement d'un site web en production, etc.

La plupart de ces outils sont aussi disponibles sur les autres plateformes comme **GitHub**, **Bitbucket**, etc (avec leurs propres spécificités).

## Découverte de GitLab CI/CD et des pipelines

**GitLab** propose un outil appelé **GitLab CI/CD** (pour **continuous integration/continuous delivery**) disponible dans chaque repository qui permet notamment de détecter quand un événement survient sur un dépôt (par exemple, un **push** sur une branche spécifique...) et de déclencher automatiquement des **scripts** (appelés **jobs**) sur différents **conteneurs dockers** (machines virtuelles) contenant le code du projet. Tous ces **jobs** sont regroupés dans diverses étapes (appelées **stages**) et s'exécutent de manière ordonnée ou parallèle à travers un **pipeline**.

Les **jobs** vont donc vous permettre de charger votre projet sur un système **Linux** virtuel pré-configuré de votre choix (par exemple, un conteneur qui contient java et Maven) et de réaliser des actions dessus (compilation, tests, publication d'un exécutable, et bien d'autres)...

Nous le verrons par la suite, il est possible de conditionner le déclenchement des jobs. Quand un événement survient sur le repository (push, création de tag, etc) le pipeline exécute tous les jobs concernés. On peut suivre la progression des tâches en direct et, en cas d'échec (par exemple, un test ne passe pas, le programme ne compile pas...) **GitLab** prévient en ligne qu'il y a eu des erreurs, avec les détails (il est possible de consulter les logs de la machine virtuelle exécutant chaque job).

Avec ce système, **GitLab** pourrait détecter automatiquement s'il y a des soucis quand, par exemple, deux branches sont **fusionnées** avec succès, mais que le code ne compile plus, ou ne passe pas les tests.

Au-delà de ça, les **jobs** peuvent aussi servir à automatiser certaines tâches comme le déploiement d'un site web (ou autre), la mise en ligne de la documentation, etc.

Les événements qui peuvent déclencher les workflows sont nombreux, on peut en retrouver la liste complète [ici](https://docs.github.com/en/actions/using-workflows/events-that-trigger-workflows).

### Le fichier .gitlab-ci.yml

Le pipeline (et les différents **jobs**) d'un repository est défini au travers d'un fichier `.gitlab-ci.yml` (au format `YAML`) qui se place à la racine du dépôt.

Voici l'allure générale d'un tel fichier et des options courantes qu'on peut utiliser :

```yml
stages:
  - stage1
  - stage2

job1:
  stage: stage1
  image: nom_image_docker
  script:
    - ...
    - ...
  artifacts:
    paths:
      - ...
  dependencies:
    - ...
  rules:
    - if: ...

job2:
  stage: stage1
  image: nom_image_docker
  ...

job3:
  stage: stage2
  image: nom_image_docker
  ...
  rules:
    - if: '$CI_COMMIT_BRANCH == $CI_DEFAULT_BRANCH'   
```

Comme vous pouvez le constater, le fichier de configuration du **pipeline** commence par définir des **stages**. Les différents **stages** s'exécutent **dans l'ordre**, les uns après les autres. Un **job** est lié à un **stage**. Tous les **jobs** d'un stage s'exécutent en **parallèle**. Dans l'exemple ci-dessus, il y a deux stages et trois jobs. Les deux premiers jobs sont liés au `stage1` et s'exécutent donc en parallèle. Le troisième job appartient au `stage2` et ne s'exécutera que quand `stage1` sera terminé, donc quand `job1` et `job2` seront terminés. Si un job d'un stage échoue, le stage suivant ne sera pas réalisé.

Revenons maintenant sur la configuration d'un `job` et intéressons-nous à ses options (certaines sont obligatoires, d'autres non) :

* `stage` (optionnel, mais très fortement recommandé) : définit dans quel stage s'exécute le job. Si on ne met rien, il est placé dans un stage par défaut.

* `image` (quasiment obligatoire tout le temps) : spécifie quelle est l'image docker utilisée par ce job. Il existe énormément d'images, on doit cibler en fonction des besoins du job. Par exemple, si on doit tester un programme `java` (qui tourne sur la version 21), on peut utiliser l'image `maven:3.9.5-eclipse-temurin-21` qui contient java 21 et Maven. On peut éventuellement spécifier une image par défaut qui sera utilisée par chaque job (dans des conteneurs différents), mais de manière générale, on spécifie par job. Si on ne précise rien, une image par défaut sera utilisée.

* `script` (obligatoire) : c'est la partie la plus importante. Il s'agit d'une liste de commandes (comme si vous étiez dans un terminal) qui vont s'exécuter dans la machine virtuelle. Lorsque le job démarre et que le conteneur est initialisé, les sources du projet sont chargées et vous vous trouvez directement à sa racine. Vous pouvez donc directement interagir avec le projet. Si toutes les commandes s'exécutent sans problème, le job réussi, sinon il échoue.

* `artifacts` (optionnel) : lorsque qu'un job démarre, il est isolé dans un conteneur et contient seulement le code du projet. Tous les fichiers potentiellement créés par d'autres jobs ne sont donc pas accessibles par défaut. Cependant, il arrive parfois qu'un job ait besoin de fichiers créés lors d'un job/stage précédent pour s'exécuter. La directive `artifacts` permet de spécifier quels fichiers seront sauvegardés et transmis aux jobs d'un prochain **stage**. Attention toutefois, les jobs d'un même stage s'exécutent en parallèle et ne peuvent donc pas se transmettre de fichier de cette manière (par défaut, mais c'est éventuellement possible avec une configuration avancée). Ce sont donc seulement les jobs des stages suivants qui auront accès aux fichiers sauvegardés par les stages précédents. On peut également se servir de cette directive pour sauvegarder et exposer des fichiers importants lors de la publication de **releases** (nous y reviendrons plus tard). On pourrait donc traduire le terme **artifacts** par "fichiers exportés" (depuis un job).

* `dependencies` (optionnel) : permet d'indiquer que ce job a besoin des artifacts (fichiers exportés) d'un certain `job` (d'un stage précédent). Cela n'est pas obligatoire de la préciser si le job correspondant intervient dans le stage qui suit celui qui a créé les `artifacts` (les artifacts seront transmis automatiquement).

* `rules` (optionnel) : permet de spécifier des conditions pour que le job se déclenche. Par exemple, `job3` ne se déclenche qu'en cas de `push` sur la branche par défaut du repository (`main` ou `master` par exemple). Si rien n'est spécifié (comme pour `job1` et `job2`) le job s'exécute lors de chaque événement (par exemple, en cas de push sur n'importe quelle branche, la création d'un tag, etc). On peut aller dans le détail et écrire des conditions complexes, et même des conditions pour spécifier quand le job ne s'exécute pas, etc. Dans l'exemple de `job3` on aurait aussi pu spécifier une branche spécifique (par exemple `'$CI_COMMIT_BRANCH == development'`) ou bien `$CI_COMMIT_BRANCH` pour n'autoriser le job à s'exécuter seulement si on a un push de commits (pas de création de tags ou autre). On notera qu'un `merge` d'une branche résultera en un `push` à un moment donné, dans la branche qui intègre les changements de la branche fusionnée.

Il existe beaucoup d'autres options que nous n'aborderons pas dans ce TP, mais que vus pouvez retrouver [ici](https://docs.gitlab.com/ci/yaml/#keywords).

Aussi, diverses variables prédéfinies sont fournies par `GitLab` et accessibles dans tous les **jobs**. Ces variables permettent de récupérer et exploiter des informations sur l'événement ayant déclenché le pipeline (message de commit, nom du tag, nom de la branche, etc). Par exemple `$CI_COMMIT_BRANCH` contient le nom de la branche sur laquelle est effectué le push, `$CI_DEFAULT_BRANCH` contient le nom de la branche par défaut (main, master) ou autre, etc. Ces variables sont préfixées d'un `$`. On peut retrouver la liste des variables prédéfinies sur [cette page](https://docs.gitlab.com/ci/variables/predefined_variables/#predefined-variables).

### Exemple

Voici un exemple un peu plus concret :

```yml
stages:
  - test
  - deploy

test:
  stage: test
  image: php:8.4
  script:
    - php -r "copy('https://getcomposer.org/installer', 'composer-setup.php');" && \
      php -r "if (hash_file('sha384', 'composer-setup.php') === 'dac665fdc30fdd8ec78b38b9800061b4150413ff2e3b6f88543c636f7cd84f6db9189d43a81e5503cda447da73c7e5b6') { echo 'Installer verified'; } else { echo 'Installer corrupt'; unlink('composer-setup.php'); } echo PHP_EOL;" && \
      php composer-setup.php && \
      php -r "unlink('composer-setup.php');" && \
      mv composer.phar /usr/local/bin/composer
    - composer install
    - echo "Lancement des tests unitaires"
    - php -d xdebug.mode=coverage ./vendor/bin/phpunit

deploy:
  stage: deploy
  image: alpine:latest
  script:
    - rm -rf .git
    - rm .gitlab-ci.yml
    - commande pour uploader les fichier vers un serveur (ftp par exemple...)
    - connexion ssh au serveur pour exécuter divers commandes de déploiement...
  rules:
    - if: '$CI_COMMIT_BRANCH == $CI_DEFAULT_BRANCH'
```

Ce pipeline contient deux stages qui contiennent chacun un job. Comme il n'y a qu'un job par stage, on préfère nommer chaque job comme le stage dans lequel il intervient (mais c'est n'est pas obligatoire, bien entendu).

Le premier job `test` :
  * S'exécute sur l'image `php:8.4` (machine virtuelle qui contient la version 8.4 de php).
  * S'exécute dans tous les cas (pas de conditions).
  * Installe le logiciel `composer` puis installe les dépendances du projet.
  * Un message est affiché en console puis les tests unitaires sont exécutés.

Le deuxième job `deploy` :
  * S'exécute seulement si un push est réalisé sur la branche par défaut (principale) du repository.
  * S'exécute après le stage `test` donc après le job du même nom.
  * Ne s'exécute pas si le job `test` échoue.
  * S'exécute sur l'image `alpine:latest` (machine virtuelle simple).
  * Supprime divers fichiers non utiles au déploiement
  * Exécute une commande pour uploader les fichiers du projet vers un repository distant...
  * Se connecte en ssh à un serveur pour exécuter diverses commandes supplémentaires de déploiement...

### Premiers pas

Vous allez maintenant créer votre premier pipeline (très simple) sur le projet d'**éditeur de texte** du TP précédent. Normalement, vous aviez travaillé à deux sur le même projet à la fin de ce TP, donc techniquement, un des deux membres du binôme à un projet plus avancé. Ici, vous travaillerez seul sur votre propre projet, mais ce n'est pas grave s'il manque les dernières fonctionnalités des exercices réalisés en binôme (si c'est le cas et que cela vous gêne vraiment, vous pouvez faire un fork du repository de votre collègue...).

<div class="exercise">

1. En local, ouvrez **votre** projet d'**éditeur de texte** puis placez-vous sur la branche `development` et assurez-vous d'être à jour avec le dépôt distant (`git pull origin`).

2. À la racine du dépôt, créez un fichier `.gitlab-ci.yml`.

3. À l'aide de ce fichier, créez le pipeline qui exécute un stage nommé `hello` qui contient un seul job (du nom que vous voulez) qui s'exécute sur l'image `alpine:latest` et affiche un message (de votre choix) en console. Ce job doit seulement s'exécuter sur la branche `development`.

4. Créez un commit pour ajouter ce fichier puis poussez-le sur le dépôt distant.

5. Rendez-vous sur la page de votre projet sur GitLab [https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/editeur-de-texte/etu/votrelogin/editeur-de-texte](https://gitlabinfo.iutmontp.univ-montp2.fr/qualite-de-developpement-semestre-3/editeur-de-texte/etu/votrelogin/editeur-de-texte) puis, à gauche, dans le menu `Build` → `Pipelines`.

6. Dans ce nouveau menu, vous devriez voir votre pipeline en train de s'exécuter (soit en cours, soit terminée selon votre vitesse et les performances du serveur). Si le pipeline a échoué c'est que vous vous êtres trompés à un endroit, il faudra alors corriger et recommencer (nouveau commit, nouveau push). Si tout est bon (en attente ou terminé), cliquez sur le status du pipeline pour ouvrir une nouvelle fenêtre.

7. Dans la nouvelle fenêtre, vous pouvez observer chaque job du pipeline (un seul dans votre cas). Cliquez sur votre job afin d'ouvrir les logs de la machine virtuelle, et vérifiez que votre message s'affiche bien à la fin de l'exécution.

8. En local, créez et déplacez-vous vers une nouvelle branche `test_rapide` depuis la branche `development`. Ajoutez ensuite un fichier bidon (par exemple, un fichier texte vide) puis faites un commit et poussez la nouvelle branche. Rendez-vous dans le menu des pipelines et observez que (normalement) rien ne se produit. Si toutefois un pipeline s'exécute quand même, cela signifie que vous n'avez pas bien rédigé la condition de déclenchement sur le job de votre pipeline ! Si tel est le cas, revenez sur `development`, supprimez `test_rapide`, corrigez, poussez le fichier de configuration et recommencez.

9. Revenez sur la branche `development` puis supprimez la branche `test_rapide` (en local et à distance).

</div>

## Automatisation des tests sur Gitlab

Vous allez maintenant améliorer votre pipeline afin de lui permettre de vérifier que votre programme **compile** bien puis pour qu'elle exécute les **tests unitaires** sur votre application. Mais tout d'abord... il vous faut des tests unitaires ! (comment, vous n'avez pas écrit de tests unitaires depuis le début?!)

<div class="exercise">

1. Si ce n'est pas déjà fait, placez-vous dans votre branche `development`.

2. Créez le dossier de tests `src/test/java` (il n'existe pas encore, parce que vous n'avez écrit aucun test). Pour le créer, depuis IntelliJ le plus simple est de cliquer droit sur le répertoire `src` → **New** → **Directory** → Choisissez `test/java`. Par convention, la couleur verte indique qu'il s'agit du répertoire contenant le code source des tests.

3. Créez un paquetage `fr.iut.editeur.document` dans `src/test/` puis, à l'intérieur, créez la classe `DocumentTest`. Remarquez, qu'en fait, vous n'avez pas vraiment créé ce paquetage... puisqu'il existe déjà ! Seule l'arborescence des répertoires a été créée dans `src/test/`. En effet, le paquetage est le même que celui de la classe `Document` (dans `src/main/java`). C'est normal, car une convention répandue dit que les tests unitaires doivent être écrits dans le même paquetage que les classes qu'ils testent.

4. Écrire quelques méthodes pour tester les méthodes de la classe `Document`. Si vous ne vous rappelez plus comment faire, jetez un œil à vos cours de *Dev-Objets* de l'an dernier ! Voici un squelette de cette classe :

  ```java
  package fr.iut.editeur.document;

  import org.junit.jupiter.api.Test;

  import static org.junit.jupiter.api.Assertions.*;

  public class DocumentTest {

      @Test
      public void testMethode() {
          assertXXX(...)
      }

  }
  ```

5. Pour exécuter les tests, **IntelliJ** vous permet de le faire simplement, en cliquant sur le bouton de lancement, à côté de la déclaration de la classe.

</div>

Maintenant que vous avez des tests unitaires prêts et fonctionnels, nous allons faire en sorte que **GitLab** vérifie que votre programme compile bien puis exécute les tests après n'importe quelle mise à jour sur le repository.

Dans votre **pipeline**, vous allez diviser le travail deux **stages** et deux **jobs** :

1. Un premier stage (associé à un job) qui teste la compilation.

2. Un deuxième stage (associé à un autre job, s'exécutant après le stage de compilation) qui lance les tests unitaires.

Pour cela, vous aurez besoin des ressources suivantes :

* L'image `maven:3.9.5-eclipse-temurin-21` qui permet d'avoir un environnement avec java (21) et Maven (pour avoir la commande `mvn`).

* La commande `mvn compile` (qui permet de compiler un projet) et la commande `mvn test` (exécution de tests unitaires).

Cela peut sembler lourd de séparer cela en deux stages/jobs, mais cela nous permet de former un enchaînement logique bien divisé : si nous avions tout regroupé dans un seul job, en cas d'échec, il aurait été plus difficile de dire ce qui ne va pas (compilation, tests, les deux ?). Ici, on a l'information immédiatement grâce aux noms des stages/jobs. De plus, avec cette organisation, si le stage de compilation ne passe pas, le stage des tests unitaires n'est pas réalisé.

<div class="exercise">

1. Dans votre fichier `.gitlab-ci.yml`, supprimez ce que vous aviez fait lors de l'exercice précédent puis définissez les deux stages et les deux jobs demandés. Pour rappel, ils doivent s'exécuter dans tous les cas, donc il n'y a pas de conditions à préciser. Le premier job teste la compilation, le deuxième lance les tests unitaires.

2. Faites un `commit` et un `push` sur votre branche `development`. Sur `GitLab`, rendez-vous sur votre dépôt et retournez dans l'onglet des pipelines. Vous devriez voir votre pipeline en cours d'exécution. Cliquez sur son statut pour ouvrir les détails puis inspectez chaque `job`. Normalement, tout devrait passer.

3. Maintenant, faites en sorte de modifier légèrement votre code pour qu'il ne compile plus. Faites un commit et un push puis vérifiez que le premier job de votre pipeline échoue bien et que le second n'est pas exécuté. Remettez votre code en ordre.

4. Pour finir, modifiez légèrement la classe `Document` pour qu'un ou plusieurs tests ne passent plus. Attention, le programme doit compiler ! Faites un commit et un push puis vérifiez que le premier job de votre pipeline passe, mais pas le second. Enfin, remettez tout en ordre.

</div>

## Automatisation des releases

### Releases et tags

**GitLab** permet de publier des **releases** de notre application, c'est-à-dire publier une version fonctionnelle du logiciel dans un espace de notre dépôt en ligne, avec les exécutables et les ressources nécessaires.

Sur **git** il est possible d'associer un **commit** à un **tag**. Un **tag** est une étiquette nommée. Généralement, on associe une `release` à un **tag**. Il est aussi possible de faire un `checkout` directement sur un tag !

Par convention, les tags s'utilisent donc pour indiquer la version d'un programme sous la forme `vX.Y.Z`. Ainsi, par exemple `v0.0.1`, `v1.0.0`, etc. `X` désigne les mises à jour majeures (le logiciel change quasi-complétement), `Y` les mises à jour intermédiaires (ajout de nouvelles fonctionnalités, par exemple après un sprint) et `Z` les mises à jour mineures (fixes de bugs par exemple).

Pour créer un **tag**, on utilise simplement la commande :

```bash
git tag vX.Y.Z
```

Cela aura pour effet d'associer le dernier commit à ce **tag**. Pour indiquer au dépôt distant que le tag a été créé, il faut le **pousser**. Par exemple :

```bash
git push origin v0.0.1
```

Pour **supprimer** un tag en local, on utilise l'option `-d` avec la commande `tag` :

```bash
git tag -d vX.Y.Z
```

Et pour le supprimer sur le dépôt distant :

```bash
git push -d origin v0.0.1
```

### Release automatique de l'application d'édition de texte

Nous allons faire en sorte que, dès qu'un **tag** est **push** sur le dépôt distant, le code de l'application soit **build** en un exécutable java `.jar` et qu'une **release** contenant notre exécutable soit publiée. Ainsi, dès qu'une nouvelle version est prête, il suffit de créer un **tag** et **GitLab** se charge alors du reste.

Dans une **release**, il est possible d'inclure des liens vers des fichiers. Par défaut, le code source de l'application est mis à disposition. Dans notre cas, nous allons seulement ajouter un lien de téléchargement vers l'exécutable `.jar` de l'application, mais dans l'absolu, il est tout à fait possible d'inclure d'autres fichiers.

Nous allons répartir le travail en deux stages/jobs :

1. Premier **job** : construire l'exécutable de l'application et l'exporter pour le prochain stage :
  * Le script lance la construction de l'exécutable grâce à une commande `maven`, tout en précisant la version de l'application (qu'on obtient grâce au nom du **tag**).
  * Il déplace ensuite l'exécutable produit dans le dossier courant.
  * Enfin, on utilise le système d'**artifacts** pour exporter le fichier `jar` vers le prochain stage.

2. Deuxième **job** : publier une **release** contenant l'exécutable :
  * On utilise le système d'artifacts pour exporter encore une fois le fichier `jar` (qu'on a reçu du précédent stage/job) de manière définitive (pour qu'il ne soit pas supprimé à l'issue de l'exécution du pipeline).
  * On utilise la directive `release` (que nous allons bientôt voir) pour publier la release en y attachant le lien pointant sur l'artifact correspondant à notre exécutable `.jar`.

Pour pouvoir mettre tout cela en place, nous allons avoir besoin de nous attarder sur différentes options qu'il est possible de définir dans les `jobs` :

```yml
stages:
  - exemple1

exemple1:
  stage: exemple1
  image: ...
  variables:
    NOM_VAR_1: valeur
    NOM_VAR_2: bis_$NOM_VAR_1 #contient bis_valeur
  script:
    - commande1 $NOM_VAR_1
    - commande2 $NOM_VAR_2
    - etc...
  artifacts:
    paths:
      - "chemin/fichier1.xxx"
      - "chemin/fichier2.xxx"
      - "chemin/dossier1/"
    expire_in: ...
  rules:
    - if: '$CI_COMMIT_TAG'
```

Expliquons tout cela :

* La section `variables` permet de définir des variables accessibles dans le job. La variable est ensuite utilisable sous le nom `$NOM_VAR_1` (et on peut l'utiliser n'importe où dans le job). Cela nous sera utile par la suite pour stocker le nom de la version (sans le `v`) ou bien le nom complet de l'exécutable `jar` (que nous allons utiliser plusieurs fois).

* Dans la section `paths` de `artifacts`, on précise les chemins (relatifs ou absolu) des fichiers ou dossiers que l'on souhaite exporter (à noter que l'ajout d'un dossier est récursif). Enfin, on peut préciser une durée de vie de ces fichiers avec la section `expires_in`. Si on ne précise pas d'unité de temps, cela sera en secondes, sinon on peut spécifier par exemple `secs`, `mins`, `hrs` (abréviations de secondes minutes et heures, mais il y a plein d'autres formats acceptés). Par exemple, on peut spécifier `10 mins`. On peut également préciser `never` pour garder ces fichiers exportés pour toujours.

* Enfin, la condition `if: '$CI_COMMIT_TAG'` permet de faire en sorte que le job ne s'exécuter que si un tag est poussé sur le dépôt distant.

Nous allons procéder par étape et vous allez d'abord commencer par implémenter le job de `build` sans la release. Nous pourrons ainsi voir si l'exécutable est bien produit et exporté. Voici ce dont vous aurez besoin :

* Pour ce job (et ce stage) nous allons utiliser encore une fois l'image `maven:3.9.5-eclipse-temurin-21`.

* La variable prédéfinie `$CI_COMMIT_TAG` permet d'obtenir le nom du tag poussé sur le dépôt.

* Il est judicieux de définir deux variables pour ce job :
  * Une variable contenant la **version** correspondant au tag sans le `v`. Pour cela, on peut utiliser la syntaxe `${CI_COMMIT_TAG#v}` pour enlever le `v`.
  * Une variable contenant le **nom de l'exécutable** : `EditeurDeTexte-$VERSION.jar` (où `$VERSION` correspondant au nom de la variable contenant la version...).
  * Donc, par exemple, si le tag poussé est `v1.0.2`, on obtient les variables `1.0.2` et `EditeurDeTexte-1.0.2.jar`.

* On peut utiliser les variables partout dans le job (commande du `script`, dans le `path` des `artifacts`, etc).

* Pour le **script**, on peut utiliser trois commandes :

  * `mvn versions:set -DnewVersion=X.Y.Z -DgenerateBackupPoms=false` qui permet de définir la version de l'exécutable `jar` produit (en remplaçant `X.Y.Z` par cette version, bien entendu).

  * `mvn package` pour produire l'exécutable dans le dossier `target/NomExecutable-X.Y.Z.jar`.

  * `mv target/NomExecutable-X.Y.Z.jar ./` pour déplacer le `.jar` dans le dossier courant (plus facile pour la suite) en remplaçant par le nom adéquat, bien entendu.

* Concernant les `artifacts`, on exporte seulement le `.jar` qui se trouve dans le dossier courant (donc, dans `paths`, on peut simplement mettre le nom du jar vu qu'il se trouve dans le dossier courant). On peut alors mettre une expiration d'une heure (pour être large). Ce fichier ne sera pas conservé, il a pour but d'être utilisé par le job de **release** que nous développerons par la suite.

Allez, il est temps de mettre en application !

<div class="exercise">

1. Dans votre fichier `.gitlab-ci.yml`, ajoutez un nouveau **stage** `build` à la suite et un **job** associé (avec le même nom) qui :
  * Produit le `jar` de l'application avec le bon libellé de version.
  * L'exporte comme `artifact` avec une durée de vie d'une heure.
  * S'exécute seulement quand un **tag** est poussé.

2. Faites un `commit` et un `push` sur votre branche `development`. Sur `GitLab`, rendez-vous sur votre dépôt et retournez dans l'onglet des pipelines. Normalement, les deux premiers jobs doivent bien s'exécuter, mais pas le dernier (car se déclenche seulement quand on pousse un `tag`).

3. Créez un **tag** nommé `v1.0.0` puis, poussez-le sur le dépôt distant.

4. Sur la page de gestion des pipelines, observez le déroulement des jobs, et vérifiez que le job `build` s'exécute bien à la fin. À l'issue de l'exécution, rendez-vous dans le menu accessible via le panneau latéral gauche `Build`→ `Artifacts` et vérifiez que votre fichier `.jar` est bien accessible en déroulant les fichiers associés au job `build`. Vérifiez également que son nom est correct (`EditeurDeTexte-1.0.0.jar`).

5. S'il y a une erreur quelque part, vous devrez bien penser à pousser vos modifications sur le dépôt distant puis à créer et pousser un nouveau tag pour re-tester (ou supprimer celui-ci en local et à distance puis le pousser de nouveau). La version en suffixe de l'exécutable `jar` doit correspondre au tag.

</div>

Tout fonctionne jusqu'ici ? Parfait ! Il ne nous reste donc plus qu'une dernière étape : faire en sorte que notre pipeline exporte de manière définitive l'exécutable, créé une release et y attache le lien de téléchargement du fichier.

Voyons comment faire cela :

```yml
stages:
  - build
  - release

#job qui build et exporte l'exécutable dans un artifact
build:
  ...

release:
  stage: release
  image: registry.gitlab.com/gitlab-org/release-cli:latest
  dependencies:
    - build
  artifacts:
    paths:
      - "chemin/fichier1.xxx"
      - "chemin/fichier2.xxx"
    expire_in: never
  script:
    - echo "Publication de la release X.Y.Z..."
  release:
    name: 'Release X.Y.Z'
    description: "Version X.Y.Z de l'application"
    tag_name: '$CI_COMMIT_TAG$'
    ref: '$CI_COMMIT_TAG'
    assets:
      links:
        - name: "fichier1.xxx"
          url: "$CI_JOB_URL/artifacts/raw/fichier1.xxx"
        - name: "fichier2.xxx"
          url: "$CI_JOB_URL/artifacts/raw/fichier2.xxx"
  rules:
    - if: '$CI_COMMIT_TAG'
```

Attardons-nous sur tout cela :

* Afin de publier une release, on utilise l'image `registry.gitlab.com/gitlab-org/release-cli:latest` pour faciliter les choses.

* La section `dependencies` indique le `job` dont on souhaite récupérer les artifacts.

* On réutilise encore la section `artifacts` pour exporter les fichiers qu'on souhaite mettre à disposition dans notre release. Cette-fois, on indique `never` comme date d'expiration (car on souhaite conserver ces fichiers pour qu'ils puissent être téléchargés).

* On doit obligatoirement inclure une section `script` (même si on ne fait rien de particulier). Ici, on met simple message de log.

* On configure ensuite la `release`. On remplit les différentes sections obligatoires `name`, `description`, `tag_name` et `ref`. On peut préciser le numéro de version dans le nom et la description (même si ce n'est pas obligatoire).

* Enfin, on définit la section `links` qui nous permettra d'inclure les différents fichiers qu'on souhaite attacher à la release et le lien de téléchargement. Le lien `$CI_JOB_URL/artifacts/raw/` permet de télécharger les artifacts exportés par ce `job` (en spécifiant le nom du fichier souhaité à la fin du lien, bien entendu).

* Encore une fois, on exécute le job que si un tag est poussé (grâce à la section `rules`).

Votre but est donc de créer un **stage** et un **job** associé qui fait suite au job de `build`, récupère ses artifacts (ici, on aura seulement le fichier `EditeurDeTexte-X.Y.Z.jar`), l'exporte via les artifacts et publie la release. Voici quelques conseils pour votre prochaine mission :

* Comme indiqué plus haut, vous devez utiliser l'image `registry.gitlab.com/gitlab-org/release-cli:latest`.

* Redéfinissez les mêmes variables que dans le job `build` (numéro de version sans `v` et du nom de l'exécutable) dans ce nouveau job : vous aen aurez besoin un peu partout (pour `paths` dans `artifacts`, dans la section `release`, pour le nom du fichier et le lien de téléchargement, etc.).

* N'oubliez pas d'inclure une section `scripts` avec une commande simple (qui fait un écho ou autre).

* N'oubliez pas d'inclure la section `dependencies`.

<div class="exercise">

1. Dans votre fichier `.gitlab-ci.yml`, ajoutez un nouveau **stage** `release` à la suite et un **job** associé (avec le même nom) qui :
  * Exporte l'exécutable `jar` récupéré du job `build` comme `artifact` avec une durée de vie infinie (pas d'expiration).
  * Crée une release avec un lien de téléchargement vers cet exécutable.
  * S'exécute seulement quand un **tag** est poussé.

2. Faites un `commit` et un `push` sur votre branche `development`.

3. Créez un **tag** nommé `v1.1.0` (ou autre, tant que ça respecte le format `vX.Y.Z`) puis, poussez-le sur le dépôt distant.

4. Sur la page de gestion des pipelines, observez le déroulement des jobs, et vérifiez que le job `release` s'exécute bien à la fin. 

5. Enfin, si tout s'est bien passé, rendez-vous dans le menu `Deploy` → `Releases` au niveau du panneau latéral gauche. Vous devriez alors voir votre release! Vérifiez que l'exécutable `.jar` peut bien être téléchargé.

</div>

Félicitations, vous avez automatisé le processus de release de votre application ! Dorénavant, dès qu'un tag est créé et poussé, une release sera créé et publié. On peut souligner le fait qu'il n'est pas nécessairement obligatoire de passer par le système d'artifact pour publier un fichier dans une release. On peut spécifier n'importe quel lien. On pourrait donc imaginer un job qui upload les fichiers désirés sur un serveur externe et on utiliserait alors ces liens dans la release.

## Déploiement d'un site web PHP

Grâce à l'action [SFTP Deploy](https://github.com/marketplace/actions/sftp-deploy), nous pouvons uploader les fichiers du dépôt vers un répertoire dans un serveur accessible via FTP (par exemple, le serveur web de l'IUT !).

Voici l'allure générale d'un tel **workflow** :

```yml
name : nom_custom_workflow

on:
  push:
    branches:
      - master

jobs:

  deploy-website:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
      - name: Upload files on FTP server
        uses: wlixcc/SFTP-Deploy-Action@v1.2.4
        with:
          # Adresse du serveur
          server: sftp.exemple.com
          # Numéro de port
          port: 22
          # Nom d'utilisateur
          username: username
          # Mot de passe
          password: password
          # Dossier de destination dans le serveur (absolu, ou relatif...)
          remote_path: /public/www/
          # Si on utilise sftp
          sftp_only: true
```

Attention, le dossier ciblé par `remote_path` doit déjà exister sur le serveur distant.

Peut-être que vous êtes choqué de voir `password` et même `username` écrits en clair dans ce fichier, et vous savez raison ! Tout le monde peut lire les fichiers de **workflow**. Il est donc totalement exclu d'y placer des informations sensibles ! Alors comment faire ?

GitHub permet d'associer des **variables secrètes** à notre dépôt et d'y faire référence dans nos **workflows**. Ainsi, à la lecture, personne ne pourra voir le contenu réel de ces données, mais lors de l'exécution, la bonne valeur sera utilisée.

Pour créer une **variable secrète** à partir de la page du dépôt, on se rend dans `Settings`, `Secrets and Variables` et `Actions`. Ensuite, il faut appuyer sur le bouton `New repository secret`. On donne alors un nom (qui sera celui utilisé dans le **workflow**) puis on place la valeur réelle de la variable (le mot de passe en clair, par exemple).

Il faut respecter quelques règles de nommage :

* Les noms peuvent contenir uniquement des caractères alphanumériques et des underscores (`A-Z`, `a-z`, `0-9`, `_`). Les espaces ne sont pas autorisés.

* Les noms ne doivent pas commencer par un chiffre.

Ensuite, pour l'utiliser dans un **workflow**, on utilise ce format : {% raw %}`${{ secrets.nom_variable }}`{% endraw %}. Par exemple :

{% raw %}
```yml
jobs:

  deploy-website:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
      - name: Upload files on FTP server
        uses: wlixcc/SFTP-Deploy-Action@v1.2.4
        with:
          ...
          password: ${{ secrets.mdp }}
```
{% endraw %}

Concernant les informations pour se connecter au serveur FTP de l'IUT :

* Adresse : `ftpinfo.iutmontp.univ-montp2.fr`

* Port : `22`

* sftp_only : `true` (le serveur de l'IUT est uniquement accessible est SFTP)

* username / password : vos identifiants de département **(à gérer avec des variables secrètes)**.

<div class="exercise">

1. Téléchargez le fichier [index.php]({{site.baseurl}}/assets/TP2/index.php) et placez-le dans un nouveau dossier de projet. Il s'agit d'une simple page web affichant "Hello world".

2. Initialisez le dépôt git ce projet en local, puis sur GitHub, créez un nouveau dépôt vierge (privé ou public, comme vous voulez) et associez-le à votre dépôt local.

3. A l'aide de [cette page](https://iutdepinfo.iutmontp.univ-montp2.fr/intranet/acces-aux-serveurs/) (il faut utiliser vos identifiants habituels du département, rechargez cette page après vous être connecté) connectez-vous en **SFTP** au serveur de l'iut (en utilisant le logiciel **FileZila**, par exemple). Ensuite, sur le serveur, rendez-vous dans le dossier `public_html` et créez un dossier `hello_world_site`.

4. Sur votre dépôt GitHub, créez deux nouvelles variables **secrètes**. Un pour le nom d'utilisateur et un pour le mot de passe. Il s'agit de vos identifiants SFTP qui sont les mêmes que vous utilisez pour vous connecter sur vos machines, à GitLab, etc...

5. Créez un fichier `deploy.yml` dans un nouveau dossier `.github/workflows` placé dans votre dépôt.

6. Faites en sorte que ce workflow s'exécute seulement quand on réalise un **push** sur la branche **master**.

7. Ajoutez un **job** permettant de déployer votre projet vers le dossier `./public_html/hello_world_site/` du serveur FTP de l'IUT. Pensez à bien utiliser les variables secrètes définies plus tôt pour le nom d'utilisateur et le mot de passe !

8. Poussez le projet sur le dépôt distant. Suivez son état. Si tout se passe bien, alors, le site a été déployé et vous pouvez y accéder sur le serveur web de l'IUT : [https://webinfo.iutmontp.univ-montp2.fr/~login/hello_world_site/](https://webinfo.iutmontp.univ-montp2.fr/~login/hello_world_site/) (en remplaçant `login`, bien entendu).

9. Dans votre dépôt local, ajoutez la ligne de code suivante dans le fichier `index.php` :

    ```php
    echo "<p>Nous sommes le <strong>{$date->format('j F Y')}</strong> et il est <strong>{$date->format('H:i')}</strong></p>";
    ```

10. Poussez cette modification sur le dépôt distant, patientez et vérifiez que votre site a bien été mis à jour !

</div>

Vous pouvez maintenant déployer vos projets web sur leur serveur de destination avec un simple **push** sur une branche !

Ici, nous avons utilisé l'action **SFTP Deploy** car le serveur de l'IUT utilise SFTP. Pour un serveur utilisant seulement **FTP**, on utilisera plutôt l'action [FTP Deploy](https://github.com/marketplace/actions/ftp-deploy).

## Conclusion

À travers ce dernier TP, vous avez donc appris à vous servir de certaines fonctionnalités plus poussées de la plateforme **GitLab**.

Comme vous l'avez constaté, les techniques de `CI/CD` présentent beaucoup d'avantages dans le cadre du développement d'un projet. Dans ce TP, nous avons étudié seulement quelques exemples, mais il est possible de faire bien plus ! Les `actions` mises à disposition par la communauté ainsi que les événements permettant de déclencher les `workflows` sont très nombreux.
