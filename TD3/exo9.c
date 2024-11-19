#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

char *arguments[] = {NULL};
char *environnement[] = {NULL};


void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

int testerFichierExiste(const char *lien) {
    struct stat statsFichier;
    int exist = stat(lien, &statsFichier);

    return exist == 0;
}

void executerProgramme(const char *programme) {
    if (testerFichierExiste(programme)) {
        char lien[BUFSIZ] = "./";
        strcat(lien, programme);

        printf("Execution de '%s'\n", programme);
        execve(lien, arguments, environnement);
    } else {
        printf("Le fichier '%s' n'existe pas.\n", programme);
    }
}

void creerFils(const int index, const char *programme, int *fils) {
    switch (fils[index] = fork()) {
        case -1:
            erreur("fork");
        case 0:
            executerProgramme(programme);
            exit(EXIT_SUCCESS);
        default:
            break;
    }
}

int main(const int argc, char const *argv[]) {
    int nombreProgrammes = argc - 1;
    int fils[nombreProgrammes];

    for (int i = 0; i < nombreProgrammes; i++) {
        creerFils(i, argv[i + 1], fils);
    }

    // ici le pere
    for (int j = 0; j < nombreProgrammes; j++) {
        waitpid(fils[j], NULL, 0);
    }
    printf("Fin du programme exo9\n");

    return EXIT_SUCCESS;
}
