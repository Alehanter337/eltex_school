#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	int pipefd[2];
	char *string_child;
	char *string_main;
	pid_t pid;
	pipe(pipefd);
	

	if ((pid = fork()) == 0)
	{
		string_child = "Hello";
		write(pipefd[1], &string_child, sizeof(string_child));
		close (pipefd[1]);
		read(pipefd[0], &string_main, sizeof(string_main));
		printf("string from main: %s\n", string_main);
		close(pipefd[0]);
	}
	else 
	{
		read(pipefd[0], &string_child, sizeof(string_child)); 
		close(pipefd[0]);
		printf("String from child: %s\n", string_child);
		string_main = "Hi";
		write(pipefd[1], &string_main, sizeof(string_main));
		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	}
		
	return 0;
}
