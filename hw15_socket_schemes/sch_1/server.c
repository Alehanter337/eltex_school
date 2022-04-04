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


void *thread_func(void *args)
{
	int *new_fd = (int*)args;
	int size = 10;
	char buf[size];
	while(1)
	{
		recv(*new_fd, buf, size, 0);
		printf("recv %s\n", buf);

		if (strncmp(buf, "exit", size) == 0)
		{
			printf("thread close fd %d\n", *new_fd);
			close(*new_fd);
			*new_fd = -1;
			pthread_exit(0);
		}

		send(*new_fd, buf, size, 0);
		printf("send %s\n", buf);
	}

	
};

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

	int serv = bind(fd, (const struct sockaddr *) &server, sizeof(struct sockaddr_in));
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
	
	pthread_attr_t thread_attr;
	pthread_attr_init(&thread_attr);

	pthread_t threads[100];
	int new_fd[100];

	for (int i = 0; i < 100; i++)
	{
		new_fd[i] = -1;
	}

	for (int i = 0; i < 100; i++)
	{
		if(i == 100)
		{
			i = 0;
		}
		
		if (new_fd[i] != -1)
		{
			continue;
		}

		printf("Server accept...\n");
		new_fd[i] = accept(fd, NULL, NULL);
		
		if (new_fd[i] == -1)
		{
			perror("ERROR: new fd failed");
			exit(EXIT_FAILURE);
		}
		
		void *param = (void *)&new_fd[i];
		if (pthread_create(&threads[i], &thread_attr, thread_func, param))
		{
			perror("ERROR: pthread create failed");
		}

	}
	
	close(fd);
	return 0;
}

