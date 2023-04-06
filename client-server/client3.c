#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>

#define PORTNUM 15000

int main(int argc, char **argv)
{
    int s, ns;
    int pid;
    int i, j;
    struct sockaddr_in serv_addr;
    struct hostent *hp;
    char buf[80] = "Hello, World!";
    
    int nport = PORTNUM;
    nport = htons((ushort)nport);
    
    if(argc < 2)
    {
	fprintf(stderr, "USAGE: client <host> <message>\n\t Send 'terminate' to shut the server down\n");
	return 1;
    }

// Преобразует строку имени хоста в ip-адрес	
    if((hp = gethostbyname(argv[1])) == 0)
    {
        perror("Error gethostbyname()"); exit(3);
    }
    //strcpy(buf, argv[2]);
    
    bzero(&serv_addr, (size_t)sizeof(serv_addr));
    bcopy(hp->h_addr, &(serv_addr.sin_addr), hp->h_length);
    serv_addr.sin_family = hp->h_addrtype;
    serv_addr.sin_port = nport;

    if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror(" Error socket()"); exit(1);
    }

    fprintf(stderr, "Server's host address: %s\n", inet_ntoa(serv_addr.sin_addr));

// Соединение с сервером    
    if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("Error connect()"); exit(1);
    }
    
    //send(s, buf, sizeof(buf), 0);

  while (1) {
	//scanf ("%s", buf);
	fgets (buf, sizeof(buf) - 1, stdin);
	send (s, buf, sizeof(buf), 0);
	bzero (buf, sizeof (buf));
    if (recv(s, buf, sizeof(buf), 0) < 0)
    {
        perror("Error recv()"); exit(1);
    }
     printf ("Received from server: %s\n", buf);
     //close(s);
     //printf("Client completed\n\n");
     //if (strcmp (buf, "#") == 0) {
	 //printf ("%s", buf);
	 printf ("%d\n", strcmp (buf, "#"));
	 if ((strcmp (buf, "#")) == 0) {
	     printf ("It is the end!");
		 close (s);
		 printf ("Client completed\n");
		 return 0;
	    }
	//fgets (buf, sizeof (buf), stdin);
	//printf ("I am buf %s", buf);
    // return 0;
  }
  return 0;
}
