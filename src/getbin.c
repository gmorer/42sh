/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getbin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:11:06 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/04 17:48:48 by gmorer           ###   ########.fr       */
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

void		ft_ctrlz(int i)
{
	(void)i;
	ft_putendl("lol");
}

void		launch_process(char **argv, char *bin)
{
	pid_t pid;

	pid = getpid();
	setpgid(pid, pid);
	shell->current_job->pgid = pid;
	//ft_putstr("binaire du programme : ");
	//ft_putstr(shell->current_job->command);
	//ft_putchar('\n');
	if (tcsetpgrp(shell->terminal, getpid()) == -1)
	{
		ft_putendl("error lancement");
		if (errno == EBADF)
			ft_putendl("fd n'est pas un descripteur valide.");
		if (errno == EINVAL)
			ft_putendl("pgrp a une valeur illégale.");
		if (errno == ENOTTY)
			ft_putendl("Le processus appelant n'a pas de terminal de contrôle, ou il en a un mais ce n'est pas celui décrit par fd, ou, pour tcsetpgrp(), ce terminal de contrôle n'est plus associé avec la session du processus appelant.");
		if (errno == EPERM)
			ft_putendl("pgrp a une valeur légale, mais ce n'est pas l'ID d'un groupe de processus dans la même session que le processus appelant.");
	}
	tcsetattr(shell->terminal, TCSADRAIN, &(shell->dfl_term));
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTTIN, SIG_DFL);
	signal (SIGTTOU, SIG_DFL);
	signal (SIGCHLD, SIG_DFL);
	execve(bin, argv, shell->env);
	exit (1);
}

int			ft_exec(char *bin, char **temp, char ***env, t_shell *shell)
{
	int		exit;
	int		i;
	pid_t	pid;

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
	pid = fork();
	if (pid == 0)
		launch_process(temp, bin);
	else if (pid < 0)
	{
		perror("perror");
		return(-1);
	}
	else 
	{
		setpgid(pid, pid);
		if(waitpid(pid, &exit, WUNTRACED) == -1)
		{
			ft_putendl("waitpid bug");
			i = errno;
			ft_putnbr(i);
		}
	}
	if (shell->current_job == NULL)
		return (146);
	tcsetpgrp(shell->terminal, shell->pgid);
	shell->current_job->pgid = pid;
	shell->first_job = shell->current_job;
	i = casenofor(*env, "_=");
	if (i > -1)
		free((*env)[i]);
	ft_signal();
	if (i > -1)
		(*env)[i] = ft_strjoin("_=", bin);
	else
		*env = ft_strstradd(ft_strjoin("_=", bin), *env);
	if (WIFEXITED(exit))
		return (WEXITSTATUS(exit));
	return (WIFSIGNALED(exit) ? WTERMSIG(exit) : exit);
}
