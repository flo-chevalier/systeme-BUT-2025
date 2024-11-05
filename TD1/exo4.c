#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_MIN 1
#define NB_MAX 100
#define TAILLE_MIN 1
#define TAILLE_MAX 1000

int randomNumber() {
    return (rand() % (NB_MAX - NB_MIN)) + NB_MIN;
}

int saisirTailleTableau() {
    int taille = 0;
    printf("Saisir la taille du tableau (1 -> 1000) :\n");
    scanf("%d", &taille);

    return taille;
}

void verifierTailleTableau(const int taille) {
    if (taille < TAILLE_MIN) {
        printf("Nombre trop petit. Fin du programe\n");
        exit(1);
    }

    if (taille > TAILLE_MAX) {
        printf("Nombre trop grand. Fin du programe\n");
        exit(1);
    }
}

int *construireTableau(const int taille) {
    int *tab = (int*) malloc(taille * sizeof(int));

    if (tab == NULL) {
        printf("Allocation échouée\n");
        exit(1);
    }

    for (int i = 0; i < taille; ++i) {
        tab[i] = randomNumber();
    }

    return tab;
}

void afficherTableau(int *tab, const int taille) {
    printf("Affichage\n");

    for (int i = 0; i < taille; ++i) {
        printf("[%d] = %d\n", i, tab[i]);
    }
}

void detruireTableau(int *tab) {
    free(tab);
    tab = NULL;
}


int main(const int argc, const char *argv[]) {
    srand(time(NULL));

    int tailleTableau = saisirTailleTableau();
    verifierTailleTableau(tailleTableau);

    printf("Construction d'un tableau de taille %d\n", tailleTableau);
    int *tableau = construireTableau(tailleTableau);
    afficherTableau(tableau, tailleTableau);
    detruireTableau(tableau);

    return 0;
}
