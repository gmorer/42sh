/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:08:37 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/05 17:36:17 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

static void		catch_kill(int i)
{
	char	**temp;
	int		j;

	j = 130;
	temp = NULL;
	ft_putendl("lol");
	if(i == SIGINT)
	{
		ft_putchar('\n');
		boucle(temp, j, shell->table);
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
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, catch_kill);	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	return (1);
}
