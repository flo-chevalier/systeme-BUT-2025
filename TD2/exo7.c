#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX 1000

char buffer[MAX];
struct stat statut = {0};

void saisirNomDossier();
int creerDossier();


int main(int argc, char const *argv[]) {
    while (1) {
        saisirNomDossier();

        if (creerDossier() < 0) {
            return -1;
        }
    }
    return 0;
}

void saisirNomDossier() {
    printf("Saisir le nom d'un dossier\n");
    scanf("%s", buffer);
}

int creerDossier() {
    // on teste si le dossier n'existe pas
    if (stat(buffer, &statut) == -1) {
        printf("Création du dossier : %s\n", buffer);
        if (mkdir(buffer, 0777) < 0) {
            printf("Erreur création dossier\n");
            return -1;
        }
    } else {
        printf("Le dossier %s existe déjà.\n", buffer);
    }
}
