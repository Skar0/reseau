    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
 
#include <stdio.h>
#include <stdlib.h>
#define PORT 1350
 
 
 
int main( int argc, const char* argv[] )
{


printf("Lacement du client\n %s \n ",argv[0]);
	

char buffer[32]= "dfqsdfdfqsdfqsdfsfs";


    int erreur = 0;

 
    SOCKET sock;
    SOCKADDR_IN sin;
 
    if(!erreur)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);
 
        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr(argv[1]);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 	printf("salut\n");
        /* Si le client arrive à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR){
           
	    printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
	 int nombre1 = atoi(argv[2]);
	 int nombre2 = atoi(argv[3]);

	 buffer[0]= nombre1 & 0xff; //8 bits de poids faibles 
	 buffer[1]= (nombre1 >> 8) & 0xff;
	 buffer[2]= (nombre1 >> 16) & 0xff;
	 buffer[3]= (nombre1 >> 24) & 0xff;//8 bits de poids fort
	
	 buffer[4]= nombre2 & 0xff; //8 bits de poids faibles 
	 buffer[5]= (nombre2 >> 8) & 0xff;
	 buffer[6]= (nombre2 >> 16) & 0xff;
	 buffer[7]= (nombre2 >> 24) & 0xff;//8 bits de poids fort
	
	 printf("%c\n",argv[4][0]);
	 buffer[8] = argv[4][0];
	



	    if(send(sock,(char*)buffer,9, 0)){
		printf("Message envoyer\n");
	    }
            else printf("erreur a envoi \n");
	     /*send(sock,(void*)&d,sizeof(int32_t), 0);*/
	 	
	   read(sock, buffer, 32);


	     int nombreA = buffer[0] | ( (int)buffer[1] << 8 ) | ( (int)buffer[2] << 16 ) | ( (int)buffer[3] << 24 );

	                printf("Recu : %d\n", nombreA);
	}
        else
            printf("Impossible de se connecter\n");
 
        /* On ferme la socket précédemment ouverte */
        closesocket(sock);
 
    }
 
    return EXIT_SUCCESS;
}
