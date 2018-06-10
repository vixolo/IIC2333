#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

char * decimal_to_binary(int n){
  /* MÉTODO OBTENIDO DE https://www.programmingsimplified.com/c/source-code/\
  c-program-convert-decimal-to-binary */
   int c, d, count;
   char *pointer;
   count = 0;
   pointer = (char*)malloc(8+1);
   if (pointer == NULL)
      exit(EXIT_FAILURE);
   for (c = 7 ; c >= 0 ; c--){
      d = n >> c;
      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';
      count++;
   }
   *(pointer+count) = '\0';
   return  pointer;
}

char* stringToBinary(char* s) { //https://stackoverflow.com/questions/41384262/convert-string-to-binary-in-c
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

void start_connection(int clientSocket, char * buffer, int bytes){
  strncpy(buffer, "0000000100000000\0", bytes);
  send(clientSocket, buffer, bytes, 0);
  return;
}

void error_not_implemented(int server){
  send(server, "0001100000000000\0", 17, 0);
  return;
}

void return_nickname(int server){
  char * nombrecito = malloc(50);
  char * aux = malloc(8);
  char * aux2 = malloc(8);
  strncpy(aux, "00000100", 8);
  gets(nombrecito);
  strcpy(aux2, decimal_to_binary(strlen(nombrecito)));
  strcat(aux, aux2);
  strcat(aux, stringToBinary(nombrecito));
  strcat(aux, "\0");

  //printf("Te llamas %s de largo %d ??? \n", nombrecito, strlen(nombrecito));
  send(server, aux,17+strlen(nombrecito)*8, 0);
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

void recibir_mensaje(int server, char * buffer, char * idaux, int bytes){
  recv(server, buffer, bytes, 0);
  strncpy(idaux, buffer, 8);
  if(!strcmp(idaux, "00000010\0")){
    printf("%s\n", "CONNECTION ESTABLISHED");
    return;
  }
  else if(!strcmp(idaux, "00000011\0")){
    return_nickname(server);
    return;
  }
  else if(!strcmp(idaux, "00000101\0")){
    printf("Tu oponente se llama %s\n", traducir(buffer, getsize(buffer)));
    return;
  }
  printf("este es tu idaux %s\n", idaux);
  error_not_implemented(server);
  return;
}

int main(int argc, char const *argv[]){
  // ref https://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/
  printf("%s\n","Iniciando conexion al servidor ... " );
  printf("Direccion ip %s\n", argv[2]);
  printf("Puerto %i\n", atoi(argv[4]));
  int clientSocket;
  char * idaux = malloc(9);
  idaux[8] = '\0';
  char * buffer = malloc(1024);
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[4]));
  serverAddr.sin_addr.s_addr = inet_addr(argv[2]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  start_connection(clientSocket, buffer, 17);
  recibir_mensaje(clientSocket, buffer, idaux, 17);
  recibir_mensaje(clientSocket, buffer, idaux, 17);

  recibir_mensaje(clientSocket, buffer, idaux, 1024);
  sleep(20);
  free(buffer);
  close(clientSocket);
  return 0;
}
