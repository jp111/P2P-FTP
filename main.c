
// =====================================================================================
// 
//        Version:  1.0
//       Compiler:  gcc
// 
//         Author:  Aniruddh Kanojia , Jaspreet Singh
// 
// =====================================================================================
#define pl(x) printf("%lld",x)
#define pls(x) printf("%lld ",x)
#define pln(x) printf("%lld\n",x)
#define pi(x) printf("%d",x)
#define pis(x) printf("%d ",x)
#define pin(x) printf("%d\n",x)
#define ps(x) printf("%s",x)
#define pss(x) printf("%s ",x)
#define psn(x) printf("%s\n",x)
#define pc(x) printf("%c",x)
#define pcs(x) printf("%c ",x)
#define pcn(x) printf("%c\n",x)
#define ll long long int
#define si(x) scanf("%d",&x)
#define sl(x) scanf("%lld",&x)
#define ss(x) scanf("%s",&x)
#define sc(x) scanf("%c",&x)
#define s2i(x,y) scanf("%d%d",&x,&y)
#define s3i(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define s2l(x,y) scanf("%lld%lld",&x,&y)
#define s3l(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define REP(i,a,b) for(i=a;i<=b;i++)
#define gc  getchar
#define dbg(x,y) printf("%s %d\n",x,y)
#define MOD 1000000007

#include "header.h"
void pr(char *str)
{
	printf("\n%s\n\n",str);
	exit(0);
}
int main()
{
	printf("Choose Whether To Run This Instance As Server Or Client\n");
	char str[200]={'\0'};
	int port;
	scanf("%s",str);
	if(str[0]=='s'||str[0]=='S')
	{
		printf("\nEnter Port Number to be used\n\n");
		scanf("%d",&port);
		printf("\n\nChoose TCP/UDP\n");
		scanf("%s",str);
		if(str[0]=='T'||str[0]=='t')
			flag=0;
		else if(str[0]=='U'||str[0]=='u')
			flag=1;
		else
			pr("Invalid Protocol");
		server(port);
	}
	else if(str[0]=='c'||str[0]=='C')
	{
		printf("\nEnter Port Number of Server \n\n");
		scanf("%d",&port);
		printf("\nChoose TCP/UDP\n\n");
		scanf("%s",str);
		if(str[0]=='T'||str[0]=='t')
			flag=0;
		else if(str[0]=='U'||str[0]=='u')
			flag=1;
		else
			pr("Invalid Protocol");
		client(port);
	}
	else
	{
		pr("Invalid Choice");
	}


}
char * scpy(char *dst, char *src)
{
	char *ptr;
	ptr = dst;
	while(*dst++=*src++);
	return(ptr);
}
char * scat(char *dest, char *src)
{
	    char *rdest = dest;

	        while (*dest)
			      dest++;
		    while (*dest++ = *src++)
			          ;
		        return rdest;
}
/*
   Aniruddh Kanojia
       201202029
#include<stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
  		     */
