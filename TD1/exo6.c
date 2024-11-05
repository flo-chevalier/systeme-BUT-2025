#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_MIN 0
#define NB_MAX 100
#define MIN_LIGNE 2
#define MAX_LIGNE 10

int randomNumber() {
    return (rand() % (NB_MAX - NB_MIN)) + NB_MIN;
}

int saisirNombreLignes() {
    int nb = 0;
    printf("Saisir le nombre de lignes (%d -> %d) :\n", MIN_LIGNE, MAX_LIGNE);
    scanf("%d", &nb);

    return nb;
}

int saisirNombreColonnes() {
    int nb = 0;
    printf("Saisir le nombre de colonnes (%d -> %d) :\n", MIN_LIGNE, MAX_LIGNE);
    scanf("%d", &nb);

    return nb;
}

int *constructionTableau(const int taille) {
    int *tableau = (int *) malloc(taille * sizeof(int));

    if (tableau == NULL) {
        printf("Allocation echouée\n");
    }

    for (int i = 0; i < taille; i++) {
        tableau[i] = randomNumber();
    }

    return tableau;
}

void affichageMatrice(int **matrice, const int nbLignes, const int nbColonnes) {
    for (int i = 0; i < nbLignes; i++) {
        for (int j = 0; j < nbColonnes; j++) {
            printf("%d\t", matrice[i][j]);
        }
        printf("\n");
    }
}

int **constructionMatrice(const int nbLignes, const int nbColonnes) {
    int **matrice = (int **) malloc(nbLignes * sizeof(int *));

    if (matrice == NULL) {
        printf("L'allocation a échouée!\n");
    }

    for (int i = 0; i < nbLignes; i++) {
        matrice[i] = constructionTableau(nbColonnes);
    }

    return matrice;
}

void destructionMatrice(int **matrice, const int nbLignes) {
    for (int i = 0; i < nbLignes; i++) {
        free(matrice[i]);
    }

    free(matrice);
    matrice = NULL;
}

void verifierValiditeSaisie(const int nombre) {
    if (nombre > MAX_LIGNE) {
        printf("Nombre trop grand. Fin du programme\n");
        exit(1);
    }

    if (nombre < MIN_LIGNE) {
        printf("Nombre trop petit. Fin du programme\n");
        exit(1);
    }
}


int main(const int argc, char *argv[]) {
    srand(time(NULL)); //initialise le générateur aléatoire

    int nbLignes = saisirNombreLignes();
    verifierValiditeSaisie(nbLignes);

    int nbColonnes = saisirNombreColonnes();
    verifierValiditeSaisie(nbColonnes);

    printf("Construction d'une matrice %dx%d\n", nbLignes, nbColonnes);
    int **matrice = constructionMatrice(nbLignes, nbColonnes);

    affichageMatrice(matrice, nbLignes, nbColonnes);
    destructionMatrice(matrice, nbLignes);

    return 0;
}
