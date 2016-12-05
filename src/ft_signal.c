/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:08:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/01 12:16:29 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

void			catch_kill(int i)
{
	struct termios	o;
	char			c;

	if(i == SIGTSTP)
	{
		tcgetattr(0, &o);
		c = o.c_cc[VSUSP];
		ioctl(0, TIOCSTI, &c);
		signal(SIGTSTP, SIG_DFL);
	}
	else if(i == SIGINT)
	{
		ft_putchar('\n');
		prompt(shell->env, 1);
	}
	else if (i != SIGTSTP)
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
	prompt(shell->env, 0);
	ioctl(0, TIOCSTI, &i);
}

int				ft_signal(void)
{
	signal(SIGCONT, cont);
	signal(SIGTSTP, catch_kill);
	signal(SIGINT, catch_kill);	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	return (1);
}
