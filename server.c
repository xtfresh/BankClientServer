/*///////////////////////////////////////////////////////////
*
* FILE:		server.c
* AUTHOR:	Montek Singh
* PROJECT:	CS 3251 Project 1 - Professor Ellen Zegura 
* DESCRIPTION:	Network Server Code
* CREDIT:	Adapted from Professor Traynor
*
*////////////////////////////////////////////////////////////

/*Included libraries*/

#include <stdio.h>	  /* for printf() and fprintf() */
#include <sys/socket.h>	  /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>	  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>	  /* supports all sorts of functionality */
#include <unistd.h>	  /* for close() */
#include <string.h>	  /* support any string ops */

#define RCVBUFSIZE 512		/* The receive buffer size */
#define SNDBUFSIZE 512		/* The send buffer size */
#define BUFSIZE 40		/* Your name can be as many as 40 chars*/

/* The main function */
int main(int argc, char *argv[])
{

    int serverSock;				/* Server Socket */
    int clientSock;				/* Client Socket */  
    struct sockaddr_in changeServAddr;		/* Local address */
    struct sockaddr_in changeClntAddr;		/* Client address */
    unsigned short changeServPort;		/* Server port */
    unsigned int clntLen;			/* Length of address data struct */
    int recvMsgSize;
    
    
    /*account balances*/
    int checkingBal = 100;
    int savingBal = 200;
    int retirmentBal = 300;
    int collegeBal = 400;

    int checkingAc = 0;
    int savingAc = 0;
    int retirmentAc = 0;
    int collegeAc = 0;


    char nameBuf[BUFSIZE];			/* Buff to store account name from client */
    int  balance = 1;				/* Place to record account balance result */
    char *type;
    
    if (argc != 2) 
    {
       printf("Incorrect number of arguments. The correct format is:\n\t serverPort\n");
       exit(1);
    }

    changeServPort = atoi(argv[1]);

    /* Create new TCP Socket for incoming requests*/
    serverSock = socket(AF_INET, SOCK_STREAM,0);


    /* Construct local address structure*/
    memset(&changeServAddr, '0', sizeof(changeServAddr));
    memset(&nameBuf, '0', sizeof(nameBuf));

    changeServAddr.sin_family = AF_INET;
    changeServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    changeServAddr.sin_port = htons(changeServPort);
    
    /* Bind to local address structure */
    bind(serverSock, (struct sockaddr*)&changeServAddr, sizeof(changeServAddr));

    /* Listen for incoming connections */
    listen(serverSock, 10);

    /* Loop server forever*/
    while(1)
    {

        clntLen = sizeof(changeClntAddr);
	   /* Accept incoming connection */
        clientSock = accept(serverSock, (struct sockaddr *)&changeClntAddr, &clntLen);

	   /* Extract the account name from the packet, store in nameBuf */
       /* Receive message from client */
        if ((recvMsgSize = recv(clientSock, nameBuf, BUFSIZE, 0)) < 0)
            perror("recv() failed");

	   /* Look up account balance, store in balance */
        if(nameBuf[7] == 'o'){
            balance = collegeBal;
            collegeAc++;
            if(nameBuf[0] == 'C')
                balance = collegeAc;
        }
        else if(nameBuf[7] == 'e'){
            balance = retirmentBal;
            retirmentAc++;
            if(nameBuf[0] == 'C')
                balance = retirmentAc;
        }
        else if(nameBuf[7] == 'a'){
            balance = savingBal;
            savingAc++;
            if(nameBuf[0] == 'C')
                balance = savingAc;
        }
        else if(nameBuf[7] == 'h'){
            balance = checkingBal;
            checkingAc++;
            if(nameBuf[0] == 'C')
                balance = checkingAc;
        }

	   /* Return account balance to client */
        //balance = htons(balance);
        
        if (send(clientSock, (const char*)&balance, sizeof(balance), 0) != sizeof(balance))
            perror("send() failed");
        close(clientSock);
    }

}

