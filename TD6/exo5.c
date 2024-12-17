#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_TOUR 9
#define NB_THREADS 10
#define NB_MIN 0
#define NB_SECONDES 8

typedef struct {
    int *tableau;
    double tempsMax;
} Variables;


pthread_mutex_t mutexCompteur;
pthread_mutex_t mutexTableau;
int compteur = 1;

int randomNumber(const int max);
void creerTableau(Variables *structure);
void *fonctionPourThread(void *arg);


int main(const int argc, char const *argv[]) {
    srand(time(NULL));
    Variables donnees;
    // On calcule le moment où la boucle infinie devra s'arrêter (voir plus loin)
    donnees.tempsMax = (double) (time(NULL) + NB_SECONDES);

    creerTableau(&donnees);

    //initialisation des mutex
    pthread_mutex_init(&mutexCompteur, NULL);
    pthread_mutex_init(&mutexTableau, NULL);

    // on crée les threads
    pthread_t *my_thread = malloc(NB_THREADS * sizeof(pthread_t));

    for (int i = 0; i < NB_THREADS; i++) {
        if (pthread_create(&(my_thread[i]), NULL, fonctionPourThread, (void *) &donnees) != 0) {
            printf("erreur\n");
            exit(EXIT_FAILURE);
        }
    }

    // on attend tous les threads
    for (int i = 0; i < NB_THREADS; i++) {
        pthread_join(my_thread[i], NULL);
    }

    free(my_thread);
    my_thread = NULL;

    free(donnees.tableau);
    donnees.tableau = NULL;

    return EXIT_SUCCESS;
}

int randomNumber(const int max) {
    return (rand() % (max - NB_MIN)) + NB_MIN;
}

void creerTableau(Variables *structure) {
    structure->tableau = (int *) malloc(NB_THREADS * sizeof(int));

    if (structure->tableau == NULL) {
        printf("Allocation echouée\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NB_THREADS; i++) {
        structure->tableau[i] = randomNumber(100);
    }
}

void *fonctionPourThread(void *arg) {
    Variables *temp = (Variables *) arg;

    // on met le verrou
    pthread_mutex_lock(&mutexCompteur);
    int numeroThread = compteur;
    compteur++;
    // on enlève le verrou
    pthread_mutex_unlock(&mutexCompteur);

    while (time(NULL) < temp->tempsMax) {
        int numCase = randomNumber(NB_THREADS);

        // on met le verrou
        pthread_mutex_lock(&mutexTableau);
        printf("Thead %d - tableau[%d] = %d \n", numeroThread, numCase, temp->tableau[numCase]);
        // on enlève le verrou
        pthread_mutex_unlock(&mutexTableau);

        sleep(1);
    }

    pthread_exit(NULL);
}
