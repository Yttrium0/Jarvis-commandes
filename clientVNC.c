#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define TAILLE 50

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

int main(int argc, char* argv[])
{

  char envoie[TAILLE] = argv[1];
  char recu[TAILLE];
  SOCKET sock;
  SOCKADDR_IN sin;
  socklen_t recsize = sizeof(sin);

  sock = socket(AF_INET, SOCK_STREAM, 0);

  sin.sin_addr.s_addr = inet_addr("192.168.1.14");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(80);

  if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != -1)
  {
    send(sock, envoie, TAILLE, 0);
    recv(sock, recu, TAILLE, 0);
    printf("%s", recu);
    getchar();
  }
  else
  {
    perror("Connection impossible");
  }
  shutdown(sock, 2);
  close(sock);
}
