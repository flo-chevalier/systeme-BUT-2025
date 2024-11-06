#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 1000
#define TRUE 1
#define FALSE 0

int choix;
int continuer = TRUE;
char buffer[MAX];
char courant[PATH_MAX];
struct stat statut = {0};

void scannerChaine();
int afficherMenu();
int afficherDossierCourant();
void afficherAction();
int executerAction();
void saisirChoix();
void saisirNomDossier();
void saisirNomFichier();
void saisirCheminDestination();
int creerDossier();
int creerFichier();
int changerDossier();


int main(int argc, char const *argv[]) {
    while (continuer) {
        if (afficherMenu() < 0) {
            printf("Fin programme.\n");
            return -1;
        };

        saisirChoix();
        afficherAction();

        if (continuer) {
            if (executerAction() < 0) {
                printf("Fin programme.\n");
                return -1;
            }
        }
    }

    return 0;
}

int afficherMenu() {
    printf("\nChoisir son action :\n");
    printf("1. Changer de dossier\n");
    printf("2. Créer un dossier\n");
    printf("3. Créer un fichier\n");
    printf("0. Quitter\n\n");

    return afficherDossierCourant();
}

int afficherDossierCourant() {
    if (getcwd(courant, sizeof(courant)) != NULL) {
        printf("Vous êtes içi : %s\n", courant);
    } else {
        printf("Erreur fonction getcwd()\n");
        return -1;
    }
    return 0;
}

void afficherAction() {
    switch (choix) {
        case 1:
            saisirCheminDestination();
            break;
        case 2:
            saisirNomDossier();
            break;
        case 3:
            saisirNomFichier();
            break;
        default:
            continuer = FALSE;
    }
}

int executerAction() {
    switch (choix) {
        case 1:
            return changerDossier();
        case 2:
            return creerDossier();
        case 3:
            return creerFichier();
        default:
            continuer = FALSE;
    }
}

void saisirChoix() {
    scanf("%d", &choix);
}

void saisirCheminDestination() {
    printf("Saisir le chemin\n");
    scannerChaine();
}

void saisirNomDossier() {
    printf("Saisir le nom du nouveau dossier\n");
    scannerChaine();
}

void saisirNomFichier() {
    printf("Saisir le nom du nouveau fichier\n");
    scannerChaine();
}

void scannerChaine() {
    scanf("%s", buffer);
}

int creerDossier() {
    // on teste si le dossier n'existe pas
    if (stat(buffer, &statut) == -1) {
        printf("Création du dossier : %s\n", buffer);
        if (mkdir(buffer, S_IRWXU) < 0) {
            printf("Erreur création dossier\n");
            return -1;
        }
    } else {
        printf("Le dossier %s existe déjà.\n", buffer);
    }
}

int creerFichier() {
    printf("Création du fichier : %s\n", buffer);
    if (open(buffer, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR) < 0) {
        printf("Erreur création fichier\n");
        return -1;
    }
}

int changerDossier() {
    printf("Changement de dossier vers : %s\n", buffer);
    if (chdir(buffer) != 0) {
        printf("Erreur changement de dossier\n");
        return -1;
    }
}
