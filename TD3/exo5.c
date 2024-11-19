#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void capturerSignal(const int sig) {
    printf("signal %d reçu\n", sig);
}

int main(int argc, char const *argv[]) {
    printf("Voici mon pid : %d\n", getpid());

    for (int i = 1; i < NSIG; ++i) {
        if (signal(i, capturerSignal) == SIG_ERR) {
            printf("Erreur attente signal %d\n", i);
        }
    }

    while (1);

    return EXIT_SUCCESS;
}
