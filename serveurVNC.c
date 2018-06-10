#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

int main(int argc, char* argv[])
{
  SOCKET sock;
  SOCKET csock;
  SOCKADDR_IN sin;
  SOCKADDR_IN csin;
  socklen_t recsize = sizeof(sin);
  socklen_t csize = sizeof(csin);

  int erreur = -1;
  char buffer[50] = "connection établie";
  char requete[50];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  printf("Creation de la socket...\n");

  if(sock != 0)
  {
    sin.sin_addr.s_addr = htons(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(70);
    printf("%d\n", htonl(INADDR_ANY));

    erreur = bind(sock, (SOCKADDR*)&sin, recsize);
    printf("Ouverture du port 23...\n");
    if(erreur != -1)
    {
      erreur = listen(sock, 1);

      if(erreur != -1)
      {
        while(1)
        {
          csock = accept(sock, (SOCKADDR*)&csin, &csize);
          recv(csock, requete, 50, 0);
          send(csock, buffer, 50, 0);

          if(requete = "demarrage")
          {
            system("C:\\Users\\Youcef\\Desktop\\RaspberryPi.vnc");
          }
          else if(requete == "arret")
          {
            system("taskkill vncserver.exe");
          }
        }
      }
      else
      {
        perror("listen");
      }
    }
    else
    {
      perror("bind");
    }
  }
  else
  {
    perror("socket");
  }
  close(sock);
  close(csock);
}
