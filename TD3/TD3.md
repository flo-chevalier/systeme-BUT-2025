# TD3 : Processus

## Exercice 1 : Premiers forks

Écrire un programme C qui crée 3 processus fils. Chaque fils affiche son PID et celui de son père. Les 3 fils doivent être frères.

Une fois les 3 processus fils exécutés, le père indique que tout va bien.

## Exercice 2 : Boucle

Écrire un programme C qui crée 2 processus fils. Chaque processus fils affiche son PID
toutes les secondes.

## Exercice 3 : Execution d'autres programmes

1. Ecrire un programme C `3.A` qui affiche votre prénom et nom. Le compiler.
2. Ecrire un programme C `3.B` qui affiche une phrase. Le compiler.
3. Ecrire un programme C qui crée 2 processus fils. Le premier exécute le programme compilé `3.A` et le second exécute le programme compilé `3.B`.

**Aide** : Il faut utilise la fonction execv pour lancer un programme.

## Exercice 4 : Un début de terminal

Écrire un programme C qui demande à l’utilisateur un programme à exécuter, puis l’exécute dans un processus fils, puis en demande un à nouveau, et ainsi de suite.

## Exercice 5 : signal

Écrire un programme C qui attrape tous les signaux. Dès qu’il attrape un signal, il affiche un
message dans le terminal avec le numéro du signal.

Utiliser la commande kill dans le terminal : `kill -numSignal numPid`

La commande `kill -l` permet de lister les signaux disponibles

## Exercice 6 : génocide des fils

Écrire un programme C qui génère n fils (n est passé en argument au programme : argv).

Chaque fils écrit son PID ainsi que son numéro de création toutes les secondes.

Le père tue tous ses fils après 5 secondes (signal 9).

## Exercice 7 : discussion entre père et fils (tube)

Écrire un programme C qui crée un processus. Le père demande un texte dans le terminal, l’envoie au fils et le fils l’affiche dans le terminal (en précisant qu’il est le fils).

Voir [rappel](#rappel)

## Exercice 8 : discussion en entre père et fils avec réponse (double tubes)

Écrire un programme C qui crée un processus. Le père demande un texte dans le terminal, l’envoie au fils et le fils affiche qu’il l’a bien reçu, puis le renvoie au père qui l’affichera.

# Pour les plus rapides

## Exercice bonus :

Ecrire un programme C reproduisant les fonctions d'un terminal. Par exemple :

* Executer les programmes que l'utilisateur tape
* Permettre l'execution de programmes avec des paramètres
* Permettre l'utilisation du pipe `|` pour que deux programmes communiques
* Interrompre un programme en cours avec CTRL+C (signal SIGINT)
* ...

# Rappel

## Création et utilisation d’un tube anonyme

```c
int tube[2]; // déclare le tube
pipe(tube); // crée le tube anonyme
read(tube[0], tampon, 10); // lire 10 caractères dans le tube
write(tube[1], tampon, 10); // écrire 10 caractères dans le tube
close(tube[0]); // ferme le tube côté lecture
close(tube[1]); // ferme le tube côté écriture
```

