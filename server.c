#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    while(1){

        int portno; //Numéro de port ou on écoute

        int n; //Val de retour de write and read ie nombre de charactères écrits/lu
        socklen_t clientAddressSize; //Taille de l'adresse du client
        int sockfd, newsockfd; //Entier de retour du socket
        struct sockaddr_in server_address , client_address;
        char buffer[256]; //Buffer de lecture
	char bufferRep[32]; //buffer de réponse

        if (argc < 2) {
                 printf("ERROR, no port provided\n");
                 exit(1);
        }

        sockfd = socket(AF_INET,SOCK_STREAM,0);

        if (sockfd < 0)  {
                printf("ERROR opening socket\n");
        }

        bzero((char *) &server_address, sizeof(server_address)); //Initialise l'adresse du serveur à 0
        portno = atoi(argv[1]); //Transforme le stream de string de l'argument en entier et le passe dans la variable du num de port

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY; //Adresse ip du serveur récupérée avec la constante INADDR_ANY
        server_address.sin_port = htons(portno); //Transforme l'adresse du port en adresse dans le format du réseau

        //Lie le socket au port en lui donnant le descripteur de fichier du socket, l'adresse du serveur et la taille de l'adresse
        bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address));


        listen(sockfd,5); //Ecoute sur le port et permet 5 connections en attente

        clientAddressSize = sizeof(client_address);

        //On accepte une connexion en donnant le socket qui accepte la connexion, l'adresse du client et la taille de l'adresse du client
        newsockfd = accept(sockfd, (struct sockaddr *) &client_address, &clientAddressSize);
        bzero(buffer,256); //Initialise le buffer
        n = read(newsockfd,buffer,255);//Lit le nouveau socket et place le résultat dans le buffer


        int nombreA = buffer[0] | ( (int)buffer[1] << 8 ) | ( (int)buffer[2] << 16 ) | ( (int)buffer[3] << 24 );
        int nombreB = buffer[4] | ( (int)buffer[5] << 8 ) | ( (int)buffer[6] << 16 ) | ( (int)buffer[7] << 24 );
        char op = buffer[8];
        int res;
	printf("%d\n",nombreA);
	printf("%d\n",nombreB);
	printf("%c\n",op);
        if(op == '+') {
            res = nombreA+nombreB;
        }

        else if(op == '-') {
            res = nombreA-nombreB;
        }

        else if(op == '/') {
            res = nombreA/nombreB;
        }
        else{
            printf("%s","erreur\n");
        }


        bufferRep[0]= res & 0xff;
        bufferRep[1]= (res >> 8) & 0xff;
        bufferRep[2]= (res >> 16) & 0xff;
        bufferRep[3]= (res >> 24) & 0xff;
	
        int retourTest = bufferRep[0] | ( (int)bufferRep[1] << 8 ) | ( (int)bufferRep[2] << 16 ) | ( (int)bufferRep[3] << 24 );
        // n = write(newsockfd,buffer,256);
	printf("%d\n",retourTest);

	send(newsockfd,(char*)bufferRep,4, 0);

    }

    return 0;
}
