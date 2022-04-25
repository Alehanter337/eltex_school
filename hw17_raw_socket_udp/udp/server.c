#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


int main()
{
	struct sockaddr_in server;
	struct sockaddr_in client;
	int port = 1337;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (fd == -1)
	{
		perror("ERROR: Socket fd");
		exit(EXIT_FAILURE);
	}
	socklen_t sockaddr_len = sizeof(struct sockaddr_in);;
	int size = 10;
	char buf[size];

	int serv = bind(fd, (const struct sockaddr *) &server, sizeof(struct sockaddr_un));
	if (serv == -1)
	{
		perror("ERROR: bind failed");
		exit(EXIT_FAILURE);
	}
	

	while(1)
	{
		printf("SERVER waiting UDP packet from client...\n");
		
		memset(&client, 0, sizeof(struct sockaddr_in));
		char packet[10];
		int ret = recvfrom(fd, packet, 10, 0, (struct sockaddr *)&client, &sockaddr_len);
		if (ret < 0)
		{
			perror("recvfrom error");
			EXIT_FAILURE;
		}
		printf("client ip:  %s, client port: %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		printf("server - message: %d, bytes: %s\n", ret, packet);
		strcat(packet, "from server");;
		ret = sendto(fd, packet, strlen(packet) * sizeof(char), 0, (struct sockaddr*)&client, sockaddr_len);
		if (ret < 0)
		{
			perror("sendto error");
			EXIT_FAILURE;
		}

	}
	close(fd);
	exit(EXIT_SUCCESS);
}
