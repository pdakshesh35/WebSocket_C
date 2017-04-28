#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SUCCESS_READ  -2324
void error(char *msg)
{
    perror(msg);
    exit(0);
}


struct CLIENTPRINT {
  size_t size;
  char filename[256];
  char data[2000];
  int flag;
  int file;
};

struct READFROMSERVER {
  int success_failure;
  int size;
  char data[3000];
};


struct CLIENTPRINT client;
int FILE_SUCCESS_FAILURE = -1;

struct READFROMSERVER readFromServer(char * line){
  struct READFROMSERVER client;
  char * pch;
   pch = strtok (line,"(");

   int i = 0;

   while (pch != NULL)
   {
      if (i == 0){
       //Filemode
       client.size = atoi(pch);


     } else if (i == 1){
       //FILEPATH
       client.success_failure = atoi(pch);

     } else if (i == 2) {
       strcpy(client.data,pch);
     } else {
       perror("Invalid open File format from client");
     }

     pch = strtok (NULL, "(");
     i++;
   }
   return client;
}


char* strip (char* input){
    int loop;
    char *output = (char*) malloc (strlen(input));
    char *dest = output;

    if (output)
    {
        for (loop=0; loop<strlen(input); loop++)
            if (input[loop] != ' ')
                *dest++ = input[loop];

        *dest = '\0';
    }
    return output;
}





//Global data
int globalSock;
struct READFROMSERVER server;


void netserverinit(char * hostname, char * port) {
          // Declare initial vars
            int sockfd = -1;																// file descriptor for our socket
        	int portno = -1;																// server port to connect to
        	int n = -1;																		// utility variable - for monitoring reading/writing from/to the socket
        	char buffer[256], server_reply[2000];															// char array to store data going to and coming from the server
            struct sockaddr_in serverAddressInfo;						// Super-special secret C struct that holds address info for building our socket
            struct hostent *serverIPAddress;									// Super-special secret C struct that holds info about a machine's address



        	// If the user didn't enter enough arguments, complain and exit


        	portno = atoi(port);

            serverIPAddress = gethostbyname(hostname);
            if (serverIPAddress == NULL)
        	{
                fprintf(stderr,"ERROR, no such host\n");
                exit(0);
            }


            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0)
        	{
                error("ERROR creating socket");
        	}


        	// zero out the socket address info struct .. always initialize!
            bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

        	// set a flag to indicate the type of network address we'll be using
            serverAddressInfo.sin_family = AF_INET;

        	// set the remote port .. translate from a 'normal' int to a super-special 'network-port-int'
        	serverAddressInfo.sin_port = htons(portno);


            bcopy((char *)serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);




        	//   if it doesn't work, complain and exit
            if (connect(sockfd,(struct sockaddr *)&serverAddressInfo,sizeof(serverAddressInfo)) < 0)
        	{
                perror("ERROR connecting");
        	} else {

                //connection established
                globalSock = sockfd;
        }

}

int netOpen(const char * path, int flags){

      char buffer[256];
      strcpy(buffer, "(o");

      if(flags == O_WRONLY){
        strcat(buffer, "w");
      } else if (flags == O_RDONLY) {
        strcat(buffer,"r");
      } else if (flags == O_RDWR) {
        strcat(buffer, "c");
      } else {

        strcat(buffer, "e");
      }
      strcat(buffer,"(");
      strcat(buffer,path);

     char sendFile[256];
     char recvFile[100000];
      char tp[100000];

     send(globalSock,buffer, sizeof(buffer),0);
     recv(globalSock, recvFile, sizeof(recvFile),0);

     server = readFromServer(recvFile);
     printf("%s\n", server.data);
     FILE_SUCCESS_FAILURE = server.success_failure;
    if (server.success_failure > 0) {
      strcpy(client.filename,path);
      client.flag = flags;

    }



      return 0;
}

size_t netread(int flides, void * tbuffer, size_t nbyte) {

    char buffer[256];
    strcpy(buffer,"(r");


    if(client.flag == O_WRONLY){
      strcat(buffer, "w");
    } else if (client.flag == O_RDONLY) {
      strcat(buffer,"r");
    } else if (client.flag == O_RDWR) {
      strcat(buffer, "c");
    } else {

      strcat(buffer, "e");
    }

    //prepare for send string
    strcat(buffer,"(");
    strcat(buffer,client.filename);
    send(globalSock,buffer,strlen(buffer),0);


    char tp[10000];
    int total = 0;
    if( recv(globalSock, tp + total, sizeof(tp) - total,0) < 0) {
        perror("error");
    } else {
      struct READFROMSERVER readserver = readFromServer(tp);
      if(readserver.success_failure == SUCCESS_READ) {
        printf("Bytes read : %d\n", readserver.size);
        printf("Buffer : %s\n", readserver.data);
      } else {
        printf("%s\n", readserver.data );
      }
    }
      // struct READFROMSERVER temp = readFromServer(buffer);
      // printf("data : %s\n", temp.data );




    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
  {
     fprintf(stderr,"usage %s hostname port\n", argv[0]);
     exit(0);
  }

  char * host = argv[1];
  char * port = argv[2];

 int i ;

  while(1) {
    printf("1. netOpen\n" );
    printf("2. netread\n" );
    printf("3. netWrite\n" );
    printf("4. netClose\n" );
    printf("Enter choice from the above : " );
    scanf("%d", &i);
    if(i == 1){
      netserverinit(host, port);
      netOpen("./hello.txt",O_RDONLY);
      close(globalSock);

    } else if (i == 2) {
          if(FILE_SUCCESS_FAILURE < 0) {
            printf("File has to open first!\n" );
          } else {
            netserverinit(host, port);
            char * buffer = "fsf";
            netread(1, buffer, 254);
            close(globalSock);
          }
    } else {
      break;
    }
  }

    return 0;
}
