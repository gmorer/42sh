/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:29:11 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/09 17:20:05 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"
#include "shell.h"
#include "edit_line.h"
#include "errno.h"

t_shell		*g_shell;

void		job_quit(int sig)
{
	t_job	*temp;
	t_job	*lol;
	int		i;

	i = 0;
	temp = g_shell->first_job;
	while (temp)
	{
		i++;
		if (waitpid(temp->pgid, &i, WNOHANG | WCONTINUED | WUNTRACED) == -1 &&
				errno == 10 && sig)
		{
			ft_putchar('[');
			ft_putnbr(i);
			ft_putstr("]  +  ");
			ft_putnbr(temp->pgid);
			ft_putstr(" done	");
			ft_putendl(temp->command);
			lol = temp;
			temp = temp->next;
			delet_job(lol);
		}
		else
			temp = temp->next;
	}
}

void		sig(int i)
{
	struct winsize	win;

	ft_putchar('\n');
	while (g_shell->cursor->nb_line != 1)
	{
		ft_putchar('\n');
		g_shell->cursor->nb_line--;
	}
	ioctl(0, TIOCGWINSZ, &win);
	(void)i;
	ft_bzero(g_shell->cursor->line, ft_strlen(g_shell->cursor->line));
	ft_bzero(g_shell->av, ft_strlen(g_shell->av));
	g_shell->quote[0] = 0;
	g_shell->quote[1] = 0;
	g_shell->cursor->l_marge = 3;
	g_shell->cursor->cur_line = 1;
	g_shell->cursor->nb_line = 1;
	g_shell->cursor->r_marge = 3;
	g_shell->cursor->cur_col = 3;
	g_shell->cursor->max_col = win.ws_col;
	g_shell->cursor->beg_select = -1;
	g_shell->cursor->end_select = -1;
	g_shell->cursor->str_cpy = NULL;
	prompt();
}

t_shell		*init_mainprocess(void)
{
	signal(SIGCHLD, job_quit);
	signal(SIGINT, sig);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	if (!(g_shell = (t_shell*)malloc(sizeof(t_shell))))
		return (NULL);
	g_shell->first_job = NULL;
	while (tcgetpgrp(1) != (g_shell->pgid = getpgrp()))
		kill(-g_shell->pgid, SIGTTIN);
	g_shell->pgid = getpid();
	if (setpgid(g_shell->pgid, g_shell->pgid) < 0)
	{
		ft_putendl_fd("Couldn't init the shell", STDERR_FILENO);
		free(g_shell);
		exit(1);
	}
	if (tcsetpgrp(1, g_shell->pgid) == -1)
		ft_putendl("error");
	g_shell->hist = NULL;
	g_shell->table = NULL;
	if (tcgetattr(1, &(g_shell->dfl_term)) == -1)
		ft_putendl("error");
	return (g_shell);
}
