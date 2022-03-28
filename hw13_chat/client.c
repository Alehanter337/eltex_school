#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msgData
{
	int type;
	char data[10];
};

struct msgData user1, user2;
char msg[30];
int id;

void *message_send_thread(void *arg)
{
	//char nickname[15];
	//printf("Enter your nickname: ");
	//fgets(nickname, 15, stdin);
	
	while(1)
	{
		user1.type = 2;
		//printf("%s:", nickname);
		printf("me: ");
		fgets(msg, 30, stdin);
		strcpy(user1.data, msg);	
		msgsnd(id, &user1, strlen(user1.data)+1, 0);
	}
}
/*
void *message_rcv_thread(void *arg)
{
	printf("recieve\n");
	while(1)
	{
		printf("in while");
		msgrcv(id, &user2, sizeof(user2), 3, 0);
		printf("need nickname: %s\n", user2.data);
		printf("me: ");
		fflush(stdout);
	}
}
*/
void message_send_init(pthread_t message_send)
{
	if (pthread_create(&message_send, NULL, message_send_thread, NULL) != 0)
	{
		perror("ERROR: message send thread create failed");
		exit(EXIT_FAILURE);
	}
	pthread_join(message_send, NULL);

}
/*
void message_rcv_init(pthread_t message_rcv)
{
	if (pthread_create(&message_rcv, NULL, message_rcv_thread, NULL) != 0)
	{
		perror("ERROR: message recieve thread create failed");
		exit(EXIT_FAILURE);
	}
	pthread_join(message_rcv, NULL);

}

*/
int main()
{
	id = msgget(4, IPC_CREAT|0644);
	pthread_t message_send;
	//hread_t message_rcv;
	message_send_init(message_send);
	//message_rcv_init(message_rcv);
	while(1)
	{
		msgrcv(id, &user2, sizeof(user2), 3, 0);
		printf("need nickname: %s\n", user2.data);
		printf("me: ");
		fflush(stdout);
	}

	return 0;

}
