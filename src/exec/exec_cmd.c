/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:49:51 by lvalenti          #+#    #+#             */
/*   Updated: 2017/03/09 15:45:07 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "lex_par_ast.h"
#include "builtin.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

t_shell			*g_shell;

char				*find_bin(char *arg, int error)
{
	char			*bin;
	char			*temp;
	struct stat		statvar;

	temp = NULL;
	bin = (ft_isin(arg, '/') ? ft_strdup(arg) : give_path(arg, g_shell->table));
	if (!arg)
		return (NULL);
	if (!bin)
	{
		bin = toexec(arg);
		if (bin)
		{
			temp = ft_strsub(bin, 0, ft_strlen(bin) - ft_strlen(arg) - 1);
			add_hash_to_tab(arg, temp);
			free(temp);
		}
	}
	if ((!bin || stat(bin, &statvar) == -1) && error)
		return (error_message(127, arg));
	if (bin && access(bin, X_OK) == -1)
	{
		free(bin);
		return (error ? error_message(126, arg) : NULL);
	}
	return (bin);
}

void				exec_basic_cmd(t_detail *node, char **env, int fg)
{
	char		*bin;
	pid_t		pid;

	if ((bin = find_bin(*(node->argv), 1)))
	{
		pid = getpid();
		linkio(node);
		if (fg)
		{
			setpgid(pid, pid);
			tcsetpgrp(1, pid);
			tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
		execve(bin, node->argv, env);
	}
	exit(1);
}

void				exec_pipe(t_detail *node, char **env, int fg)
{
	int			pfd[2];

	pipe(pfd);
	if (fork() == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		exec_basic_cmd(node, env, fg);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		if (node->next->next)
			exec_pipe(node->next, env, fg);
		exec_basic_cmd(node->next, env, fg);
	}
}

int				exec_cmd(t_node *tree, char **env, t_job *current_job)
{
	pid_t		pid;
	int			status;
	char		*temp;

	status = 0;
	if ((temp = find_bin(*(tree->lst->argv), 0)))
		free(temp);
	if ((pid = fork()) == 0)
	{
		if (tree->lst->pipe)
			exec_pipe(tree->lst, env, tree->fg);
		else
			exec_basic_cmd(tree->lst, env, tree->fg);
	}
	else
	{
		dup2(tree->in, STDIN_FILENO);
		dup2(tree->out, STDOUT_FILENO);
		dup2(tree->err, STDERR_FILENO);
		current_job->pgid = pid;
		if (tree->fg)
		{
			setpgid(pid, pid);
			status = wait_for_job(current_job);
		}
		else
		{
			ft_putchar('[');
			ft_putnbr(add_job(current_job));
			ft_putstr("]	");
			ft_putnbr(current_job->pgid);
			ft_putchar('\n');
		}
	}
	return (status);
}

int				prep_exec(t_node *tree, char **env)
{
	int			status;
	t_job		*current_job;

	if (select_redir(tree))
		return (1);
	if (tree->lst && !tree->lst->next
			&& (status = builtin(tree->lst)) != -1)
	{
		dup2(tree->in, STDIN_FILENO);
		dup2(tree->out, STDOUT_FILENO);
		dup2(tree->err, STDERR_FILENO);
		return (status);
	}
	status = 0;
	current_job = (t_job*)malloc(sizeof(t_job));
	*current_job = (t_job){NULL, ft_strdup(tree->str), 0};
	status = exec_cmd(tree, env, current_job);
	if (tree->fg)
	{
		tcsetpgrp(1, g_shell->pgid);
		tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WIFSIGNALED(status) ? WTERMSIG(status) : status);
}
