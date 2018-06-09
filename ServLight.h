#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 4444
#define TAILLE 100

int lum();

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

int main()
{
		wiringPiSetupGpio();
		pinMode(20, OUTPUT);
		
		SOCKADDR_IN sin;
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		socklen_t recsize = sizeof(sin);
		
		SOCKADDR_IN csin;
		SOCKET csock;
		socklen_t crecsize = sizeof(csin);
		
		int sock_err = 0;
		char allume[TAILLE] = "allumée";
		char eteint[TAILLE] = "éteinte";
		
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);
		
		sock_err = bind(sock, (SOCKADDR*)&sin, recsize);
		
		if(sock_err != -1)
		{
			//printf("Reception connection\n");
			while(1)
			{
				sock_err = listen(sock, 1);
			
				csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
			
				if(csock != -1)
					if(lum() == 0)
						send(csock, allume, TAILLE, 0);
					else
						send(csock, eteint, TAILLE, 0);
				else
					perror("sock");
			}
			
		}
		else
			perror("bind");
		
		
		
		return EXIT_SUCCESS;
}

int lum()
{
	int msg = digitalRead(20);
	
	if(msg == 1)
		digitalWrite(20, 0);
		
	if(msg == 0)
		digitalWrite(20, 1);
		
	return msg;
}
