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

void connection_established(int client){
  send(client, "0000001000000000\0", 17, 0);
  return;
}

void error_not_implemented(int client){
  send(client, "0001100000000000\0", 17, 0);
  return;
}

void ask_nickname(int client){
  send(client, "0000001100000000\0", 17, 0);
  return;
}

int getsize(char * data){
  int pot = 1;
  int sum = 0;
  for (int i = 15; i >= 8; i--) {
    if(data[i] == '1'){
      sum = sum + pot;
    }
    pot = pot * 2;
  }
  return sum;
}

int toint(char * data, int offset){
  int pot = 1;
  int sum = 0;
  for (int i = 15+offset*8; i >= 8+offset*8; i--) {
    if(data[i] == '1'){
      sum = sum + pot;
    }
    pot = pot * 2;
  }
  return sum;
}

char * traducir(char* buffer, int n){
  char * aux = malloc(n+1);
  char * foo = malloc(1);
  for (int i = 1; i <= n; i++) {
    foo = toint(buffer, i);
    aux[i-1] = foo;
  }
  aux[n] = '\0';
  return aux;
}

void recibir_mensaje(int client, char * buffer, char * idaux, int bytes){
  recv(client, buffer, bytes, 0);
  strncpy(idaux, buffer, 8);
  if(!strcmp(idaux, "00000001\0")){
    printf("%s\n","Estableciendo conexion" );
    connection_established(client);
    return;
  }
  else if(!strcmp(idaux, "00000100\0")){
    printf("El jugador 1 se llama %s\n", traducir(buffer, getsize(buffer)));
    return;
  }
  error_not_implemented(client);
  return;
}

int main(int argc, char const *argv[]){
  printf("%s\n","Iniciando conexion en ... " );
  printf("Direccion ip %s\n", argv[2]);
  printf("Puerto %i\n", atoi(argv[4]));
  // ref https://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/
  int welcomeSocket, cliente_1, cliente_2;
  char * idaux = malloc(9);
  idaux[8] = '\0';
  char * buffer = malloc(1024);
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[4]));
  serverAddr.sin_addr.s_addr = inet_addr(argv[2]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  addr_size = sizeof serverStorage;
  
  while(listen(welcomeSocket,2));
  cliente_1 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  recibir_mensaje(cliente_1, buffer, idaux, 17);
  ask_nickname(cliente_1);
  recibir_mensaje(cliente_1, buffer, idaux, 1024);

  while(listen(welcomeSocket,2));
  cliente_2 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  recibir_mensaje(cliente_2, buffer, idaux, 17);
  ask_nickname(cliente_2);
  recibir_mensaje(cliente_2, buffer, idaux, 1024);

  free(buffer);
  free(idaux);
  close(welcomeSocket);
  return 0;
}
