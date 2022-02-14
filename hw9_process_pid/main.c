#include <stdio.h>
#include <unistd.h>

struct Process {
	pid_t pid;
	pid_t ppid;
};

int main(void){
	struct Process proc;
	proc.pid = getpid();
	proc.ppid = getppid();
	printf("child pid = %d, parrent pid = %d\n", proc.pid, proc.ppid);
	return 0;
}
