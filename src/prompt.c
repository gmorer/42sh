#include "minishell.h"

void static	allenv(char *temp, char *temp1, char *temp2)
{
	if (ft_strstr(temp, temp1) != NULL)
	{
		ft_putstr(temp2);
		ft_putstr(temp + ft_strlen(temp1));
	}
	else
		ft_putstr(temp);
}

void		prompt(char **env, int returnvalue)
{
	char	*temp1;
	char	*temp2;
	char	*temp;
	ft_putchar('[');
	ft_putnbr(returnvalue);
	ft_putstr("] -> ");
	temp = getcwd(NULL, 0);
	temp1 = getenvline(env, "HOME=");
	temp2 = getenvline(env, "USER=");
	if(temp1 && temp2)
	{
		allenv(temp, temp1, temp2);
		free(temp2);
		free(temp1);
	}
	else
		ft_putstr(temp);
	free(temp);
	ft_putstr(": ");
}
