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

void error(char *msg)
{
    perror(msg);
    exit(0);
}


char* strip (char* input)
{
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

int globalSock = -1;
int netOpen(const char * path, int flags){

  char buffer[256];
  strcpy(buffer, "o");

  if(flags == O_WRONLY){
    strcat(buffer, "w");
  } else if (flags == O_RDONLY) {
    strcat(buffer,"r");
  } else if (flags == O_RDWR) {
    strcat(buffer, "c");
  } else {
    perror("Invalid flags");
  }

  write(globalSock,buffer,strlen(buffer));

  return 0;
}



int main(int argc, char *argv[])
{
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



	/** If the user gave enough arguments, try to use them to get a port number and address **/

	// convert the text representation of the port number given by the user to an int
	portno = atoi(argv[2]);

	// look up the IP address that matches up with the name given - the name given might
	//    BE an IP address, which is fine, and store it in the 'serverIPAddress' struct
    serverIPAddress = gethostbyname(argv[1]);
    if (serverIPAddress == NULL)
	{
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

	// try to build a socket .. if it doesn't work, complain and exit
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
	{
        error("ERROR creating socket");
	}



	/** We now have the IP address and port to connect to on the server, we have to get    **/
	/**   that information into C's special address struct for connecting sockets                     **/

	// zero out the socket address info struct .. always initialize!
    bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));

	// set a flag to indicate the type of network address we'll be using
    serverAddressInfo.sin_family = AF_INET;

	// set the remote port .. translate from a 'normal' int to a super-special 'network-port-int'
	serverAddressInfo.sin_port = htons(portno);

	// do a raw copy of the bytes that represent the server's IP address in
	//   the 'serverIPAddress' struct into our serverIPAddressInfo struct
    bcopy((char *)serverIPAddress->h_addr, (char *)&serverAddressInfo.sin_addr.s_addr, serverIPAddress->h_length);



	/** We now have a blank socket and a fully parameterized address info struct .. time to connect **/

	// try to connect to the server using our blank socket and the address info struct
	//   if it doesn't work, complain and exit
    if (connect(sockfd,(struct sockaddr *)&serverAddressInfo,sizeof(serverAddressInfo)) < 0)
	{
        perror("ERROR connecting");
	} else {

    globalSock = sockfd;

	/** If we're here, we're connected to the server .. w00t!  **/

  //keep communicating with server

      printf("Enter message : ");
      scanf ("%[^\n]%*c", buffer);



      //Send some s
      if( send(sockfd , buffer , strlen(buffer) , 0) < 0)
      {
          puts("Send failed");

      }

      //Receive a reply from the server
      if( recv(sockfd , server_reply , 2000 , 0) > 0)
      {
        read(sockfd,server_reply,256);
      //  printf("%s\n",server_reply );
        printf("server_reply %s\n",server_reply );

      }

      int file;
    if (( file = netOpen("hello.txt", O_RDONLY)) != -1){
      printf("%d\n",file );
    } else {
      perror("Can not open File");
    };



  close(sockfd);
}
    return 0;
}
