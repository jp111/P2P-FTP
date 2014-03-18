#include "header.h"
/*
 */
void server(int port)
{
	int sock, connected, true = 1,bytes_recieved,length_address;  
	char DataSent [1024],DataRecieved[1024],copy[1024];       
	char regex[100];
	struct sockaddr_in server_addr,client_addr;    
	int sin_size;
	if(flag==0)
		sock = socket(AF_INET, SOCK_STREAM, 0);
	else
		sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) 
		pr("Socket");

	server_addr.sin_family = AF_INET;         
	server_addr.sin_port = htons(port);     
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	memset( &(server_addr.sin_zero),0,8);
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) 
		pr("Unable to bind");

	if(flag==0 &&  (listen(sock, 5) == -1) )
		pr("Unable To Listen");
	if(flag==1)
		printf("\nUDPServer Waiting for client on port %d\n",port);
	else
		printf("\nTCPServer Waiting for client on port %d\n",port);
	length_address = sizeof(struct sockaddr);
	if(flag==0)
	{
		sin_size = sizeof(struct sockaddr_in);
		connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
		printf("\n I got a connection\n");
	}
	char * pch;
	fflush(stdout);
	char CMND[1024];
	char lw[100],up[100],cpy[1000];
	int counter=0;
	char BUFFER[1000];

	FILE *fpr;
	FILE *fpr2;
	int place=0;
	while (1)
	{
		if(flag==1)
			bytes_recieved=recvfrom(sock,DataRecieved,1024,0,(struct sockaddr *)&client_addr, &length_address);
		else
			bytes_recieved=recv(connected,DataRecieved,1024,0);

		DataRecieved[bytes_recieved] = '\0';

		if (strcmp(DataRecieved , "q") == 0 || strcmp(DataRecieved , "Q") == 0)
		{	
			
			timeToclose = 1;
			close(connected);
			printf("Closing\n");
			break;
		}
		else if(DataRecieved[0]=='F' && DataRecieved[1]=='C')
		{
			system("find . -type f -exec sh -c 'printf \"%s %s \n\" \"$(ls -l --time-style=+%Y%m%d%H%M%S $1 )\" \"$(md5sum $1 | cut -d\" \" -f1)\"' '' '{}' '{}' \\; | awk '{print $7, $6, $8}' > checkall");

			FILE *fp = fopen("checkall","r");
			if(fp == NULL)
			{
				printf("File Not Found\n");
				continue;
			}
			memset(DataSent,0,1024);
			int byteR,sentN;
			while(!feof(fp))
			{	
				byteR = fread(DataSent,1,1024,fp);
				DataSent[byteR] = '\0';
				if(flag==1)
					sentN =  sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				else
					sentN =  write(connected,DataSent,1024);
				printf("%s",DataSent);
				printf("read %d sent %d--------\n",sentN,byteR);				
			}
			printf("End file\n");
			memset(DataSent,0,1024);
			char end[]= "End Of File";
			scpy(DataSent,end);
			if(flag==1)
				sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
			else
				write(connected,DataSent,1024);
			fclose(fp);

			continue;
		}

	
		else if(DataRecieved[0]=='F' && DataRecieved[1]=='V')
		{
			printf("Identified FV\n");
			strncpy(regex,(char*)DataRecieved+2,100);
			printf("Filename is %s\n",regex);

			scpy(CMND,"openssl md5 ");
			scat(CMND,regex);
			scat(CMND," | cut -d\" \" -f2 > md5");
			system(CMND);
			scpy(CMND,"date -r ./");
			scat(CMND,regex);
			scat(CMND," +%Y%m%d%H%M%S > date");
			system(CMND);
			scpy(CMND,"paste md5 date > verify");

			system(CMND);
			scpy(CMND,"rm md5 date");
			system(CMND);

			FILE *fp = fopen("verify","r");
			if(fp == NULL)
			{
				printf("File Not Found\n");
				continue;
			}
			memset(DataSent,0,1024);
			int byteR,sentN;
			while(!feof(fp))
			{	
				byteR = fread(DataSent,1,1024,fp);
				DataSent[byteR] = '\0';
				if(flag==1)
					sentN =  sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				else
					sentN =  write(connected,DataSent,1024);
			}
			printf("End file\n");
			memset(DataSent,0,1024);
			char end[]= "End Of File";
			scpy(DataSent,end);
			if(flag==1)
				sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
			else
				write(connected,DataSent,1024);
			fclose(fp);

			printf("DataRecieved after verify : %s \n",DataRecieved);
			continue;
		}
		else if(strlen(DataRecieved)>2 && DataRecieved[0]=='D' && DataRecieved[1]==' ')
		{
			char arr[100];
			scpy(arr,DataRecieved+2);
			//scat(arr,pch);
			printf("opening %s\n",arr);
			FILE *fp = fopen(arr,"r");
			if(fp == NULL)
			{
				printf("File Not Found\n");
				continue;
			}
			memset(DataSent,0,1024);
			int byteR,sentN;
			while(!feof(fp))
			{	
				byteR = fread(DataSent,1,1024,fp);
				DataSent[byteR] = '\0';

				if(flag==1)
					sentN =  sendto(sock, DataSent, byteR, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				else
					sentN =  write(connected,DataSent,byteR);
				printf("%s",DataSent);
				printf("read %d sent %d--------\n",sentN,byteR);
			}
			printf("End file\n");
			memset(DataSent,0,1024);
			char end[]= "End Of File";
			scpy(DataSent,end);

			if(flag==1)
				sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
			else
				write(connected,DataSent,1024);
			fclose(fp);

		}
		else if(DataRecieved[0] == 'I' && DataRecieved[1]=='S')
		{
			printf("Identified IR\n");
			strncpy(regex,(char*)DataRecieved+2,100);
			printf("Timestamps are is %s\n",regex);
			pch = strtok (regex," ");
			scpy(lw,pch);
			pch = strtok (NULL, " ");
			scpy(up,pch);
			system("ls -l --time-style=+%Y%m%d%H%M%S -t > ls");
			fpr = fopen( "ls", "r" );
			fpr2 = fopen( "is", "w" );
			while ( fgets( BUFFER, 1000, fpr ) != NULL )
			{	
				if(counter!=0 && counter!=1)
				{
					printf("%d hahaha    %s",counter,BUFFER);
					scpy(cpy,BUFFER);
					place=0;
					pch = strtok (BUFFER," ");
					while (pch != NULL)
					{
						if(place==5)
						{
							printf("%s\n", pch);
							if(strcmp(pch,lw)>0 && strcmp(pch,up)<0)
							{
								printf("printing\n");
								fprintf(fpr2,"%s",cpy);
							}
						}
						place++;
						pch = strtok (NULL," ");
					}
				}
				counter++;
			}
			fclose( fpr );
			fclose( fpr2 );

			FILE *fp = fopen("is","r");
			if(fp == NULL)
			{
				printf("File Not Found\n");
				continue;
			}
			memset(DataSent,0,1024);
			int byteR,sentN;
			while(!feof(fp))
			{	
				byteR = fread(DataSent,1,1024,fp);
				DataSent[byteR] = '\0';

				if(flag==1)
					sentN =  sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				else
					sentN =  write(connected,DataSent,1024);
				printf("%s",DataSent);
				printf("read %d sent %d--------\n",sentN,byteR);
			}
			memset(DataSent,0,1024);
			char end[]= "End Of File";
			scpy(DataSent,end);
			if(flag==1)
				sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
			else
				write(connected,DataSent,1024);
			fclose(fp);

			printf("DataRecieved after regex : %s \n",DataRecieved);
			continue;


		}
		else if(DataRecieved[0]=='I' && DataRecieved[1]=='L')
		{

			printf("Recieved LongList\n");
			system("find . -printf '%p %TY%Tm%Td%TH%Tm%Tm %k \n' > il");

			FILE *fp = fopen("il","r");
			if(fp == NULL)
			{
				printf("File Not Found\n");
				continue;
			}
			memset(DataSent,0,1024);
			int byteR,sentN;
			while(!feof(fp))
			{	
				byteR = fread(DataSent,1,1024,fp);
				DataSent[byteR] = '\0';
				if(flag==1)
					sentN =  sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(server_addr));
				else
					sentN =  write(connected,DataSent,1024);
				printf("%s",DataSent);
				printf("read %d sent %d--------\n",sentN,byteR);
			}
			printf("End file\n");
			memset(DataSent,0,1024);
			char end[]= "End Of File";
			scpy(DataSent,end);
			if(flag==1)
				sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(server_addr));
			else
				write(connected,DataSent,1024);

			fclose(fp);

			continue;
		}
		else if(strlen(DataRecieved)>2 && DataRecieved[0]=='U' && DataRecieved[1]==' ')
		{
			char arr[100],cmd2[200];
			strncpy(arr,(char*)DataRecieved+2,100);
			
			sprintf(cmd2,"touch %s\n",arr);
			system(cmd2);
			close(fd[0]);
			write(fd[1],arr,strlen(arr)+1);		
		}

			else if(DataRecieved[0]=='I' && DataRecieved[1]=='R')
			{
			printf("Identified IR\n");
			strncpy(regex,(char*)DataRecieved+2,100);
			printf("Regex is %s\n",regex);

			scpy(CMND,"find . -name \"");
			scat(CMND,regex);
			scat(CMND,"\" > ir");
			system(CMND);
			FILE *fp = fopen("ir","r");
			if(fp == NULL)
			{
				printf("File Not Found\n");
				continue;
			}
			memset(DataSent,0,1024);
			int byteR,sentN;
			while(!feof(fp))
			{	
				byteR = fread(DataSent,1,1024,fp);
				DataSent[byteR] = '\0';

				if(flag==1)
					sentN =  sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
				else
					sentN =  write(connected,DataSent,1024);
				printf("%s",DataSent);
				printf("read %d sent %d--------\n",sentN,byteR);
			}
			printf("End file\n");
			memset(DataSent,0,1024);
			char end[]= "End Of File";
			scpy(DataSent,end);
			if(flag==1)
				sendto(sock, DataSent, 1024, 0,(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
			else
				write(connected,DataSent,1024);
			fclose(fp);


			printf("DataRecieved after regex : %s \n",DataRecieved);
			continue;
		}
	
		else{

			printf("%s\n" , DataRecieved);
		}


		close(sock);


	}
}
