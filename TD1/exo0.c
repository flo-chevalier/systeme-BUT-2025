#include <stdio.h>

int main(const int argc, char *argv[] ){
    // argc : nombre d’arguments
    // argv : le tableau contenant la valeur des arguments
    int a = 1 ;
    printf(" le chiffre est %d \n ", a);

    char clavier[100];
    printf(" Saisissez le texte : \n");
    scanf("%s", clavier);
    printf("vous avez saisie : %s \n", clavier);

    printf("\nMainenant, on va lister tous les arguments (argv)\n");
    int i;
    for (i = 0; i < argc; i++){
        printf("%s \n", argv[i]);
    }

    return 0;
}
