#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

int main(const int argc, char const *argv[]) {
    int i;
    int pid[N];

    for (i = 0; i < N; i++) {
        switch (pid[i] = fork()) {
            case -1:
                erreur("fork");
            case 0:
                printf("Je suis un fils : %d\n", getpid());
                printf("Mon père est : %d\n\n", getppid());
                exit(EXIT_SUCCESS); // on kill les fils
            default:
                //ici le pere
                break;
        }
    }

    // à partir d'ici il ne reste que le père
    for (int j = 0; j < N; ++j) {
        waitpid(pid[j], NULL, 0);
    }

    printf("Je suis ton père !\n");
    printf("Tout va bien\n");

    return EXIT_SUCCESS;
}
