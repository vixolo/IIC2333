#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include "poker.h"
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[]){
  printf("%s\n","Iniciando conexion en ... " );
  printf("Direccion ip %s\n", argv[2]);
  printf("Puerto %i\n", atoi(argv[4]));
  // ref https://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[4]));
  serverAddr.sin_addr.s_addr = inet_addr(argv[2]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if(listen(welcomeSocket,5)==0){
    printf("Listening\n");
  }
  else{
    printf("Error\n");
  }
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  strcpy(buffer,"Hello World\n");
  send(newSocket,buffer,13,0);
  printf("envia3 el buffer %s\n", buffer);
  return 0;
}
