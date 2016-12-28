/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:08:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/23 16:58:46 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

void		ctrlz(int i)
{
	t_job	*job;
//	char	c;

//	c = 26;
	if (shell->current_job == NULL)
	{
		return;
	}
	(void)i;
	ft_putnbr(shell->current_job->pgid);
	//ft_putendl("catch them all");
	job = shell->first_job;
	while(job && job->next)
	{
		job = job->next;
	}
	if (!job)
		shell->first_job = shell->current_job;
	else
		job->next = shell->current_job;
//	ioctl(0, TIOCSTI, &c);
	ioctl(0, TIOCSTI, "\n");
	kill(shell->current_job->pgid, SIGTSTP);
	shell->current_job = NULL;
}

void			catch_kill(int i)
{
	if(i == SIGINT)
	{
		ft_putchar('\n');
		ft_prompt(shell->env, 1);
	}
	else
	{
		exit(1);
	}
	return ;
}

static void		cont(int i)
{
	i = '\n';
	/*
	 * things to do
	 */
	//prompt(ft_save_env(NULL), 0);
	ft_prompt(shell->env, 0);
	ioctl(0, TIOCSTI, &i);
}

int				ft_signal(void)
{
	signal(SIGCONT, cont);
	signal(SIGTSTP, ctrlz);
	signal(SIGINT, catch_kill);	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	return (1);
}
