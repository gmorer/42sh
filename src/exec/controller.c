/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 09:45:19 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/14 17:07:54 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell			*g_shell;

int				delet_job(t_job *job)
{
	t_job		*prev;
	t_job		*temp;
	int			i;

	i = 0;
	prev = NULL;
	temp = g_shell->first_job;
	while (temp)
	{
		if ((i++ || 1) && temp == job)
		{
			if (prev && job->next)
				prev->next = job->next;
			else if (prev)
				prev->next = NULL;
			else
				g_shell->first_job = job->next;
			ft_strdel(&job->command);
			free(job);
			return (i);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

static int		job_is_in(t_job *job)
{
	t_job		*temp;

	temp = g_shell->first_job;
	while (temp)
	{
		if (temp->pgid == job->pgid)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int				add_job(t_job *job)
{
	t_job		*temp;
	int			i;

	i = 1;
	temp = g_shell->first_job;
	while (g_shell->first_job && g_shell->first_job->next)
	{
		i++;
		g_shell->first_job = g_shell->first_job->next;
	}
	if (!g_shell->first_job)
		g_shell->first_job = job;
	else
	{
		g_shell->first_job->next = job;
		g_shell->first_job = temp;
	}
	return (i);
}

static void		add_process(pid_t pid, int status, t_job *job)
{
	if (WIFSTOPPED(status))
	{
		if (job_is_in(job))
			return ;
		add_job(job);
		return ;
	}
	else
	{
		if (job_is_in(job))
			delet_job(job);
		else
		{
			ft_strdel(&job->command);
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

int				wait_for_job(t_job *job)
{
	int			status;
	pid_t		pid;

	(void)job;
	status = 0;
	pid = waitpid(job->pgid, &status, WUNTRACED);
	add_process(pid, status, job);
	return (status);
}
