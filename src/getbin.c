/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/10/10 15:53:12 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
