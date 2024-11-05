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


int main(const int argc, char *argv[]) {
    Coordonnees ici;

    printf("initialisation\n");
    initialiser(&ici);
    afficher(&ici);

    printf("addition\n");
    additionner(&ici);
    afficher(&ici);

    printf("multiplication\n");
    multiplier(&ici);
    afficher(&ici);

    return 0;
}
