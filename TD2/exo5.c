#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

int afficherContenuDossier(char const *chemin) {
    DIR *d = opendir(chemin);
    if (d == NULL) {
        printf("Erreur ouverture dossier");
        return -1;
    }

    struct dirent *entree;

    while ((entree = readdir(d)) != NULL) {
        // si ce n'est pas un dossier
        if (entree->d_type != DT_DIR) {
            printf("%s%s\n", BLUE, entree->d_name);
        } else if (entree->d_type == DT_DIR
                   && strcmp(entree->d_name, ".") != 0
                   && strcmp(entree->d_name, "..") != 0) {
            printf("%s%s\n", GREEN, entree->d_name);
        }
    }

    closedir(d);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Le programme attend un argument !\n");
        return -1;
    }

    printf("Lecture du dossier : %s\n", argv[1]);
    printf("%s\n", NORMAL_COLOR);

    if (afficherContenuDossier(argv[1])) {
        return -1;
    }

    printf("%s\n", NORMAL_COLOR);

    return 0;
}
