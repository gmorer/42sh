#include "minishell.h"

int main(int argc, char **argv)
{
	char **temp;
	pid_t father;

	father = fork();
	temp = ft_strstrdup(argv);
	temp = ft_strstrdelfirst(temp);
	ft_putendl("test1i");
	if (father > 0)
	{
		wait();
		ft_putendl("test2");
	}
	if (father == 0)
	{
		execve(ft_strjoin("/bin/",argv[1]), temp, NULL);
	}
	ft_putendl("test3");
	return (0);
}
