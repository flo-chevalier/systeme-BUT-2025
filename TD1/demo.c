#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char const *argv[]) {

    int i = 6;
    int *p = &i;

    printf("valeur de i %d\n", i);
    printf("adresse de i %d\n", &i);
    printf("valeur de p %d\n", p);
    printf("adresse de p %d\n", &p);

    printf("valeur de i via p %d\n", *p);

    return 0;
}
