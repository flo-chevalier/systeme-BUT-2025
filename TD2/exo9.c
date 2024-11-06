#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 1000
#define TRUE 1
#define FALSE 0

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

const char *CD = "cd";
const char *EXIT = "exit";
const char *LS = "ls";
const char *MKDIR = "mkdir";
const char *RM = "rm";
const char *RMDIR = "rmdir";
const char *TOUCH = "touch";

int continuer = TRUE;
char commande[MAX];
char courant[PATH_MAX];
char *token1;
char *token2;
struct stat statut = {0};

void scannerChaine();
int afficherDossierCourant();
int executerAction();
int afficherContenuDossier();
int creerDossier();
int creerFichier();
int changerDossier();
int effacerFichier();
int effacerDossier();
int argumentPresent();


int main(int argc, char const *argv[]) {
    printf("Début du simulateur de terminal.\n\n");

    char buffer[MAX];

    while (continuer) {
        if (afficherDossierCourant() < 0) {
            printf("Fin programme.\n");
            return -1;
        };

        scannerChaine();
        token1 = strtok(commande, " \n");
        token2 = strtok(NULL, " \n");

        if (executerAction() < 0) {
            printf("Fin programme.\n");
            return -1;
        }
    }

    printf("Fin du simulateur de terminal.\n");

    return 0;
}

int afficherDossierCourant() {
    if (getcwd(courant, sizeof(courant)) != NULL) {
        printf("user@desktop:%s$ ", courant);
    } else {
        printf("Erreur fonction getcwd()\n");
        return -1;
    }
    return 0;
}

int executerAction() {
    if (strcmp(token1, EXIT) == 0) {
        continuer = FALSE;
    } else if (strcmp(token1, CD) == 0) {
        return changerDossier();
    } else if (strcmp(token1, LS) == 0) {
        return afficherContenuDossier();
    } else if (strcmp(token1, MKDIR) == 0) {
        return creerDossier();
    } else if (strcmp(token1, RM) == 0) {
        return effacerFichier();
    } else if (strcmp(token1, RMDIR) == 0) {
        return effacerDossier();
    } else if (strcmp(token1, TOUCH) == 0) {
        return creerFichier();
    } else {
        printf("commande inconnue\n");
    }

    return 0;
}

void scannerChaine() {
    fgets(commande, MAX, stdin);
}

int creerDossier() {
    if (!argumentPresent()) {
        return 0;
    }

    // on teste si le dossier n'existe pas
    if (stat(token2, &statut) == -1) {
        printf("Création du dossier : %s\n", token2);
        if (mkdir(token2, S_IRWXU) < 0) {
            printf("Erreur création dossier\n");
            return -1;
        }
    } else {
        printf("Le dossier %s existe déjà.\n", commande);
    }
}

int creerFichier() {
    if (!argumentPresent()) {
        return 0;
    }

    printf("Création du fichier : %s\n", token2);
    if (open(token2, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR) < 0) {
        printf("Erreur création fichier\n");
        return -1;
    }
}

int changerDossier() {
    if (!argumentPresent()) {
        return 0;
    }

    printf("Changement de dossier vers : %s\n", token2);
    if (chdir(token2) != 0) {
        printf("Erreur changement de dossier\n");
        return -1;
    }
}

int effacerFichier() {
    if (!argumentPresent()) {
        return 0;
    }

    printf("Suppression du fichier %s\n", token2);
    if (unlink(token2) != 0) {
        printf("Erreur suppression fichier\n");
        return -1;
    }
}

int effacerDossier() {
    if (!argumentPresent()) {
        return 0;
    }

    char temp[MAX];
    printf("Suppression du dossier %s\n", token2);

    strcpy(temp, "rm -r ");
    strcat(temp, token2);

    if (system(temp) < 0) {
        return -1;
    }
}

int afficherContenuDossier() {
    DIR *d = opendir(courant);
    if (d == NULL) {
        printf("Erreur ouverture dossier");
        return -1;
    }

    struct dirent *dossier;
    printf("%s\n", NORMAL_COLOR);

    while ((dossier = readdir(d)) != NULL) {
        // si ce n'est pas un dossier
        if (dossier->d_type != DT_DIR) {
            printf("%s%s\n", BLUE, dossier->d_name);
        } else if (dossier->d_type == DT_DIR
                   && strcmp(dossier->d_name, ".") != 0
                   && strcmp(dossier->d_name, "..") != 0) {
            printf("%s%s\n", GREEN, dossier->d_name);
        }
    }

    closedir(d);
    printf("%s\n", NORMAL_COLOR);
}

int argumentPresent() {
    if (token2 == NULL) {
        printf("Erreur : argument manquant\n");
        return FALSE;
    }

    return TRUE;
}
