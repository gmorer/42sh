/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:40:09 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/06 14:39:13 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

static int			delet_job(t_job *job)
{
	t_job	*prev;
	t_job	*temp;

	prev = NULL;
	temp = shell->first_job;
	while(temp)
	{
		if (temp == job)
		{
			if (prev)
				prev->next = job->next;
			else
				shell->first_job = job->next;
			free(job->command);
			free(job);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

static int			job_is_in(t_job *job)
{
	t_job	*temp;

	temp = shell->first_job;
	while (temp)
	{
		if (temp->pgid == job->pgid)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static void		add_job(t_job *job)
{
	t_job *temp;

	ft_putstr("add de ");
	ft_putendl(job->command);
	temp = shell->first_job;
	if (!shell->first_job)
		ft_putendl("il n'y a pas d'autre job");
	while (shell->first_job && shell->first_job->next)
	{
		ft_putendl("il y a dautre job");
		shell->first_job = shell->first_job->next;
	}
	if (!shell->first_job)
		shell->first_job = job;
	else
	{
		shell->first_job->next = job;
		shell->first_job = temp;
	}
}

static void		add_process(pid_t pid, int status, t_job *job)
{
	if (WIFSTOPPED(status))
	{
		if (job_is_in(job))
		{
			//free(job->command);
			//free(job);
			return ;
		}
		add_job(job);
		return ;
	}
	else
	{
		if (job_is_in(job))
			delet_job(job);
		else
		{
			free(job->command);
			free(job);
		}
		if (WIFSIGNALED(status))
		{
			ft_putnbr((int)pid);
			ft_putstr(" : Terminated by signal ");
			ft_putnbr(WTERMSIG(status));
			ft_putchar('\n');
		}
		return ;
	}
}

void		wait_for_job(t_job *job)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	add_process(pid, status, job);
}
