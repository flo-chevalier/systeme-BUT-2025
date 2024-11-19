#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void tuerFils(const int pid) {
    printf("On tue le fils %d\n", pid);
    kill(pid, 9);
}

void tuerLesFils(const int fils[], const int nombre) {
    for (int i = 0; i < nombre; ++i) {
        tuerFils(fils[i]);
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("On attend 1 argument\n");
        exit(EXIT_FAILURE);
    }

    int nombre = atoi(argv[1]);
    int fils[nombre];

    for (int i = 0; i < nombre; i++) {
        switch (fils[i] = fork()) {
            case -1:
                printf("Erreur fork. Arret du programme.\n");
                exit(EXIT_FAILURE);
            case 0:
                while (1) {
                    printf("Le fils %d (%d), j'attends\n", i + 1, getpid());
                    sleep(1);
                }
        }
    }

    sleep(4);

    // on teste si on est le père, normalement pas besoin
    if (fils[0] != 0) {
        tuerLesFils(fils, nombre);
    }

    for (int j = 0; j < nombre; ++j) {
        waitpid(fils[j], NULL, 0);
    }

    printf("Je suis le père. Fin du programme\n");

    return EXIT_SUCCESS;
}
