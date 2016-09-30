/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:08:37 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/30 10:48:02 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_save_env(char **env)
{
	static char		**save;

	if (env == NULL)
		return (save);
	else
	{
	//	ft_putendl("env saved");
		save = env;
	}
	return (save);
}
/*
static int		ft_terminer(struct termios o)
{
	tputs(tgetstr("ve", NULL), 1, ft_tputchar);
	if (tcsetattr(0, TCSADRAIN, &o) == -1)
		return (0);
	ft_putstr_fd("\033[?1049l", 2);
	return (1);
}
*/
void			catch_kill(int i)
{
	struct termios	o;
	char			c;

	//ft_putnbr(i);
	//ft_putendl("got it");
	//ft_terminer(ft_save_term(o, 0));
	if(i == SIGTSTP)
	{
		tcgetattr(0, &o);
	//	ft_putendl("sigstp");
		c = o.c_cc[VSUSP];
		ioctl(0, TIOCSTI, &c);
		signal(SIGTSTP, SIG_DFL);
	}
	else if(i == SIGINT)
	{
		ft_putchar('\n');
		prompt(ft_save_env(NULL), 1);
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
	prompt(ft_save_env(NULL), 0);
	//ioctl(0, TIOCSTI, &i);
}

int				ft_signal(void)
{
	int		i;

	i = 0;/*
	signal(SIGWINCH, resize_draw);
	signal(SIGTSTP, catch_kill);
	ft_save_term(o, 1);*/
	signal(SIGCONT, cont);
	while (i < 32)
	{
		if (i != SIGCONT && i != SIGWINCH && i != SIGTTIN && i != SIGSEGV && i != SIGCHLD)
			signal(i, catch_kill);
		i++;
	}
	return (1);
}
