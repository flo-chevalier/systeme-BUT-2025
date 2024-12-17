#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 6
#define NB_MIN 1
#define NB_MAX 5

typedef struct {
    int *tab;
    int nb;
} Variables;


int randomNumber();
void saisirTailleTableau(Variables *structure);
void creerTableau(Variables *structure);
void *afficherTableau(void *arg);
void *initialiserTableau(void *arg);

int main(const int argc, char const *argv[]) {
    Variables donnees;
    pthread_t thread1;
    pthread_t thread2;

    saisirTailleTableau(&donnees);
    printf("Création d'un tableau de %d\n", donnees.nb);
    creerTableau(&donnees);

    if (pthread_create(&thread1, NULL, initialiserTableau, &donnees) != 0) {
        printf("erreur de creation du thread 1\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&thread2, NULL, afficherTableau, &donnees) != 0) {
        printf("erreur de creation du thread 2\n");
        return EXIT_FAILURE;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    free(donnees.tab);
    donnees.tab = NULL;

    return EXIT_SUCCESS;
}

int randomNumber() {
    return rand() % (NB_MAX - NB_MIN) + NB_MIN;
}

void saisirTailleTableau(Variables *structure) {
    printf("Saisir la taille du tableau :\n");
    scanf("%d", &(structure->nb));
}

void creerTableau(Variables *structure) {
    structure->tab = (int *) malloc(structure->nb * sizeof(int));

    if (structure->tab == NULL) {
        printf("Allocation echouée\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->nb; i++) {
        structure->tab[i] = 0;
    }
}

void *initialiserTableau(void *arg) {
    Variables *temp = (Variables *) arg;
    srand(time(NULL)); // initialisation de rand

    for (int i = 0; i < temp->nb; i++) {
        temp->tab[i] = randomNumber();
        printf("\nThread initialisation - init de la case %d\n", i);
        sleep(1);
    }

    pthread_exit(NULL);
}

void *afficherTableau(void *arg) {
    int compteur = 0;
    Variables *temp = (Variables *) arg;

    while (compteur < MAX) {
        printf("\nThread affichage - Tour %d\n", compteur + 1);
        for (int i = 0; i < temp->nb; i++) {
            printf("case %d = %d\n", i, temp->tab[i]);
        }

        compteur++;
        sleep(2);
    }

    pthread_exit(NULL);
}
