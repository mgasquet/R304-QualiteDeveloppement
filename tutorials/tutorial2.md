---
title: TP2 &ndash; Git avancé 2/2
subtitle: Pages, Documentation, Workflows, Tests automatisés, Intégration et déploiement continu
layout: tutorial
lang: fr
---

Dans ce second (et dernier) TP, nous allons changer de plateforme et étudier diverses fonctionnalités proposées par **GitHub** notamment des outils de **CI/CD** (continuous integration/continuous delivery). Globalement, il s'agit d'automatiser différentes tâches qui seraient fastidieuses (et chronophages) de faire "à la main" comme le fait de tester l'intégration de différents modules de code, la construction et la mise à disposition de l'exécutable de l'application, sur plusieurs environnements. Si nécessaire, la mise en ligne de la documentation...

La plupart de ces outils sont aussi disponibles sur les autres plateformes comme **GitLab**, si le bon module est activé.

## Prise en main de GitHub

Tout d'abord, vous allez devoir vous inscrire à GitHub (si ce n'est pas déjà fait) puis utiliser une clé (on peut réutiliser la même que celle utilisée sur **GitLab**).

<div class="exercise">

1. Si ce n'est pas déjà fait, créez-vous un compte [GitHub](https://github.com/signup?ref_cta=Sign+up&ref_loc=header+logged+out&ref_page=%2F&source=header-home).

2. Copiez la clé d'authentification qui se trouve dans `~/.ssh/id_rsa.pub` (à adapter au cas où votre clé se nomme différamment ou que vous êtes sous Windows). Vous pouvez ouvrir le fihcier avec un editeur de texte et copier son contenu.

