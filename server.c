#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
while(1){
printf("\t ** salut c'est cool ** \n ");

int portno; //Numéro de port ou on écoute
int n; //Val de retour de write and read ie nombre de charactères écrits/lu
socklen_t clientAddressSize; //Taille de l'adresse du client
int sockfd, newsockfd; //entier de retour du socket
struct sockaddr_in server_address , client_address;
char buffer[256]; //buffer de lecture


if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
}

sockfd = socket(AF_INET,SOCK_STREAM,0);

 if (sockfd < 0) 
        error("ERROR opening socket");

bzero((char *) &server_address, sizeof(server_address)); //Initialise l'adresse du serveur à 0 (le buffer)
portno = atoi(argv[1]); //Transforme le stream de string de l'argument en entier et le passe dans la variable du num de port

server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = INADDR_ANY; //Adresse ip du serveur récupérée avec la constante INADDR_ANY
server_address.sin_port = htons(portno); //Transforme l'adresse du port en adress du network

//Lier le socket au port en lui donnant le descripteur de fichier du socket, l'adresse du serveur et la taille de l'adresse
int test =0;

bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address));


listen(sockfd,5); //Ecoute sur le port et permet 5 connections en attente

clientAddressSize = sizeof(client_address);

newsockfd = accept(sockfd, (struct sockaddr *) &client_address, &clientAddressSize); //On accepte une connetion en donnant le socket qui accepte la connection, l'adresse du client et la taille de l'adresse du client

bzero(buffer,256); //Initialise le buffer
n = read(newsockfd,buffer,255);//Lit le nouveau socket et place le résultat dans le buffer

 
int nombreA = buffer[0] | ( (int)buffer[1] << 8 ) | ( (int)buffer[2] << 16 ) | ( (int)buffer[3] << 24 );
int nombreB = buffer[4] | ( (int)buffer[5] << 8 ) | ( (int)buffer[6] << 16 ) | ( (int)buffer[7] << 24 );
char op = buffer[8];
int res;

if(op == '+') {
	res = nombreA+nombreB;
	close(newsockfd);
}

else if(op == '-') {
	res = nombreA-nombreB;
	close(newsockfd);
}

else if(op == '/') {
	res = nombreA/nombreB;
	close(newsockfd);
}
else{
	printf("%s","erreur");
}

int nombre1 = res;
buffer[0]= nombre1 & 0xff; 
buffer[1]= (nombre1 >> 8) & 0xff;
buffer[2]= (nombre1 >> 16) & 0xff;
buffer[3]= (nombre1 >> 24) & 0xff;

n = write(newsockfd,buffer,256);

}

return 0;
}
