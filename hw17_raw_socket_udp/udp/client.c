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
	int port = 7331;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (fd == -1)
	{
		perror("ERROR: Socket fd");
		exit(EXIT_FAILURE);
	}

	socklen_t sockaddr_len = sizeof(struct sockaddr_in);;
	
	int size = 10;

	char buf[size];	
	char packet[10];
	char *msg = "hello";
	struct udphdr *udp_header;
	udp_header = (struct udphdr *)packet;
	udp_header->source = htons(port);
	udp_header->dest = htons(1337);
	udp_header->check = 0;
	udp_header->len = htons(strlen(msg) - 1 + sizeof(struct udphdr));

	while(1)
	{		
		int ret = sendto(fd, msg, 5, 0, (struct sockaddr *)&server, sockaddr_len);
		if (ret < 0)
		{
			perror("sendto error");
			EXIT_FAILURE;
		}
		
		struct iphdr *ip_header = (struct iphdr *)packet;
		udp_header = (struct udphdr *) (packet + sizeof(struct iphdr));

		if (ntohs(udp_header->dest) == port)
		{
			struct in_addr saddr;
			saddr.s_addr = ip_header->saddr;
			printf("server ip:  %s, server port: %d, dest port: %d\n", inet_ntoa(saddr), ntohs(udp_header->source), ntohs(udp_header->dest));
			printf("recieved packet: %d\n", ret);
			//printf("message: %s\n", packet + sizeof)
			break;
		}

				
	}

	close(fd);
	free(msg);;
	exit(EXIT_SUCCESS);
}
