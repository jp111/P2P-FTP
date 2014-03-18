#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
void clientTCP(int port);
void clientUDP(int port);
void serverTCP(int port);
void serverUDP(int port);
void server(int port);
void pr(char * str);
int flag;
int timeToclose;
int fd[2];
char *scpy(char *dst, char *src);
char *cat(char *dest, char *src);
#endif
