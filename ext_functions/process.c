#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	int		pid;
	int		status;
	int		i;
	int		pipefd[2];
	char	buff[100];
	/*
	   printf("Beginning of the main process\n");
	   pid = fork();
	   if (pid == 0)
	   {
	   printf("Child process created\n");
	   i = 12;
	   printf("i: %i\n", i);
	   sleep(2);
	   exit(0);
	   }
	   else
	   {
	   waitpid(pid, &status, 0);
	   printf("Parent has waited for child\n");
	   }
	   printf("i: %i\n", i);
	   printf("Status: %i\n", status);
	 */
	// Write  something in the child process and get it to the main process
	i = 5;
	printf("Beginning of the main process\n");
	if (pipe(pipefd) == -1)
	{	
		perror("Pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
			// We now write into the pipe instead of stdout
		{
			perror("Dup");
			exit (0);
		}
		write(pipefd[1], "OK", 2);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
			// We now read into the pipe instead of stdin
		{
			perror("Dup");
			exit (0);
		}
		if (read(pipefd[0], buff, 2) == -1)
		{
			perror("Read");
			exit (0);
		}
		printf("Result: %s\n", buff);
	}
	return (0);
}
