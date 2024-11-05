#include <stdio.h>
#include <stdlib.h>

void plus(const int *a, const int *b, int *c) {
    *c = *a + *b;
}

void moins(const int *a, const int *b, int *c) {
    *c = *a - *b;
}

void fois(const int *a, const int *b, int *c) {
    *c = *a * *b;
}

int main(const int argc, char const *argv[]) {
    int x = 50;
    int y = 20;
    int z = 0;

    plus(&x, &y, &z);
    printf("plus \t: x=%d y=%d z=%d\n", x, y, z);
    moins(&x, &y, &z);
    printf("moins \t: x=%d y=%d z=%d\n", x, y, z);
    fois(&x, &y, &z);
    printf("fois \t: x=%d y=%d z=%d\n", x, y, z);

    return 0;
}
