/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/14 17:39:45 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**getline(char **env, char *argv)
{
	int	i;

	i = 0;
	while (ft_strstr(env[i], argv) == NULL)
		i++;
	return (ft_strsplit(strstr(env[i], argv), ':'));
}
/*
static char	*getexec(char *path, char *file)
{
	char			*tmp;
	char			*tmp1;

	tmp = ft_strjoin(path, "/");
	tmp1 = ft_strjoin(tmp, file);
	free(tmp);
	if (ft_checklink(tmp1) == 1)
	{
		free(tmp1);
		return (path);
	}
	free(tmp1);
	return (NULL);
}*/
/*
char		*toexec(char **env, char *argv)
{
	char	**path;
	size_t	i;
	size_t	len;
	char	*temp;
	char	*temp2;

	if (casenofor(env, "PATH") == -1)
		return (NULL);
	temp = getenvline(env, "PATH=");
	path = ft_strsplit(temp, ':');
	free(temp);
	len = ft_strlen(path[0]);
	len = ft_strstrlen(path);
	i = 0;
	//while (i < len && getexec(path[i], argv) == NULL)
	while (path[i] && getexec(path[i], argv) == NULL)
		i++;
	if (i == len)
		ft_strstrfree(path);
	if (i == len)
		return (NULL);
	temp = ft_strjoin(path[i], "/");
	ft_strstrfree(path);
	temp2 = ft_strjoin(temp, argv);
	free(temp);
	return (temp2);
}*/

int			ft_exec(char *bin, char **temp, char ***env)
{
	int		exit;
	pid_t	pid;
	int		i;

	if ((exit = 1) && access(bin, X_OK) == -1)
	{
		ft_putstr(bin);
		ft_putendl(": Permission denied.");
		return (1);
	}
	pid = fork();
	if (pid > 0)
		waitpid(pid, &exit, 0);
	if (pid == 0)
		execve(bin, temp, *env);
	i = casenofor(*env, "_=");
	if (i > -1)
		free((*env)[i]);
	if (i > -1)
		(*env)[i] = ft_strjoin("_=", bin);
	else
		*env = ft_strstradd(ft_strjoin("_=", bin), *env);
	if (WIFEXITED(exit))
		return (WEXITSTATUS(exit));
	return (WIFSIGNALED(exit) ? WTERMSIG(exit) : exit);
}
