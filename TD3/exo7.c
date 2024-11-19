#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX 100

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

void lireMessage(char tampon[]) {
    printf("Saisir un message à envoyer :\n");
    fgets(tampon, MAX, stdin);
}

void ouvrirTube(int tube[]) {
    if (pipe(tube) == -1) {
        erreur("ouverture tube");
    }
}

int main(int argc, char const *argv[]) {
    int pid;
    int tube[2];
    char tampon[MAX];

    ouvrirTube(tube);

    pid = fork();

    if (pid == -1) {
        erreur("fork");
    } else if (pid == 0) {
        //fils
        printf("Je suis le fils, mon pid = %d\n", getpid());

        read(tube[0], tampon, MAX);
        printf("Je suis le fils, j'ai recu : %s\n", tampon);

        close(tube[0]);
        close(tube[1]);

        exit(EXIT_SUCCESS);
    } else {
        //père
        sleep(1);

        lireMessage(tampon);

        write(tube[1], tampon, strlen(tampon) + 1);
        wait(&pid);

        close(tube[0]);
        close(tube[1]);
    }

    return EXIT_SUCCESS;
}
