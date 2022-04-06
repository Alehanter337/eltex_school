#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <mqueue.h>


short int threads_available[100];

struct param_for_threads
{
	int ID;
	char *queue_name;
};

void *thread_func(void *args)
{
	struct param_for_threads *threads_params = (struct param_for_threads *)args;
	
	mqd_t fd_queue = mq_open(threads_params->queue_name, O_RDONLY);
	if (fd_queue == -1)
	{
		perror("ERROR: fd_queue faild");
		EXIT_FAILURE;
	}

	int size = 10;
	char buf_2[size];
	char buf_3[size];
	int fd_data;


	while(1)
	{
		if (mq_receive(fd_queue, buf_2, size, NULL))
		{
			perror("ERROR: mq_recive failed");
			EXIT_FAILURE;
		}
		fd_data = atoi(buf_2);
		printf("Server thread fd recieved = %d\n", fd_data);		
		
		while(1)
		{
			recv(fd_data, buf_3, size, 0);
			
			if (strncmp(buf_3, "exit", size) == 0)
			{
				close(fd_data);
				threads_available[threads_params->ID] = 1;
				break;
			}

			send(fd_data, buf_3, size, 0);
			
		}
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
	
	struct mq_attr queue_attr;
	queue_attr.mq_flags = 0;
	queue_attr.mq_maxmsg = 10;
	queue_attr.mq_msgsize = 256;
	queue_attr.mq_curmsgs = 0;
	
	pthread_t threads[100];
	int fd_data[100];
	
	mqd_t queues[100];
	char **queues_name = malloc(sizeof(char *) * 100);
	struct param_for_threads threads_params[100];

	for (int i = 0; i < 100; i++)
	{
		queues_name[i] = malloc(sizeof(char) * 32);
		sprintf(queues_name[i], "client %d", i);
		queues[i] = mq_open(queues_name[i], O_WRONLY | O_CREAT, 0777, &queue_attr);
		
		if (queues[i] == -1)
		{
			perror("ERROR: mq_open failed");
			EXIT_FAILURE;
		}

		threads_params[i].ID = i;
		threads_params[i].queue_name = queues_name[i];
		void *param = (void *)&threads_params[i];
		
		if (pthread_create(&threads[i], &thread_attr, thread_func, param))
		{
			perror("ERROR: pthread create failed");
			EXIT_FAILURE;
		}

		threads_available[i] = 1;

	}

	for (int i = 0; ; i++)
	{
		if(i == 100)
		{
			i = 0;
		}

		if (threads_available[i] != 1)
		{
			continue;
		}

		fd_data[i] = accept(fd, NULL, NULL);

		if (fd_data[i] == -1)
		{
			perror("ERROR: Accept failed");
			EXIT_FAILURE;
		}

		char buf[size];
		sprintf(buf, "%d", fd_data[i]);
		if(mq_send(queues[i], buf, size + 1, 5) == -1)
		{
			perror("ERROR: mq_send failed");
			EXIT_FAILURE;
		}
		threads_available[i] = 0;
		printf("send %d", fd_data[i]);
	}

	close(fd);
	EXIT_SUCCESS;
}

