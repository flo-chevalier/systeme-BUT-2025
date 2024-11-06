#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TAILLE 10
#define DECALAGE 15

int main(int argc, char const *argv[]) {
    int fichier;
    int offset;
    char buffer[TAILLE + 1];

    if (argc != 2) {
        printf("Le programme attend 1 argument !\n");
        return -1;
    }

    printf("Ouverture fichier : %s\n", argv[1]);
    if ((fichier = open(argv[1], O_RDONLY)) < 0) {
        printf("Erreur ouverture fichier\n");
        return -1;
    }

    if ((offset = lseek(fichier, DECALAGE, SEEK_SET)) != DECALAGE) {
        printf("Erreur dans le déplacement\n");
        return -1;
    }

    if (read(fichier, buffer, TAILLE) < 0) {
        printf("Erreur lecture fichier\n");
        close(fichier);

        return -1;
    }

    printf("Le programme a lu : %s\n", buffer);

    close(fichier);

    return 0;
}
