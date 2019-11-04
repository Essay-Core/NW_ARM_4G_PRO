#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
	pid_t pid, pid_wait;
	int status;
	pid = fork();
	if(pid == -1)
	{
		printf("Error to create new process\n");
		return 0;
	}
	else if(pid == 0)
	{
		printf("Child process...\n");
	}
	else
	{
		printf("Parent process!, Child process ID:%d\n", pid);
		pid_wait = waitpid(pid, &status, 0);
		printf("Child process %d returned!\n", pid_wait);
	}

	return 0;
}

