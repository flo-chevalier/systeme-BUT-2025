#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2
#define MAX 10

int compteur = 0;
char programme[BUFSIZ];
char *arguments[] = {NULL};


void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

void saisirProgramme() {
    printf("Saisir le nom d'un programme\n");
    scanf("%s", programme);
}

int testerFichierExiste(const char *lien) {
    struct stat statsFichier;
    int existe = stat(lien, &statsFichier);

    return existe == 0;
}

void executerProgramme() {
    int pid;

    if (testerFichierExiste(programme)) {
        switch (pid = fork()) {
            case -1:
                erreur("fork");
            case 0:
                printf("Execution de '%s'\n", programme);
                execv(programme, arguments);
                exit(EXIT_SUCCESS);
        }
    } else {
        printf("Le fichier '%s' n'existe pas.\n", programme);
    }
}

int main(const int argc, char const *argv[]) {
    while (compteur < MAX) {
        saisirProgramme();

        executerProgramme();
        compteur++;
        wait(NULL);
    }

    printf("Je suis ton père.\nFin du programme exo4\n");
    return EXIT_SUCCESS;
}
