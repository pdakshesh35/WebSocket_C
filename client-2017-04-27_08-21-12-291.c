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
  char file_mode[256];
};

struct READFROMSERVER {
  int success_failure;
  int size;
  char data[3000];
};



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
int globalSock = -1;
struct READFROMSERVER server;
struct CLIENTPRINT client;


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
     printf("%s\n", server.data );


      return 0;
}

size_t netread(int flides, void * tbuffer, size_t nbyte) {

    char r[10];
    strcpy(r,"r");

    char buffer[10000];
    int total = 0;
    if( recv(globalSock, buffer + total, sizeof(buffer) - total,0) < 0) {
        perror("error");
    } else {
      printf("%s\n", buffer);
    }
      // struct READFROMSERVER temp = readFromServer(buffer);
      // printf("data : %s\n", temp.data );




    return 0;
}

void netserverinit(char * hostname) {
  // Declare initial vars
    int sockfd = -1;																// file descriptor for our socket
	int portno = -1;																// server port to connect to
	int n = -1;																		// utility variable - for monitoring reading/writing from/to the socket
	char buffer[256], server_reply[2000];															// char array to store data going to and coming from the server
    struct sockaddr_in serverAddressInfo;						// Super-special secret C struct that holds address info for building our socket
    struct hostent *serverIPAddress;									// Super-special secret C struct that holds info about a machine's address



	// If the user didn't enter enough arguments, complain and exit
    if (argc < 3)
	{
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

	portno = 8888;

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


	/** If we're here, we're connected to the server .. w00t!  **/

  //keep communicating with server

            int file = netOpen("./hello.txt", O_RDONLY);

          char * buffer = "whoaa";
          netread(1, buffer, 1000);


          close(sockfd);
}

}
int main(int argc, char *argv[])
{
    netserverinit(argv[1]);

    return 0;
}
