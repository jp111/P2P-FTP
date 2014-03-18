#include "header.h"
int client(int port )
{
  int connected, bytes_recieved,addr_len;  
  char udpsend [20000],tcpsend[20000],udpreceive[20000],tcpreceive[20000];
  char regex[20000];
  char fileName[20000];
  struct hostent *h;
  struct sockaddr_in server_addr;  
  h= (struct hostent *) gethostbyname((char *)"127.0.0.1");
  if(flag==0)
    connected = socket(AF_INET, SOCK_STREAM, 0);
  else
    connected = socket(AF_INET, SOCK_DGRAM, 0);

  if (connected  == -1) {
    perror("Socket");
    exit(1);
  }


  server_addr.sin_family = AF_INET;     
  server_addr.sin_port = htons(port);   
  server_addr.sin_addr = *((struct in_addr *)h->h_addr);

  if(flag == 0)	
    bzero(&(server_addr.sin_zero), 8); 

  addr_len = sizeof(struct sockaddr);

  if(flag == 0)
  {
    while (connect(connected, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1) ;

  }
  /*	Connection established between client and server
  */
  printf("Usage: \n1. Download <filename>\n2. Upload <filename>\n3. IndexGet LongList \n4. IndexGet ShortList <start-timestamp> <end-timestamp>\n5. IndexGet RegEx\n6. FileHash Verify <filename>7. FileHash CheckAll\nEnter your command here:\n");

  char *str;
  char copy[20000];
  while(1)
  {
    if(flag == 1)
      gets(udpsend); // DATA which is got in the input buffer
    else
      gets(tcpsend); // DATA which is got in the input buffer



    if(flag == 1)
      scpy(copy,udpsend);
    else
      scpy(copy,tcpsend);
    str = strtok (copy," ");

    /*
       IndexGet 
       */
    if(str!=NULL)
    {
      if(!strcmp(str,"FileHash"))
      {
        str = strtok (NULL, " ");
        if(str !=NULL)
        {
          if(strcmp(str,"Verify")==0)
          {
            str = strtok (NULL, " ");
            if(str!=NULL)
            {
              if(flag == 1)
              {
                printf("udpsend : %s\n",udpsend);
                scpy(udpsend,"FV");
                scat(udpsend,str);
                sendto(connected, udpsend, strlen(udpsend), 0,
                    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
              }
              else
              {
                scpy(tcpsend,"FV");
                scat(tcpsend,str);
                send(connected, tcpsend,strlen(tcpsend), 0);
              }



              while(1)
              {
                if(flag == 1)
                {
                  bytes_recieved=recvfrom(connected,udpreceive,20000,0,
                      (struct sockaddr *)&server_addr, &addr_len);
                  udpreceive[bytes_recieved] = '\0';
                  if(strcmp(udpreceive,"End Of File") == 0)break;
                  fwrite(udpreceive,1,bytes_recieved,stdout);
                }
                else
                {
                  bytes_recieved=recv(connected,tcpreceive,20000,0);
                  tcpreceive[bytes_recieved] = '\0';
                  if(strcmp(tcpreceive,"End Of File") == 0)break;
                  fwrite(tcpreceive,1,bytes_recieved,stdout);

                }									

              }
              if(flag == 1)
                printf("\ndone\n");
              continue;
            }

          }
          else if(strcmp(str,"CheckAll")==0)
          {
            if(flag == 1)
            {
              scpy(udpsend,"FC");
              sendto(connected, udpsend, strlen(udpsend), 0,
                  (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
            }
            else
            {
              scpy(tcpsend,"FC");
              send(connected, tcpsend,strlen(tcpsend), 0);
            }

            while(1)
            {
              if(flag == 1)
              {
                bytes_recieved=recvfrom(connected,udpreceive,20000,0,
                    (struct sockaddr *)&server_addr, &addr_len);
                udpreceive[bytes_recieved] = '\0';
                if(strcmp(udpreceive,"End Of File") == 0)break;
                fwrite(udpreceive,1,bytes_recieved,stdout);
              }
              else
              {
                bytes_recieved=recv(connected,tcpreceive,20000,0);
                tcpreceive[bytes_recieved] = '\0';
                if(strcmp(tcpreceive,"End Of File") == 0)break;
                fwrite(tcpreceive,1,bytes_recieved,stdout);
              }	
            
            }
            printf("\ndone\n");
            continue;
          }
        }
        else printf("Please enter correct command\n");
      }
      else if(strcmp(str,"IndexGet")==0)	
      {
        
        str = strtok (NULL, " ");
        if(str!=NULL)
        {
         
          if(strcmp(str,"ShortList")==0)
          {
            printf("InShortlist\n");
            str = strtok (NULL, " ");
            if(str!=NULL)
            {
              if(flag == 1)
              {
                scpy(udpsend,"IS");
                scat(udpsend,str);
              }
              else
              {
                scpy(tcpsend,"IS");
                scat(tcpsend,str);
              }
              str = strtok (NULL, " ");
              printf("Enter Danger %s\n",str);
              if(str!=NULL)
              {
                if(flag == 1)
                {
                  scat(udpsend," ");
                  scat(udpsend,str);
                  printf("udpsend : %s\n",udpsend);
                  sendto(connected, udpsend, strlen(udpsend), 0,
                      (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
                }
                else
                {
                  scat(tcpsend," ");
                  scat(tcpsend,str);
                  printf("tcpsend : %s\n",tcpsend);
                  send(connected, tcpsend,strlen(tcpsend), 0);
                }
                printf("In Loop\n");
                //replace this with fiel catcher 
                while(1)
                {
                  if(flag == 1)
                  {
                    bytes_recieved=recvfrom(connected,udpreceive,20000,0,
                        (struct sockaddr *)&server_addr, &addr_len);
                    udpreceive[bytes_recieved] = '\0';
                    if(strcmp(udpreceive,"End Of File") == 0)break;
                    fwrite(udpreceive,1,bytes_recieved,stdout);
                  }
                  else
                  {
                    bytes_recieved=recv(connected,tcpreceive,20000,0);
                    tcpreceive[bytes_recieved] = '\0';
                    if(strcmp(tcpreceive,"End Of File") == 0)break;
                    fwrite(tcpreceive,1,bytes_recieved,stdout);
                  }
                }
                printf("\ndone\n");
                continue;
              }
            }		
          }

          if(strcmp(str,"ReGex")==0)
          {
            str = strtok (NULL, " ");
            if(str!=NULL)
            {
              if(flag == 1)
              {
                scpy(udpsend,"IR");
                scat(udpsend,str);
                printf("udpsend : %s\n",udpsend);
                sendto(connected, udpsend, strlen(udpsend), 0,
                    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
              }
              else
              {
                scpy(tcpsend,"IR");
                scat(tcpsend,str);
                printf("tcpsend : %s\n",tcpsend);
                send(connected, tcpsend,strlen(tcpsend), 0);
              }				


              // implement regex
              while(1)
              {
                if(flag == 1)
                {
                  bytes_recieved=recvfrom(connected,udpreceive,20000,0,
                      (struct sockaddr *)&server_addr, &addr_len);
                  udpreceive[bytes_recieved] = '\0';
                  if(strcmp(udpreceive,"End Of File") == 0)break;
                  fwrite(udpreceive,1,bytes_recieved,stdout);
                }
                else
                {
                  bytes_recieved=recv(connected,tcpreceive,20000,0);
                  tcpreceive[bytes_recieved] = '\0';
                  if(strcmp(tcpreceive,"End Of File") == 0)break;
                  fwrite(tcpreceive,1,bytes_recieved,stdout);	
                }						
              }
              printf("\ndone\n");
              continue;
            }
            else
            {
              printf("no filename given\n");
            }
          }


          else if(strcmp(str,"LongList")==0)
          {
            if(flag == 1)
            {
              scpy(udpsend,"IL");
              printf("------SENDING IL\n");
              sendto(connected, udpsend, strlen(udpsend), 0,
                  (struct sockaddr *)&server_addr, sizeof(server_addr)); 
              printf("------ready to receive file\n");
            }
            else
            {
              scpy(tcpsend,"IL");
              send(connected, tcpsend,strlen(tcpsend), 0); 
            }

            while(1)
            {

              if(flag == 1)
              {
                int temp = sizeof(struct sockaddr);
                bytes_recieved=recvfrom(connected,udpreceive,20000,0,
                    (struct sockaddr *)&server_addr, &temp);
                udpreceive[bytes_recieved] = '\0';


                if(strcmp(udpreceive,"End Of File") == 0)break;
                fwrite(udpreceive,1,bytes_recieved,stdout);
              }
              else
              {
                bytes_recieved=recv(connected,tcpreceive,20000,0);
                tcpreceive[bytes_recieved] = '\0';
                if(strcmp(tcpreceive,"End Of File") == 0)break;
                fwrite(tcpreceive,1,bytes_recieved,stdout);
              }						


            }
            printf("\ndone\n");
            continue;
          }
        }
      }


      else if(strcmp(str,"Download") == 0)
      {
        str = strtok (NULL, " ");
        if(str!=NULL)
        {
resend:
          if(flag == 1)
          {
            scpy(udpsend,"D ");
            scat(udpsend,str);
            sendto(connected, udpsend, 20000, 0,
                (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
          }
          else
          {
            scpy(tcpsend,"D ");
            scat(tcpsend,str);
            write(connected,tcpsend,20000);
          }

          printf("printing %s\n",str);


          FILE *fp1 = fopen(str,"wb");

          memset(udpreceive,0,20000);
          while(1)
          {
            if(flag == 1)
            {

              bytes_recieved=recvfrom(connected,udpreceive,20000,0,
                  (struct sockaddr *)&server_addr, &addr_len);
              udpreceive[bytes_recieved] = '\0';
              printf("got %s number %d-----\n",udpreceive,bytes_recieved);

              if(strcmp(udpreceive,"End Of File")==0)
              {
                break;
              }	

              fwrite(udpreceive, 1,bytes_recieved, fp1);


            }
            else
            {
              bytes_recieved=read(connected,tcpreceive,20000);

              if(strcmp(tcpreceive,"End Of File")==0)
              {
                break;
              }	
              fwrite(tcpreceive, 1,bytes_recieved, fp1);
            }
          }
          printf("File closed\n");
          fclose(fp1);
        }

        else printf("Please provide correct command");

      }

      else if(strcmp(str,"Upload") == 0)
      {
        str = strtok (NULL, " ");

        char arr[100];
        scpy(arr,str);

        printf("opening %s\n",arr);

        if(flag == 1)
        {
          scpy(udpsend,"U ");
          scat(udpsend,str);
          sendto(connected, udpsend, 20000, 0,
              (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        }
        else
        {
          scpy(tcpsend,"U ");
          scat(tcpsend,str);
          write(connected,tcpsend,20000);
        }
      }
      else{

        if ((strcmp(udpsend , "q") == 0 || strcmp(udpsend , "Q") == 0) || timeToclose ==1)
        {
          if(timeToclose)
            printf("quitting\n");
          if(flag == 1)					
            sendto(connected, udpsend, strlen(udpsend), 0,
                (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) ;
          else
            send(connected, tcpsend,strlen(tcpsend), 0);
          fflush(stdout);
          close(connected);
          exit(0);
          break;
        }

        else
        {
          if(flag == 1)
            sendto(connected, udpsend, strlen(udpsend), 0,
                (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
          else
            send(connected, tcpsend,strlen(tcpsend), 0);  
        }
      }

    }


  }
  return 0;
}
