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

  int sd, newSd, cliLen, n,num1,num2,num3,sum, nome, cargo, salario,novosalario;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG],line1[MAX_MSG],line2[MAX_MSG];


  /**********************************/ 
  /* montando estrutura dos acessos */
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
  /* vinculando portas  */
  /**************************/ 

  bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  printf("Porta ok. \n");


  /********************************/ 
  /* numero de clientes conectados */
  /********************************/ 

  listen(sd,5);


  while(1) {

    printf("Esperando o cliente conectar na porta TCP %u\n",SERVER_PORT);

    /*****************************/
    /* esperando o cliente.......*/
    /*****************************/   

    cliLen = sizeof(cliAddr);
    newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);

    printf("Conectado! Detalhes: [IP %s ,TCP port %d]\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    /*****************************/
    /* esperando dados do cliente */
    /*****************************/     

    do{
      memset(line,0x0,MAX_MSG);

      n=recv(newSd, line, MAX_MSG, 0);
      num1=atoi(line);

      n=recv(newSd, line, MAX_MSG, 0);
      num2=atoi(line);

      n=recv(newSd, line, MAX_MSG, 0);
      num3=atoi(line);

	sum=(num1+num2+num3)/3;

      sprintf(line1,"%d",sum);

	if (sum<7) {

      printf("\n recebido notas do aluno [IP %s ,TCP port %d] : %s, aluno reprovado. \n.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	} else if (sum>7) {

      printf("\n recebido notas do aluno [IP %s ,TCP port %d] : %s, aluno aprovado.",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);
	}


    } while(abs(strcmp(line, "quit")));


    /**************************/
    /* fechando conexão... */
    /**************************/   

    printf("conexão terminada com host [IP %s ,TCP port %d]\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    close(newSd);
  }
}
