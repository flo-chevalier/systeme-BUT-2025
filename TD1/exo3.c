#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int z;
} Coordonnees;

void afficher(Coordonnees *c) {
    printf("x=%d y=%d z=%d\n", c->x, c->y, c->z);
}

void initialiser(Coordonnees *c) {
    c->x = 10;
    c->y = 5;
    c->z = 2;
}

void additionner(Coordonnees *c) {
    c->z = c->x + c->y;
}

void multiplier(Coordonnees *c) {
    c->z = c->x * c->y;
}

void initialiserEtAfficher(Coordonnees *c) {
    initialiser(c);
    afficher(c);
}

void additionnerEtAfficher(Coordonnees *c) {
    additionner(c);
    afficher(c);
}

void multiplierEtAfficher(Coordonnees *c) {
    multiplier(c);
    afficher(c);
}


int main(const int argc, char *argv[]) {
    Coordonnees ici;

    printf("initialisation\n");
    initialiserEtAfficher(&ici);

    printf("addition\n");
    additionnerEtAfficher(&ici);

    printf("multiplication\n");
    multiplierEtAfficher(&ici);

    return 0;
}
