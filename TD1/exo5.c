#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_MIN 0
#define NB_MAX 100
#define TAILLE_MIN 1
#define TAILLE_MAX 1000

int randomNumber() {
    return (rand() % (NB_MAX - NB_MIN)) + NB_MIN;
}

int *constructionTableau(const int taille) {
    int *tableau = (int *) malloc(taille * sizeof(int));

    if (tableau == NULL) {
        printf("Allocation echouée\n");
        exit(1);
    }

    for (int i = 0; i < taille; i++) {
        tableau[i] = randomNumber();
    }

    return tableau;
}

void destructionTableau(int *chiffres) {
    free(chiffres);
    chiffres = NULL;
}

void afficherTableau(int *chiffres, const int taille) {
    printf("Affichage\n");

    for (int i = 0; i < taille; i++) {
        printf("[%d] : %d\n", i, chiffres[i]);
    }
}

int saisirTailleTableau() {
    int taille = 0;
    printf("Saisir la taille du tableau (1 -> 1000) :\n");
    scanf("%d", &taille);

    return taille;
}

void verifierValiditeSaisie(const int nombre) {
    if (nombre > TAILLE_MAX) {
        printf("Nombre trop grand. Fin du programme\n");
        exit(1);
    }

    if (nombre < TAILLE_MIN) {
        printf("Nombre trop petit. Fin du programme\n");
        exit(1);
    }
}

void modifierTailleTableau(int *chiffres, const int nouvelleTaille, const int ancienneTaille) {
    int *nouveau = realloc(chiffres, nouvelleTaille * sizeof(int));

    if (nouveau == NULL) {
        printf("La réallocation a échouée!\n");
        free(nouveau);

        exit(1);
    }

    // si la nouvelle taille est plus grande, on génère des nombres pour les nouvelles cases
    if (nouvelleTaille > ancienneTaille) {
        for (int i = ancienneTaille; i < nouvelleTaille; i++) {
            nouveau[i] = randomNumber();
        }
    }

    chiffres = nouveau;
}


int main(const int argc, char *argv[]) {
    srand(time(NULL)); //initialise le générateur aléatoire
 
    int tailleTableau = saisirTailleTableau();
    verifierValiditeSaisie(tailleTableau);

    printf("Construction d'un tableau de taille %d\n", tailleTableau);
    int *tableau = constructionTableau(tailleTableau);
    afficherTableau(tableau, tailleTableau);

    int nouvelleTailleTableau = saisirTailleTableau();
    verifierValiditeSaisie(nouvelleTailleTableau);

    printf("Nouvelle taille du tableau %d\n", nouvelleTailleTableau);
    modifierTailleTableau(tableau, nouvelleTailleTableau, tailleTableau);

    afficherTableau(tableau, nouvelleTailleTableau);
    destructionTableau(tableau);

    return 0;
}
