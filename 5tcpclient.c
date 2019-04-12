#include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <netdb.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>
 #include <strings.h>

#define MAX_MSG 100
 #define SERVER_ADDR "127.0.0.1"
 #define CLIENT_ADDR "127.0.0.1"
 #define SERVER_PORT 3787
 #define CLIENT_PORT 8229

main () {

 int sd, rc, i,n;
 struct sockaddr_in clientAddr, servAddr;
 char line[MAX_MSG];

/**********************************/
 /* build server address structure */
 /**********************************/

bzero((char *)&servAddr, sizeof(servAddr));
 servAddr.sin_family = AF_INET;
 servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
 servAddr.sin_port = htons(SERVER_PORT);

bzero((char *)&clientAddr, sizeof(clientAddr));
 clientAddr.sin_family = AF_INET;
 clientAddr.sin_addr.s_addr = INADDR_ANY;
 clientAddr.sin_port = htons(0);

/************************/
 /* create stream socket */
 /************************/

sd = socket(AF_INET, SOCK_STREAM, 0);
 printf("Socket criado com sucesso. \n");

/**************************/
 /* bind local port number */
 /**************************/

bind(sd, (struct sockaddr *) &clientAddr, sizeof(clientAddr));
 printf("Porta ok. \n");

/*********************/
 /* connect to server */
 /*********************/

connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
 printf("Conectado com o Servidor! \n");

/***********************/
 /* send data to server */
 /***********************/

do{
 printf("Coloque a idade do NADADOR: ");
 scanf("%s", line);
 send(sd, line, strlen(line) + 1, 0);
 printf("idade enviada (%s)\n", line);

 n=recv(sd, line, MAX_MSG, 0);
 printf("Idade enviada: %s\n", line);
 }while(strcmp(line, "quit"));

 printf("conexão fechada... obrigado.\n");
 close(sd);
 }