3. Rendez-vous sur [la page de gestion des clés](https://github.com/settings/keys) de votre profil GitHub. Cliquez sur **"New SSH key"**.

4. Précisez le nom que vous souhaitez, puis **collez votre clé publique** (qui doit normalement être dans votre presse-papier). Validez et constatez que votre clé a bien été ajoutée à votre profil **GitHub**.

</div>

Tout est prêt pour que vous puissiez travailler !

## Les pages de GitHub

Vous l'ignorez peut-être, mais GitHub met à disposition un outil appelé **GitHub Pages** qui permet d'héberger un **site web statique** (côté client donc, pas de PHP ou autres technologies serveur...). Des pages HTML/CSS simples, une application JS, un site construit avec une technologie réactive comme Angular, React, etc. peuvent donc être hébergés à travers un dépôt et accessibles au monde entier via une URL !

D'ailleurs, le site de TP utilise la technologie **Jekyll** et est hébergé sur GitHub ! Vous pouvez même cliquer sur **Source** en haut de la page pour accéder au dépôt !

Pour que cela fonctionne, il faut que votre dépôt soit **public**.

### Hébergement de pages statiques simples

Nous allons faire un premier essai d'hébergement d'un site statique simple. 

<div class="exercise">

1. Créez un site web simple avec une **page HTML** possédant le contenu de votre choix (et éventuellement du CSS). Par exemple, le site de Chuck Norris que vous avez développé en première année.

2. Dans le répertoire contenant votre page HTML, **initialisez** un dépôt (`git init`).

3. Sur **GitHub**, [créez un dépôt](https://github.com/new) avec une visibilité **public** (c'est important) puis reliez-le à votre dépôt en local (`git remote add origin adresse`). L'adresse à utiliser est affichée sur la page du dépôt (zone `Quick Setup`). Utilisez celle en `ssh`, pas celle `https`. Enfin, faites un add, un commit puis un push de votre site.

4. Toujours sur **GitHub**, dans votre dépôt, rendez-vous dans l'onglet **Settings** puis **Pages** (sur le menu latéral gauche).

5. Dans la section **branch**, sélectionnez **master**. On vous propose deux dossiers : **root** (la racine du dépôt) ou un éventuel dossier **docs**. Laissez donc le paramétrage à **root**.

6. Cliquez sur **Save** et patientez un petit peu (environ une minute). Votre site web sera bientôt accessible à l'adresse : [https://votre_pseudo_git.github.io/nom_dépôt/](https://votre_pseudo_git.github.io/nom_dépôt/). Si votre page ne s'appelle pas `index.html`, il faudra rajouter le nom de la page dans l'URL.

</div>

### Un site pour la Javadoc

Il est possible d'ajouter de la documentation à divers éléments d'un programme codé en Java : Classes, méthodes, etc. Une fois la documentation écrite, il est alors possible de générer un **site web** permettant d'explorer votre documentation !

Nous allons combiner cela avec les **pages** de GitHub afin que le dépôt héberge notre Javadoc et qu'elle soit accessible, en ligne.

Nous n'allons pas entrer dans le détail des possibilités que nous offre la syntaxe de documentation Java (on peut faire beaucoup de choses !) donc nous allons simplement voir les basiques :

Au-dessus de n'importe quelle méthode (même un constructeur) :

```java
/**
 * Description de la méthode
 * @param var1 description du premier paramètre
 * @param var2 description du second paramètre
 * @return Description de la valeur retournée
 */
public TypeRetour methode(Type var1, Type var2) {
  //...
}
```

S'il n'y a pas de paramètre ou de valeur de retour (void) on n'indique pas d'annotation `@param` et `@return`.

Pour documenter une **classe** :

```java
/**
 * Description de la classe
 */
class MaClasse {

  /**
   * Description de la propriété
   */
  private Type prop1;

  /**
   * Description de la propriété
   */
  private Type prop2;

}
```

Il est possible d'utiliser des balises **HTML** dans les différentes descriptions (par exemple `<p>...</p>`).

On peut aussi utiliser des **tags** avancés dans nos descriptions. Par exemple :

```java
/**
 * Description de la méthode
 * Il peut être intéressant de consulter la méthode {@link AutreClasse#methode} !
 * @param var1 description du premier paramètre
 */
public void methode(Type var1) {
  //...
}
```

Le **tag** `{@link AutreClasse#reference}` permet de référencer une méthode ou une propriété d'une autre classe (ou bien la classe toute seule si on ne met pas `#`). Dans le site généré, cela a pour effet de créer un lien vers la page et l'élément concerné !

Plus tard, vous pouvez vous documenter sur des guides plus complets : [ici](https://www.oracle.com/fr/technical-resources/articles/java/javadoc-tool.html) et [ici](https://www.tutorialspoint.com/java/java_documentation.htm).

Pour `PHP`, on retrouve [plus ou moins la même chose](https://www.jetbrains.com/help/phpstorm/phpdoc-comments.html).

<div class="exercise">

1. Créez un nouveau dépôt vierge sur **GitHub** (toujours avec une visibilité en `public`). Reprenez votre projet **éditeur de texte** (du TP précédent). Nous allons changer l'adresse du dépôt distant. 

    Pour cela, on modifie **origin** (pointant actuellement sur le dépôt GitLab) :

    ```bash
    git remote set-url origin nouvelle_adresse
    ```

2. Faites un **push** et vérifiez que votre projet apparait bien sur le dépôt distant **sur GitHub**.

3. Ajoutez de la **documentation** à quelques classes et méthodes (pas *tout* le projet, mais quand même quelques suffisamment !)

4. Nous allons ajouter une **tâche** à exécuter afin que le gestionnaire de dépendances et de projet (ici **Maven**) génère le site de la **Javadoc**. Sur IntelliJ IDEA, rendez-vous dans **Run** puis **Edit Configurations**. Appuyez sur `+` et sélectionnez **Maven**. Donnez le nom **"Javadoc"** à votre nouvelle tâche et spécifiez `javadoc::javadoc` dans le champ `Run`. Validez.

5. En haut à droite, sélectionnez votre tâche `Javadoc` (à côté du bouton "play") et exécutez-la. Dans votre exploreur de fichiers, rendez-vous ensuite dans le dossier `target/reports/apidocs` du projet et explorez le site web créé, en local.

6. Déplacez le dossier `apidocs` à la racine du dépôt et renommez-le `docs`.

7. Enfin, faites un commit et poussez-le sur votre dépôt distant. Sur **GitHub**, configurez votre **page** sur la branche **master** et le sous-dossier **docs**. Validez et patientez un peu, votre documentation est alors accessible en ligne ! Toujours à l'adresse [https://votre_pseudo_git.github.io/nom_dépôt/](https://votre_pseudo_git.github.io/nom_dépôt/).

</div>

Il peut être intéressant de mettre votre documentation en ligne de cette manière, notamment si votre projet à vocation à être utilisé par d'autres développeurs (si vous faites une **API** ou bien une **bibliothèque**, etc.). Néanmoins, il est fastidieux de répéter toutes ces opérations manuellement à chaque changement du code ! Nous allons donc voir comment automatiser tout ce processus grâce aux **workflows**.

Notez qu'il est également possible de générer la documentation d'un projet `PHP` de manière similaire : voir [cette ressource](https://docs.phpdoc.org/guide/getting-started/generating-documentation.html).

## Découverte des workflows

**GitHub** propose un outil appelé **GitHub actions**. Ce système permet de détecter quand un événement survient sur un dépôt (par exemple, un **push** sur une branche spécifique...) et de déclencher un **script** appelé **workflow** en conséquence. C'est un peu similaire aux **triggers** en base de données.

Le **workflow** va vous permettre de charger votre projet sur le (ou les) systèmes de votre choix et de réaliser des actions dessus (compilation, tests, publication d'un exécutable, et bien d'autres)... On peut même interagir directement avec notre dépôt, les branches, les issues, etc. Les systèmes disponibles sont **ubuntu**, **windows** et **macOs**.

Quand l'élément ciblé par le fichier de **workflow** survient, le script est exécuté. On peut suivre la progression des tâches en direct et, en cas d'échec (par exemple, un test ne passe pas, le programme ne compile pas...) **GitHub** prévient en ligne qu'il y a eu des erreurs, avec les détails et un mail est aussi envoyé aux collaborateurs du dépôt.

Avec ce système, **GitHub** pourrait détecter automatiquement s'il y a des soucis quand, par exemple, deux branches sont **fusionnées** avec succès, mais que le code ne compile plus, ou ne passe pas les tests.

Au-delà de ça, le **workflow** peut aussi servir à automatiser certaines tâches comme la mise à jour du site de la documentation, par exemple.

Les événements qui peuvent déclencher les workflows sont nombreux, on peut en retrouver la liste complète [ici](https://docs.github.com/en/actions/using-workflows/events-that-trigger-workflows).

### Le fichier de workflow

Un fichier de **workflow** est un fichier `.yml` (format `YAML`) qui se place dans un sous-dossier `.github/workflows` à partir de la racine du dépôt.

Voici l'allure générale d'un tel fichier :

```yml
name : nom_custom_workflow

on: evenement #Par exemple, "push"

jobs: #Un job est un processus qui contient lui-même des étapes

  nom-job1: #Nom du job 1
    runs-on: systeme #Sélection du système d'exploitation où s'exécute le job
    steps: #Etapes à réaliser sur le système
      - name: nom #Nom de l'action 1
        run: commande #Commande à exécuter (par exemple, javac, gcc, etc...)
      - name: nom2 #Nom de l'action 2
        uses : exemple/action #Utilisation d'une action externe
        with : #Paramètres de l'action externe (si besoin)
            param1: ...
            param2: ...
        ...    

    nom-job2: #Nom du job2
        ...

permissions:
  ....      
```

Comme vous pouvez le constater, un **workflow** est constitué de différents processus appelés `jobs` qui s'exécutent en **parallèle**. Chaque processus s'exécuté sur un environnement cible (par exemple, `ubuntu-latest`).

Chaque `job` contient une liste de tâches nommées qui s'exécutent dans l'ordre. Il y a deux types de tâches :

- Les tâches `run` qui exécutent une commande. Si cette commande échoue (par exemple, échec de compilation) le workflow échoue.

- Les tâches `uses` qui permettent d'appeler une action de workflow **externe**, pour réaliser une action précise. Par exemple, `actions/checkout@v4` est fréquemment utilisé comme première étape, car elle permet de déplacer la machine virtuelle dans une copie locale de votre dépôt (dans l'environnement d'exécution) et donc, d'accéder aux fichiers. Certaines actions ont besoin de paramètres qu'on peut préciser avec le bloc `with`. Beaucoup d'actions sont proposées par l'équipe de GitHub, mais d'autres actions très utiles sont aussi proposées par la communauté !

Bref, tous vos **jobs** auront donc cette allure :

```yml
name : nom_custom_workflow

on: evenement #Par exemple, "push"

jobs:

  job1:
    runs-on: ubuntu-latest #Tourne sur une VM ubuntu
    steps: #Etapes à réaliser sur le système
      #On se place dans le dépôt...
      - name: Checkout
        uses: actions/checkout@v4
      #Suite des actions...
      - name: ...
        uses: ...
```

On peut donner des `permissions` au robot exécutant le script. Par exemple, si on souhaite que notre `workflow` puisse créer des nouvelles branches ou bien publier des `releases`, il faut lui donner des droits d'écriture en précisant la permission `contents: write`.

Pour un événement, il est aussi possible de préciser des conditions supplémentaires, par exemple, "seulement quand on push sur la branche development" :

```yml
#Se déclenche quand on push quelque chose
name : nom_custom_workflow

on: push

jobs:
  job1:
    ...
```

```yml
#Se déclenche quand on push sur n'importe quelle branche
name : nom_custom_workflow

on:
  push:
    branches:
      - '*'

jobs:
  job1:
    ...
```

```yml
#Se déclenche seulement quand on push sur la branche "development"
name : nom_custom_workflow

on:
  push:
    branches:
      - development

jobs:
  job1:
    ...
```

À noter qu'un `merge` d'une branche résultera en un `push` à un moment donné, dans la branche qui intègre les changements de la branche fusionnée.

### Automatisation des tests sur GitHub

Pour mettre en pratique, nous allons coder un **workflow** très simple permettant de lancer les **tests unitaires** sur votre application. Mais tout d'abord... il vous faut des tests unitaires ! (comment, vous n'avez pas écrit de tests unitaires depuis le début?!)

<div class="exercise">

1. Placez-vous dans votre branche `development`.

2. Créez le dossier de tests `src/test/java` (il n'existe pas encore, parce que vous n'avez écrit aucun test). Pour le créer, depuis IntelliJ le plus simple est de cliquer droit sur le répertoire `src` → **New** → **Directory** → Choisissez `test/java`. Par convention, la couleur verte indique qu'il s'agit du répertoire contenant le code source des tests.

3. Créez un paquetage `fr.iut.editeur.document` dans `src/test/` puis, à l'intérieur, créez la classe `DocumentTest`. Remarquez, qu'en fait, vous n'avez pas vraiment créé ce paquetage... puisqu'il existe déjà ! Seule l'arborescence des répertoires a été créée dans `src/test/`. En effet, le paquetage est le même que celui de la classe `Document` (dans `src/main/java`). C'est normal, car une convention répandue dit que les tests unitaires doivent être écrits dans le même paquetage que les classes qu'ils testent.

4. Écrire quelques méthodes pour tester les méthodes de la classe `Document`. Si vous ne vous rappellez plus comment faire, jetez un oeil à vos cours Java de l'an dernier ! Voici une squelette de cette classe :

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

Maintenant que vous avez des tests unitaires prêts et fonctionnels, nous allons faire en sorte que **GitHub** les exécutent après un **push** sur n'importe quelle branche.

Dans le workflow, vous aurez besoin d'un **job** pour :

1. Se déplacer dans votre dépôt. Vous pouvez utiliser l'action `actions/checkout@v4` pour cela.

2. Installer et mettre en place `Java` (version 17). Vous pouvez utiliser l'action `actions/setup-java@v4` paramétrée (au niveau du `with`) avec `java-version: 17` et `distribution: 'oracle'`.

3. Exécuter la commande `mvn test` (exécution de tests avec `maven`).

<div class="exercise">

1. Créez un fichier `tests.yml` dans un nouveau dossier `.github/workflows` (placé à la racine de votre dépôt).

2. Grâce à ce **workflow**, faites en sorte qu'un **push** (sur n'importe quelle branche) exécute les tests unitaires. Dans le `job` que vous allez mettre en place, utilisez le système `ubuntu-latest`. N'oubliez pas de nommer chaque `step` dans votre `job`.

3. Faites un `commit` et un `push` sur votre branche `development`. Sur `GitHub`, rendez-vous sur votre dépôt et sélectionnez l'onglet `Actions`. Vous devriez voir votre message de commit et un processus en cours d'exécution. Cliquez dessus puis sur le nom du workflow en train de s'exécuter, pour obtenir plus de détail et suivre le déroulement de chaque étape.

4. Maintenant, modifiez légèrement la classe `Document` pour qu'un ou plusieurs tests ne passent plus. Faites un commit et un push et vérifiez que le `workflow` échoue bien. Enfin, remettez tout en ordre.

</div>

### Gestion automatique de la Javadoc

Maintenant que vous maîtrisez les **workflows**, vous allez pouvoir en créer un qui va automatiquement générer le site de la Javadoc et le mettre en ligne à l'aide de **GitHub pages** !

Pour cela, vous aurez besoin de créer un `job` qui doit :

1. Se déplacer dans votre dépôt puis installer et mettre en place `Java` (version 17). Comme dans le workflow précédent.

2. Générer le site de la `javadoc` avec la commande `mvn javadoc::javadoc`.

3. Publier le contenu du site sur une branche dédiée. Pour cela, vous pouvez utiliser l'action `peaceiris/actions-gh-pages@v4`. Cette action nécessite deux paramètres :

    - `github_token` : permet de vous identifier pour autoriser le robot exécutant le script à pousser sur votre branche. Ce "token" est déjà disponible, il suffit de le préciser avec {% raw %}`${{ secrets.GITHUB_TOKEN }}`{% endraw %}.

    - `publish_dir` : le chemin du dossier contenant les fichiers à publier. En fait, cette action va créer une branche `gh-pages` contenant les fichiers du dossier précisé par le chemin `publish_dir`. Dans notre cas le site de la `javadoc` est généré dans le dossier `./target/reports/apidocs/`.

Comme le robot va **créer une branche**, il faut lui donner les droits d'écriture (section à part, par exemple avant ou après les `jobs`) :

```yml
permissions :
    contents: write
```

<div class="exercise">

1. Créez un fichier `documentation.yml` dans le dossier `.github/workflows`.

2. Grâce à ce **workflow**, faites en sorte qu'un **push** **sur la branche master** génère la documentation et la publie sur la branche `gh-pages`. Dans le `job` que vous allez mettre en place, utilisez le système `ubuntu-latest`. N'oubliez pas de nommer chaque `step` dans votre `job`.

3. Faites un `commit` et un `push` sur votre branche `development`. Sur `GitHub`, rendez-vous sur votre dépôt et sélectionnez l'onglet `Actions`. Vérifiez le workflow correspondant n'est pas éxécuté (car on n'a pas push sur master !). Par contre, l'autre worflow (celui des tests unitaires) devrait s'éxécuter (car on a pas spécifier de branches...).

4. Dans votre terminal, déplacez-vous dans votre branche `master` et réalisez un `merge` de la branche `development`. Faites un `push` de la branche `master` et observez le déroulement de votre workflow dans l'onglet `Actions`. À l'issue, vous devriez voir qu'une branche `gh-pages` est créée !

5. Dans la configuration de `GitHub pages`, précisez la branche `gh-pages` plutôt que `master` et sélectionnez `root`.

</div>

Et voilà ! Maintenant, dès qu'un push sera effectué sur la branche de **production** `master`, le site de la `javadoc` de votre application sera automatiquement mis à jour sans actions supplémentaires de votre part !

## Déploiement

Avec les `workflows`, nous pouvons automatiser le processus de **déploiement** d'une application, c'est-à-dire sa **mise en production** afin qu'elle soit utilisable et exploitable par les utilisateurs. Il s'agit de la partie `CD` (continous delivery) où l'application est déployée / délivrée de manière continue.

### Releases

**GitHub** permet de publier des **releases** de notre application, c'est-à-dire une version fonctionnelle du logiciel, avec les exécutables et les ressources nécessaires.

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

### Déploiement de l'application d'édition de texte

Nous allons faire en sorte que, dès qu'un **tag** est **push** sur le dépôt distant, le code de l'application soit compilé et qu'une **release** contenant notre exécutable (ici le fichier `.jar`) soit publié. Ainsi, dès qu'une nouvelle version est prête, il suffit de créer un **tag** et **GitHub** se charge alors du reste.

Dans une **release**, il est possible d'uploader différents types de fichiers. Par défaut, le code source de l'application est mis à disposition. Dans notre cas, nous allons seulement ajouter l'exécutable `.jar` de l'application, mais dans l'absolu, il est tout à fait possible d'inclure d'autres fichiers.

Pour réaliser ce processus, le `job` du workflow aura besoin de :

1. Se déplacer dans votre dépôt puis installer et mettre en place `Java` (version 17). Comme dans pour les workflows précédents.

2. Générer l'exécutable `.jar` de votre application avec la commande `mvn package`. L'exécutable est placé dans le dossier `target` sous le nom `EditeurDeTexte-0.0.1.jar`.

3. Créer une `release` contenant le fichier `EditeurDeTexte-0.0.1.jar`. Pour cela, vous pouvez utiliser l'action `softprops/action-gh-release@v2`. Cette action nécessite un paramètre :

    - `files` : le chemin des fichiers à inclure dans la `release` (ici `target/EditeurDeTexte-0.0.1.jar`).

    Si on doit préciser **plusieurs fichiers**, on utilise ce format :

    ```yml
        files: |
            chemin1
            chemin2
            ...
    ```

Pour préciser qu'on souhaite exécuter ce **workflow** seulement si un **tag** est poussé, on écrit :

```yml
on:
  push:
    tags:
    - '*'
```

Là aussi, il faudra donner la permission d'écriture (car il publie une relase sur le repository `github`) :

```yml
permissions :
    contents: write
```

<div class="exercise">

1. Créez un fichier `release.yml` dans le dossier `.github/workflows`.

2. Grâce à ce **workflow**, faites en sorte qu'un **push** d'un **tag** génère une **release** contenant le fichier **.jar**.

3. Faites un `commit` et un `push` sur votre branche `master`.

4. Créez un **tag** nommé `v0.0.1` puis, poussez-le sur le dépôt distant.

5. Sur `GitHub`, rendez-vous sur votre dépôt et sélectionnez l'onglet `Actions`. Suivez l'avancement de la création de votre `release`.

6. Une fois le `workflow` achevé, rendez-vous sur la page principale de votre `dépôt` puis cliquez sur `Releases` dans le menu latéral droit. Vous devriez voir votre `release` et le fichier `.jar` qu'elle contient !

</div>

Très bien, votre `workflow` fonctionne, mais on aimerait que la version affichée sur le fichier `.jar` s'adapte au nom du `tag`. Pour cela, il est possible de préciser à `maven` de changer la `version` du projet avant de générer le `.jar`. Sans cela, il faudrait modifier le fichier `workflow` à chaque publication d'une nouvelle version (et aussi modifier `pom.xml`).

Dans votre `workflow`, vous pouvez donc intégrer l'exécution de la commande suivante (avant `mvn package`) :

```bash
mvn versions:set -DnewVersion=nouvelle_version -DgenerateBackupPoms=false
```

À la place de `nouvelle_version` vous pouvez utiliser {% raw %}`${{ github.ref_name }}`{% endraw %} qui permet d'obtenir, via le `workflow` le nom de l'élément en train d'être poussé sur le dépôt. Pour un commit, il s'agirait de son identifiant, et pour un tag, il s'agit simplement de son nom. Ainsi, lors de la construction du `.jar`, si le **tag** se nomme `v0.0.2`, le fichier généré sera `EditeurDeTexte-v0.0.2.jar`.

On doit utiliser une nouvelle fois {% raw %}`${{ github.ref_name }}`{% endraw %} pour le chemin du fichier à inclure dans le paramètre `files` de l'action `softprops/action-gh-release@v2`.

<div class="exercise">

1. Apportez les modifications nécessaires à votre `workflow` pour que le nom de l'exécutable s'adapte au nom du **tag**.

2. Faites un commit et poussez-le sur le dépôt distant puis créez un tag `v0.0.2` et poussez-le aussi.

3. Vérifiez que le `workflow` s'exécute bien puis vérifiez que le fichier placé dans la release `v0.0.2` porte le bon nom.

</div>

### Déploiement d'un site web PHP

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

### Déploiement d'un programme multiplateforme

Pour un programme développé avec un langage interprété (comme `python`) ou pour un langage utilisant une machine virtuelle (comme `Java`), le fichier du programme ou l'exécutable généré est compatible avec n'importe quel système d'exploitation. En effet, si vous compilez un programme java sur `windows`, il pourra être directement exécuté sur un système tournant sur `macOS`, par exemple.

Cela ne s'applique pas pour les programmes `compilés` comme le `C` où l'exécutable dépend du système d'exploitation. Ainsi, un programme `C` compilé sous `windows` donnera un exécutable en `.exe` qu'on ne peut pas lancer tel quel sur `ubuntu`, par exemple. C'est pour cela que, quand on livre un tel programme, on propose généralement 3 types de téléchargements, selon le système d'exploitation de l'utilisateur.

Comme nous l'avons vu, les `workflows` permettent aussi d'utiliser `windows` et `macOS` dans les `jobs`! Nous pouvons donc lancer 3 `jobs` pour compiler un programme `C` sur les différents systèmes et ensuite inclure les 3 fichiers à une release.

Nous allons tester ce système sur un petit programme très simple, codé en `C`

<div class="exercise">

1. Téléchargez le fichier [puissance.c]({{site.baseurl}}/assets/TP2/puissance.c). Ce programme permet de calculer le résultat de `x` élevé à la puissance `n`. Il s'utilise en passant `x` et `n` en argument.

2. Compilez le programme, testez-le rapidement.

3. Créez un dépôt contenant seulement le fichier `puissance.c`.

4. Sur `GitHub`, créez un nouveau dépôt (privé ou public, comme vous voulez) puis reliez-le à votre dépôt local. Faites ensuite votre premier `commit` ainsi que votre premier `push`.

</div>

De la même manière que pour l'application d'édition de texte, nous allons créer un `workflow` permettant de publier une `release` quand un `tag` est poussé.

Dans chaque système utilisable dans les `jobs`, le programme `gcc` (pour compiler) est déjà installé.  
Voici donc un `job` que l'on pourrait utiliser pour compiler le programme pour un environnement `windows` :

```yml
  build-windows:
    runs-on: windows-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
      - name: Build
        run: gcc puissance.c -o puissance-windows.exe
```

<div class="exercise">

1. Créez un fichier `release.yml` dans un nouveau dossier `.github/workflows` placé dans votre dépôt.

2. Faites en sorte que ce workflow s'exécute seulement quand un `tag` est `push`.

3. Ajoutez **trois jobs** pour compiler le programme dans chaque système. Les systèmes disponibles sont : `ubuntu-latest`, `windows-latest` et `macos-latest`. Pour `ubuntu`, l'exécutable compilé devra se nommer `puissance-linux.bin`, pour `macos` : `puissance-macos` (pas d'extension) et pour `windows` on aura donc `puissance-windows.exe`.

</div>

Vous avez maintenant trois **jobs** qui permettent de compiler votre programme de puissance dans chaque système. Cependant, pour créer la `release`, nous avons besoin de récupérer ces trois exécutables ! Et cela pose problème, car on ne peut pas y accéder directement (car chaque `job` s'exécute sur un environnement différent).

Pour résoudre ce problème, nous allons utiliser le système `artifact`. Il s'agit d'une action qui permet d'uploader un fichier depuis un `job` (avec un nom associé) vers un espace spécial sur `GitHub` puis de le télécharger dans un autre `job`.

Les `artifacts` s'utilisent au travers de **deux actions** :

- `actions/upload-artifact@master` : permet d'uploader un artifact pour le rendre disponible aux autres `jobs`. Il faut préciser un paramètre `name` correspondant au nom de l'artifact et un autre paramètre `path` correspondant au chemin du fichier ciblé (qu'on souhaite uploader). Le fichier sera mis à disposition sous le nom précisé par `name` et les autres `jobs` pourront alors le télécharger.

Par exemple, pour windows :

```yml
    build-windows:
      runs-on: windows-latest
      steps:
        - name: Checkout
          uses: actions/checkout@v4
        - name: Build
          run: gcc puissance.c -o puissance-windows.exe
        - name: Upload
          uses: actions/upload-artifact@master
          with:
            name: puissance-windows
            path: ./puissance-windows.exe
```

- `actions/download-artifact@master` : permet de télécharger un artifact. Il faut préciser un paramètre `name` correspondant au nom de l'artifact ciblé. Le fichier est alors téléchargé et disponible dans l'environnement du `job`.

Par exemple :

```yml
    exemple:
      runs-on: ubuntu-latest
      steps:
        - name: Download puissance-windows artifact
          uses: actions/download-artifact@master
          with:
            name: puissance-windows
```

Le but est donc que chaque `job` fasse un `upload` de l'exécutable compilé. Ensuite, un autre `job` doit télécharger ces fichiers puis créer la `release` en ajoutant les trois exécutables.

Attention, de base, tous les `jobs` sont concurrents (s'exécutent en parallèle) mais celui-ci a besoin d'attendre que les trois autres soient terminés. Pour cela, on peut utiliser le paramètre `needs` au niveau du job pour préciser que ce job doit attendre que les `jobs` précisés doivent s'être achevés avant de débuter.

Par exemple :

```yml
name : exemple

on: ...

jobs:

    j1:
        runs-on: ...
        steps:
            ...
    
    j2:
        runs-on: ...
        steps:
            ...

    j3:
        needs: [j1, j2]
        runs-on: ...
        steps:
            ...

```

<div class="exercise">

1. Modifiez votre `workflow` afin que les trois `jobs` fasse un `upload` de leur exécutable.

2. Ajoutez un `job` qui doit **attendre** que les trois autres `jobs` soient terminés avant de s'exécuter. Ce job s'exécutera sur `ubuntu-latest` et devra télécharger les trois exécutables compilés puis créer une `release` contenant ces trois fichiers. Il y aura plusieurs fichiers à placer dans la release (la manière de faire cela est indiqué dans ce TP).

3. Pour que votre `workflow` soit autorisé à créer une `release`, donnez-lui la permission `contents: write`.

4. Faites un `commit`, un `push`, puis créez un `tag` nommé `v1.0.0` que vous pousserez également sur votre dépôt distant.

5. Observez l'exécution du `workflow` dans l'onglet `Actions` puis vérifiez que la **release** créée contient bien les trois exécutables. 

</div>

Bravo ! Vous pouvez maintenant déployer votre programme aisément, sur toutes les 3 plateformes. Cependant, pour les langages compilés et notamment pour le `C`, certaines librairies ne sont pas forcément les mêmes selon le système (par exemple, certaines librairies sur les `sockets`). C'est toute la problématique de la **portabilité**. 

Dans ce cas, il faut donc, par exemple, avoir un code source (ou une partie) pour `ubuntu`, un pour `windows` et faire l'adaptation. Les `workflows` de **GitHub** peuvent toujours être utilisés en compilant les fichiers spécifiques, selon le système, mais également pour tester qu'un programme fonctionne comme attendu dans un des systèmes cibles (il serait fastidieux de tester les trois systèmes à la main après chaque mise à jour !)

Vous aurez peut-être noté que certaines actions que nous réalisons dans les trois `jobs` pour compiler le programme sont assez redondantes. Nous pourrions optimiser cela avec des `matrices` qui permettraient d'exécuter le contenu d'un `job` sur les trois systèmes, en faisant de légères adaptations (pour les noms des exécutables produits).  
Si le temps le permet, allez consulter la [documentation](https://docs.github.com/en/actions/using-jobs/using-a-matrix-for-your-jobs) à ce propos et essayez donc de rendre votre `workflow` plus léger.

## Conclusion

À travers ce dernier TP, vous avez donc appris à vous servir de certaines fonctionnalités plus poussées de la plateforme **GitHub**.

Comme vous l'avez constaté, les techniques de `CI/CD` présentent beaucoup d'avantages dans le cadre du développement d'un projet. Dans ce TP, nous avons étudié seulement quelques exemples, mais il est possible de faire bien plus ! Les `actions` mises à disposition par la communauté ainsi que les événements permettant de déclencher les `workflows` sont très nombreux.
