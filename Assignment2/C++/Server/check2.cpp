#include <iostream>
#include <cstring>      
#include <sys/socket.h>     
#include <netdb.h>      
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <pthread.h>
// #include <sys/SSL_writefile.h>
#include <fcntl.h>
#include <vector>

int main(int argc, char **argv) {

  fd_set fds, readfds;
  int i, clientaddrlen;
  int clientsock[5], rc, numsocks = 0, maxsocks = 5;

  int serversock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serversock == -1) perror("Socket");

  struct sockaddr_in serveraddr, clientaddr;  
  bzero(&serveraddr, sizeof(struct sockaddr_in));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(atoi(argv[1]));

  if (-1 == bind(serversock, (struct sockaddr *)&serveraddr, 
                 sizeof(struct sockaddr_in))) 
    perror("Bind");

  if (-1 == listen(serversock, SOMAXCONN))
    perror("Listen");

  FD_ZERO(&fds);
  FD_SET(serversock, &fds);

  while(1) {
    std::cout<<"starting while loop\n";
    readfds = fds;
    rc = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
    std::cout<<"selected"<<std::endl;
    if (rc == -1) {
      perror("Select");
      break;
    }
    int counter =0;
    std::cout<<FD_SETSIZE<<std::endl;
    for (i = 0; i < maxsocks; i++) 
    {
      std::cout<<"entering for loop\n"<<counter<<std::endl;
      counter++;
      if (FD_ISSET(i, &readfds)) 
      {
        std::cout<<"first if\n";
        if (i == serversock) 
        {
          if (numsocks < maxsocks)
          {
            clientsock[numsocks] = accept(serversock,
                                      (struct sockaddr *) &clientaddr,
                                      (socklen_t *)&clientaddrlen);
            std::cout<<clientsock[numsocks]<<"    "<<serversock<<std::endl;
            if (clientsock[numsocks] == -1) 
              perror("Accept");
            else printf("Accepted\n" );
            FD_SET(clientsock[numsocks], &fds);
            numsocks++;
          } 
          else 
          {
            printf("Ran out of socket space.\n");
          }
        } 
        else 
        {
          int messageLength = 20;
          char message[messageLength+1];
          int in, index = 0, limit = messageLength+1;

          in = recv(i, message, limit, 0);
          std::cout<<clientsock[i]<<std::endl;         
          printf("%d\n", index);
          printf("%s\n", message);

        }
      }
    }
  }

  close(serversock);
  return 0;
}