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
    int tubeVersFils[2];
    int tubeVersPere[2];
    char tampon[MAX];

    ouvrirTube(tubeVersFils);
    ouvrirTube(tubeVersPere);

    pid = fork();

    if (pid == -1) {
        erreur("fork");
    } else if (pid == 0) {
        //fils
        close(tubeVersFils[1]);
        close(tubeVersPere[0]);
        printf("Je suis le fils, mon pid = %d\n", getpid());

        read(tubeVersFils[0], tampon, MAX);
        printf("Je suis le fils, j'ai recu : %s\n", tampon);

        sleep(1);
        lireMessage(tampon);

        printf("Je suis le fils, j'envoie %s\n", tampon);
        write(tubeVersPere[1], tampon, strlen(tampon) + 1);

        close(tubeVersFils[0]);
        close(tubeVersPere[1]);

        exit(EXIT_SUCCESS);
    } else {
        //père
        sleep(1);

        close(tubeVersFils[0]);
        close(tubeVersPere[1]);

        lireMessage(tampon);

        write(tubeVersFils[1], tampon, strlen(tampon) + 1);

        read(tubeVersPere[0], tampon, MAX);
        printf("Je suis le père, j'ai recu : %s\n", tampon);

        wait(&pid);

        close(tubeVersFils[1]);
        close(tubeVersPere[0]);
    }

    return EXIT_SUCCESS;
}
