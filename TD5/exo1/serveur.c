#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 6000
#define MAX_BUFFER 1000


int ouvrirUneSocketAttente() {
    struct sockaddr_in coordonneesServeur;

    const int socketTemp = socket(PF_INET, SOCK_STREAM, 0);

    if (socketTemp < 0) {
        printf("socket incorrecte\n");
        exit(EXIT_FAILURE);
    }

    // On prépare l’adresse d’attachement locale
    const int longueurAdresse = sizeof(struct sockaddr_in);
    memset(&coordonneesServeur, 0x00, longueurAdresse);

    // connexion de type TCP
    coordonneesServeur.sin_family = PF_INET;
    // toutes les interfaces locales disponibles
    coordonneesServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    // le port d'écoute
    coordonneesServeur.sin_port = htons(PORT);

    if (bind(socketTemp, (struct sockaddr *) &coordonneesServeur, sizeof(coordonneesServeur)) == -1) {
        printf("erreur de bind\n");
        exit(EXIT_FAILURE);
    }

    if (listen(socketTemp, 5) == -1) {
        printf("erreur de listen\n");
        exit(EXIT_FAILURE);
    }

    printf("En attente de connexion...\n");

    return socketTemp;
}


int main(int argc, char const *argv[]) {
    int fdSocketCommunication;
    struct sockaddr_in coordonneesAppelant;
    char tampon[MAX_BUFFER];

    const int fdSocketAttente = ouvrirUneSocketAttente();

    socklen_t tailleCoord = sizeof(coordonneesAppelant);

    if ((fdSocketCommunication = accept(fdSocketAttente, (struct sockaddr *) &coordonneesAppelant,
                                        &tailleCoord)) == -1) {
        printf("erreur de accept\n");
        exit(EXIT_FAILURE);
    }

    printf("Client connecté\n");

    // on attend le message du client
    // la fonction recv est bloquante
    int nbRecu = recv(fdSocketCommunication, tampon, MAX_BUFFER, 0);

    if (nbRecu > 0) {
        tampon[nbRecu] = 0;
        printf("Recu : %s\n", tampon);
    }

    printf("Envoi du message au client.\n");
    strcpy(tampon, "Message renvoyé par le serveur vers le client !");
    // on envoie le message au client
    send(fdSocketCommunication, tampon, strlen(tampon), 0);

    close(fdSocketCommunication);
    close(fdSocketAttente);

    return EXIT_SUCCESS;
}
