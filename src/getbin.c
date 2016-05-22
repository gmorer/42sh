#include "minishell.h"

char	**getline(char **env, char *argv)
{
	int	i;

	i = 0;
	while(strstr(env[i], argv) == NULL)
		i++;
	return(ft_strsplit(strstr(env[i], argv), ':'));
}

char	*getexec(path, file)
{


}
char	*toexec(char **env, char *argv)
{
	char	**path;
	int	i;

	i = 0;
	path = getline(env, "PATH=");
	while(getexec(path[i], argv) == NULL)
		i++;

}
