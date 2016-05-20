#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	execute_program(char **av, char **env)
{
	pid_t	pid;
	int		status;

	(void)*av++;
	pid = fork();
	if (pid < 0)
	{
		printf("fork() error\n");
	}
	else if (pid == 0)
	{
		execve(av[0], av, env);
	}
	else
	{
		waitpid(pid, &status, env);
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	if (ac > 1)
		return (execute_program(av, env));
	return (0);
}
