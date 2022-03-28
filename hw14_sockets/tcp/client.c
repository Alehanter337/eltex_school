#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>


#define SOCKET_PATH "/tmp/mysocket.socket"

int main()
{
	struct sockaddr_un server;
	server.sun_family = AF_LOCAL;
	strncpy(server.sun_path, SOCKET_PATH, sizeof(server.sun_path) - 1);
	int fd = socket(AF_LOCAL, SOCK_STREAM, 0);

	if (fd == -1)
	{
		perror("ERROR: Socket fd failed");
		exit(EXIT_FAILURE);
	}

	int size = 10;
	char buf[size];
	
	int conn = connect(fd, (const struct sockaddr *) &server, sizeof(struct sockaddr_un));
	if (conn == -1)
	{
		perror("ERROR: connect failed");
		exit(EXIT_FAILURE);
	}
		
	if (fd == -1)
	{
		perror("ERROR: new fd failed");
		exit(EXIT_FAILURE);
	}
	
	send(fd, "hello", size, 0);
	printf("send\n");
	recv(fd, buf, size, 0);
	printf("recv %s\n", buf);
	close(fd);
	return 0;
}
