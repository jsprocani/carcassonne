<img src="https://upload.wikimedia.org/wikipedia/fr/thumb/1/10/Logo_Carcassonne_v3.png/495px-Logo_Carcassonne_v3.png">

<h3>DESCRIPTION :</h3>

Carcassonne est un jeu de pose de tuiles, où l'on construit le plateau de jeu au cours de la partie. Des points sont attribués en fonction de la taille des combinaisons créées — villes, champs, routes, abbayes.

Ce projet est une adaption numérique non-officielle dérivée du jeu de base, codé en C et développé par deux étudiants de l'UPVD : Jonas Sprocani & Guilhem Pluche

> ### À propos de ce dépôt :
> Ce répertoire a été préparé spécifiquement pour mes candidatures en Master, afin d'offrir un aperçu clair et direct depuis mon CV. Il s'agit d'une version consolidée d'un projet académique :
> * **Historique condensé :** L'ensemble du développement a été regroupé en un commit unique pour mettre immédiatement en valeur le résultat abouti.
> * **Fidélité au projet initial :** Quelques correctifs mineurs ont été appliqués pour garantir un code parfaitement fonctionnel. Le périmètre et les fonctionnalités restent cependant strictement identiques à la version d'origine.


<h3>PRÉREQUIS :</h3>

Le projet contient des dépendances et utilise Raylib, assurez-vous d'avoir la librairie Raylib téléchargée (fournie par le projet) pour commencer à procéder.

Remarque : Si vous avez déjà Raylib d'installé (dynamiquement), le téléchargement de la librairie (statique) est optionnel.


<h3>CONSTRUCTION :</h3>

Pour compiler le projet, ouvrez un terminal dans le répertoire racine puis exécutez dans le terminal la commande suivante : `make`

Si la compilation est réussie, un exécutable Carcassonne est créé dans le dossier bin.


Si le message suivant est affiché :

`make: *** Pas de cible spécifiée et aucun makefile n'a été trouvé. Arrêt.`

Vérifiez d'avoir bien téléchargé le fichier Makefile dans le répertoire racine.


<h3>UTILISATION :</h3>

Pour lancer le jeu, vous devez posséder dans le répertoire racine deux fichiers annexes : un fichier CSV contenant la liste des tuiles du jeu, ainsi qu'un fichier CFG contenant les identifiants images et les positions initiales des tuiles. Ces deux fichiers doivent avoir le même nom mais chacun leur extension : .csv et .cfg

Vous avez deux méthodes pour lancer jeu : 
<br/>-exécuter dans le terminal et en écrivant à la main le nom (sans extension) des fichiers annexes dans la commande suivante : `./bin/carcassonne [Nom fichiers]`
<br/>-exécuter directement dans le terminal la commande suivante : `make run`

Exemple d'utilisation : `./bin/carcassonne tuiles_base_simplifiees`

Note : Le projet fourni par défaut deux fichiers CSV et CFG : tuiles_base_simplifiees.csv et tuiles_base_simplifiees.cfg
 
Remarque : Le projet utilise des images, si vous remarquez des images manquantes en cours de jeu, vérifier d'avoir téléchargé toutes les images dans le dossier images.

Commandes du jeu :

- Clic gauche de la souris : Placer une tuile
- Clic droit de la souris : Poser un meeple
- Molette de souris : Roter la tuile
- Touches flèches : Déplacer la caméra sur la grille
- Touche espace : Recentrer la caméra sur la grille
- Touche échap : Quitter le jeu


<h3>CONTRIBUTION :</h3>

Si vous souhaitez contribuer au projet, l'utilisation de fichiers annexes vous permet d'utiliser vos propres tuiles. Cela permet l'ajout d'extensions, par exemple l'ajout des rivières et des abbés.

Remarque : vous pouvez utiliser vos propres images avec certaines conditions, elles doivent être au format PNG et se nommer de la manière suivante : Tuile_[ID].png

Note : Vous pouvez nommer vos propres ID pour utiliser des images supplémentaires, l'ID peut être figuré dans le fichier CFG.


<h3>SOURCES :</h3>
Logo : <a href="https://fr.wikipedia.org/wiki/Carcassonne_(jeu)">Wikipédia</a>
<br/>
Tuiles : <a href="https://wikicarpedia.com/car/Main_Page/fr">Wikicarpedia</a>

