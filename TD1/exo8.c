#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exo8.h"

int main(const int argc, char *argv[]) {
    int i;
    int longueur;
    char tampon[MAX_LONGUEUR_CHAINE];

    int taille = saisirNombreChaines(tampon);
    verifierValiditeTaille(taille);

    char **tableau = construireTableau(taille);

    for (i = 0; i < taille; i++) {
        saisirChaine(tampon, i + 1);

        longueur = strlen(tampon) + 1; // +1 pour le marqueur de fin de chaine \n
        tableau[i] = (char *) malloc(longueur * sizeof(char));
        strcpy(tableau[i], tampon);
    }

    printf("\nVoici le tableau de chaines :\n\n");
    afficherTableauChaines(tableau, taille);

    detruireTableauChaines(tableau, taille);

    return 0;
}


char **construireTableau(const int taille) {
    char **tableau = malloc(taille * sizeof(char *));

    if (tableau == NULL) {
        printf("L'allocation a échouée!\n");
        exit(1);
    }

    return tableau;
}

void detruireTableauChaines(char **chaines, const int taille) {
    for (int i = 0; i < taille; i++) {
        free(chaines[i]);
    }

    free(chaines);
    chaines = NULL;
}

void afficherTableauChaines(char **chaines, const int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d. %s", i + 1, chaines[i]);
    }
}

/** On utilise fgets pour autoriser les espaces dans les chaines. */
void saisirChaine(char tampon[], const int numero) {
    printf("Saisir la chaine %d\n", numero);
    fgets(tampon, MAX_LONGUEUR_CHAINE, stdin);
}

int saisirNombreChaines(char tampon[]) {
    int taille;
    printf("Saisir le nombre de chaines (%d -> %d):\n", MIN_NB_MOTS, MAX_NB_MOTS);
    fgets(tampon, 10, stdin);
    taille = atoi(tampon);
    return taille;
}

void verifierValiditeTaille(const int taille) {
    if (taille > MAX_NB_MOTS) {
        printf("Nombre trop grand. Fin du programme\n");
        exit(1);
    }

    if (taille < MIN_NB_MOTS) {
        printf("Nombre trop petit. Fin du programme\n");
        exit(1);
    }
}
