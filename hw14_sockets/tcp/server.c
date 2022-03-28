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

	int serv = bind(fd, (const struct sockaddr *) &server, sizeof(struct sockaddr_un));
	if (serv == -1)
	{
		perror("ERROR: bind failed");
		exit(EXIT_FAILURE);
	}
	
	if (listen(fd, 5) == -1)
	{
		perror("ERROR: listen failed");
		exit(EXIT_FAILURE);
	}
	
	int new_fd = accept(fd, NULL, NULL);
	if (new_fd == -1)
	{
		perror("ERROR: new fd failed");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		recv(new_fd, buf, size, 0);
		printf("recv %s\n", buf);
		send(new_fd, buf, size, 0);
		printf("send %s\n", buf);
	}
	close(new_fd);
	close(fd);
	return 0;
}
