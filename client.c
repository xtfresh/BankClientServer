/*///////////////////////////////////////////////////////////
*
* FILE:		client.c
* AUTHOR:	Montek Singh
* PROJECT:	CS 3251 Project 1 - Professor Ellen Zegura 
* DESCRIPTION:	Network Client Code
* CREDIT:	Adapted from Professor Traynor
*
*////////////////////////////////////////////////////////////

/* Included libraries */

#include <stdio.h>		    /* for printf() and fprintf() */
#include <sys/socket.h>		    /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>		    /* for sockaddr_in and inet_addr() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Constants */
#define RCVBUFSIZE 512		    /* The receive buffer size */
#define SNDBUFSIZE 512		    /* The send buffer size */
#define REPLYLEN 32

/* The main function */
int main(int argc, char *argv[])
{

    int clientSock;		    /* socket descriptor */
    struct sockaddr_in serv_addr;   /* server address structure */

    char *accountName;		    /* Account Name  */
    char *servIP;		    /* Server IP address  */
    unsigned short servPort;	    /* Server Port number */
    

    char sndBuf[SNDBUFSIZE];	    /* Send Buffer */
    char rcvBuf[RCVBUFSIZE];	    /* Receive Buffer */
    
    int balance = 2;		    /* Account balance */
    char *acType;
	

    /* Get the Account Name from the command line */
    if (argc != 5) 
    {
	   printf("Incorrect number of arguments. The correct format is:\n\t BAL/CNT accountName serverIP serverPort\n");
	   exit(1);
    }
    acType = argv[1];
    accountName = argv[2];
    memset(&sndBuf, 0, SNDBUFSIZE);
    memset(&rcvBuf, 0, RCVBUFSIZE);

    /* Get the addditional parameters from the command line */
    servIP = argv[3];
    servPort = atoi(argv[4]);

    /* Create a new TCP socket*/
 	if ((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    	perror("socket() failed");


    /* Construct the server address structure */
    memset(&serv_addr, 0, sizeof(serv_addr));     /* Zero out structure */
    serv_addr.sin_family      = AF_INET;             /* Internet address family */
    serv_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    serv_addr.sin_port        = htons(servPort); /* Server port */


    /* Establish connecction to the server */
    if (connect(clientSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        perror("connect() failed");


    
    /* Send the string to the server */
    sprintf(sndBuf, "%s %s", acType, accountName);
    if (send(clientSock, sndBuf, strlen(sndBuf), 0) < 0)
        perror("send() sent a different number of bytes than expected");


    /* Receive and print response from the server */
    
    if ((recv(clientSock, &balance, sizeof(balance), 0)) < 0)
        perror("recv() failed or connection closed prematurely");
    

    printf("%s\n", accountName);
    
    if(!strcmp(acType, "BAL"))
		printf("Balance is: %d\n", balance);
    else
		printf("Total Count is: %d\n",(balance-1));

    close(clientSock);
    return 0;
}

