#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
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

void verifierSiMoinsDeLignes(const int ancienNbLignes, const int newNbLignes, int **matrice) {
    //suppression data si moins de lignes
    if (newNbLignes < ancienNbLignes) {
        for (int i = newNbLignes; i < ancienNbLignes; i++) {
            free(matrice[i]);
        }
    }
}

void renseignerNouvellesColonnes(int **matrice, const int ancienNbLignes,
                                 const int newNbColonnes, const int ancienNbColonnes) {
    for (int i = 0; i < ancienNbLignes; ++i) {
        for (int j = ancienNbColonnes; j < newNbColonnes; ++j) {
            matrice[i][j] = randomNumber();
        }
    }
}

void renseignerNouvellesLignes(int **matrice, const int newNbLignes,
                               const int ancienNbLignes, const int newNbColonnes) {
    for (int i = ancienNbLignes; i < newNbLignes; ++i) {
        for (int j = 0; j < newNbColonnes; ++j) {
            matrice[i][j] = randomNumber();
        }
    }
}


int main(const int argc, char const *argv[]) {
    int **matrice;
    srand(time(NULL));

    int nbLignes = saisirNombreLignes();
    verifierValiditeSaisie(nbLignes);

    int nbColonnes = saisirNombreColonnes();
    verifierValiditeSaisie(nbColonnes);

    printf("Construction d'une matrice %dx%d\n", nbLignes, nbColonnes);
    matrice = constructionMatrice(nbLignes, nbColonnes);

    affichageMatrice(matrice, nbLignes, nbColonnes);

    // modification
    int newNbLignes = saisirNombreLignes();
    verifierValiditeSaisie(newNbLignes);

    int newNbColonnes = saisirNombreColonnes();
    verifierValiditeSaisie(newNbColonnes);

    printf("Construction d'une matrice %dx%d\n", newNbLignes, newNbColonnes);
    verifierSiMoinsDeLignes(nbLignes, newNbLignes, matrice);

    matrice = (int **) realloc(matrice, sizeof(int *) * newNbLignes);
    if (matrice == NULL) {
        destructionMatrice(matrice, nbLignes);
        return -1;
    }

    for (int i = 0; i < nbLignes; ++i) {
        matrice[i] = (int *) realloc(matrice[i], sizeof(int) * newNbColonnes);

        if (matrice[i] == NULL) {
            printf("La réallocation a échouée!\n");
            destructionMatrice(matrice, newNbLignes);
            return -1;
        }
    }

    // on alloue de la memoire pour les nouvelles lignes
    // si newNbLignes < nbLignes --> jamais executé
    for (int i = nbLignes; i < newNbLignes; ++i) {
        matrice[i] = (int *) malloc(sizeof(int) * newNbColonnes);

        if (matrice[i] == NULL) {
            printf("L'allocation a échouée!\n");
            destructionMatrice(matrice, newNbLignes);
            return -1;
        }
    }

    renseignerNouvellesColonnes(matrice, nbLignes, newNbColonnes, nbColonnes);
    renseignerNouvellesLignes(matrice, newNbLignes, nbLignes, newNbColonnes);

    affichageMatrice(matrice, newNbLignes, newNbColonnes);
    destructionMatrice(matrice, newNbLignes);

    return 0;
}
