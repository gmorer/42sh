/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/08 14:18:58 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getexec(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*ofile;
	char			*tmp;
	char			*tmp1;

	(void)file;
	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	tmp1 = NULL;
	while ((ofile = readdir(dir)) && (ft_strcmp(ofile->d_name, file) ||
				ft_checklink((tmp1 = ft_strjoin(tmp, ofile->d_name))) == 0))
		if (ft_strcmp(ofile->d_name, file) == 0)
			free(tmp1);
	if (ofile && ft_strcmp(ofile->d_name, file) == 0)
		free(tmp1);
	free(tmp);
	if (ofile && ofile->d_name[0] != '.')
	{
		closedir(dir);
		return (path);
	}
	closedir(dir);
	return (NULL);
}

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
	while (i < len && getexec(path[i], argv) == NULL)
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
}

char	*ft_give_path(char *name, t_binary **table, char **env)
{
	int			hash;
	t_binary	*bin;

	if (!table)
		return (NULL);
	hash = ft_hash_algo(name, env);
	bin = table[hash];
	while (bin)
	{
		if (bin->data)
		{
			if (ft_strcmp(bin->data->name, name) == 0)
				return (ft_strdup(bin->data->full_path));
		}
		bin = bin->next;
	}
	return (NULL);
}

int			ft_exec(char *bin, char **temp, char ***env)
{
	int		exit;
	pid_t	pid;
	int		i;

	if ((exit = 1) && access(bin, F_OK) == -1)
	{
		ft_putstr(bin);
		ft_putendl(": Command not found.");
		return (1);
	}
	if (access(bin, X_OK) == -1)
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
	{
		free((*env)[i]);
	}
	if (i > -1)
		(*env)[i] = ft_strjoin("_=", bin);
	else
		*env = ft_strstradd(ft_strjoin("_=", bin), *env);
	if (WIFEXITED(exit))
		return (WEXITSTATUS(exit));
	return (WIFSIGNALED(exit) ? WTERMSIG(exit) : exit);
}
