# TD1 - Les pointeurs

## Exercice 0 : premier code C

```c
#include <stdio.h>

int main(const int argc, char *argv[] ){
    //argc : nombre d’arguments, argv : le tableau contenant la valeur des arguments
    int a = 1 ;
    printf(" le chiffre est %d \n ", a);

    char clavier[100];
    printf(" Saisissez le texte : ");
    scanf("%s", clavier);
    printf("vous avez saisie : %s \n", clavier);

    printf("\nMainenant, on va lister tous les arguments (argv)\n");
    int i;
    for (i = 0; i < argc; i++){
        printf("%s \n", argv[i]);
    }
    return 0;
}

```

Commande de compilation : `gcc nom_du_fichier.c -o nom_executable`

Execution : `./nom_executable`

## Exercice 1 : pointeurs simples

Créer 3 fonctions "*plus*", "*moins*" et "*fois*".

Chacune des trois fonctions prend 3 paramètres de type pointeur d’entier (int*) et effectue l’opération entre les deux premiers paramètres pour stocker le résultat dans le troisième.

Dans le *main()*, définir 3 variables de type entier x, y et z (x=50, y=20, z=0).
Puis tester les 3 fonctions en affichant le résultat entre chaque utilisation d’une fonction.

## Exercice 2 : pointeurs avec structure

Définir une structure "Coordonnees" contenant 3 entiers (x, y, z)

La fonction *main()* déclare une variable **ici** de type "Coordonnees". Elle envoie l’adresse de cette variable à une fonction *"initialiser"* qui initialise respectivement les valeurs x, y et z à 1,
5 et 2.

Ensuite, la fonction *main()* envoie l’adresse de la variable **ici** aux 3 fonctions suivantes :
* afficher : affiche la valeur de x, y et z ;
* multiplier : multiplie x et y puis stocke le résultat dans z ;
* additionner : additionne x et y puis stocke le résultat dans z.

La fonction *"afficher"* peut être utilisée plusieurs fois afin de voir l’évolution des opérations.

## Exercice 3 : pointeurs plus

Reprendre l’exercice précédent, mais cette fois la fonction *"afficher"* sera appelée dans les fonctions de multiplication et d’addition

## Exercice 4 : création de tableau dynamique

Proposer un programme C qui demande de saisir une taille de tableau, puis alloue dynamiquement un tableau d’entiers de cette taille (voir [rappel](#rappel)), le remplit avec des valeurs aléatoires comprises entre 0 et 100 et l’affiche.

## Exercice 5 : modification de tableau dynamique

Reprendre le code précédent et, en plus, on changera la taille du tableau (en gardant les données initiales) en fonction d’une nouvelle taille saisie par l’utilisateur (voir [rappel](#rappel)). Si la taille est plus grande, il faut ajouter de nouvelles valeurs aléatoires.

On affichera le nouveau tableau.

## Exercice 6 : création de matrice dynamique

Proposer un programme C qui alloue dynamiquement une matrice (int **) d’entiers, la remplit avec des valeurs aléatoires et l’affiche.

Le nombre de lignes et de colonnes étant saisis, au clavier, par l’utilisateur.

## Exercice 7 : modification de matrice dynamique

Reprendre le code précédent et, en plus, on changera la taille de la matrice en fonction de deux nouveaux nombres de lignes et de colonnes saisis au clavier. La matrice doit garder les anciennes valeurs.

On affichera la nouvelle matrice

## Exercice 8 : tableau de chaînes de caractères

Proposer un programme C qui saisit un nombre **N** de chaînes. Puis alloue dynamique un tableau de **N** chaînes de caractères et le remplit avec des valeurs saisies dans le terminal. Les chaînes de caractères doivent aussi être alloué dynamiquement (en utilisant la taille de chaque chaîne entrée)

Le programme doit afficher, **à la fin**, les chaînes du tableau.

Fonctions utiles : Il faut inclure `string.h`
* `strlen(chaîne)` pour avoir la taille d'une chaîne
* `strcpy(tableauCible, tableauACopier)` pour copier une chaîne
* `fgets(chaîne, maxLength, stream)` pour remplacer `scanf` et qui permet de lire des espaces
    * Dans notre cas, **stream** sera `stdin`
* `atoi(chaîne)` pour convertir une chaîne en entier


## Rappel

### Création d'un tableau dynamique

```c
char * tableau = malloc(20 * sizeof(char)); //Allocation d'un tableau de 20 caractères
if (tableau == NULL) {
    printf("L'allocation n'a pu être réalisée\n");
} else {
    printf("L'allocation a été un succès\n");
    ... je fais des traitements ...
    free(tableau); //Libération des 20 caractères précédemment alloués
    tableau = NULL; // Invalidation du pointeur
}
```

### Modification d'un tableau

```c
char * tmp = realloc(tableau, nouvelleTaille * sizeof(char));
if (tmp == NULL) {
    free(tableau);
    printf("La réallocation n'a pu être réalisée\n");
} else {
    tableau = tmp;
}
```
