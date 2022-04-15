#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <string.h>


int main()
{
	struct sockaddr_in sender;
	int port = 7331;
	sender.sin_family = AF_INET;
	sender.sin_port = htons(port);
	sender.sin_addr.s_addr = INADDR_BROADCAST;

	int size = 20;
	char buf[] = "Broadcast";
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd == -1)
	{
		perror("ERROR: Socket fd failed");
		EXIT_FAILURE;
	}

	socklen_t sockaddr_len = sizeof(struct sockaddr_in);
	int serv = bind(fd, (struct sockaddr *)&sender, sockaddr_len);

	if (serv == -1)
	{ 
		perror("ERROR: bind failed");
		EXIT_FAILURE;
	}

	int flag = 1;
	int ret = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));

	if (ret < 0)
	{
		perror("ERROR: Setsockopt failed");
		EXIT_FAILURE;
	}
	
	//memset(buf, '\0', 10);

	while(1)
	{
		int send_len = sendto(fd, buf, size, 0, (struct sockaddr *)&sender, sizeof(sender));
		if (send_len < 0)
		{
			perror("ERROR: sendto failed");
			close(fd);
			EXIT_FAILURE;
		}	
		else (printf("send: %s\n", buf));

	}
	close(fd);
	return 0;
}

