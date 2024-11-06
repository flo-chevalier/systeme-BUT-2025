#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
    int fichier;

    printf("Création du dossier\n");
    if (mkdir("DOSSIER", S_IRWXU) < 0) {
        printf("Erreur création dossier\n");
        return -1;
    }

    sleep(1);

    printf("Création du lien\n");
    if (link("test.txt", "t_link") != 0) {
        printf("Erreur de creation de lien\n");
        return -1;
    }

    sleep(1);

    printf("Suppression du lien\n");
    if (unlink("t_link") != 0) {
        printf("Erreur suppression lien\n");
        return -1;
    }

    printf("Changement de dossier\n");
    if (chdir("DOSSIER") != 0) {
        printf("Erreur changement de dossier\n");
        return -1;
    }

    sleep(1);

    printf("Création du fichier\n");
    if ((fichier = open("test_td2.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) < 0) {
        printf("Erreur création fichier\n");
        return -1;
    }

    sleep(1);

    printf("Suppression du dossier\n");
    system("rm -r ../DOSSIER"); // sinon plus brutal, pas besoin fermer le fichier

    return 0;
}
