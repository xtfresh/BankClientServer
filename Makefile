#################################################################
##
## FILE:	Makefile
## PROJECT:	CS 3251 Project 1 - Professor Ellen Zegura 
## DESCRIPTION: Compile Project 1
## CREDIT:	Adapted from Professor Traynor
##
#################################################################

CC=gcc

OS := $(shell uname -s)

# Extra LDFLAGS if Solaris


all: client server 

client: client.c
	$(CC) client.c -o nameChanger

server: server.c
	$(CC) server.c -o changeServer

clean:
	    rm -f client server *.o

