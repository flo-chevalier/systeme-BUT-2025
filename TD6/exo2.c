#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int valeur;
} Variables;

void *ajouter4Thread1(void *arg);
void *diviser2Thread2(void *arg);
void *multiplier4Thread3(void *arg);
void *soustraire5Thread4(void *arg);
void afficherValeur(const int valeur);
void ecrireDansFichierDeLog(const int valeur);

FILE *fichierDeLog;

int main(const int argc, char const *argv[]) {
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    Variables donnee;

    printf("Début du programme\nInitialisation de la valeur à 10\n\n");
    donnee.valeur = 10;

    if (pthread_create(&thread1, NULL, ajouter4Thread1, &donnee) != 0) {
        printf("erreur de creation de thread 1\n");
        return -1;
    }

    printf("Creation de thread1 ok\n");

    if (pthread_create(&thread2, NULL, diviser2Thread2, &donnee) != 0) {
        printf("erreur de creation de thread 2\n");
        return -1;
    }

    printf("Creation de thread2 ok\n");

    if (pthread_create(&thread3, NULL, multiplier4Thread3, &donnee) != 0) {
        printf("erreur de creation de thread 3\n");
        return -1;
    }

    printf("Creation de thread3 ok\n");

    if (pthread_create(&thread4, NULL, soustraire5Thread4, &donnee) != 0) {
        printf("erreur de creation de thread 4\n");
        return -1;
    }

    printf("Creation de thread4 ok\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    ecrireDansFichierDeLog(donnee.valeur);

    printf("\nFin du programme\nLa valeur est à %d\n", donnee.valeur);

    return EXIT_SUCCESS;
}


void *ajouter4Thread1(void *arg) {
    Variables *temp = (Variables *) arg;
    printf("Je suis le thread1 - valeur = %d\n", temp->valeur);
    (temp->valeur) += 4;
    afficherValeur(temp->valeur);

    pthread_exit(NULL);
}

void *diviser2Thread2(void *arg) {
    Variables *temp = (Variables *) arg;
    printf("Je suis le thread2 - valeur = %d\n", temp->valeur);
    (temp->valeur) /= 2;
    afficherValeur(temp->valeur);

    pthread_exit(NULL);
}

void *multiplier4Thread3(void *arg) {
    Variables *temp = (Variables *) arg;
    printf("Je suis le thread3 - valeur = %d\n", temp->valeur);
    (temp->valeur) *= 4;
    afficherValeur(temp->valeur);

    pthread_exit(NULL);
}

void *soustraire5Thread4(void *arg) {
    Variables *temp = (Variables *) arg;
    printf("Je suis le thread4 - valeur = %d\n", temp->valeur);
    (temp->valeur) -= 5;
    afficherValeur(temp->valeur);

    pthread_exit(NULL);
}

void afficherValeur(const int valeur) {
    printf("La valeur vaut maintenant : %d\n", valeur);
}

void ecrireDansFichierDeLog(const int valeur) {
    fichierDeLog = fopen("./log2.txt", "a");
    fprintf(fichierDeLog, "%d\n", valeur);
    fclose(fichierDeLog);
}
