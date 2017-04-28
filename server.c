#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define SIZE 5000
#define SUCCESS_READ -2324

int globalSock;

void notify(char * message, int flag) {
  char temp[10000];
  sprintf(temp, "%s", message);
  char newtemp[10000];
  sprintf(newtemp, "(%lu(%d(%s", strlen(temp), flag, temp);
  send(globalSock, newtemp, 3000,0);
}
void * error(int errornum) {

  char temp[2000];
  sprintf(temp, "%s", strerror(errornum));
  notify(temp,-1);
  return 0;
}



struct CLIENTFILE_OPEN {

  char filename[256];
  char data[2000];
  char file_mode[256];
  char open_or_read;
  char open_mode;
};

struct CLIENTFILE_READ{
  size_t size;
  char data[2000];
};


//read from client and check whether there is an open or read request
struct CLIENTFILE_OPEN openFromClient(char * rcvFile){
  struct CLIENTFILE_OPEN client;
  char * pch;
   pch = strtok (rcvFile,"(");

   int i = 0;

   while (pch != NULL)
   {
      if (i == 0){
       //Filemode
       strcpy(client.file_mode, pch);

       client.open_or_read = client.file_mode[0];
       if (client.open_or_read == 'o'){
         client.open_mode = client.file_mode[1];
       }


     } else if (i == 1){
       //FILEPATH
       strcpy(client.filename, pch);

     } else {
       perror("Invalid open File format from client");
     }

     pch = strtok (NULL, "(");
     i++;
   }
   return client;
}


struct FILEDATA {
  char filename[256];
  char file_mode[156];

};







struct FILEDATA* data[SIZE];
struct FILEDATA* item;

struct FILEDATA *search(char * filename){
  int index = 0;
  while (data[index] != NULL) {

    if (strcmp(data[index]->filename, filename) == 0){
      return data[index];
    }
    ++index;

    /* code */
  }

  return NULL;

}


void insert(char * filename, char * file_mode){
  struct FILEDATA * item = (struct FILEDATA *) malloc (sizeof(struct FILEDATA));
  strcpy(item->filename, filename);
  strcpy(item->file_mode,file_mode);

  int index = 0;

  while (data[index] != NULL) {
    ++index;
  }

  data[index] = item;
}



//the thread function
void *connection_handler(void *);

//FILE -> OPEN
int  fileOpen(char * path, char flag);

void * fileRead(int file, char * path, char flag);


int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c, *new_sock;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);


    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
        new_sock = malloc(1);
        *new_sock = client_sock;

        if( pthread_create( &thread_id , NULL ,  connection_handler , (void *) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");


    }

    if (client_sock < 0)
    {
        perror("accept failed");

        return 1;
    }

    return 0;
}

/*
 * This will handle connection for each client
 * */



void *connection_handler(void *socket_desc)
{
      //Get the socket descriptor
     int sock = *(int*)socket_desc;
     int read_size,  send_size;
     char *message , client_message[2000];
     globalSock = sock;

     //Send some messages to the client
     // message = "Greetings! I am your connection handler\n";
     // write(sock , message , strlen(message));
     //
     // message = "Now type something and i shall repeat what you type \n";
     // write(sock , message , strlen(message));

     char temp[256];
     int file;
     //Receive a message from client
     if( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
     {
       int j;
       printf("%s\n",client_message );
       sprintf(temp, "%s", client_message);
      struct CLIENTFILE_OPEN openservice;
      openservice = openFromClient(temp);

      //if FILE -> open
      int file;

      if(openservice.open_or_read == 'o') {
          file = fileOpen(openservice.filename, openservice.open_mode);

        } else if (openservice.open_or_read == 'r') {

            printf("%c\n",client_message[2] );
            fileRead(file, openservice.filename, client_message[2]);




         //Send the message back to client
       } else {
        error(errno);

      }


     if ((send_size = send(sock,temp,strlen(temp),0)) > 0 ) {

        printf("Message sent from socket\n" );
      } else {
        error(errno);

      }


     if(read_size == 0 || send_size == 0)
     {
         error(errno);
         fflush(stdout);
     }
     else if(read_size == -1 || send_size == -1)
     {
         error(errno);
     }

 //Free the socket pointer
 free(socket_desc);


}
  return 0;
}

int fileOpen(char * path, char flag){
    int flags;
    if(flag == 'r') {
      flags = O_RDONLY;
    } else if(flag == 'w') {
      flags = O_WRONLY;
    } else if(flag == 'c') {
      flag = O_RDWR;
    } else if(flag == 'e') {
      notify("Invalid flags", -1);

    }

    char buffer[100];
    int file;
    file = open(path,flags);

    if(file < 0){
      error(errno);
    } else {
        //Successfully send file
        notify("Successfully opened file!",file);

    }


    return file;
}

void * fileRead(int file,char * path, char flag){

    int flags;
    char buffer[10000];


    if(flag == 'r') {
      flags = O_RDONLY;
    } else if (flag == 'c') {
      flags = O_RDWR;
    } else {
      notify("Flags are Invalid to read!",-1);

    }


    file = open(path,flags);

      char tp[10];

      int t = read(file,buffer,sizeof(buffer));

      if (t > 0) {
          char  temp[10000];
          sprintf(temp, "(%lu(%d(%s", strlen(buffer), SUCCESS_READ, buffer);
          printf("%s\n",temp );
          notify(buffer,-2324);
      } else {
        error(errno);
      }



      close(globalSock);
  return 0;

}
