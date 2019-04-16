#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#define MAX_MSG 100
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 3787


 main ( ) {

  int sd, newSd, cliLen, n,num1,num2,num3,sum, nome, cargo, salario,novosalario,idade;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG],line1[MAX_MSG],line2[MAX_MSG];


  /**********************************/ 
  /* estrutura de conexão */
  /**********************************/ 

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  servAddr.sin_port = htons(SERVER_PORT);

  /************************/ 
  /* criando sockets */
  /************************/ 

  sd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket criado com sucesso. \n");

  /**************************/ 
  /* vinculando portas */
  /**************************/ 

  bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  printf("Porta ok. \n");


  /********************************/ 
  /* numero de clientes que podem */
  /* se conectar..........        */
  /********************************/ 

  listen(sd,5);


  while(1) {

    printf("Esperando o cliente conectar na porta TCP %u\n",SERVER_PORT);

    /*****************************/
    /* esperando cliente....     */
    /*****************************/   

    cliLen = sizeof(cliAddr);
    newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);

    printf("Conectado! Detalhes: [IP %s ,TCP port %d]\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    /*****************************/
    /* esperando dados do cliente*/
    /*****************************/     

    do{
//      memset(line,0x0,MAX_MSG);

      n=recv(newSd, line, MAX_MSG, 0);
      idade=atoi(line);

      sprintf(line1,"%d",idade);

	if (idade > 5 && idade < 7) {

      printf("\n Recebido [IP %s ,TCP port %d] : %s, NADADOR INFANTIL A. \n.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	} else if (idade > 8 && idade < 10) {

      printf("\n Recebido [IP %s ,TCP port %d] : %s, NADADOR INFANTIL B. \n.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	} else if (idade > 11 && idade < 13) {

      printf("\n Recebido [IP %s ,TCP port %d] : %s, NADADOR JUVENIL A. \n.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	} else if (idade > 14 && idade < 17) {

      printf("\n Recebido [IP %s ,TCP port %d] : %s, NADADOR JUVENIL B. \n.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	} else if (idade > 18) {

      printf("\n Recebido [IP %s ,TCP port %d] : %s, NADADOR ADULTO! \n.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	}




    } while(abs(strcmp(line, "quit")));


    /**************************/
    /* fechando conexão.......*/
    /**************************/   

    printf("conexão terminada com host [IP %s ,TCP port %d]\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    close(newSd);
  }
}
