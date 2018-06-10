#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[]){
  // ref https://www.programminglogic.com/example-of-client-server-program-in-c-using-sockets-and-tcp/
  printf("%s\n","Iniciando conexion al servidor ... " );
  printf("Direccion ip %s\n", argv[2]);
  printf("Puerto %i\n", atoi(argv[4]));
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[4]));
  serverAddr.sin_addr.s_addr = inet_addr(argv[2]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  if(recv(clientSocket, buffer, 1024, 0) > 0){
    printf("Data received: %s",buffer);
  }

  return 0;
}
