#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NB 10

typedef struct {
    int tableau[NB];
} Variables;

void initialiserTableau(int tab[]);
void *afficherTableau(void *arg);

int main(const int argc, char const *argv[]) {
    Variables donnees;
    pthread_t monThread;

    printf("Initialisation du tableau\n");
    initialiserTableau(donnees.tableau);

    if (pthread_create(&monThread, NULL, afficherTableau, &donnees) != 0) {
        printf("erreur de creation de thread\n");
        return EXIT_FAILURE;
    }

    printf("Creation du thread -> ok\n");
    pthread_join(monThread, NULL);

    return EXIT_SUCCESS;
}

void initialiserTableau(int tab[]) {
    for (int i = 0; i < NB; i++) {
        tab[i] = i * i;
    }
}

void *afficherTableau(void *arg) {
    Variables *structure = (Variables *) arg;
    printf("Je suis un thread et voici les valeurs de tableau :\n");

    for (int i = 0; i < NB; i++) {
        printf("%d\n", structure->tableau[i]);
    }

    pthread_exit(NULL);
}
