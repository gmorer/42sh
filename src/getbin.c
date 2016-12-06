/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/06 12:27:01 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

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
/*
void		lol(int i)
{
	t_job	*job;

	(void)i;
	ft_putendl("catch them all");
	kill(shell->current_job->pgid, SIGTSTP);
	job = shell->first_job;
	while(job && job->next)
	{
		job = job->next;
	}
	if (!job)
		shell->first_job = shell->current_job;
	else
		job->next = shell->current_job;
	shell->current_job = NULL;
}*/
int			ft_exec(char *bin, char **temp, char ***env, t_shell *shell)
{
	int		exit;
	int		i;

	ft_putendl("COMMENCE LEXECUTION");
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
	if(!(shell->current_job = (t_job*)malloc(sizeof(t_job))))
		return (1);
	*(shell->current_job) = (t_job){NULL, ft_strdup(bin), NULL, 0, 0, 0, 0, 0};
	shell->current_job->pgid = fork();
	//signal(SIGCHLD, SIG_DFL);
	//signal(SIGTSTP, lol);
	if (shell->current_job->pgid == 0)
	{
		free(shell->current_job);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		//signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		//signal(SIGTSTP, lol);
		//if execve(bin, temp, *env) == -1);
		if (execvp(bin, temp) == -1)
		{
			ft_putendl("exec error");
			i = errno;
			ft_putnbr(i);
			ft_signal();
			return (0);
		}
		ft_putendl("lolololol");
	}
	else if (shell->current_job && shell->current_job->pgid < 0)
	{
		free(shell->current_job);
		ft_putendl("error pgid");
		ft_signal();
		return(-1);
	}
	else if (shell->current_job && shell->current_job->pgid > 0)
		if(waitpid(shell->current_job->pgid, &exit, WUNTRACED) == -1)
		{
			ft_putendl("waitpid bug");
			i = errno;
			ft_putnbr(i);
			free(shell->current_job);
			ft_signal();
			return(1);
		}
	if (shell->current_job == NULL)
		return (146);
//		setpgid(pid, pid);
//	tcsetpgrp(shell->terminal, shell->pgid);
	ft_putendl("FINI LEXECUTION");
	free(shell->current_job->command);
	free(shell->current_job);
	shell->current_job = NULL;
	i = casenofor(*env, "_=");
	if (i > -1)
	{
		free((*env)[i]);
	}
	ft_signal();
	if (i > -1)
		(*env)[i] = ft_strjoin("_=", bin);
	else
		*env = ft_strstradd(ft_strjoin("_=", bin), *env);
	if (WIFEXITED(exit))
		return (WEXITSTATUS(exit));
	return (WIFSIGNALED(exit) ? WTERMSIG(exit) : exit);
}
