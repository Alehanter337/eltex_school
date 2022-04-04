#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/un.h>
#include <mqueue.h>


int main()
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	int port = 7331;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		perror("ERROR: Socket fd failed");
		exit(EXIT_FAILURE);
	}
	
	int size = 10;
	char buf[size];

	int serv = connect(fd, (const struct sockaddr *) &server, sizeof(struct sockaddr_in));
	if (serv == -1)
	{
		perror("ERROR: connect failed");
		exit(EXIT_FAILURE);
	}
	
	while(1)
	{
		printf("Print message:");
		fgets(buf, size, stdin);
		if (strncmp(buf, "exit", 3) == 0)
		{
			close(fd);
			break;
		}
		send(fd, buf, size, 0);
		printf("client send msg\n");
		
		recv(fd, buf, size, 0);
		printf("client recieve msg: %s\n", buf);
		
	}	


	close(fd);
	return 0;
}

