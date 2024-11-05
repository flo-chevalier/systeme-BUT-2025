#ifndef SYSTEME_EXO8_H
#define SYSTEME_EXO8_H

#define MIN_NB_MOTS 2
#define MAX_NB_MOTS 20
#define MAX_LONGUEUR_CHAINE 1000

int saisirNombreChaines(char tampon[]);
char **construireTableau(const int taille);
void detruireTableauChaines(char **chaines, const int taille);
void afficherTableauChaines(char **chaines, const int taille);
void saisirChaine(char tampon[], const int numero);
void verifierValiditeTaille(const int taille);

#endif //SYSTEME_EXO8_H
