#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

int main(const int argc, char const *argv[]) {
    int fils1;
    int fils2;

    char *programme1 = "exo3a.prog";
    char *programme2 = "exo3b.prog";
    char *arguments[] = {NULL};

    switch (fils1 = fork()) {
        case -1:
            erreur("fork fils1");
        case 0:
            printf("Je suis le fils 1\n");
            execv(programme1, arguments);
            exit(EXIT_SUCCESS); // normalement pas besoin, si on revient ici c'est que execv s'est mal passé
    }

    switch (fils2 = fork()) {
        case -1:
            erreur("fork fils2");
        case 0:
            printf("Je suis le fils 2\n");
            execv(programme2, arguments);
            // normalement rien n'est executé après execv
            exit(EXIT_SUCCESS); // on kill
    }

    // ici le pere
    wait(&fils1);
    wait(&fils2);
    printf("Fin du programme exo3\n");

    return EXIT_SUCCESS;
}
