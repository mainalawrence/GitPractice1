#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h> 
#include <unistd.h> 
#include<pthread.h>

char clientMessage[20];
char buffer[20];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * socketThread(void *arg)
{
  int newSocket = *((int *)arg);
  recv(newSocket , clientMessage , 20 , 0);
  pthread_mutex_lock(&lock);
   char charValue[1];
  sprintf(charValue, "%c",((char)it));
  char *message = malloc(sizeof(clientMessage));
  strcat(message,clientMessage);
  strcat(message,"\n");
  strcpy(buffer,message);
  free(message);
  pthread_mutex_unlock(&lock);
  
  send(newSocket,buffer,20,0);
  printf("Exiting Thread\n");
  close(newSocket);
  pthread_exit(NULL);
}

int main(){
  int serverSocket, newSocket;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
 
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(10501);

  serverAddr.sin_addr.s_addr =inet_addr("10.247.53.97");
   
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
  if(listen(serverSocket,10)==0)
    printf("Server Listening....\n ");
  else
    printf("Error Server Failed\n");
    pthread_t tid[10];
    int i = 0;
    while(1)
    {
       
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

        int on = 1;
    if (setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
        if( pthread_create(&tid[i++], NULL, socketThread, &newSocket) != 0 )
           printf("Failed to create thread\n");

        if( i >= 10)
        {
          i = 0;
          while(i < 10)
          {
            pthread_join(tid[i++],NULL);
            
          }
          i = 0;
        }
    }
  return 0;
}

